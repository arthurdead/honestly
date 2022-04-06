#pragma once

#include <ctl/version>
#include <ctl/utility>
#include <ctl/memory>
#include <gal/gal.hpp>
#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS window;
	class CTL_LOCAL_CLASS connection;

	class CTL_LOCAL_CLASS screen final
	{
	public:
		screen() noexcept = default;
		screen(screen &&other) noexcept = default;
		screen &operator=(screen &&other) noexcept = default;

		screen(xcb_screen_t *ptr, connection &conn) noexcept;

		monitor_dimension primary_monitor() const noexcept;
		std::vector<monitor_info> monitors() const noexcept;

		inline xcb_render_pictformat_t picture_format_id() const noexcept
		{ return pic_fmt; }

		void destroy_root_win() noexcept;

		using assign_pair_t = std::pair<xcb_screen_t *, connection &>;
		screen &operator=(assign_pair_t pair) noexcept;

		inline const xcb_screen_t *operator->() const noexcept
		{ return scrn; }
		inline operator const xcb_screen_t *() const noexcept
		{ return scrn; }
		inline operator xcb_screen_t *() noexcept
		{ return scrn; }

		inline window &root_window() noexcept
		{ return *root_win; }
		inline const window &root_window() const noexcept
		{ return *root_win; }

	private:
		screen(const screen &) noexcept = delete;
		screen &operator=(const screen &) noexcept = delete;

		void init() noexcept;

		xcb_screen_t *scrn;
		connection *conn;
		ctl::unique_ptr<window> root_win;
		xcb_render_pictformat_t pic_fmt;
	};
}
