#pragma once

#include <ctl/version>
#include <ctl/string_view>
#include <ctl/string>
#include <ctl/vector>
#include <ctl/functional>
#include <ctl/charconv>
#include "geometry.hpp"

#include "__private/api.hpp"

namespace gal
{
	struct pci
	{
		std::size_t domain;
		std::size_t bus;
		std::size_t device;
		std::size_t function;

		inline bool operator==(const pci &other) const noexcept
		{
			return (domain == other.domain &&
					bus == other.bus &&
					device == other.device &&
					function == other.function);
		}
		inline bool operator!=(const pci &other) const noexcept
		{ return !operator==(other); }
	};
}

namespace std
{
	template <>
	struct hash<gal::pci>
	{
		inline std::size_t operator()(gal::pci p) const noexcept
		{
			std::size_t value{0};
			value ^= std::hash<std::size_t>{}(p.domain) + 0x9e3779b9 + (value << 6) + (value >> 2);
			value ^= std::hash<std::size_t>{}(p.bus) + 0x9e3779b9 + (value << 6) + (value >> 2);
			value ^= std::hash<std::size_t>{}(p.device) + 0x9e3779b9 + (value << 6) + (value >> 2);
			value ^= std::hash<std::size_t>{}(p.function) + 0x9e3779b9 + (value << 6) + (value >> 2);
			return value;
		}
	};
}

namespace gal
{
	enum class render_ctx_backend : unsigned char
	{
		vulkan,
		egl,
	#if CTL_TARGET_OS & CTL_OS_FLAG_UNIX
		glx,
	#elif CTL_TARGET_OS == CTL_OS_WINDOWS
		wgl,
	#endif
	};

	enum class render_backend : unsigned char
	{
		vulkan,
		opengl,
	};

	enum class window_backend : unsigned char
	{
	#if CTL_TARGET_OS & CTL_OS_FLAG_UNIX
		xcb,
		xlib,
	#endif
	};

	struct vendor_info
	{
		std::string name;
		std::size_t id;

		inline bool operator==(const vendor_info &other) const noexcept
		{ return id == other.id; }
		inline bool operator!=(const vendor_info &other) const noexcept
		{ return id != other.id; }
	};

	struct device_info
	{
		inline device_info(const vendor_info &vendor_) noexcept
			: vendor{vendor_}
		{
		}

		enum class type : unsigned char
		{
			integrated,
			dedicated
		};

		ctl::cref_wrapper<vendor_info> vendor;
		std::string name;
		std::size_t id;
		enum type type;

		inline bool operator==(const device_info &other) const noexcept
		{ return (*vendor == *other.vendor && id == other.id); }
		inline bool operator!=(const device_info &other) const noexcept
		{ return !operator==(other); }

	private:
		device_info() = delete;
	};

	struct physical_device_info
	{
		inline physical_device_info(const device_info &device_) noexcept
			: device{device_}
		{
		}

		ctl::cref_wrapper<device_info> device;

		struct pci pci;

		inline bool operator==(const physical_device_info &other) const noexcept
		{ return pci == other.pci; }
		inline bool operator!=(const physical_device_info &other) const noexcept
		{ return pci != other.pci; }

	private:
		physical_device_info() = delete;
	};

	struct gpu_list
	{
		ctl::ptr_vector<vendor_info> vendors;
		ctl::ptr_vector<device_info> devices;
		std::vector<physical_device_info> physical_devices;
	};

	extern GAL_SHARED_API gpu_list GAL_SHARED_API_CALL collect_gpus() noexcept;

	struct version_t
	{
		enum type_t : unsigned char
		{
			triplet,
			quadruplet_variant,
			quadruplet_subminor,
		};

		constexpr inline version_t() noexcept
			: type{triplet}
		{
		}

		constexpr inline version_t(type_t type_) noexcept
			: type{type_}
		{
		}

		constexpr inline version_t(type_t type_, std::size_t raw__) noexcept
			: type{type_}, raw_{raw__}
		{
		}

		constexpr inline version_t(std::size_t major_, std::size_t minor_, std::size_t patch_) noexcept
			: type{triplet}
		{ set(major_, minor_, patch_); }

		constexpr inline version_t(bool is_variant, std::size_t variant_, std::size_t major_, std::size_t minor_, std::size_t patch_) noexcept
			: type{is_variant ? quadruplet_variant : quadruplet_subminor}
		{ set(variant_, major_, minor_, patch_); }

		constexpr inline void set(type_t type_) noexcept
		{ type = type_; }

		constexpr inline void set(type_t type_, std::size_t raw__) noexcept
		{ type = type_; raw_ = raw__; }

