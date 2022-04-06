#pragma once

#include <ctl/version>
#include "../font.hpp"
#include "connection.hpp"
#include "xcb.hpp"
#include "picture.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS glyph_set final : public __font::glyphs_impl
	{
	public:
		glyph_set(glyph_set &&) noexcept = default;
		glyph_set &operator=(glyph_set &&) noexcept = default;

		inline glyph_set(connection &conn_, __font::impl &font, const __font::shape_impl &shape_) noexcept
			: conn{&conn_}, id{xcb_generate_id(*conn)}
		{
			GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_create_glyph_set, 
				id, conn->picture_format_alpha8()
			);

			load(font, shape_);
		}

		~glyph_set() noexcept override final;

		#define __API_BRIDGE_DECLARATION
		#include "../__private/glyphset_funcs.priv.gen.hpp"

		void render(std::size_t x, std::size_t y, const picture &src, const picture &dst, xcb_render_pict_op_t op) noexcept;

	private:
		friend class font;

		glyph_set() = delete;
		glyph_set(const glyph_set &) = delete;
		glyph_set &operator=(const glyph_set &) = delete;

		void load(__font::impl &base, const __font::shape_impl &shape_) noexcept;

		bool load(__font::impl &base, const __font::shape_impl &shape_, std::size_t i, double &x, double &y) noexcept;

		connection *conn;
		xcb_render_glyphset_t id;
		xcb_render_util_composite_text_stream_t *stream;
	};
}
