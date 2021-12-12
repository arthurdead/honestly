#pragma once

#include <ctl/version>

#define __GAL_VK_USE_RAII
#define __GAL_VK_DYN_LOADER

#define VULKAN_HPP_NAMESPACE vk
#ifdef __GAL_VK_USE_RAII
	#define VULKAN_HPP_RAII_NAMESPACE raii
#endif

#define VK_ENABLE_BETA_EXTENSIONS

#if CTL_TARGET_OS & CTL_OS_FLAG_UNIX
	#define VK_USE_PLATFORM_XLIB_KHR
	#define VK_USE_PLATFORM_XCB_KHR
#else
	#error
#endif

#ifdef __GAL_VK_DYN_LOADER
	#define VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL 1
#else
	#define VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL 0
#endif

#define VULKAN_HPP_DISABLE_IMPLICIT_RESULT_VALUE_CAST

#if VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL == 1
	#define VK_NO_PROTOTYPES
#endif

#ifdef __GAL_VK_USE_RAII
	#define VULKAN_HPP_NO_SMART_HANDLE
#else
	#define VULKAN_HPP_NO_EXCEPTIONS
#endif

#include <vulkan/vulkan.hpp>
#ifdef __GAL_VK_USE_RAII
	#include <vulkan/vulkan_raii.hpp>
#endif

#ifdef VK_ENABLE_BETA_EXTENSIONS
	#define VK_VIDEO_ENCODE_RATE_CONTROL_RESET_BIT_KHR VK_VIDEO_ENCODE_RATE_CONTROL_RESERVED_0_BIT_KHR
#endif

#define GAL_VK_MAKE_API_VERSION(variant, major, minor, patch) \
	((static_cast<uint32_t>(variant) << 29) | \
		(static_cast<uint32_t>(major) << 22) | \
		(static_cast<uint32_t>(minor) << 12) | \
		static_cast<uint32_t>(patch))

#define GAL_VK_MAKE_VERSION(major, minor, patch) \
	((static_cast<uint32_t>(major) << 22) | \
		(static_cast<uint32_t>(minor) << 12) | \
		static_cast<uint32_t>(patch))

#define GAL_VK_API_VERSION_VARIANT(version) (static_cast<uint32_t>(version) >> 29)
#define GAL_VK_API_VERSION_MAJOR(version) ((static_cast<uint32_t>(version) >> 22) & 0x7FU)
#define GAL_VK_API_VERSION_MINOR(version) ((static_cast<uint32_t>(version) >> 12) & 0x3FFU)
#define GAL_VK_API_VERSION_PATCH(version) (static_cast<uint32_t>(version) & 0xFFFU)

#define GAL_VK_VERSION_MAJOR(version) (static_cast<uint32_t>(version) >> 22)
#define GAL_VK_VERSION_MINOR GAL_VK_API_VERSION_MINOR
#define GAL_VK_VERSION_PATCH GAL_VK_API_VERSION_PATCH

#define GAL_NV_VERSION_MAJOR(version) ((static_cast<uint32_t>(version) >> 22) & 0x3ff)
#define GAL_NV_VERSION_MINOR(version) ((static_cast<uint32_t>(version) >> 14) & 0x0ff)
#define GAL_NV_VERSION_SUBMINOR(version) ((static_cast<uint32_t>(version) >> 6) & 0x0ff)
#define GAL_NV_VERSION_PATCH(version) (static_cast<uint32_t>(version) & 0x003f)

namespace vk_ext
{
#ifndef VULKAN_HPP_NO_SMART_HANDLE
	template <typename T>
	using UniqueHandle = vk::UniqueHandle<T, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
#endif

	template <typename T>
	static std::string_view prop_name(const T &) noexcept = delete;

	template <>
	inline std::string_view prop_name<vk::ExtensionProperties>(const vk::ExtensionProperties &prop) noexcept
	{ return static_cast<std::string_view>(prop.extensionName); }
	template <>
	inline std::string_view prop_name<vk::LayerProperties>(const vk::LayerProperties &prop) noexcept
	{ return static_cast<std::string_view>(prop.layerName); }

	template <typename T, typename F>
	void remove_unsupported(std::vector<const char *> &wanted, const std::vector<T> &supported, F &&func) noexcept
	{
		wanted.erase(std::remove_if(wanted.begin(), wanted.end(),
			[&supported,&func](const char *name_ptr) noexcept -> bool {
				std::string_view name{name_ptr};
				typename std::vector<T>::const_iterator it{
					std::find_if(supported.cbegin(), supported.cend(), 
						[name](const T &prop) noexcept -> bool {
							return (prop_name<T>(prop) == name);
						}
					)
				};
				if(it == supported.cend()) {
					func(name);
					return true;
				} else {
					return false;
				}
			}
		), wanted.end());
	}

	template <typename T>
	typename T::CType native(const T &obj) noexcept
	{
		if constexpr(vk::isVulkanHandleType<T>::value) {
			return static_cast<typename T::CType>(obj);
		} else {
			return static_cast<typename T::CType>(*obj);
		}
	}
}
