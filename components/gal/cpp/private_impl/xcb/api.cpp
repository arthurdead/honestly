#include "api.hpp"
#include <ctl/memory>
#include "window.hpp"
#include "../window.hpp"
#include "connection.hpp"
#include "screen.hpp"
#include "event.hpp"
#include "xcb.hpp"
#include <unordered_map>
#include <gal/window.hpp>
#if CTL_DEBUG_LEVEL > 0
	#include <osal/terminal.hpp>
#endif


#include <gal/font.hpp>
#include "../font.hpp"
#include "font.hpp"

namespace gal::xcb
{
	namespace __private
	{
		CTL_GLOBAL_CTOR_BEGIN
		static ctl::unique_ptr<connection> conn;
		using user_window_map_t = std::unordered_map<window *, gal::window *>;
		static user_window_map_t user_window_map;
		static screen scrn;
		static software_list softinfo;
		static std::size_t desktop{~0u};
		static monitor_dimension mon;
		static std::vector<monitor_dimension> work_areas;
		CTL_GLOBAL_CTOR_END
	}

	GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL set_software_info(const software_list &info) noexcept
	{ __private::softinfo = info; }

	GAL_XCB_SHARED_API std::vector<std::string> GAL_XCB_SHARED_API_CALL collect_desktops() noexcept
	{ return __private::conn->desktop_names(true); }

	GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL select_desktop(std::size_t desk) noexcept
	{ __private::desktop = desk; }

	GAL_XCB_SHARED_API std::vector<monitor_info> GAL_XCB_SHARED_API_CALL collect_monitors() noexcept
	{ return __private::scrn.monitors(); }

	GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL select_monitor(const monitor_dimension &mon) noexcept
	{ __private::mon = mon; }

	GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL initialize() noexcept
	{
		__private::conn.emplace();
		__private::scrn = __private::conn->screen();
		__private::mon = __private::scrn.primary_monitor();
		__private::work_areas = __private::conn->work_areas();

	#if CTL_DEBUG_LEVEL > 0
		using namespace std::literals::string_view_literals;

		osal::this_terminal::info("num screens = "sv, __private::conn->num_screens(), '\n');

		osal::this_terminal::info("current screen = "sv, __private::conn->screen_number(),'\n');

		osal::this_terminal::info("num desktops = "sv, __private::conn->num_desktops(), '\n');

		osal::this_terminal::info("screen pix = "sv, (*__private::scrn).width_in_pixels,'x',(*__private::scrn).height_in_pixels, '\n');

		osal::this_terminal::info("screen mil = "sv, (*__private::scrn).width_in_millimeters, 'x',(*__private::scrn).height_in_millimeters,'\n');

		osal::this_terminal::info("current desktop = "sv, __private::conn->current_desktop(),'\n');

		dimension desktop_size{__private::conn->desktop_size()};
		osal::this_terminal::info("desktop size = "sv, desktop_size.width, 'x',desktop_size.height,'\n');

		osal::this_terminal::info("desktop names:\n"sv);
		const std::vector<std::string> names{__private::conn->desktop_names()};
		for(const std::string &name : names) {
			osal::this_terminal::info("  "sv, name, '\n');
		}

		osal::this_terminal::info("monitors:\n"sv);
		const std::vector<monitor_info> mons{__private::scrn.monitors()};
		for(const monitor_info &info : mons) {
			osal::this_terminal::info("  "sv, info.name, '\n');
			osal::this_terminal::info("    "sv, info.x, 'x', info.y,'x',info.width, 'x',info.height,'\n');
			osal::this_terminal::info("    "sv, info.primary, '\n');
		}

		osal::this_terminal::info("work areas:\n"sv);
		const std::vector<monitor_dimension> areas{__private::conn->work_areas()};
		for(const monitor_dimension &area : areas) {
			osal::this_terminal::info("    "sv, area.x, 'x', area.y,'x',area.width, 'x',area.height,'\n');
		}

		osal::this_terminal::info("viewports:\n"sv);
		const std::vector<absolute_point> viewports{__private::conn->desktops_viewport()};
		for(const absolute_point &viewport : viewports) {
			osal::this_terminal::info("    "sv, viewport.x, 'x', viewport.y,'\n');
		}
	#endif
	}

	GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL shutdown() noexcept
	{
		__private::scrn.destroy_root_win();

		for(__private::user_window_map_t::value_type &it : __private::user_window_map) {
			delete it.first;
		}

		__private::conn.reset();

		window::shutdown();
		__private::user_window_map.clear();
	}

