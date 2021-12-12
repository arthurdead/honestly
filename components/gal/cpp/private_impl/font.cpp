#include "freetype2.hpp"
#include "font.hpp"
#include <ctl/memory>

namespace gal
{
	ucs4_string::ucs4_string(std::string_view str) noexcept
	{
		const std::size_t olen{str.length()};

		data = new std::uint32_t[olen];

		std::size_t shift{0};
		while(true) {
			const char &c{str[shift]};
			if(c == '\0') {
				break;
			}

			shift += static_cast<std::size_t>(FcUtf8ToUcs4(reinterpret_cast<const FcChar8 *>(&c), reinterpret_cast<FcChar32 *>(&data[len]), static_cast<int>(olen-shift)));

			++len;
		}
	}

	namespace __font
	{
		std::size_t impl::left() const noexcept
		{ return static_cast<std::size_t>(face->glyph->bitmap_left); }
		std::size_t impl::top() const noexcept
		{ return static_cast<std::size_t>(face->glyph->bitmap_top); }
		std::size_t impl::width() const noexcept
		{ return static_cast<std::size_t>(face->glyph->metrics.width); }
		std::size_t impl::height() const noexcept
		{ return static_cast<std::size_t>(face->glyph->metrics.height); }
		absolute_point impl::advance() const noexcept
		{ return absolute_point{static_cast<std::size_t>(face->glyph->advance.x), static_cast<std::size_t>(face->glyph->advance.y)}; }
		const std::uint8_t *impl::data() const noexcept
		{ return reinterpret_cast<const std::uint8_t *>(face->glyph->bitmap.buffer); }

		CTL_GLOBAL_CTOR_BEGIN
		static ctl::unique_ptr<font_manager> mgr;
		CTL_GLOBAL_CTOR_END

		impl::impl(FT_Face face_) noexcept
			: id{reinterpret_cast<FTC_FaceID>(this)}, face{face_}
		{
			FT_Select_Charmap(face, FT_Encoding::FT_ENCODING_UNICODE);
			cmap = face->charmap;
			cmap_idx = static_cast<std::size_t>(FT_Get_Charmap_Index(cmap));
		}

		impl::~impl() noexcept
		{
			FTC_Manager_RemoveFaceID(__font::mgr->f2_f_cache, id);
			FT_Done_Face(face);
		}

		bool impl::load_glyph(char32_t c) noexcept
		{
			FT_UInt idx{FTC_CMapCache_Lookup(__font::mgr->f2_fc_cache, id, static_cast<FT_Int>(cmap_idx), static_cast<FT_UInt>(c))};
			if(idx == 0) {
				return false;
			}

			std::size_t flags{FT_LOAD_RENDER
			#if CTL_DEBUG_LEVEL > 0
				|FT_LOAD_PEDANTIC
			#endif
			};

			if((0)) {
				flags |= FT_LOAD_COLOR;
			} else {
				flags |= FT_LOAD_MONOCHROME;
			}

			if((0)) {
				flags |= FT_LOAD_NO_HINTING|FT_LOAD_NO_AUTOHINT;
			} else if((0)) {
				flags |= FT_LOAD_FORCE_AUTOHINT;
			}

			FT_Load_Glyph(face, idx, static_cast<FT_Int32>(flags));
			return true;
		}
	}

	void font_manager::init() noexcept
	{
		__font::mgr.emplace();
	}

	void font_manager::shutdown() noexcept
	{
		__font::mgr.reset();
	}

	namespace __font
	{
		static FT_Error f2requester(FTC_FaceID face_id, FT_Library library, FT_Pointer req_data, FT_Face *face) noexcept
		{
			*face = reinterpret_cast<FT_Face>(face_id);
			return FT_Err_Ok;
		}
	}

	font_manager::font_manager() noexcept
	{
		FcInit();
		FT_Init_FreeType(&f2_lib);
		FTC_Manager_New(f2_lib, ~0u, ~0u, ~0u, reinterpret_cast<FTC_Face_Requester>(__font::f2requester), nullptr, &f2_f_cache);
		FTC_CMapCache_New(f2_f_cache, &f2_fc_cache);
		fcconfig = FcConfigGetCurrent();
	}

	font_manager::~font_manager() noexcept
	{
		FTC_Manager_Done(f2_f_cache);
		FT_Done_FreeType(f2_lib);
		FcFini();
	}

	std::optional<__font::impl> font_manager::query(std::string_view query_) const noexcept
	{
		std::optional<__font::impl> ret{std::nullopt};
		FcPattern *find_patt{FcNameParse(reinterpret_cast<const FcChar8 *>(query_.data()))};
		FcDefaultSubstitute(find_patt);
		FcConfigSubstitute(fcconfig, find_patt, FcMatchPattern);
		FcResult result;
		FcPattern *found_patt{FcFontMatch(fcconfig, find_patt, &result)};
		switch(result) {
			case FcResult::FcResultMatch: {
				FcValue file_value;
				FcPatternGet(found_patt, FC_FILE, 0, &file_value);
				FcValue face_value;
				FcPatternGet(found_patt, FC_FILE, 0, &face_value);
				const char *file_path{reinterpret_cast<const char *>(file_value.u.s)};
				FT_Face face;
				FT_New_Face(f2_lib, file_path, face_value.u.i, &face);
				ret.emplace(__font::impl{face});
				break;
			}
		}
		FcPatternDestroy(found_patt);
		FcPatternDestroy(find_patt);
		return ret;
	}

	GAL_SHARED_API std::optional<font> GAL_SHARED_API_CALL query_font(std::string_view query) noexcept
	{
		std::optional<__font::impl> ret{__font::mgr->query(query)};
		if(!ret) {
			return std::nullopt;
		}

		font tmp;
		tmp.impl.emplace<__font::impl>(std::move(ret.value()));

		return std::make_optional(std::move(tmp));
	}
}
