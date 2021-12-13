#include "api.hpp"
#include "vulkan.hpp"
#include "../gal.hpp"
#include "renderer.hpp"
#if CTL_DEBUG_LEVEL > 0
	#include <osal/environment.hpp>
	#include <osal/process.hpp>
	#include <osal/terminal.hpp>
#endif
#include "instance.hpp"
#include "device.hpp"

namespace gal::vulkan
{
	namespace __private
	{
		CTL_GLOBAL_CTOR_BEGIN
		static vk::ApplicationInfo appinfo{
			nullptr, 0,
			nullptr, 0,
			GAL_VK_HEADER_VERSION_COMPLETE
		};
		static ctl::unique_ptr<vk::raii::Context> ctx;
		static ctl::unique_ptr<instance> inst;
		static const vk::raii::PhysicalDevice *dev;
		using dev_map_t = std::unordered_map<pci, vk::raii::PhysicalDevice>;
		static dev_map_t dev_map;
		CTL_GLOBAL_CTOR_END
	}

	GAL_VULKAN_SHARED_API void GAL_VULKAN_SHARED_API_CALL set_software_info(const software_list &info) noexcept
	{
		__private::appinfo.setPApplicationName(info.app.name.c_str());
		__private::appinfo.setApplicationVersion(static_cast<std::uint32_t>(info.app.version.raw()));

		__private::appinfo.setPEngineName(info.engine.name.c_str());
		__private::appinfo.setEngineVersion(static_cast<std::uint32_t>(info.engine.version.raw()));
	}

	#define __GAL_VK_PROP_CHAIN_TYPES_BASE \
		vk::PhysicalDeviceProperties2, \
		vk::PhysicalDevicePCIBusInfoPropertiesEXT

#if CTL_DEBUG_LEVEL > 0
	#define __GAL_VK_PROP_CHAIN_TYPES \
		__GAL_VK_PROP_CHAIN_TYPES_BASE, \
		vk::PhysicalDeviceDriverProperties
#else
	#define __GAL_VK_PROP_CHAIN_TYPES \
		__GAL_VK_PROP_CHAIN_TYPES_BASE
#endif

	GAL_VULKAN_SHARED_API bool GAL_VULKAN_SHARED_API_CALL gpu_supported(__win::impl &win, const pci &gpu) noexcept
	{
		__private::dev_map_t::const_iterator it{__private::dev_map.find(gpu)};
		if(it == __private::dev_map.end()) {
			return false;
		}

		const vk::raii::PhysicalDevice &phy{it->second};

		if(!device::extensions_supported(phy)) {
			return false;
		}

		vk::raii::SurfaceKHR surf{(*__private::inst).create_surface(win)};

		if(!device::has_complete_queue_family(phy, surf)) {
			return false;
		}

		if(!swapchain::is_supported(phy, surf)) {
			return false;
		}

		return true;
	}

