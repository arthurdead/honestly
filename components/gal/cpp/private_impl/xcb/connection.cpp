#include "connection.hpp"
#include <ctl/charconv>
#include <osal/environment.hpp>
#include "event.hpp"
#if CTL_DEBUG_LEVEL > 0
	#include <osal/terminal.hpp>
#endif

namespace gal::xcb
{
#if CTL_DEBUG_LEVEL > 0
	void connection::print_error(const xcb_generic_error_t *err) const noexcept
	{
		using namespace std::literals::string_view_literals;

		if(!err) {
			return;
		}

		const char *mjcode{xcb_errors_get_name_for_major_code(errctx, err->major_code)};
		const char *mn_code{xcb_errors_get_name_for_minor_code(errctx, err->major_code, err->minor_code)};
		const char *ext{nullptr};
		const char *errstr{xcb_errors_get_name_for_error(errctx, err->error_code, &ext)};

		if(mjcode) {
			osal::this_terminal::error(mjcode);

			if(mn_code) {
				osal::this_terminal::error(" "sv,mjcode);
			}

			osal::this_terminal::error(" "sv);
		}

		if(errstr) {
			osal::this_terminal::error(errstr);

			if(ext) {
				osal::this_terminal::error(ext);
			}
		}

		osal::this_terminal::print('\n');
	}
#endif

	connection::connection() noexcept
		: __GAL_XCB_CONN_EMPTY_CTOR_ATOMS
			conn{nullptr}
	{
		using namespace std::literals::string_view_literals;

		std::string display;
		osal::environment::get("DISPLAY"sv, display);
		conn = xcb_connect(display.data(), &scrn_id);
		init(display);
	}

	void connection::init(std::string_view display) noexcept
	{
	#if CTL_DEBUG_LEVEL > 0
		xcb_errors_context_new(conn, &errctx);
	#endif

		xcb_intern_atom_cookie_t *cookie{xcb_ewmh_init_atoms(conn, &ewmh)};
		xcb_ewmh_init_atoms_replies(&ewmh, cookie, nullptr);

		__GAL_XCB_CONN_EWMH_ATOMS

		using namespace std::literals::string_view_literals;

		display = display.substr(1);

		std::size_t dot{display.find('.')};
		if(dot != std::string_view::npos) {
			display = display.substr(0, dot-1);
			CTL_DEBUGTRAP;
		}

		__GAL_XCB_CONN_ICCCM_ATOMS

		const xcb_render_query_pict_formats_reply_t *pic_formats{xcb_render_util_query_formats(conn)};

		pic_a8 = xcb_render_util_find_standard_format(pic_formats, XCB_PICT_STANDARD_A_8);
	}

	connection::~connection() noexcept
	{
		xcb_ewmh_connection_wipe(&ewmh);

	#if CTL_DEBUG_LEVEL > 0
		xcb_errors_context_free(errctx);
	#endif

		xcb_render_util_disconnect(conn);

		xcb_disconnect(conn);
	}

