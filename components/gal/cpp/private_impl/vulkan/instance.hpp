#pragma once

#include <ctl/version>
#include "vulkan.hpp"
#include "../window.hpp"

namespace gal::vulkan
{
	class CTL_LOCAL_CLASS instance final
	{
	public:
		instance(instance &&) noexcept = default;
		instance &operator=(instance &&) noexcept = default;

		instance(const vk::raii::Context &ctx, vk::ApplicationInfo &&info) noexcept;
		~instance() noexcept;

		inline const std::vector<const char *> layers() const noexcept
		{ return layers_; }

		inline const vk::raii::Instance &operator*() const noexcept
		{ return *handle; }
		inline const vk::raii::Instance *operator->() const noexcept
		{ return handle.get(); }

		vk::raii::SurfaceKHR create_surface(__win::impl &win) noexcept;

		static bool extensions_supported(const vk::raii::Context &ctx) noexcept;

	private:
		instance() = delete;
		instance(const instance &) = delete;
		instance &operator=(const instance &) = delete;

		std::vector<const char *> layers_;
		ctl::unique_ptr<vk::raii::Instance> handle;
	#if CTL_DEBUG_LEVEL > 0
		ctl::unique_ptr<vk::raii::DebugUtilsMessengerEXT> dbgutils;
		//ctl::unique_ptr<vk::raii::DebugReportCallbackEXT> dbgreport;
	#endif
	};
}
