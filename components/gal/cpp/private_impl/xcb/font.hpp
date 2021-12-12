#pragma once

#include <ctl/version>
#include "../font.hpp"
#include "connection.hpp"
#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS font final
	{
	public:
		inline font(connection &conn_, __font::impl &base_, xcb_render_pictformat_t fmt_) noexcept
			: conn{&conn_}, base{base_}, fmt{fmt_}
		{
		}

		class CTL_LOCAL_CLASS glyph_set final
		{
		public:
			glyph_set(glyph_set &&) noexcept = default;
			glyph_set &operator=(glyph_set &&) noexcept = default;

			inline glyph_set(connection &conn_, xcb_render_pictformat_t fmt) noexcept
				: conn{&conn_}, id{xcb_generate_id(*conn)}
			{ GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_create_glyph_set, id, fmt); }
			inline ~glyph_set() noexcept
			{
				xcb_render_util_composite_text_free(stream);
				GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_free_glyph_set, id);
			}

		private:
			glyph_set() = delete;
			glyph_set(const glyph_set &) = delete;
			glyph_set &operator=(const glyph_set &) = delete;

			void load(__font::impl &base, std::string_view str) noexcept;

			bool load(__font::impl &base, char32_t c) noexcept;
			inline bool load(__font::impl *base, char c) noexcept
			{ return load(base, static_cast<char32_t>(c)); }

			connection *conn;
			xcb_render_glyphset_t id;
			xcb_render_util_composite_text_stream_t *stream;
		};

		inline glyph_set compose(std::string_view str) noexcept
		{
			glyph_set ret{*conn, fmt};
			ret.load(*base, str);
			return ret;
		}

	private:
		connection *conn;
		__font::impl *base;
		xcb_render_pictformat_t fmt;
	};
}
