#include "graphic_context.hpp"

namespace gal::xcb
{
	graphic_context::graphic_context(connection &conn_, xcb_drawable_t draw_, GAL_XCB_PARAMS(xcb_create_gc_value_list_t) params) noexcept
		: conn{&conn_}, id{xcb_generate_id(*conn)}, draw{draw_}
	{
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_create_gc_aux, 
			id,
			draw,
			params.mask(), &params
		);
	}

	#define __GAL_XCB_GC_CONVERT_POINT \
		const std::size_t size{values.size()}; \
		std::vector<xcb_point_t> tmp; \
		tmp.resize(values.size()); \
		const struct point *valdata{std::data(values)}; \
		for(std::size_t i{0}; i < size; ++i) { \
			tmp[i].x = static_cast<std::int16_t>(valdata[i].x); \
			tmp[i].y = static_cast<std::int16_t>(valdata[i].y); \
		}

	#define __GAL_XCB_GC_CONVERT_RECT \
		const std::size_t size{values.size()}; \
		std::vector<xcb_rectangle_t> tmp; \
		tmp.resize(values.size()); \
		const struct rectangle *valdata{std::data(values)}; \
		for(std::size_t i{0}; i < size; ++i) { \
			tmp[i].x = static_cast<std::int16_t>(valdata[i].x); \
			tmp[i].y = static_cast<std::int16_t>(valdata[i].y); \
			tmp[i].width = static_cast<std::uint16_t>(valdata[i].width); \
			tmp[i].height = static_cast<std::uint16_t>(valdata[i].height); \
		}

	#define __GAL_XCB_GC_CONVERT_SEG \
		const std::size_t size{values.size()}; \
		std::vector<xcb_segment_t> tmp; \
		tmp.resize(values.size()); \
		const struct segment *valdata{std::data(values)}; \
		for(std::size_t i{0}; i < size; ++i) { \
			tmp[i].x1 = static_cast<std::int16_t>(valdata[i].x[0]); \
			tmp[i].x2 = static_cast<std::int16_t>(valdata[i].x[1]); \
			tmp[i].y1 = static_cast<std::int16_t>(valdata[i].y[0]); \
			tmp[i].y2 = static_cast<std::int16_t>(valdata[i].y[1]); \
		}

	#define __GAL_XCB_GC_CONVERT_ARC \
		const std::size_t size{values.size()}; \
		std::vector<xcb_arc_t> tmp; \
		tmp.resize(values.size()); \
		const struct arc *valdata{std::data(values)}; \
		for(std::size_t i{0}; i < size; ++i) { \
			tmp[i].x = static_cast<std::int16_t>(valdata[i].x); \
			tmp[i].y = static_cast<std::int16_t>(valdata[i].y); \
			tmp[i].width = static_cast<std::uint16_t>(valdata[i].width); \
			tmp[i].height = static_cast<std::uint16_t>(valdata[i].height); \
			tmp[i].angle1 = static_cast<std::int16_t>(valdata[i].angle[0]); \
			tmp[i].angle2 = static_cast<std::int16_t>(valdata[i].angle[1]); \
		}

	void graphic_context::point(std::initializer_list<struct point> values, bool relative) noexcept
	{
		__GAL_XCB_GC_CONVERT_POINT
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_poly_point, 
			relative ?
				XCB_COORD_MODE_PREVIOUS
			:
				XCB_COORD_MODE_ORIGIN,
			draw, id,
			static_cast<std::uint32_t>(size), tmp.data()
		);
	}

	void graphic_context::line(std::initializer_list<struct point> values, bool relative) noexcept
	{
		__GAL_XCB_GC_CONVERT_POINT
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_poly_line, 
			relative ?
				XCB_COORD_MODE_PREVIOUS
			:
				XCB_COORD_MODE_ORIGIN,
			draw, id,
			static_cast<std::uint32_t>(size), tmp.data()
		);
	}

	void graphic_context::rectangle(std::initializer_list<struct rectangle> values, bool filled) noexcept
	{
		__GAL_XCB_GC_CONVERT_RECT
		auto func = filled ? xcb_poly_fill_rectangle : xcb_poly_rectangle;
		GAL_XCB_CHECKED_FUNCTION_PTR(*conn, func, 
			draw, id,
			static_cast<std::uint32_t>(size), tmp.data()
		);
	}

	void graphic_context::segment(std::initializer_list<struct segment> values) noexcept
	{
		__GAL_XCB_GC_CONVERT_SEG
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_poly_segment, 
			draw, id,
			static_cast<std::uint32_t>(size), tmp.data()
		);
	}

	void graphic_context::arc(std::initializer_list<struct arc> values, bool filled) noexcept
	{
		__GAL_XCB_GC_CONVERT_ARC
		auto func = filled ? xcb_poly_fill_arc : xcb_poly_arc;
		GAL_XCB_CHECKED_FUNCTION_PTR(*conn, func, 
			draw, id,
			static_cast<std::uint32_t>(size), tmp.data()
		);
	}

	void graphic_context::fill(std::initializer_list<struct point> values, shape_type type, bool relative) noexcept
	{
		xcb_poly_shape_t shape{};

		switch(type) {
			case shape_type::complex:
			{ shape = XCB_POLY_SHAPE_COMPLEX; break; }
			case shape_type::convex:
			{ shape = XCB_POLY_SHAPE_CONVEX; break; }
			case shape_type::non_convex:
			{ shape = XCB_POLY_SHAPE_NONCONVEX; break; }
		}

		__GAL_XCB_GC_CONVERT_POINT
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_fill_poly, 
			draw, id,
			shape,
			relative ?
				XCB_COORD_MODE_PREVIOUS
			:
				XCB_COORD_MODE_ORIGIN,
			static_cast<std::uint32_t>(size), tmp.data()
		);
	}
}
