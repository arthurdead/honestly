#include "screen.hpp"
#include "window.hpp"

namespace gal::xcb
{
	void screen::destroy_root_win() noexcept
	{ root_win.reset(); }

	screen::screen(xcb_screen_t *ptr, connection &conn_) noexcept
		: scrn{ptr}, conn{&conn_}, root_win{new window{scrn->root, *conn, *this}}
	{
	}

	screen &screen::operator=(assign_pair_t pair) noexcept
	{
		conn = &pair.second;
		scrn = pair.first;
		root_win.emplace(scrn->root, *conn, *this);
		return *this;
	}

	monitor_dimension screen::primary_monitor() const noexcept
	{
		monitor_dimension tmp{};
		xcb_randr_get_monitors_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_randr_get_monitors)(*conn, scrn->root, 0)};
		xcb_randr_get_monitors_reply_t *reply{GAL_XCB_REPLY_FUNCTION(*conn, xcb_randr_get_monitors_reply, cookie)};
		xcb_randr_monitor_info_iterator_t it{xcb_randr_get_monitors_monitors_iterator(reply)};
		std::size_t size{static_cast<std::size_t>(xcb_randr_get_monitors_monitors_length(reply))};
		for(std::size_t i{0}; i < size; ++i) {
			const xcb_randr_monitor_info_t &data{*(it.data)};
			if(!data.primary) {
				xcb_randr_monitor_info_next(&it);
				continue;
			}

			tmp.x = static_cast<std::size_t>(data.x);
			tmp.y = static_cast<std::size_t>(data.y);
			tmp.width = static_cast<std::size_t>(data.width);
			tmp.height = static_cast<std::size_t>(data.height);
			break;
		}
		delete reply;
		return tmp;
	}

	std::vector<monitor_info> screen::monitors() const noexcept
	{
		std::vector<monitor_info> tmp;
		xcb_randr_get_monitors_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_randr_get_monitors)(*conn, scrn->root, 0)};
		xcb_randr_get_monitors_reply_t *reply{GAL_XCB_REPLY_FUNCTION(*conn, xcb_randr_get_monitors_reply, cookie)};
		xcb_randr_monitor_info_iterator_t it{xcb_randr_get_monitors_monitors_iterator(reply)};
		std::size_t size{static_cast<std::size_t>(xcb_randr_get_monitors_monitors_length(reply))};
		for(std::size_t i{0}; i < size; ++i) {
			const xcb_randr_monitor_info_t &data{*(it.data)};
			monitor_info &info{tmp.emplace_back()};
			info.x = static_cast<std::size_t>(data.x);
			info.y = static_cast<std::size_t>(data.y);
			info.width = static_cast<std::size_t>(data.width);
			info.height = static_cast<std::size_t>(data.height);
			info.primary = static_cast<bool>(data.primary);
			class atom name_atom{data.name, *const_cast<connection *>(conn)};
			info.name = name_atom.string();
			xcb_randr_monitor_info_next(&it);
		}
		delete reply;
		return tmp;
	}
}
