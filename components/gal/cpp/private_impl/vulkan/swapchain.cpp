#include "swapchain.hpp"
#include <osal/terminal.hpp>

namespace gal::vulkan
{
	bool swapchain::is_supported(const vk::raii::PhysicalDevice &phy, const vk::raii::SurfaceKHR &surf) noexcept
	{
		const std::vector<vk::SurfaceFormatKHR> fmts{phy.getSurfaceFormatsKHR(*surf)};
		if(fmts.empty()) {
			return false;
		}

		const std::vector<vk::PresentModeKHR> modes{phy.getSurfacePresentModesKHR(*surf)};
		if(modes.empty()) {
			return false;
		}

		return true;
	}

	swapchain::swapchain(const vk::raii::PhysicalDevice &phy, device &dev, const vk::raii::SurfaceKHR &surf, std::size_t w, std::size_t h) noexcept
	{
	#if CTL_DEBUG_LEVEL > 0
		using namespace std::literals::string_view_literals;
	#endif

		const std::vector<vk::SurfaceFormatKHR> fmts{phy.getSurfaceFormatsKHR(*surf)};
	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("supported formats:\n"sv);
		for(const vk::SurfaceFormatKHR &it : fmts) {
			osal::this_terminal::info("  "sv, vk::to_string(it.format), " - "sv, vk::to_string(it.colorSpace), '\n');
		}
	#endif

		vk::ColorSpaceKHR clrspace;

		if(std::find_if(fmts.cbegin(), fmts.cend(), 
			[](const vk::SurfaceFormatKHR &it) noexcept -> bool {
				return (it.format == vk::Format::eB8G8R8A8Srgb &&
						it.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear);
			}
		) != fmts.end()) {
			fmt = vk::Format::eB8G8R8A8Srgb;
			clrspace = vk::ColorSpaceKHR::eSrgbNonlinear;
		} else if(!fmts.empty()) {
			fmt = fmts[0].format;
			clrspace = fmts[0].colorSpace;
		} else {
			fmt = vk::Format::eB8G8R8A8Srgb;
			clrspace = vk::ColorSpaceKHR::eSrgbNonlinear;
		}

		const vk::SurfaceCapabilitiesKHR surfcap{phy.getSurfaceCapabilitiesKHR(*surf)};

		std::uint32_t imgcount{surfcap.minImageCount+1};
		if(surfcap.maxImageCount > 0 && imgcount > surfcap.maxImageCount) {
			imgcount = surfcap.maxImageCount;
		}

		vk::Extent2D extent;
		if(surfcap.currentExtent.width != std::numeric_limits<std::uint32_t>::max()) {
			extent = surfcap.currentExtent;
		} else {
			extent.width = std::clamp(static_cast<std::uint32_t>(w), surfcap.minImageExtent.width, surfcap.maxImageExtent.width);
			extent.height = std::clamp(static_cast<std::uint32_t>(h), surfcap.minImageExtent.height, surfcap.maxImageExtent.height);
		}

		const std::vector<vk::PresentModeKHR> modes{phy.getSurfacePresentModesKHR(*surf)};
	#if CTL_DEBUG_LEVEL > 0
		osal::this_terminal::info("supported modes:\n"sv);
		for(vk::PresentModeKHR it : modes) {
			osal::this_terminal::info("  "sv, vk::to_string(it), '\n');
		}
	#endif

		const bool mailbox{std::find(modes.cbegin(), modes.cend(), vk::PresentModeKHR::eMailbox) != modes.cend()};

		handle.emplace(
			*dev,
			vk::SwapchainCreateInfoKHR{
				vk::SwapchainCreateFlagsKHR{},
				*surf,
				imgcount,
				fmt,
				clrspace,
				extent,
				1,
				vk::ImageUsageFlagBits::eColorAttachment,
				dev.exclusive_queue() ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent,
				dev.queue_indexes(),
				surfcap.currentTransform,
				vk::CompositeAlphaFlagBitsKHR::eOpaque,
				mailbox ? vk::PresentModeKHR::eMailbox : vk::PresentModeKHR::eFifo,
				true,
				nullptr
			}
		);

		{
			const std::vector<VkImage> tmp{handle->getImages()};
			for(VkImage tmpimg : tmp) {
				images.emplace_back(tmpimg);
			}
		}

		for(vk::Image img : images) {
			image_views.emplace_back(
				dev.create_image_view(
					img,
					fmt,
					vk::ImageAspectFlagBits::eColor,
					1
				)
			);
		}
	}
}
