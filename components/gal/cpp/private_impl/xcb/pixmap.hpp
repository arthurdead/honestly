#pragma once

#include <ctl/version>
#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS pixmap
	{
	public:
		pixmap(pixmap &&) noexcept = default;
		pixmap &operator=(pixmap &&) noexcept = default;

		inline pixmap(connection &conn_, xcb_drawable_t draw, std::size_t w, std::size_t h, std::size_t depth) noexcept
			: conn{&conn_}, id{xcb_generate_id(*conn)}
		{
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_create_pixmap, 
				static_cast<std::uint8_t>(depth),
				id,
				draw,
				static_cast<std::uint16_t>(w), static_cast<std::uint16_t>(h)
			);
		}
		inline ~pixmap() noexcept
		{ GAL_XCB_CHECKED_FUNCTION(*conn, xcb_free_pixmap, id); }

		inline operator xcb_pixmap_t() const noexcept
		{ return id; }

	private:
		pixmap() = delete;
		pixmap(const pixmap &) = delete;
		pixmap &operator=(const pixmap &) = delete;

		connection *conn;
		xcb_pixmap_t id;
	};
}
