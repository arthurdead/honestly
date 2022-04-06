#pragma once

#include <ctl/version>

namespace gal::xcb
{
	class CTL_LOCAL_CLASS picture final
	{
	public:
		picture(picture &&) noexcept = default;
		picture &operator=(picture &&) noexcept = default;

		picture(connection &conn_, xcb_drawable_t draw, xcb_render_pictformat_t fmt, GAL_XCB_PARAMS(xcb_render_create_picture_value_list_t) params = {}) noexcept
			: conn{&conn_}, id{xcb_generate_id(*conn)}
		{
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_create_picture_aux, 
				id,
				draw, fmt,
				params.mask(), &params
			);
		}

		inline ~picture() noexcept
		{ GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_free_picture, id); }

		inline operator xcb_render_picture_t() const noexcept
		{ return id; }

		/*void rectangle(xcb_render_pict_op_t op, xcb_render_color_t clr, std::initializer_list<struct rectangle> values) noexcept
		{
			__GAL_XCB_PEN_CONVERT_RECT
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_fill_rectangles, 
				op,
				id,
				clr,
				static_cast<std::uint32_t>(size), tmp.data()
			);
		}*/

	private:
		picture() = delete;
		picture(const picture &) = delete;
		picture &operator=(const picture &) = delete;

		connection *conn;
		xcb_render_picture_t id;
	};
}
