#include "instance.hpp"
#include <osal/environment.hpp>
#if CTL_DEBUG_LEVEL > 0
	#include <osal/terminal.hpp>
#endif
#include "../gal.hpp"

namespace gal::vulkan
{
	namespace __inst
	{
		static constexpr const std::initializer_list<const char *> extensions{
			VK_KHR_SURFACE_EXTENSION_NAME,
		#if CTL_DEBUG_LEVEL > 0
			//VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		#endif
		};

		static constexpr const std::initializer_list<const char *> layers{
			"VK_LAYER_MESA_device_select",
			"VK_LAYER_NV_optimus",
		#if CTL_DEBUG_LEVEL > 0
			"VK_LAYER_KHRONOS_validation",
			//"VK_LAYER_LUNARG_api_dump",
			"VK_LAYER_LUNARG_monitor",
			"VK_LAYER_MESA_overlay",
		#endif
		};

	#if CTL_DEBUG_LEVEL > 0
		/*static std::uint32_t CTL_SHARED_CALL reportcallback(vk::DebugReportFlagsEXT flags, vk::DebugReportObjectTypeEXT objectType, std::uint64_t object, std::size_t location, std::int32_t messageCode, const char *pLayerPrefix, const char *pMessage, [[maybe_unused]] void *pUserData)
		{
			return 0;
		}*/

		static std::uint32_t CTL_SHARED_CALL msgcallback(vk::DebugUtilsMessageSeverityFlagsEXT messageSeverity, vk::DebugUtilsMessageTypeFlagsEXT messageTypes, const vk::DebugUtilsMessengerCallbackDataEXT *pCallbackData, [[maybe_unused]] void *pUserData)
		{
			using namespace std::literals::string_view_literals;

			if(messageTypes == vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral &&
				(messageSeverity == vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose ||
				messageSeverity == vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) &&
				pCallbackData->messageIdNumber == 0) {
				return 0;
			}

			std::string message{pCallbackData->pMessage};

			std::string_view prefix;

			if(messageTypes == vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation) {
				if(messageSeverity ==  vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
					prefix = "Validation Error: "sv;
				} else if(messageSeverity ==  vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
					prefix = "Validation Warning: "sv;
				} else if(messageSeverity ==  vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) {
					prefix = "Validation Information: "sv;
				}
			} else if(messageTypes == (vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation|vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral)) {
				if(messageSeverity ==  vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose) {
					prefix = "DEBUG: "sv;
				}
			} else if(messageTypes == vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance) {
				if(messageSeverity ==  vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
					prefix = "Validation Performance Warning: "sv;
				}
			}

			std::string_view name{pCallbackData->pMessageIdName ? pCallbackData->pMessageIdName : ""sv};
			std::string speclink;
			std::string specmsg;

			if(!prefix.empty()) {
				message.erase(message.begin(), message.begin()+static_cast<std::string::difference_type>(prefix.length()));

				if(!name.empty() && message[0] == '[') {
					message.erase(message.begin(), message.begin()+static_cast<std::string::difference_type>(name.length())+5);
				}

				std::size_t idx{message.find('|')};
				if(idx != std::string::npos) {
					idx = message.find('|', idx+1);
					if(idx != std::string::npos) {
						message.erase(message.begin(), message.begin()+static_cast<std::string::difference_type>(idx+2));

						std::string_view specprefix{" The Vulkan spec states: "sv};
						idx = message.find(specprefix);
						if(idx != std::string::npos) {
							specmsg = message.substr(idx+specprefix.length());
							message.erase(message.begin()+static_cast<std::string::difference_type>(idx), message.end());
							specprefix = " (http"sv;
							idx = specmsg.find(specprefix);
							if(idx != std::string::npos) {
								speclink = specmsg.substr(idx+2);
								specmsg.erase(specmsg.begin()+static_cast<std::string::difference_type>(idx), specmsg.end());
								speclink.pop_back();
							}
						}
					}
				}
			}

			//#define __GAL_VK_USE_SPECMSG

			if(!name.empty()) {
				osal::this_terminal::print(name);
				if(!speclink.empty()) {
					osal::this_terminal::print(" ("sv,speclink,')');
				}
				osal::this_terminal::print(":\n  "sv);
			#ifdef __GAL_VK_USE_SPECMSG
				if(!specmsg.empty()) {
					osal::this_terminal::print(specmsg);
				} else
			#endif
				{
					osal::this_terminal::print(message);
				}
				osal::this_terminal::print('\n');
			} else {
				osal::this_terminal::print(message,'\n');
			}

			return 0;
		}
	#endif
	}

	instance::~instance() noexcept
	{
		dbgutils.reset();
		handle.reset();
	}

	bool instance::extensions_supported(const vk::raii::Context &ctx) noexcept
	{
		const std::vector<vk::ExtensionProperties> supported_extensions{ctx.enumerateInstanceExtensionProperties()};

		std::vector<const char *> required_extensions{__inst::extensions};

		switch(gal::__private::get_win_backend()) {
			case window_backend::xcb: {
				required_extensions.emplace_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
				break;
			}
			default: {
				CTL_DEBUGTRAP;
				return false;
			}
		}

		bool value{true};

		vk_ext::remove_unsupported(required_extensions, supported_extensions, 
			[&value]([[maybe_unused]] std::string_view) noexcept -> void {
				value = false;
			}
		);

		return value;
	}

