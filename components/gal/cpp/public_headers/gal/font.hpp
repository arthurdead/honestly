#pragma once

#include <ctl/version>
#include <ctl/optional>
#include <ctl/memory>
#include "window.hpp"
#include "__private/api.hpp"

namespace gal
{
	class CTL_LOCAL_CLASS glyph_set final
	{
	public:
		glyph_set(glyph_set &&) noexcept = default;
		glyph_set &operator=(glyph_set &&) noexcept = default;

		#include "__private/glyphset_funcs.pub.gen.hpp"

	private:
		glyph_set(const glyph_set &) = delete;
		glyph_set &operator=(const glyph_set &) = delete;

	__GAL_PRIVATE:
		glyph_set() noexcept = __GAL_DELETE;

		ctl::unique_ptr_opaque impl;
	};

	class CTL_LOCAL_CLASS font
	{
	public:
		font(font &&) noexcept = default;
		font &operator=(font &&) noexcept = default;

		GAL_SHARED_API glyph_set GAL_SHARED_API_CALL compose(std::string_view str) noexcept;

	private:
		font(const font &) = delete;
		font &operator=(const font &) = delete;

	__GAL_PRIVATE:
		font() noexcept = __GAL_DELETE;

		ctl::unique_ptr_opaque impl;
	};

	extern GAL_SHARED_API std::optional<font> GAL_SHARED_API_CALL query_font(std::string_view query) noexcept;
}
