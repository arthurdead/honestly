#pragma once

#include <ctl/version>
#include "vulkan.hpp"
#include "device.hpp"

namespace gal::vulkan
{
	class CTL_LOCAL_CLASS swapchain final
	{
	public:
		swapchain(swapchain &&) noexcept = default;
		swapchain &operator=(swapchain &&) noexcept = default;

		swapchain(const vk::raii::PhysicalDevice &phy, device &dev, const vk::raii::SurfaceKHR &surf, std::size_t w, std::size_t h) noexcept;

		inline vk::Format format() const noexcept
		{ return fmt; }

		inline void reset() noexcept
		{ image_views.clear(); handle.reset(); }

		inline const vk::raii::SwapchainKHR &operator*() const noexcept
		{ return *handle; }
		inline const vk::raii::SwapchainKHR *operator->() const noexcept
		{ return handle.get(); }

		static bool is_supported(const vk::raii::PhysicalDevice &phy, const vk::raii::SurfaceKHR &surf) noexcept;

	private:
		swapchain() = delete;
		swapchain(const swapchain &) = delete;
		swapchain &operator=(const swapchain &) = delete;

		vk::Format fmt;

		std::vector<vk::raii::ImageView> image_views;
		std::vector<vk::Image> images;

		ctl::unique_ptr<vk::raii::SwapchainKHR> handle;
	};
}
