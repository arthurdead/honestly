#pragma once

#include <ctl/version>
#include <ctl/string_view>
#include <ctl/string>
#include "atom.hpp"
#include "screen.hpp"
#include "xcb.hpp"
#include <gal/gal.hpp>
#include <gal/geometry.hpp>

#include "__private/connection_atoms.gen.hpp"

#if CTL_DEBUG_LEVEL > 0
	#define GAL_XCB_UNCHECKED(x) \
		x
	#define GAL_XCB_CHECKED(x) \
		x##_checked
#else
	#define GAL_XCB_UNCHECKED(x) \
		x##_unchecked
	#define GAL_XCB_CHECKED(x) \
		x
#endif

#define GAL_XCB_REPLY_FUNCTION(conn, x, ...) \
	(conn).__reply_func<false>(x, __VA_ARGS__)
#define GAL_XCB_CHECKED_FUNCTION(conn, x, ...) \
	(conn).__checked_func<false>(GAL_XCB_CHECKED(x), __VA_ARGS__)
#define GAL_XCB_CHECKED_FUNCTION_PTR(conn, x, ...) \
	(conn).__checked_func<false>(x, __VA_ARGS__)

#define GAL_XCB_REPLY_FUNCTION_EWMH(conn, x, ...) \
	(conn).__reply_func<true>(x, __VA_ARGS__)
#define GAL_XCB_CHECKED_FUNCTION_EWMH(conn, x, ...) \
	(conn).__checked_func<true>(GAL_XCB_CHECKED(x), __VA_ARGS__)

namespace gal::xcb
{
	class generic_event;

	namespace __conn
	{
		template <typename T>
		struct result_t;

		template <typename R, typename ...Args>
		struct result_t<R(&)(Args...)>
		{
			using type = R;
		};
	}

	class CTL_LOCAL_CLASS connection final
	{
		using screen_t = gal::xcb::screen;

	public:
		inline connection(connection &&other) noexcept
			: __GAL_XCB_CONN_MOVE_CTOR_ATOMS
				conn{std::move(other.conn)},
				ewmh{std::move(other.ewmh)},
				scrn_id{std::move(other.scrn_id)}
		{
			__GAL_XCB_CONN_RELEASE_OTHER_ATOMS
		}

		inline connection &operator=(connection &&other) noexcept
		{
			conn = std::move(other.conn);
			ewmh = std::move(other.ewmh);
			scrn_id = std::move(other.scrn_id);
			__GAL_XCB_CONN_ASSIGN_MOVE_ATOMS
			__GAL_XCB_CONN_RELEASE_OTHER_ATOMS
			return *this;
		}

		inline connection(std::string_view display) noexcept
			: __GAL_XCB_CONN_EMPTY_CTOR_ATOMS
				conn{xcb_connect(display.data(), &scrn_id)}
		{ init(display); }

		connection() noexcept;
		~connection() noexcept;

		inline int num_screens() noexcept
		{ return ewmh.nb_screens; }

		screen_t screen(std::size_t i) noexcept;
		screen_t screen() noexcept;

		inline operator const xcb_connection_t *() const noexcept
		{ return conn; }
		inline operator xcb_connection_t *() noexcept
		{ return conn; }

		inline operator const xcb_ewmh_connection_t *() const noexcept
		{ return &ewmh; }
		inline operator xcb_ewmh_connection_t *() noexcept
		{ return &ewmh; }

		inline int screen_number() const noexcept
		{ return scrn_id; }

		inline void flush(bool wait=false) noexcept
		{
			if(wait) {
				xcb_aux_sync(conn);
			} else {
				xcb_flush(conn);
			}
		}

		bool poll(generic_event &dst) const noexcept;

		class atom atom(std::string_view name, bool if_exists = true) noexcept;

		std::size_t num_desktops() const noexcept;
		std::vector<std::string> desktop_names(bool limit = false) const noexcept;
		std::vector<monitor_dimension> work_areas() const noexcept;
		dimension desktop_size() const noexcept;
		std::vector<absolute_point> desktops_viewport() const noexcept;
		std::size_t current_desktop() const noexcept;

		template <bool is_ewmh, typename F, typename ...Args>
		inline auto __reply_func(F &&f, Args && ...args) const noexcept -> typename __conn::result_t<F>::type
		{
			using reply_t = typename __conn::result_t<F>::type;

			reply_t reply;

		#if CTL_DEBUG_LEVEL > 0
			xcb_generic_error_t *err{nullptr};

			#define __GAL_XCB_CONN_REPLY_ERR_ARG &err
		#else
			#define __GAL_XCB_CONN_REPLY_ERR_ARG nullptr
		#endif

			if constexpr(is_ewmh) {
				reply = f(&const_cast<xcb_ewmh_connection_t &>(ewmh), std::forward<Args>(args)..., __GAL_XCB_CONN_REPLY_ERR_ARG);
			} else {
				reply = f(const_cast<xcb_connection_t *>(conn), std::forward<Args>(args)..., __GAL_XCB_CONN_REPLY_ERR_ARG);
			}

		#if CTL_DEBUG_LEVEL > 0
			print_error(err);
		#endif

			return reply;
		}

		template <bool is_ewmh, typename F, typename ...Args>
		inline void __checked_func(F &&f, Args && ...args) const noexcept
		{
			xcb_void_cookie_t cookie;

			if constexpr(is_ewmh) {
				cookie = f(&const_cast<xcb_ewmh_connection_t &>(ewmh), std::forward<Args>(args)...);
			} else {
				cookie = f(const_cast<xcb_connection_t *>(conn), std::forward<Args>(args)...);
			}

		#if CTL_DEBUG_LEVEL > 0
			print_error(xcb_request_check(conn, cookie));
		#endif
		}

		__GAL_XCB_CONN_ATOMS

	private:
	#if CTL_DEBUG_LEVEL > 0
		void print_error(const xcb_generic_error_t *err) const noexcept;
	#endif

		void init(std::string_view display) noexcept;

		connection(const connection &) = delete;
		connection &operator=(const connection &) = delete;

		xcb_render_pictforminfo_t *pic_a8;

		xcb_connection_t *conn;
		xcb_ewmh_connection_t ewmh{};
		int scrn_id;

	#if CTL_DEBUG_LEVEL > 0
		xcb_errors_context_t *errctx;
	#endif
	};
}
