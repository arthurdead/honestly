#include "freetype2.hpp"
#include <harfbuzz/hb-ft.h>
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
		std::size_t impl::width() const noexcept
		{ return static_cast<std::size_t>(face->glyph->bitmap.width); }
		std::size_t impl::rows() const noexcept
		{ return static_cast<std::size_t>(face->glyph->bitmap.rows); }
		const std::uint8_t *impl::buffer() const noexcept
		{ return reinterpret_cast<const std::uint8_t *>(face->glyph->bitmap.buffer); }

		CTL_GLOBAL_CTOR_BEGIN
		static ctl::unique_ptr<font_manager> mgr;
		CTL_GLOBAL_CTOR_END

		impl::impl(ctl::filesystem::path_view filepath, std::size_t index) noexcept
		#ifdef __GAL_FREETYPE2_USE_CACHE
			: id{reinterpret_cast<FTC_FaceID>(this)}
		#endif
		{
			FT_New_Face(__font::mgr->f2_lib, filepath.c_str(), static_cast<FT_Long>(index), &face);

			FT_Select_Charmap(face, FT_Encoding::FT_ENCODING_UNICODE);
			cmap = face->charmap;
			cmap_idx = static_cast<std::size_t>(FT_Get_Charmap_Index(cmap));
		
		#ifndef __GAL_FREETYPE2_USE_CACHE
			FT_Set_Char_Size(face, 32*64, 32*64, 0, 0);
		#else
			#error
		#endif

			hb_f = hb_ft_font_create_referenced(face);
		}

		impl::~impl() noexcept
		{
			hb_font_destroy(hb_f);
		#ifdef __GAL_FREETYPE2_USE_CACHE
			FTC_Manager_RemoveFaceID(__font::mgr->f2_f_cache, id);
		#endif
			FT_Done_Face(face);
		}

		bool impl::load_glyph(hb_codepoint_t c) noexcept
		{
			FT_UInt idx{
			#ifdef __GAL_FREETYPE2_USE_CACHE
				FTC_CMapCache_Lookup(__font::mgr->f2_fc_cache, id, static_cast<FT_Int>(cmap_idx), static_cast<FT_UInt>(c))
			#else
				FT_Get_Char_Index(face, static_cast<FT_ULong>(c))
			#endif
			};
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

		glyphs_impl::~glyphs_impl() noexcept
		{
			delete __shape;
		}

		extern create_glyps_t create_glyph_set;
	}

	GAL_SHARED_API glyph_set GAL_SHARED_API_CALL font::compose(std::string_view str) noexcept
	{
		__font::impl &data{impl.ref<__font::impl>()};

		__font::shape_impl *shape_data{new __font::shape_impl{}};
		shape_data->add(str);
		shape_data->cache();

		data.shape(*shape_data);

		glyph_set ret;

		__font::glyphs_impl *glyphs{__font::create_glyph_set(data, *shape_data)};
		glyphs->__shape = shape_data;

		ret.impl.reset<__font::glyphs_impl>(glyphs);

		return ret;
	}

	void font_manager::init() noexcept
	{
		__font::mgr.emplace();
	}

	void font_manager::shutdown() noexcept
	{
		__font::mgr.reset();
	}

#ifdef __GAL_FREETYPE2_USE_CACHE
	namespace __font
	{
		static FT_Error f2requester(FTC_FaceID face_id, FT_Library library, FT_Pointer req_data, FT_Face *face) noexcept
		{
			*face = reinterpret_cast<FT_Face>(face_id);
			return FT_Err_Ok;
		}
	}
#endif

	font_manager::font_manager() noexcept
	{
		FcInit();
		FT_Init_FreeType(&f2_lib);
	#ifdef __GAL_FREETYPE2_USE_CACHE
		FTC_Manager_New(f2_lib, ~0u, ~0u, ~0u, reinterpret_cast<FTC_Face_Requester>(__font::f2requester), nullptr, &f2_f_cache);
		FTC_CMapCache_New(f2_f_cache, &f2_fc_cache);
	#endif
		fcconfig = FcConfigGetCurrent();
	}

	font_manager::~font_manager() noexcept
	{
	#ifdef __GAL_FREETYPE2_USE_CACHE
		FTC_Manager_Done(f2_f_cache);
	#endif
		FT_Done_FreeType(f2_lib);
		FcFini();
	}

	std::optional<font_manager::font_info> font_manager::query(std::string_view query_) const noexcept
	{
		std::optional<font_info> ret{std::nullopt};
		FcPattern *find_patt{FcNameParse(reinterpret_cast<const FcChar8 *>(query_.data()))};
		FcDefaultSubstitute(find_patt);
		FcConfigSubstitute(fcconfig, find_patt, FcMatchPattern);
		FcResult result;
		FcPattern *found_patt{FcFontMatch(fcconfig, find_patt, &result)};
		switch(result) {
			case FcResult::FcResultMatch: {
				FcValue file_value{};
				FcPatternGet(found_patt, FC_FILE, 0, &file_value);
				const char *file_path{reinterpret_cast<const char *>(file_value.u.s)};
				FcValue face_value{};
				FcPatternGet(found_patt, FC_INDEX, 0, &face_value);
				font_info &info{ret.emplace()};
				info.filepath = std::string_view{file_path};
				info.index = static_cast<std::size_t>(face_value.u.i);
				break;
			}
		}
		FcPatternDestroy(found_patt);
		FcPatternDestroy(find_patt);
		return ret;
	}

	GAL_SHARED_API std::optional<font> GAL_SHARED_API_CALL query_font(std::string_view query) noexcept
	{
		std::optional<font_manager::font_info> ret{__font::mgr->query(query)};
		if(!ret) {
			return std::nullopt;
		}

		font_manager::font_info info{ret.value()};

		font tmp;
		tmp.impl.emplace<__font::impl>(std::move(info.filepath), info.index);

		return std::make_optional(std::move(tmp));
	}

	#define __API_BRIDGE_IMPLEMENTATION
	#include "__private/glyphset_funcs.priv.gen.hpp"
}
