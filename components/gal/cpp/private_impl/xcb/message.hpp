#pragma once

#include <ctl/version>
#include "window.hpp"
#include "connection.hpp"
#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS client_message_ping final
	{
	public:
		inline client_message_ping(const window &win_, xcb_timestamp_t time__) noexcept
			: time_{time__}, win{win_}
		{
		}

		inline xcb_timestamp_t time() const noexcept
		{ return time_; }

	//private:
		inline void init(const connection &conn) noexcept
		{ type = conn._NET_WM_PING; }

		static const atom &protocol(const connection &conn) noexcept
		{ return conn.WM_PROTOCOLS; }

	private:
		xcb_atom_t type;
		xcb_timestamp_t time_;
		xcb_window_t win;
	};

	class CTL_LOCAL_CLASS client_message_desktop final
	{
	public:
		inline client_message_desktop(std::uint32_t desktop_) noexcept
			: desktop{desktop_}
		{
		}

	//private:
		inline void init([[maybe_unused]] const connection &) noexcept
		{  }

		static const atom &protocol(const connection &conn) noexcept
		{ return conn._NET_WM_DESKTOP; }

	private:
		std::uint32_t desktop;
		xcb_ewmh_client_source_type_t source{XCB_EWMH_CLIENT_SOURCE_TYPE_NORMAL};
	};
}
