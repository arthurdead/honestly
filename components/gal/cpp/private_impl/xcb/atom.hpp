#pragma once

#include <ctl/version>
#include <ctl/string_view>
#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS connection;

	class CTL_LOCAL_CLASS atom final
	{
	public:
		atom() noexcept = default;
		atom(atom &&other) noexcept = default;
		atom &operator=(atom &&other) noexcept = default;

		atom(std::nullptr_t) noexcept
		{
		}

		inline atom(xcb_atom_t id_, connection &conn_) noexcept
			: id{id_}, conn{&conn_}
		{
		}

		using assign_pair_t = std::pair<xcb_atom_t, connection &>;
		atom &operator=(assign_pair_t pair) noexcept;

		inline atom &operator=(std::nullptr_t) noexcept
		{
			id = XCB_ATOM_NONE;
			conn = nullptr;
			return *this;
		}

		inline explicit operator bool() const noexcept
		{ return (id != XCB_ATOM_NONE); }

		inline operator xcb_atom_t() const noexcept
		{ return id; }
		inline const xcb_atom_t *operator&() const noexcept
		{ return &id; }
		inline xcb_atom_t *operator&() noexcept
		{ return &id; }

		std::string_view string() const noexcept;

	private:
		friend class connection;

		atom(const atom &) noexcept = delete;
		atom &operator=(const atom &) noexcept = delete;

		inline void reset() noexcept
		{
			id = XCB_ATOM_NONE;
			conn = nullptr;
		}

		xcb_atom_t id{XCB_ATOM_NONE};
		connection *conn{nullptr};
	};
}
