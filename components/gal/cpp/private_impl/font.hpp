#pragma once

#include <ctl/version>
#include <ctl/string_view>
#include <ctl/filesystem>
#include <ctl/optional>
#include <gal/font.hpp>
#include <gal/geometry.hpp>

#include "freetype2_fwd.hpp"
#include <fontconfig/fontconfig.h>

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
		class CTL_LOCAL_CLASS impl final
		{
		public:
			impl(impl &&) noexcept = default;
			impl &operator=(impl &&) noexcept = default;
			~impl() noexcept;

			bool load_glyph(char32_t c) noexcept;
			inline bool load_glyph(char c) noexcept
			{ return load_glyph(static_cast<char32_t>(c)); }

			std::size_t left() const noexcept;
			std::size_t top() const noexcept;
			std::size_t width() const noexcept;
			std::size_t height() const noexcept;
			absolute_point advance() const noexcept;
			const std::uint8_t *data() const noexcept;

		private:
			impl(const impl &) = delete;
			impl &operator=(const impl &) = delete;

		protected:
			impl(FT_Face face_) noexcept;

		private:
			friend class ::gal::font_manager;

			FTC_FaceID id;
			FT_Face face;
			FT_CharMap cmap;
			std::size_t cmap_idx;
		};
	}

	class CTL_LOCAL_CLASS font_manager final
	{
	public:
		font_manager() noexcept;
		~font_manager() noexcept;

		std::optional<__font::impl> query(std::string_view query_) const noexcept;

		static void init() noexcept;
		static void shutdown() noexcept;

	private:
		friend class __font::impl;

		FT_Library f2_lib;
		FTC_Manager f2_f_cache;
		FTC_CMapCache f2_fc_cache;
		FcConfig *fcconfig;
	};
}