	GAL_XCB_SHARED_API __win::impl * GAL_XCB_SHARED_API_CALL create_window(ctl::optional_ref<gal::window> usr_win, std::size_t x, std::size_t y, std::size_t w, std::size_t h) noexcept
	{
		using namespace std::literals::string_view_literals;

		connection &conn{*__private::conn};
		const screen &scrn{__private::scrn};

		const std::size_t desk{__private::desktop == ~0u ? __private::conn->current_desktop() : __private::desktop};

		const monitor_dimension &area{__private::work_areas[desk]};

		if(w == ~0u) {
			w = __private::mon.width;
		}
		if(h == ~0u) {
			h = area.height;
		}
		if(x == ~0u) {
			x = __private::mon.x + ((__private::mon.width / 2) - (w / 2));
		}
		if(y == ~0u) {
			y = __private::mon.y + ((area.height / 2) - (h / 2));
		}

		window *xcb_win{new window{conn, scrn, x, y, w, h}};

		std::string winname{"gal_window_"sv};
		winname += ctl::to_string(xcb_win->native());
		xcb_win->set_name(std::move(winname));

		xcb_win->set_desktop(desk);
		xcb_win->set_types({conn._NET_WM_WINDOW_TYPE_NORMAL});

		if(!__private::softinfo.app.name.empty()) {
			xcb_win->set_class(__private::softinfo.app.name);
		} else {
			xcb_win->set_class("gal_unnamed_app"sv);
		}

		if(usr_win) {
			__private::user_window_map[xcb_win] = &(*usr_win);
			xcb_win->map();
		} else {
			xcb_win->unmap();
		}

		xcb_win->move(x, y);

		conn.flush();

		return static_cast<__win::impl *>(xcb_win);
	}

	GAL_XCB_SHARED_API void GAL_XCB_SHARED_API_CALL upkeep() noexcept
	{
	#if CTL_DEBUG_LEVEL > 0
		using namespace std::literals::string_view_literals;
	#endif

		connection &conn{*__private::conn};

		generic_event base_event;
		if(conn.poll(base_event)) {
			std::uint8_t ev_type{base_event.type()};
			switch(ev_type) {
				case XCB_CONFIGURE_NOTIFY: {
					configure_notify_event event{base_event};
					ctl::optional_ref<window> win{event.window()};
					if(win) {
						window *ptr{&(*win)};
						__private::user_window_map_t::iterator it{__private::user_window_map.find(ptr)};
						if(it != __private::user_window_map.end()) {
							
						}
					}
					break;
				}
				case XCB_EXPOSE: {
					expose_event event{base_event};
					ctl::optional_ref<window> win{event.window()};
					if(win) {
						window *ptr{&(*win)};
						__private::user_window_map_t::iterator it{__private::user_window_map.find(ptr)};
						if(it != __private::user_window_map.end()) {
							it->second->draw();

							
						}
					}
					break;
				}
				case XCB_DESTROY_NOTIFY: {
					CTL_DEBUGTRAP;
					/*destroy_notify_event event{base_event};
					ctl::optional_ref<window> win{event.window()};
					if(win) {
						window *ptr{&(*win)};
						__private::user_window_map_t::iterator it{__private::user_window_map.find(ptr)};
						if(it != __private::user_window_map.end()) {
							delete it->second;
							__private::user_window_map.erase(ptr);
						}
					}*/
					break;
				}
				case XCB_CLIENT_MESSAGE: {
					client_message_event event{base_event};
					std::uint32_t type{event.type()};
					if(type == conn.WM_PROTOCOLS) {
						std::uint32_t msg_type{event.msg()};
						if(msg_type == conn.WM_DELETE_WINDOW) {
							ctl::optional_ref<window> win{event.window()};
							if(win) {
								window *ptr{&(*win)};
								__private::user_window_map_t::iterator it{__private::user_window_map.find(ptr)};
								if(it != __private::user_window_map.end()) {
									it->second->on_close();
									it->second->impl.reset();
									__private::user_window_map.erase(ptr);
								} else {
									ptr->destroy();
								}
							}
						} else if(msg_type == conn._NET_WM_PING) {
							client_message_ping msg{event.cast<client_message_ping>()};
							ctl::optional_ref<window> win{event.window()};
							if(win) {
								window *ptr{&(*win)};
								xcb_timestamp_t time{msg.time()};
								ptr->pong(time);
							}
						}
					}
					break;
				}
			}
		}
	}

	GAL_SHARED_API std::uintptr_t GAL_SHARED_API_CALL get_native_window(__win::impl &impl) noexcept
	{
		window &win{reinterpret_cast<window &>(impl)};
		xcb_window_t &id{win.native()};
		return reinterpret_cast<std::uintptr_t>(&id);
	}

	GAL_SHARED_API std::uintptr_t GAL_SHARED_API_CALL get_native_connection(__win::impl &impl) noexcept
	{
		window &win{reinterpret_cast<window &>(impl)};
		connection &conn{win.connection()};
		xcb_connection_t *ptr{conn};
		return reinterpret_cast<std::uintptr_t>(ptr);
	}
}
