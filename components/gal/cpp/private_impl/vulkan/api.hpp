#pragma once

#include <ctl/version>
#include <ctl/string_view>

#ifdef __GAL_VULKAN_IS_STATIC
	#define GAL_VULKAN_SHARED_API
	#define GAL_VULKAN_SHARED_API_CALL
#elif defined __GAL_VULKAN_IS_SHARED
	#ifdef __COMPILING_GAL_VULKAN
		#define GAL_VULKAN_SHARED_API CTL_SHARED_EXPORT
	#else
		#define GAL_VULKAN_SHARED_API CTL_SHARED_IMPORT
	#endif
	#define GAL_VULKAN_SHARED_API_CALL CTL_SHARED_CALL
#else
	#error
#endif

#include "../window.hpp"
#include "../renderer.hpp"

namespace gal::vulkan
{
	extern GAL_VULKAN_SHARED_API __rndr::impl * GAL_VULKAN_SHARED_API_CALL create_renderer(__win::impl &win) noexcept;

	extern GAL_VULKAN_SHARED_API void GAL_VULKAN_SHARED_API_CALL set_software_info(const software_list &info) noexcept;

	extern GAL_VULKAN_SHARED_API bool GAL_VULKAN_SHARED_API_CALL gpu_supported(__win::impl &win, const pci &gpu) noexcept;

	extern GAL_VULKAN_SHARED_API bool GAL_VULKAN_SHARED_API_CALL select_gpu(const pci &gpu) noexcept;

	extern GAL_VULKAN_SHARED_API bool GAL_VULKAN_SHARED_API_CALL initialize() noexcept;
	extern GAL_VULKAN_SHARED_API void GAL_VULKAN_SHARED_API_CALL shutdown() noexcept;
}
