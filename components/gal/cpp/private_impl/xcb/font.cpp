#include "font.hpp"
#include <cstring>

namespace gal::xcb
{
	void font::glyph_set::load(__font::impl &base, std::string_view str) noexcept
	{
		for(char c : str) {
			if(!load(base, c)) {
				CTL_DEBUGTRAP;
			}
		}

		stream = xcb_render_util_composite_text_stream(id, static_cast<std::uint32_t>(str.length()), 0);
	}

	bool font::glyph_set::load(__font::impl &base, char32_t c) noexcept
	{
		if(!base.load_glyph(c)) {
			return false;
		}

		xcb_render_glyphinfo_t info{};
		info.x = static_cast<std::int16_t>(-base.left());
		info.y = static_cast<std::int16_t>(base.top());
		info.width = static_cast<std::uint16_t>(base.width());
		info.height = static_cast<std::uint16_t>(base.height());
		const absolute_point advance{base.advance()};
		info.x_off = static_cast<std::int16_t>(advance.x/64);
		info.y_off = static_cast<std::int16_t>(advance.y/64);

		const std::size_t stride{static_cast<std::size_t>((info.width + 3) & ~3)};
		const std::size_t data_len{static_cast<std::size_t>(stride * info.height)};

		std::uint8_t *data{new std::uint8_t[data_len]};
		for(std::size_t i{0}; i < info.height; ++i) {
			std::memcpy(data + i * stride, base.data() + i * info.width, info.width);
		}

		std::uint32_t c_u32{static_cast<std::uint32_t>(c)};

		GAL_XCB_CHECKED_FUNCTION(*conn, xcb_render_add_glyphs, 
			id,
			static_cast<std::uint32_t>(1),
			&c_u32, &info,
			static_cast<std::uint32_t>(data_len), data
		);

		delete[] data;

		return true;
	}
}
