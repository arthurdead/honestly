#include "window.hpp"
#include "screen.hpp"
#include "message.hpp"
#include <osal/process.hpp>
#include <osal/network.hpp>
#include <unordered_map>
#include <ctl/algorithm>
#include <ctl/charconv>
#include "../renderer.hpp"
#include "../gal.hpp"
#include "pen.hpp"

namespace gal::xcb
{
	namespace __private
	{
		CTL_GLOBAL_CTOR_BEGIN
		using window_map_t = std::unordered_map<xcb_window_t, window *>;
		static window_map_t window_map;
		CTL_GLOBAL_CTOR_END
	}

	void window::shutdown() noexcept
	{
		__private::window_map.clear();
	}

	window::~window() noexcept
	{
		if(conn && id != XCB_ATOM_NONE) {
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_destroy_window, id);
			__private::window_map.erase(id);
			conn->flush();
		}
	}

	void window::destroy() noexcept
	{
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_destroy_window, id);
		__private::window_map.erase(id);
		conn = nullptr;
		id = XCB_ATOM_NONE;
		scrn = nullptr;
		conn->flush();
	}

	ctl::optional_ref<window> window::find(xcb_window_t win) noexcept
	{
		__private::window_map_t::iterator it{__private::window_map.find(win)};
		if(it != __private::window_map.end()) {
			return ctl::make_optional_ref(*it->second);
		} else {
			return std::nullopt;
		}
	}

	window::window(class connection &conn_, const class screen &scrn_, std::size_t x, std::size_t y, std::size_t w, std::size_t h) noexcept
		: conn{&conn_}, id{xcb_generate_id(*conn)}, scrn{&const_cast<class screen &>(scrn_)}
	{
		__private::window_map[id] = this;

		static constexpr const std::uint32_t mask{
			XCB_CW_BACK_PIXEL|
			XCB_CW_EVENT_MASK
		};

		xcb_create_window_value_list_t params{};
		params.background_pixel = (*scrn)->black_pixel;
		params.event_mask = XCB_EVENT_MASK_EXPOSURE|XCB_EVENT_MASK_STRUCTURE_NOTIFY;

		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_create_window_aux, 
			static_cast<std::uint8_t>(XCB_COPY_FROM_PARENT),
			id, (*scrn)->root,
			static_cast<std::int16_t>(x), static_cast<std::int16_t>(y),
			static_cast<std::uint16_t>(w), static_cast<std::uint16_t>(h),
			static_cast<std::uint16_t>(0),
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			(*scrn)->root_visual,
			mask, &params
		);

		GAL_XCB_CHECKED_FUNCTION_EWMH(*conn, xcb_ewmh_set_wm_pid, id, static_cast<std::uint32_t>(osal::this_process::id()));

		std::string hostname{osal::hostname()};
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_icccm_set_wm_client_machine, id, XCB_ATOM_STRING, static_cast<std::uint8_t>(8), static_cast<std::uint32_t>(hostname.length()), hostname.c_str());

		set_wm_protocols({conn->WM_DELETE_WINDOW, conn->_NET_WM_PING});
	}

	void window::set_wm_protocols(std::initializer_list<ctl::cref_wrapper<atom>> values) noexcept
	{
		std::vector<xcb_atom_t> tmp;
		tmp.resize(values.size());
		ctl::copy(values.begin(), values.end(), tmp.begin());
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_icccm_set_wm_protocols, id, conn->WM_PROTOCOLS, static_cast<std::uint32_t>(values.size()), tmp.data());
	}

	void window::set_types(std::initializer_list<ctl::cref_wrapper<atom>> values) noexcept
	{
		std::vector<xcb_atom_t> tmp;
		tmp.resize(values.size());
		ctl::copy(values.begin(), values.end(), tmp.begin());
		GAL_XCB_CHECKED_FUNCTION_EWMH(*conn, xcb_ewmh_set_wm_window_type, id, static_cast<std::uint32_t>(values.size()), tmp.data());
	}

	void window::change_desktop(std::size_t num) noexcept
	{
		send_message<client_message_desktop>(static_cast<std::uint32_t>(num));
		conn->flush();
	}

	void window::pong(xcb_timestamp_t time) const noexcept
	{
		scrn->root_window().send_message<client_message_ping>(*this, time);
		conn->flush();
	}

	__pen::impl *window::create_pen() noexcept
	{ return new pen{*conn, id}; }
}
