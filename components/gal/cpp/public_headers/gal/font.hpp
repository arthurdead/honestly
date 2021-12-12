#pragma once

#include <ctl/version>
#include <ctl/optional>
#include <ctl/memory>
#include "__private/api.hpp"

namespace gal
{
	class CTL_LOCAL_CLASS font
	{
	public:
		font(font &&) noexcept = default;
		font &operator=(font &&) noexcept = default;

	private:
		font(const font &) = delete;
		font &operator=(const font &) = delete;

	__GAL_PRIVATE:
		font() noexcept = __GAL_DELETE;

		ctl::unique_ptr_opaque impl;
	};

	extern GAL_SHARED_API std::optional<font> GAL_SHARED_API_CALL query_font(std::string_view query) noexcept;

	class CTL_LOCAL_CLASS glyph_set
	{
	public:
		glyph_set(glyph_set &&) noexcept = default;
		glyph_set &operator=(glyph_set &&) noexcept = default;

		GAL_SHARED_API GAL_SHARED_API_CALL glyph_set(const font &fnt, std::string_view text) noexcept;

	private:
		glyph_set(const glyph_set &) = delete;
		glyph_set &operator=(const glyph_set &) = delete;

	__GAL_PRIVATE:
		glyph_set() noexcept = __GAL_DELETE;

		ctl::unique_ptr_opaque impl;
	};
}
