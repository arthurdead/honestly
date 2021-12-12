#pragma once

#include <ctl/version>
#include <cstdint>

#ifdef __GAL_XCB_IS_STATIC
	#define GAL_XCB_SHARED_API
	#define GAL_XCB_SHARED_API_CALL
#elif defined __GAL_XCB_IS_SHARED
	#ifdef __COMPILING_GAL_XCB
		#define GAL_XCB_SHARED_API CTL_SHARED_EXPORT
	#else
		#define GAL_XCB_SHARED_API CTL_SHARED_IMPORT
	#endif
	#define GAL_XCB_SHARED_API_CALL CTL_SHARED_CALL
#else
	#error
#endif

#include "../window.hpp"

namespace gal::xcb
{
	extern GAL_XCB_SHARED_API __win::impl * GAL_XCB_SHARED_API_CALL create_window(ctl::optional_ref<gal::window> usr_win, std::size_t x, std::size_t y, std::size_t w, std::size_t h) noexcept;

	extern GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL set_software_info(const software_list &info) noexcept;

	extern GAL_XCB_SHARED_API std::vector<std::string> GAL_XCB_SHARED_API_CALL collect_desktops() noexcept;
	extern GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL select_desktop(std::size_t desk) noexcept;

	extern GAL_XCB_SHARED_API std::vector<monitor_info> GAL_XCB_SHARED_API_CALL collect_monitors() noexcept;
	extern GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL select_monitor(const monitor_dimension &mon) noexcept;

	extern GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL initialize() noexcept;
	extern GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL upkeep() noexcept;
	extern GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL shutdown() noexcept;

	extern GAL_XCB_SHARED_API std::uintptr_t GAL_XCB_SHARED_API_CALL get_native_window(__win::impl &win) noexcept;
	extern GAL_XCB_SHARED_API std::uintptr_t GAL_XCB_SHARED_API_CALL get_native_connection(__win::impl &win) noexcept;
}
