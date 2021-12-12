#include "atom.hpp"
#include "connection.hpp"

namespace gal::xcb
{
	std::string_view atom::string() const noexcept
	{
		xcb_get_atom_name_cookie_t cookie{GAL_XCB_UNCHECKED(xcb_get_atom_name)(*conn, id)};
		const xcb_get_atom_name_reply_t *reply{GAL_XCB_REPLY_FUNCTION(*conn, xcb_get_atom_name_reply, cookie)};
		int len{xcb_get_atom_name_name_length(reply)};
		const char *name{xcb_get_atom_name_name(reply)};
		delete reply;
		return std::string_view{name, static_cast<std::size_t>(len)};
	}

	atom &atom::operator=(assign_pair_t pair) noexcept
	{
		id = pair.first;
		conn = &pair.second;
		return *this;
	}
}