	GAL_VULKAN_SHARED_API bool GAL_VULKAN_SHARED_API_CALL initialize() noexcept
	{
	#if CTL_DEBUG_LEVEL > 0
		using namespace std::literals::string_view_literals;

		/*
		osal::environment::remove("MESA_VK_DEVICE_SELECT"sv);
		osal::environment::remove("__VK_LAYER_NV_optimus"sv);
		osal::environment::remove("__NV_PRIME_RENDER_OFFLOAD");
		osal::environment::set("DISABLE_LAYER_NV_OPTIMUS_1"sv, 1);
		osal::environment::set("NODEVICE_SELECT"sv, 1);
		osal::environment::remove("MESA_VK_VERSION_OVERRIDE"sv);
		*/

		osal::environment::remove("mesa_no_error"sv);
		osal::environment::remove("MESA_NO_ERROR"sv);
		osal::environment::set("MESA_DEBUG"sv, "incomplete_tex;incomplete_fbo;context"sv);
		osal::environment::set("LIBGL_DEBUG"sv, "verbose"sv);
		osal::environment::set("VK_LOADER_DEBUG"sv, "error,warn"sv);
		osal::environment::set("VK_LOADER_DISABLE_INST_EXT_FILTER"sv, 1);
		osal::environment::remove("VK_LAYER_DISABLES"sv);
		
		{
			std::string tmp;
			for(std::string_view it : {
				"VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT"sv,
				"VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT"sv,
				"VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT"sv,
				"VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT"sv,
				"VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT"sv,
				"VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION"sv,
				"VALIDATION_CHECK_ENABLE_VENDOR_SPECIFIC_AMD"sv,
			}) {
				tmp += it;
				tmp += ':';
			}
			tmp.pop_back();

			osal::environment::set("VK_LAYER_ENABLES"sv, tmp);
		}

		std::filesystem::path log{osal::this_process::path()};
		log.replace_extension(".vk_api.log"sv);

		osal::this_terminal::info("api dump log = "sv, log, '\n');

		osal::environment::set("VK_APIDUMP_LOG_FILENAME"sv, log);
		osal::environment::set("VK_APIDUMP_DETAILED"sv, "true"sv);
		osal::environment::set("VK_APIDUMP_NO_ADDR"sv, "false"sv);
		osal::environment::set("VK_APIDUMP_FLUSH"sv, "true"sv);
		osal::environment::set("VK_APIDUMP_OUTPUT_FORMAT"sv, "text"sv);
		osal::environment::set("VK_APIDUMP_OUTPUT_RANGE"sv, "0-0"sv);
		osal::environment::set("VK_APIDUMP_TIMESTAMP"sv, "false"sv);
	#else
		osal::environment::set("mesa_no_error"sv, "true"sv);
		osal::environment::set("MESA_NO_ERROR"sv, 1);
		osal::environment::set("MESA_DEBUG"sv, "silent"sv);
		osal::environment::remove("MESA_VK_VERSION_OVERRIDE"sv);
		osal::environment::remove("LIBGL_DEBUG"sv);
	#endif

		if(!__private::appinfo.pEngineName) {
			__private::appinfo.setPEngineName("gal_unnamed_engine");
			__private::appinfo.setEngineVersion(0);
		}

		if(!__private::appinfo.pApplicationName) {
			__private::appinfo.setPApplicationName("gal_unnamed_app");
			__private::appinfo.setApplicationVersion(0);
		}

	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("app info:\n"sv);
		osal::this_terminal::info("  api version = "sv,
			GAL_VK_API_VERSION_VARIANT(__private::appinfo.apiVersion), '-',
			GAL_VK_API_VERSION_MAJOR(__private::appinfo.apiVersion), '.',
			GAL_VK_API_VERSION_MINOR(__private::appinfo.apiVersion), '.',
			GAL_VK_API_VERSION_PATCH(__private::appinfo.apiVersion), " ("sv, __private::appinfo.apiVersion, ")\n"sv);
		osal::this_terminal::info("  engine name = "sv, __private::appinfo.pEngineName ? __private::appinfo.pEngineName : "nullptr"sv, '\n');
		osal::this_terminal::info("  engine version = "sv, __private::appinfo.engineVersion, '\n');
		osal::this_terminal::info("  app name = "sv, __private::appinfo.pApplicationName ? __private::appinfo.pApplicationName : "nullptr"sv, '\n');
		osal::this_terminal::info("  app version = "sv, __private::appinfo.applicationVersion, '\n');
	#endif

		__private::ctx.emplace();

	#if CTL_DEBUG_LEVEL > 0
		const std::uint32_t apiver{__private::ctx->enumerateInstanceVersion()};

		osal::this_terminal::info("instance api version = "sv,
			GAL_VK_API_VERSION_VARIANT(apiver), '-',
			GAL_VK_API_VERSION_MAJOR(apiver), '.',
			GAL_VK_API_VERSION_MINOR(apiver), '.',
			GAL_VK_API_VERSION_PATCH(apiver), " ("sv, apiver, ")\n"sv);
	#endif

		if(!instance::extensions_supported(*__private::ctx)) {
			return false;
		}

		__private::inst.emplace(*__private::ctx, std::move(__private::appinfo));

		vk::raii::PhysicalDevices phydevs{*(*__private::inst)};

	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("vulkan devices:\n"sv);
	#endif

		for(vk::raii::PhysicalDevice &physdev : phydevs) {
			vk::StructureChain<__GAL_VK_PROP_CHAIN_TYPES> propchain{physdev.getProperties2<__GAL_VK_PROP_CHAIN_TYPES>()};
			
			const vk::PhysicalDevicePCIBusInfoPropertiesEXT &pciprops{propchain.get<vk::PhysicalDevicePCIBusInfoPropertiesEXT>()};

		#if CTL_DEBUG_LEVEL > 0
			const vk::PhysicalDeviceProperties &props{propchain.get<vk::PhysicalDeviceProperties2>().properties};
			const vk::PhysicalDeviceDriverProperties &drvprops{propchain.get<vk::PhysicalDeviceDriverProperties>()};

			osal::this_terminal::info("  pci = "sv, pciprops.pciDomain, ':', pciprops.pciBus, ':', pciprops.pciDevice, ':', pciprops.pciFunction, '\n');
			osal::this_terminal::info("    vendorID = "sv, props.vendorID, '\n');
			osal::this_terminal::info("    deviceID = "sv, props.deviceID, '\n');
			osal::this_terminal::info("    deviceName = "sv, static_cast<std::string_view>(props.deviceName), '\n');
			osal::this_terminal::info("    deviceType = "sv, vk::to_string(props.deviceType), '\n');
			osal::this_terminal::info("    apiVersion = "sv,
				GAL_VK_API_VERSION_VARIANT(props.apiVersion), '-',
				GAL_VK_API_VERSION_MAJOR(props.apiVersion), '.',
				GAL_VK_API_VERSION_MINOR(props.apiVersion), '.',
				GAL_VK_API_VERSION_PATCH(props.apiVersion), '\n');
			osal::this_terminal::info("    driverID = "sv, vk::to_string(drvprops.driverID), '\n');
			osal::this_terminal::info("    driverName = "sv, static_cast<std::string_view>(drvprops.driverName), '\n');
			osal::this_terminal::info("    driverInfo = "sv, static_cast<std::string_view>(drvprops.driverInfo), '\n');
			if(drvprops.driverID == vk::DriverId::eNvidiaProprietary) {
				osal::this_terminal::info("    driverVersion = "sv,
					GAL_NV_VERSION_MAJOR(props.driverVersion), '.',
					GAL_NV_VERSION_MINOR(props.driverVersion), '.',
					GAL_NV_VERSION_SUBMINOR(props.driverVersion), '.',
					GAL_NV_VERSION_PATCH(props.driverVersion), '\n');
			} else {
				osal::this_terminal::info("    driverVersion = "sv,
					GAL_VK_VERSION_MAJOR(props.driverVersion), '.',
					GAL_VK_VERSION_MINOR(props.driverVersion), '.',
					GAL_VK_VERSION_PATCH(props.driverVersion), '\n');
			}
			osal::this_terminal::info("    conformanceVersion = "sv,
				static_cast<std::size_t>(drvprops.conformanceVersion.major), '.',
				static_cast<std::size_t>(drvprops.conformanceVersion.minor), '-',
				static_cast<std::size_t>(drvprops.conformanceVersion.subminor), '.',
				static_cast<std::size_t>(drvprops.conformanceVersion.patch), '\n');
		#endif

			pci tmp;
			tmp.domain = pciprops.pciDomain;
			tmp.bus = pciprops.pciBus;
			tmp.device = pciprops.pciDevice;
			tmp.function = pciprops.pciFunction;
			__private::dev_map.emplace(std::move(tmp), std::move(physdev));
		}

		return true;
	}

	GAL_VULKAN_SHARED_API bool GAL_VULKAN_SHARED_API_CALL select_gpu(const pci &gpu) noexcept
	{
		__private::dev_map_t::const_iterator it{__private::dev_map.find(gpu)};
		if(it == __private::dev_map.end()) {
			return false;
		}

		__private::dev = &it->second;

		return true;
	}

	GAL_VULKAN_SHARED_API void GAL_VULKAN_SHARED_API_CALL shutdown() noexcept
	{
		__private::dev_map.clear();
		__private::inst.reset();
	}

	GAL_VULKAN_SHARED_API __rndr::impl * GAL_VULKAN_SHARED_API_CALL create_renderer(__win::impl &win) noexcept
	{
		return new renderer{win, *__private::dev, *__private::inst};
	}
}
