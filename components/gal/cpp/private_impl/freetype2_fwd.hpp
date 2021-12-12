#pragma once

#define __GAL_FWD_FREETYPE2_HANDLE(x) \
	struct x##Rec_; \
	using x = x##Rec_ *;

using FT_Pointer = void *;

using FT_UInt = std::uint32_t;
using FTC_FaceID = FT_Pointer;

__GAL_FWD_FREETYPE2_HANDLE(FT_Face)
__GAL_FWD_FREETYPE2_HANDLE(FT_CharMap)
__GAL_FWD_FREETYPE2_HANDLE(FT_Library)
__GAL_FWD_FREETYPE2_HANDLE(FTC_Manager)
__GAL_FWD_FREETYPE2_HANDLE(FTC_CMapCache)