	class atom connection::atom(std::string_view name, bool if_exists) noexcept
	{
		xcb_intern_atom_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_intern_atom)(conn, if_exists ? 1 : 0, static_cast<std::uint16_t>(name.length()), name.data())};
		xcb_intern_atom_reply_t *reply{GAL_XCB_REPLY_FUNCTION(*this, xcb_intern_atom_reply, cookie)};
		class atom tmp{reply->atom, *this};
		delete reply;
		return tmp;
	}

	std::size_t connection::num_desktops() const noexcept
	{
		xcb_get_property_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_ewmh_get_number_of_desktops)(&const_cast<xcb_ewmh_connection_t &>(ewmh), scrn_id)};
		std::uint32_t num;
		GAL_XCB_REPLY_FUNCTION_EWMH(*this, xcb_ewmh_get_number_of_desktops_reply, cookie, &num);
		return num;
	}

	std::vector<std::string> connection::desktop_names(bool limit) const noexcept
	{
		std::size_t num{~0u};
		if(limit) {
			num = num_desktops();
		}
		xcb_get_property_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_ewmh_get_desktop_names)(&const_cast<xcb_ewmh_connection_t &>(ewmh), scrn_id)};
		xcb_ewmh_get_utf8_strings_reply_t reply;
		GAL_XCB_REPLY_FUNCTION_EWMH(*this, xcb_ewmh_get_desktop_names_reply, cookie, &reply);
		std::vector<std::string> names;
		std::string tmp;
		for(std::size_t i{0}; i < reply.strings_len; ++i) {
			char c{reply.strings[i]};
			if(c == '\0') {
				if(names.size() == num) {
					break;
				}
				names.emplace_back(std::move(tmp));
				continue;
			}
			tmp += c;
		}
		xcb_ewmh_get_utf8_strings_reply_wipe(&reply);
		return names;
	}

	dimension connection::desktop_size() const noexcept
	{
		xcb_get_property_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_ewmh_get_desktop_geometry)(&const_cast<xcb_ewmh_connection_t &>(ewmh), scrn_id)};
		std::uint32_t w;
		std::uint32_t h;
		GAL_XCB_REPLY_FUNCTION_EWMH(*this, xcb_ewmh_get_desktop_geometry_reply, cookie, &w, &h);
		return dimension{static_cast<std::size_t>(w), static_cast<std::size_t>(h)};
	}

	std::size_t connection::current_desktop() const noexcept
	{
		xcb_get_property_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_ewmh_get_current_desktop)(&const_cast<xcb_ewmh_connection_t &>(ewmh), scrn_id)};
		std::uint32_t d;
		GAL_XCB_REPLY_FUNCTION_EWMH(*this, xcb_ewmh_get_current_desktop_reply, cookie, &d);
		return static_cast<std::size_t>(d);
	}

	std::vector<absolute_point> connection::desktops_viewport() const noexcept
	{
		xcb_get_property_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_ewmh_get_desktop_viewport)(&const_cast<xcb_ewmh_connection_t &>(ewmh), scrn_id)};
		xcb_ewmh_get_desktop_viewport_reply_t reply;
		GAL_XCB_REPLY_FUNCTION_EWMH(*this, xcb_ewmh_get_desktop_viewport_reply, cookie, &reply);
		std::vector<absolute_point> viewports;
		for(std::size_t i{0}; i < reply.desktop_viewport_len; ++i) {
			const xcb_ewmh_coordinates_t &data{reply.desktop_viewport[i]};
			absolute_point &viewport{viewports.emplace_back()};
			viewport.x = static_cast<std::size_t>(data.x);
			viewport.y = static_cast<std::size_t>(data.y);
		}
		xcb_ewmh_get_desktop_viewport_reply_wipe(&reply);
		return viewports;
	}

	std::vector<monitor_dimension> connection::work_areas() const noexcept
	{
		xcb_get_property_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_ewmh_get_workarea)(&const_cast<xcb_ewmh_connection_t &>(ewmh), scrn_id)};
		xcb_ewmh_get_workarea_reply_t reply;
		GAL_XCB_REPLY_FUNCTION_EWMH(*this, xcb_ewmh_get_workarea_reply, cookie, &reply);
		std::vector<monitor_dimension> areas;
		for(std::size_t i{0}; i < reply.workarea_len; ++i) {
			const xcb_ewmh_geometry_t &data{reply.workarea[i]};
			monitor_dimension &area{areas.emplace_back()};
			area.x = static_cast<std::size_t>(data.x);
			area.y = static_cast<std::size_t>(data.y);
			area.width = static_cast<std::size_t>(data.width);
			area.height = static_cast<std::size_t>(data.height);
		}
		xcb_ewmh_get_workarea_reply_wipe(&reply);
		return areas;
	}

	bool connection::poll(generic_event &dst) const noexcept
	{ return !!(dst.evnt = xcb_poll_for_event(conn)); }

	connection::screen_t connection::screen(std::size_t i) noexcept
	{ return screen_t{ewmh.screens[i], *this}; }
	connection::screen_t connection::screen() noexcept
	{ return screen_t{ewmh.screens[scrn_id], *this}; }
}
