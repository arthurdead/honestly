#include "device.hpp"
#include <osal/environment.hpp>
#if CTL_DEBUG_LEVEL > 0
	#include <osal/terminal.hpp>
#endif

namespace gal::vulkan
{
	namespace __devc
	{
		static constexpr const std::initializer_list<const char *> extensions{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};
	}

	bool device::extensions_supported(const vk::raii::PhysicalDevice &phy) noexcept
	{
		const std::vector<vk::ExtensionProperties> supported_extensions{phy.enumerateDeviceExtensionProperties()};

		std::vector<const char *> required_extensions{__devc::extensions};

		bool value{true};

		vk_ext::remove_unsupported(required_extensions, supported_extensions, 
			[&value]([[maybe_unused]] std::string_view) noexcept -> void {
				value = false;
			}
		);

		return value;
	}

	vk::Format device::find_supported_format(const vk::raii::PhysicalDevice &phy, std::initializer_list<vk::Format> wanted, vk::ImageTiling tiling, vk::FormatFeatureFlags features) noexcept
	{
		for(vk::Format it : wanted) {
			const vk::FormatProperties props{phy.getFormatProperties(it)};

			vk::FormatFeatureFlags to_check;

			switch(tiling) {
				case vk::ImageTiling::eOptimal: {
					to_check = props.optimalTilingFeatures;
					break;
				}
				case vk::ImageTiling::eLinear: {
					to_check = props.linearTilingFeatures;
					break;
				}
				default: {
					CTL_DEBUGTRAP;
					break;
				}
			}

			if(to_check & features) {
				return it;
			}
		}

		return *wanted.begin();
	}

	device::device(const vk::raii::PhysicalDevice &phy, const instance &inst, const vk::raii::SurfaceKHR &surf) noexcept
	{
	#if CTL_DEBUG_LEVEL > 0
		using namespace std::literals::string_view_literals;
	#endif

		const std::vector<vk::LayerProperties> supported_layers{phy.enumerateDeviceLayerProperties()};
	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("device supported layers:\n"sv);
		for(const vk::LayerProperties &prop : supported_layers) {
			osal::this_terminal::info("  "sv, static_cast<std::string_view>(prop.layerName), '\n');
		}
	#endif

		const std::vector<vk::ExtensionProperties> supported_extensions{phy.enumerateDeviceExtensionProperties()};
	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("device supported extensions:\n"sv);
		for(const vk::ExtensionProperties &prop : supported_extensions) {
			osal::this_terminal::info("  "sv, static_cast<std::string_view>(prop.extensionName), '\n');
		}
	#endif

		std::vector<const char *> wanted_layers{inst.layers()};
		std::vector<const char *> wanted_extensions{__devc::extensions};

		if(osal::environment::get<bool>("OBS_VKCAPTURE"sv)) {
			wanted_extensions.emplace_back(VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME);
			wanted_extensions.emplace_back(VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME);
			wanted_extensions.emplace_back(VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME);
		}

		if(osal::environment::get<bool>("ENABLE_VKBASALT"sv)) {
			wanted_extensions.emplace_back(VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_EXTENSION_NAME);
			wanted_extensions.emplace_back(VK_KHR_IMAGE_FORMAT_LIST_EXTENSION_NAME);
		}

		vk_ext::remove_unsupported(wanted_layers, supported_layers
		#if CTL_DEBUG_LEVEL > 0
			, [](std::string_view name) noexcept -> void {
				osal::this_terminal::warning("unsupported device layer: "sv, name, '\n');
			}
		#endif
		);

		vk_ext::remove_unsupported(wanted_extensions, supported_extensions
		#if CTL_DEBUG_LEVEL > 0
			, [](std::string_view name) noexcept -> void {
				osal::this_terminal::warning("unsupported device extension: "sv, name, '\n');
			}
		#endif
		);

		queues.populate_idxs(phy, surf);

		std::vector<vk::DeviceQueueCreateInfo> queues_info;
		queues.populate_info(queues_info);

		handle.emplace(
			phy,
			vk::DeviceCreateInfo{
				vk::DeviceCreateFlags{},
				queues_info,
				wanted_layers,
				wanted_extensions,
			}
		);

		queues.populate_handles(*handle);
	}

	void device::queue_list::populate_info(std::vector<vk::DeviceQueueCreateInfo> &vec) noexcept
	{
		static constexpr const float priority{1.0f};

		for(queue &it : data) {
			vec.emplace_back(
				vk::DeviceQueueCreateInfo{
					vk::DeviceQueueCreateFlags{},
					static_cast<std::uint32_t>(it.idx()), 1,
					&priority
				}
			);
		}
	}

	void device::queue_list::populate_handles(const vk::raii::Device &dev) noexcept
	{
		for(queue &it : data) {
			it.handle.emplace(dev.getQueue(static_cast<std::uint32_t>(it.idx()), 0));
		}
	}

	device::queue &device::queue_list::allocate(std::size_t idx) noexcept
	{
		const std::uint32_t &idx_ref{idxs_.emplace_back(static_cast<std::uint32_t>(idx))};
		return data.emplace_back(idx_ref);
	}

