#pragma once

#include <ctl/version>
#include <ctl/string_view>
#include <ctl/filesystem>
#include <ctl/optional>
#include <gal/font.hpp>
#include <gal/geometry.hpp>

#include "freetype2_fwd.hpp"
#include <harfbuzz/hb.h>
#include <fontconfig/fontconfig.h>

//#define __GAL_FREETYPE2_USE_CACHE

namespace gal
{
	class CTL_LOCAL_CLASS font_manager;

	class CTL_LOCAL_CLASS ucs4_string final
	{
	public:
		ucs4_string(std::string_view str) noexcept;

		inline ~ucs4_string() noexcept
		{ delete[] data; }

		inline std::size_t length() const noexcept
		{ return len; }

		inline const std::uint32_t *begin() const noexcept
		{ return cbegin(); }
		inline const std::uint32_t *end() const noexcept
		{ return cend(); }

		inline const std::uint32_t *cbegin() const noexcept
		{ return data; }
		inline const std::uint32_t *cend() const noexcept
		{ return (data + len); }

	private:
		std::uint32_t *data;
		std::size_t len;
	};

	namespace __font
	{
		class CTL_LOCAL_CLASS impl;

		class CTL_LOCAL_CLASS shape_impl final
		{
		public:
			inline shape_impl() noexcept
				: buffer{hb_buffer_create()}
			{
			}

			inline ~shape_impl() noexcept
			{ hb_buffer_destroy(buffer); }

			inline std::size_t length() const noexcept
			{ return len; }

			inline const hb_glyph_position_t &pos(std::size_t i) const noexcept
			{ return pos_[i]; }
			inline const hb_glyph_info_t &info(std::size_t i) const noexcept
			{ return infos[i]; }

			inline hb_codepoint_t codepoint(std::size_t i) const noexcept
			{ return infos[i].codepoint; }

			inline void add(std::string_view str) noexcept
			{ hb_buffer_add_utf8(buffer, str.data(), static_cast<int>(str.length()), 0, -1); }

			inline void cache() noexcept
			{
				hb_buffer_guess_segment_properties(buffer);

				std::uint32_t tmplen{0};
				infos = hb_buffer_get_glyph_infos(buffer, &tmplen);
				len = static_cast<std::size_t>(tmplen);

				pos_ = hb_buffer_get_glyph_positions(buffer, nullptr);
			}

		private:
			friend class impl;

			hb_buffer_t *buffer;
			hb_glyph_info_t *infos;
			hb_glyph_position_t *pos_;
			std::size_t len;
		};

		class CTL_LOCAL_CLASS impl final
		{
		public:
			impl(impl &&) noexcept = default;
			impl &operator=(impl &&) noexcept = default;
			~impl() noexcept;

			bool load_glyph(hb_codepoint_t c) noexcept;

			std::size_t width() const noexcept;
			std::size_t rows() const noexcept;
			const std::uint8_t *buffer() const noexcept;

			void shape(const shape_impl &shape) noexcept
			{ hb_shape(hb_f, shape.buffer, nullptr, 0); }

			impl(ctl::filesystem::path_view filepath, std::size_t index) noexcept;
		private:
			impl(const impl &) = delete;
			impl &operator=(const impl &) = delete;

		private:
			friend class ::gal::font_manager;

		#ifdef __GAL_FREETYPE2_USE_CACHE
			FTC_FaceID id;
		#endif
			FT_Face face;
			FT_CharMap cmap;
			std::size_t cmap_idx;
			hb_font_t *hb_f;
		};

		class CTL_LOCAL_CLASS glyphs_impl
		{
		public:
			virtual ~glyphs_impl() noexcept;

			#define __API_BRIDGE_INTERFACE
			#include "__private/glyphset_funcs.priv.gen.hpp"

			shape_impl *__shape;
		};

		using create_glyps_t = glyphs_impl *(*)(impl &, const shape_impl &);
	}

	class CTL_LOCAL_CLASS font_manager final
	{
	public:
		font_manager() noexcept;
		~font_manager() noexcept;

		struct font_info
		{
			std::filesystem::path filepath;
			std::size_t index;
		};

		std::optional<font_info> query(std::string_view query_) const noexcept;

		static void init() noexcept;
		static void shutdown() noexcept;

	private:
		friend class __font::impl;

		FT_Library f2_lib;
	#ifdef __GAL_FREETYPE2_USE_CACHE
		FTC_Manager f2_f_cache;
		FTC_CMapCache f2_fc_cache;
	#endif
		FcConfig *fcconfig;
	};
}
