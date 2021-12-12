#pragma once

#include <ctl/version>
#include <ctl/functional>
#include <ctl/optional>
#include <ctl/utility>
#include <ctl/string_view>
#include <ctl/string>
#include "connection.hpp"
#include "../window.hpp"
#include "atom.hpp"
#include "xcb.hpp"
#include <limits>
#include <initializer_list>

namespace gal::xcb
{
	class CTL_LOCAL_CLASS screen;

	class CTL_LOCAL_CLASS window final : public __win::impl
	{
	public:
		window() noexcept = default;
		window(window &&other) noexcept = default;
		window &operator=(window &&other) noexcept = default;

		inline window(xcb_window_t win, class connection &conn_, const class screen &scrn_) noexcept
			: conn{&conn_}, id{win}, scrn{&const_cast<class screen &>(scrn_)}
		{
		}

		window(class connection &conn, const class screen &scrn, std::size_t x, std::size_t y, std::size_t w, std::size_t h) noexcept;
		~window() noexcept override;

		static void shutdown() noexcept;

		inline operator xcb_window_t() const noexcept
		{ return id; }
		inline xcb_window_t &native() noexcept
		{ return id; }
		inline const xcb_window_t &native() const noexcept
		{ return id; }

		__pen::impl *create_pen() noexcept override final;

		inline void map() noexcept
		{ GAL_XCB_CHECKED_FUNCTION(*conn, xcb_map_window, id); }
		inline void unmap() noexcept
		{ GAL_XCB_CHECKED_FUNCTION(*conn, xcb_unmap_window, id); }

		inline void move(std::size_t x, std::size_t y) noexcept
		{
			xcb_configure_window_value_list_t values{};
			values.x = static_cast<std::int32_t>(x);
			values.y = static_cast<std::int32_t>(y);
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_configure_window_aux, id, static_cast<std::uint16_t>(XCB_CONFIG_WINDOW_X|XCB_CONFIG_WINDOW_Y), &values);
		}

		void set_wm_protocols(std::initializer_list<ctl::cref_wrapper<atom>> values) noexcept;

		static ctl::optional_ref<window> find(xcb_window_t win) noexcept;

		void destroy() noexcept;

		inline void set_name(std::string_view name) noexcept
		{
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_icccm_set_wm_name, id, XCB_ATOM_STRING, static_cast<std::uint8_t>(8), static_cast<std::uint32_t>(name.length()), name.data());
			GAL_XCB_CHECKED_FUNCTION_EWMH(*conn, xcb_ewmh_set_wm_name, id, static_cast<std::uint32_t>(name.length()), name.data());
		}

		inline void set_class(std::string_view cls) noexcept
		{
			using namespace std::literals::string_view_literals;
			std::string winname{"gal_window_"sv};
			winname += ctl::to_string(id);
			std::string tmp;
			tmp.reserve(winname.length() + cls.length() + 1);
			tmp += std::move(winname);
			tmp += '\0';
			tmp += cls;
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_icccm_set_wm_class, id, static_cast<std::uint32_t>(tmp.length()), tmp.c_str());
		}

		void set_types(std::initializer_list<ctl::cref_wrapper<atom>> values) noexcept;

		inline void set_desktop(std::size_t num) noexcept
		{ GAL_XCB_CHECKED_FUNCTION_EWMH(*conn, xcb_ewmh_set_wm_desktop, id, static_cast<std::uint32_t>(num)); }

		void change_desktop(std::size_t num) noexcept;

		template <typename T, typename ...Args>
		inline void send_message(Args && ...args) const noexcept
		{
			union alignas(xcb_client_message_data_t) U {
				inline U(Args && ...args_) noexcept
					: tmp{std::forward<Args>(args_)...}
				{}
				T tmp;
				const xcb_client_message_data_t data;
			};
			static_assert(sizeof(U) <= sizeof(xcb_client_message_data_t));
			static_assert(sizeof(U) >= sizeof(xcb_atom_t));
			static_assert(alignof(U) == alignof(xcb_client_message_data_t));
			//static_assert(std::is_base_of_v<basic_client_message, T>);
			U u{std::forward<Args>(args)...};
			u.tmp.init(*conn);
			GAL_XCB_CHECKED_FUNCTION_PTR(*conn, xcb_ewmh_send_client_message, id, scrn->root_window(), T::protocol(*conn), static_cast<std::uint32_t>(sizeof(T)), u.data.data32);
		}

		void pong(xcb_timestamp_t time) const noexcept;

		inline class connection &connection() noexcept
		{ return *conn; }

	private:
		window(const window &) noexcept = delete;
		window &operator=(const window &) noexcept = delete;

		class connection *conn;
		xcb_window_t id;
		class screen *scrn;
	};
}
