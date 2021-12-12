#pragma once

#include <ctl/version>
#include "../renderer.hpp"
#include "vulkan.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "swapchain.hpp"

namespace gal::vulkan
{
	class CTL_LOCAL_CLASS renderer final : public __rndr::impl
	{
	public:
		renderer(renderer &&) noexcept = default;
		renderer &operator=(renderer &&) noexcept = default;

		renderer(__win::impl &win, const vk::raii::PhysicalDevice &phy, instance &inst) noexcept;
		~renderer() noexcept override;

	private:
		renderer() = delete;
		renderer(const renderer &) = delete;
		renderer &operator=(const renderer &) = delete;

		ctl::unique_ptr<vk::raii::SurfaceKHR> surf;
		device dev;
		swapchain swpchain;
		ctl::unique_ptr<vk::raii::RenderPass> rndrpass;
	};
}