		constexpr inline void set(type_t type_, std::size_t major_, std::size_t minor_, std::size_t patch_) noexcept
		{ type = type_; set(major_, minor_, patch_); }

		constexpr inline void set(type_t type_, std::size_t variant_, std::size_t major_, std::size_t minor_, std::size_t patch_) noexcept
		{ type = type_; set(variant_, major_, minor_, patch_); }

		constexpr inline void set(std::size_t major_, std::size_t minor_, std::size_t patch_) noexcept
		{
			switch(type) {
				case quadruplet_variant:
				{ set(0, major_, minor_, patch_); break; }
				case quadruplet_subminor:
				{ set(major_, minor_, 0, patch_); break; }
				case triplet: {
					raw_ = (
						(major_ << 22) |
						(minor_ << 12) |
						patch_
					);
				}
			}
		}

		constexpr inline void set(std::size_t variant_, std::size_t major_, std::size_t minor_, std::size_t patch_) noexcept
		{
			switch(type) {
				case triplet:
				{ set(major_, minor_, patch_); break; }
				case quadruplet_variant: {
					raw_ = (
						(variant_ << 29) |
						(major_ << 22) |
						(minor_ << 12) |
						patch_
					);
					break;
				}
				case quadruplet_subminor: {
					raw_ = (
						(variant_ << 29) |
						(major_ << 22) |
						(minor_ << 12) |
						patch_
					);
					break;
				}
			}
		}

		constexpr inline std::size_t variant() const noexcept
		{
			switch(type) {
				case quadruplet_variant:
				{ return (raw_ >> 29); }
				case triplet:
				case quadruplet_subminor:
				{ return 0; }
			}
		}

		constexpr inline std::size_t major() const noexcept
		{
			switch(type) {
				case triplet:
				{ return (raw_ >> 22); }
				case quadruplet_variant:
				{ return ((raw_ >> 22) & 127); }
				case quadruplet_subminor:
				{ return ((raw_ >> 22) & 1023); }
			}
		}

		constexpr inline std::size_t minor() const noexcept
		{
			switch(type) {
				case triplet:
				case quadruplet_variant:
				{ return ((raw_ >> 12) & 1023); }
				case quadruplet_subminor:
				{ return ((raw_ >> 14) & 255); }
			}
		}

		constexpr inline std::size_t subminor() const noexcept
		{
			switch(type) {
				case quadruplet_subminor:
				{ return ((raw_ >> 6) & 255); }
				case triplet:
				case quadruplet_variant:
				{ return 0; }
			}
		}

		constexpr inline std::size_t patch() const noexcept
		{
			switch(type) {
				case triplet:
				case quadruplet_variant:
				{ return (raw_ & 4095); }
				case quadruplet_subminor:
				{ return (raw_ & 63); }
			}
		}

		constexpr inline std::size_t raw() const noexcept
		{ return raw_; }

	private:
		type_t type;
		std::size_t raw_;
	};

	struct software_list
	{
		struct software_info
		{
			std::string name;
			version_t version;
		};

		software_info app;
		software_info engine;
	};

	struct init_settings
	{
		software_list soft_info;
	};

	struct init_settings_window : virtual init_settings
	{
		window_backend win_back;
		std::size_t desktop;
	};

	struct init_settings_render : virtual init_settings
	{
		render_backend rndr_back;
		render_ctx_backend ctx_back;
	};

	using monitor_dimension = absolute_rectangle;

	struct monitor_info : monitor_dimension
	{
		bool primary;
		std::string name;
	};

	extern GAL_SHARED_API bool GAL_SHARED_API_CALL initialize(const init_settings_window &settings) noexcept;
	extern GAL_SHARED_API std::vector<monitor_info> GAL_SHARED_API_CALL collect_monitors() noexcept;
	extern GAL_SHARED_API void GAL_SHARED_API_CALL select_monitor(const monitor_dimension &mon) noexcept;
	extern GAL_SHARED_API std::vector<std::string> GAL_SHARED_API_CALL collect_desktops() noexcept;
	extern GAL_SHARED_API void GAL_SHARED_API_CALL select_desktop(std::size_t desk) noexcept;
	extern GAL_SHARED_API bool GAL_SHARED_API_CALL initialize(const init_settings_render &settings) noexcept;
	extern GAL_SHARED_API bool GAL_SHARED_API_CALL gpu_supported(const pci &gpu) noexcept;
	extern GAL_SHARED_API bool GAL_SHARED_API_CALL select_gpu(const pci &gpu) noexcept;
	extern GAL_SHARED_API void GAL_SHARED_API_CALL upkeep() noexcept;
	extern GAL_SHARED_API void GAL_SHARED_API_CALL shutdown() noexcept;
}
