#include "glyph_set.hpp"
#include "window.hpp"
#include "pixmap.hpp"
#include <cmath>

namespace gal::xcb
{
	glyph_set::~glyph_set() noexcept
	{
		xcb_render_util_composite_text_free(stream);
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_free_glyph_set, id);
	}

	void glyph_set::render(const gal::window &win, std::size_t x, std::size_t y) noexcept
	{
		window &xcb_win{reinterpret_cast<window &>(win.impl.ref<__win::impl>())};
		
		//pixmap wtf{*conn, xcb_win.screen().root_window(), 1, 1, 8};
		//picture src{*conn, wtf, conn->picture_format_alpha8()};
		//render(x, y, src, xcb_win, XCB_RENDER_PICT_OP_ADD);
	}

	void glyph_set::render(std::size_t x, std::size_t y, const picture &src, const picture &dst, xcb_render_pict_op_t op) noexcept
	{
		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_util_composite_text, 
			op, src, dst,
			conn->picture_format_alpha8(),
			static_cast<std::int16_t>(x), static_cast<std::int16_t>(y),
			stream
		);
	}

	void glyph_set::load(__font::impl &base, const __font::shape_impl &shape_) noexcept
	{
		const std::size_t len{shape_.length()};

		stream = xcb_render_util_composite_text_stream(id, static_cast<std::uint32_t>(len), 0);

		double x{0.0};
		double y{0.0};

		for(std::size_t i{0}; i < len; ++i) {
			if(!load(base, shape_, i, x, y)) {
				//CTL_DEBUGTRAP;
			}
		}
	}

	bool glyph_set::load(__font::impl &base, const __font::shape_impl &shape_, std::size_t i, double &x, double &y) noexcept
	{
		const hb_codepoint_t c{shape_.codepoint(i)};

		if(!base.load_glyph(c)) {
			return false;
		}

		const std::size_t width{base.width()};
		const std::size_t rows{base.rows()};

		xcb_render_glyphinfo_t info{};
		info.width = static_cast<std::uint16_t>(width);
		info.height = static_cast<std::uint16_t>(rows);
		info.x = 0;
		info.y = static_cast<std::int16_t>(info.height - 36);
		info.x_off = 0;
		info.y_off = 0;

		if(info.width & 3) {
			info.width += (4 - (info.width & 3));
		}
		if(info.height & 3) {
			info.height += (4 - (info.height & 3));
		}

		const std::size_t buffer_len{static_cast<std::size_t>(info.width * info.height)};

		const std::uint8_t *old_buffer{base.buffer()};
		std::uint8_t *new_buffer{new std::uint8_t[buffer_len]};

		for(std::size_t xi{0}; xi < width; ++xi) {
			for(std::size_t yi{0}; yi < rows; ++yi) {
				new_buffer[yi * info.width + xi] = old_buffer[yi * width + xi];
			}
		}

		std::uint32_t c32{static_cast<std::uint32_t>(c)};
		std::uint8_t c8{static_cast<std::uint8_t>(c)};

		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_add_glyphs, 
			id,
			static_cast<std::uint32_t>(1),
			&c32, &info,
			static_cast<std::uint32_t>(buffer_len), new_buffer
		);

		delete[] new_buffer;

		const hb_glyph_position_t &pos{shape_.pos(i)};

		double newx{x + pos.x_offset / 64.0};
		double newy{y + pos.y_offset / 64.0};

		double deltax{std::round(newx + pos.x_offset / 64.0)};
		double deltay{std::round(-newy + pos.y_offset / 64.0)};

		x -= deltax;
		y -= deltay;

		xcb_render_util_glyphs_8(stream, static_cast<std::int16_t>(deltax), static_cast<std::int16_t>(deltay), 1, &c8);

		x += pos.x_advance / 64.0;
		y += pos.y_advance / 64.0;

		return true;
	}
}