	bool device::has_complete_queue_family(const vk::raii::PhysicalDevice &phy, const vk::raii::SurfaceKHR &surf) noexcept
	{
		queue_list tmp;
		return tmp.populate_idxs(phy, surf);
	}

	bool device::queue_list::populate_idxs(const vk::raii::PhysicalDevice &phy, const vk::raii::SurfaceKHR &surf) noexcept
	{
		const std::vector<vk::QueueFamilyProperties> queue_props{phy.getQueueFamilyProperties()};

		unsigned char allocated{0};
		for(std::size_t i{0}; i < queue_props.size(); ++i) {
			allocated = 0;

			if(!graphics_) {
				const vk::QueueFamilyProperties &props{queue_props[i]};
				if(props.queueFlags & vk::QueueFlagBits::eGraphics) {
					graphics_ = &allocate(i);
					allocated = 1;
				}
			}

			if(!present_) {
				if(phy.getSurfaceSupportKHR(static_cast<std::uint32_t>(i), *surf)) {
					if(allocated == 1) {
						present_ = graphics_;
						allocated = 2;
					} else {
						present_ = &allocate(i);
						allocated = 1;
					}
				}
			}

			if(allocated == 2 || complete()) {
				return true;
			}
		}

		return false;
	}

	vk::raii::ImageView device::create_image_view(vk::Image img, vk::Format fmt, vk::ImageAspectFlags aspect, std::size_t miplevel) noexcept
	{
		return vk::raii::ImageView{
			*handle,
			vk::ImageViewCreateInfo{
				vk::ImageViewCreateFlags{},
				img,
				vk::ImageViewType::e2D,
				fmt,
				vk::ComponentMapping{},
				vk::ImageSubresourceRange{
					aspect,
					0,
					static_cast<std::uint32_t>(miplevel),
					0,
					1
				}
			}
		};
	}

	vk::raii::RenderPass device::create_render_pass(vk::Format clrfmt, vk::Format depthfmt, vk::SampleCountFlagBits samples) noexcept
	{
		const std::initializer_list<const vk::AttachmentDescription> attachments{
			vk::AttachmentDescription{
				vk::AttachmentDescriptionFlags{},
				clrfmt,
				samples,
				vk::AttachmentLoadOp::eClear,
				vk::AttachmentStoreOp::eStore,
				vk::AttachmentLoadOp::eDontCare,
				vk::AttachmentStoreOp::eDontCare,
				vk::ImageLayout::eUndefined,
				vk::ImageLayout::eColorAttachmentOptimal,
			},
			vk::AttachmentDescription{
				vk::AttachmentDescriptionFlags{},
				depthfmt,
				samples,
				vk::AttachmentLoadOp::eClear,
				vk::AttachmentStoreOp::eDontCare,
				vk::AttachmentLoadOp::eDontCare,
				vk::AttachmentStoreOp::eDontCare,
				vk::ImageLayout::eUndefined,
				vk::ImageLayout::eDepthStencilAttachmentOptimal,
			},
			vk::AttachmentDescription{
				vk::AttachmentDescriptionFlags{},
				clrfmt,
				vk::SampleCountFlagBits::e1,
				vk::AttachmentLoadOp::eDontCare,
				vk::AttachmentStoreOp::eStore,
				vk::AttachmentLoadOp::eDontCare,
				vk::AttachmentStoreOp::eDontCare,
				vk::ImageLayout::eUndefined,
				vk::ImageLayout::ePresentSrcKHR,
			},
		};

		static constexpr const std::initializer_list<const vk::AttachmentReference> attachment_refs{
			vk::AttachmentReference{0, vk::ImageLayout::eColorAttachmentOptimal},
			vk::AttachmentReference{1, vk::ImageLayout::eDepthStencilAttachmentOptimal},
			vk::AttachmentReference{2, vk::ImageLayout::eColorAttachmentOptimal},
		};

		static const std::initializer_list<const vk::SubpassDescription> subpasses{
			vk::SubpassDescription{
				vk::SubpassDescriptionFlags{},
				vk::PipelineBindPoint::eGraphics,
				nullptr,
				std::data(attachment_refs)[0],
				std::data(attachment_refs)[2],
				&std::data(attachment_refs)[1],
				nullptr
			}
		};

		static constexpr const std::initializer_list<const vk::SubpassDependency> dependencies{
			vk::SubpassDependency{
				VK_SUBPASS_EXTERNAL,
				0,
				vk::PipelineStageFlagBits::eColorAttachmentOutput|vk::PipelineStageFlagBits::eEarlyFragmentTests,
				vk::PipelineStageFlagBits::eColorAttachmentOutput|vk::PipelineStageFlagBits::eEarlyFragmentTests,
				vk::AccessFlags{},
				vk::AccessFlagBits::eColorAttachmentWrite|vk::AccessFlagBits::eDepthStencilAttachmentWrite,
				vk::DependencyFlags{},
			}
		};

		return vk::raii::RenderPass{
			*handle,
			vk::RenderPassCreateInfo{
				vk::RenderPassCreateFlags{},
				attachments,
				subpasses,
				dependencies
			}
		};
	}
}