	instance::instance(const vk::raii::Context &ctx, vk::ApplicationInfo &&info) noexcept
	{
	#if CTL_DEBUG_LEVEL > 0
		using namespace std::literals::string_view_literals;
	#endif

		const std::vector<vk::LayerProperties> supported_layers{ctx.enumerateInstanceLayerProperties()};
	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("instance supported layers:\n"sv);
		for(const vk::LayerProperties &prop : supported_layers) {
			osal::this_terminal::info("  "sv, static_cast<std::string_view>(prop.layerName), '\n');
		}
	#endif

		const std::vector<vk::ExtensionProperties> supported_extensions{ctx.enumerateInstanceExtensionProperties()};
	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("instance supported extensions:\n"sv);
		for(const vk::ExtensionProperties &prop : supported_extensions) {
			osal::this_terminal::info("  "sv, static_cast<std::string_view>(prop.extensionName), '\n');
		}
	#endif

		layers_ = __inst::layers;
		std::vector<const char *> wanted_extensions{__inst::extensions};

		switch(gal::__private::get_win_backend()) {
			case window_backend::xcb: {
				wanted_extensions.emplace_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
				break;
			}
			default: {
				CTL_DEBUGTRAP;
				return;
			}
		}

		if(osal::environment::get<bool>("ENABLE_VK_LAYER_VALVE_steam_overlay_1"sv)) {
		#if CTL_TARGET_ARCHITECTURE & CTL_ARCHITECTURE_FLAG_64BITS
			layers_.emplace_back("VK_LAYER_VALVE_steam_overlay_64");
		#elif CTL_TARGET_ARCHITECTURE & CTL_ARCHITECTURE_FLAG_32BITS
			layers_.emplace_back("VK_LAYER_VALVE_steam_overlay_32");
		#else
			#error
		#endif
		}

		if(osal::environment::get<bool>("OBS_VKCAPTURE"sv)) {
		#if CTL_TARGET_ARCHITECTURE & CTL_ARCHITECTURE_FLAG_64BITS
			layers_.emplace_back("VK_LAYER_OBS_vkcapture_64");
		#elif CTL_TARGET_ARCHITECTURE & CTL_ARCHITECTURE_FLAG_32BITS
			layers_.emplace_back("VK_LAYER_OBS_vkcapture_32");
		#else
			#error
		#endif
		}

		if(osal::environment::get<bool>("ENABLE_VKBASALT"sv)) {
			layers_.emplace_back("VK_LAYER_VKBASALT_post_processing");
		}

		if(osal::environment::get<bool>("ENABLE_VK_LAYER_FLIMES"sv)) {
			layers_.emplace_back("VK_LAYER_FLIMES");
		}

		if(osal::environment::get<bool>("ENABLE_VK_LAYER_TORKEL104_libstrangle"sv)) {
			layers_.emplace_back("VK_LAYER_TORKEL104_libstrangle");
		}

		vk_ext::remove_unsupported(layers_, supported_layers
		#if CTL_DEBUG_LEVEL > 0
			, [](std::string_view name) noexcept -> void {
				osal::this_terminal::warning("unsupported instance layer: "sv, name, '\n');
			}
		#endif
		);

		vk_ext::remove_unsupported(wanted_extensions, supported_extensions
		#if CTL_DEBUG_LEVEL > 0
			, [](std::string_view name) noexcept -> void {
				osal::this_terminal::warning("unsupported instance extension: "sv, name, '\n');
			}
		#endif
		);

		handle.emplace(
			ctx,
			vk::InstanceCreateInfo{
				vk::InstanceCreateFlags{},
				&info,
				layers_,
				wanted_extensions
			}
		);

	#if CTL_DEBUG_LEVEL > 0
		CTL_CLANG_WARNING_PUSH
		CTL_CLANG_WARNING_DISABLE("-Wcast-function-type")
		dbgutils.emplace(
			*handle,
			vk::DebugUtilsMessengerCreateInfoEXT{
				vk::DebugUtilsMessengerCreateFlagsEXT{},
				vk::DebugUtilsMessageSeverityFlagsEXT{vk::FlagTraits<vk::DebugUtilsMessageSeverityFlagBitsEXT>::allFlags},
				vk::DebugUtilsMessageTypeFlagsEXT{vk::FlagTraits<vk::DebugUtilsMessageTypeFlagBitsEXT>::allFlags},
				reinterpret_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(__inst::msgcallback),
				nullptr
			}
		);
		/*dbgreport.emplace(
			*handle,
			vk::DebugReportCallbackCreateInfoEXT{
				vk::DebugReportFlagsEXT{vk::FlagTraits<vk::DebugReportFlagBitsEXT>::allFlags},
				reinterpret_cast<PFN_vkDebugReportCallbackEXT>(__inst::reportcallback),
				nullptr
			}
		);*/
		CTL_CLANG_WARNING_POP
	#endif
	}

	vk::raii::SurfaceKHR instance::create_surface(__win::impl &win) noexcept
	{
		switch(gal::__private::get_win_backend()) {
			case window_backend::xcb: {
				return vk::raii::SurfaceKHR{
					*handle,
					vk::XcbSurfaceCreateInfoKHR{
						vk::XcbSurfaceCreateFlagsKHR{},
						reinterpret_cast<xcb_connection_t *>(gal::__private::get_nat_conn(win)),
						*reinterpret_cast<xcb_window_t *>(gal::__private::get_nat_win(win))
					}
				};
			}
			default: {
				CTL_DEBUGTRAP;
				return vk::raii::SurfaceKHR{
					*handle,
					vk::XcbSurfaceCreateInfoKHR{}
				};
			}
		}
	}
}
