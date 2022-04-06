#pragma once

#include <ctl/version>

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/randr.h>
#include <xcb/render.h>
#include <xcb/xcb_renderutil.h>
#if CTL_DEBUG_LEVEL > 0
	#include <xcb/xcb_errors.h>
#endif
#include <unordered_map>

namespace xcb_ext
{
	namespace __private
	{
		template <typename T>
		struct member_hasher : public std::hash<std::size_t>
		{
			inline std::size_t operator()(const T &var) const noexcept
			{ return reinterpret_cast<std::size_t>(var); }
		};
	}

	#define __GAL_XCB_DECLARE_PARAM_TRAITS_BEGIN(type) \
		template <> \
		struct params_traits<type> \
		{ \
		private: \
			using __base = type; \
		public: \
			template <typename VB> \
			static std::uint32_t mask(VB __base::*var) noexcept \
			{ \
				using var_type = VB __base::*; \
				static std::unordered_map<var_type, std::uint32_t, __private::member_hasher<var_type>> mask_map{

	#define __GAL_XCB_DECLARE_MASK_VALUE(type, var, val) \
		std::pair<var_type, std::uint32_t>{&__base::var, val},

	#define __GAL_XCB_DECLARE_PARAM_TRAITS_END \
				}; \
				return mask_map[var]; \
			} \
		};

	template <typename T, typename VB, typename V>
	constexpr inline auto param(VB T::*var, V value) noexcept
	{ return std::pair<decltype(var), V>{var, value}; }

	#define GAL_XCB_PARAMS(type) \
		xcb_ext::params_wrapper<type>

	#define GAL_XCB_PARAM(var, value) \
		xcb_ext::param(var, value)

	template <typename T>
	struct params_traits;

	__GAL_XCB_DECLARE_PARAM_TRAITS_BEGIN(xcb_render_create_picture_value_list_t)
		__GAL_XCB_DECLARE_MASK_VALUE(xcb_render_cp_t, polyedge, XCB_RENDER_CP_POLY_EDGE)
		__GAL_XCB_DECLARE_MASK_VALUE(xcb_render_poly_mode_t, polymode, XCB_RENDER_CP_POLY_MODE)
	__GAL_XCB_DECLARE_PARAM_TRAITS_END

	__GAL_XCB_DECLARE_PARAM_TRAITS_BEGIN(xcb_create_window_value_list_t)
		__GAL_XCB_DECLARE_MASK_VALUE(std::uint32_t, background_pixel, XCB_CW_BACK_PIXEL)
		__GAL_XCB_DECLARE_MASK_VALUE(xcb_cw_t, event_mask, XCB_CW_EVENT_MASK)
	__GAL_XCB_DECLARE_PARAM_TRAITS_END

	__GAL_XCB_DECLARE_PARAM_TRAITS_BEGIN(xcb_create_gc_value_list_t)
		__GAL_XCB_DECLARE_MASK_VALUE(std::uint32_t, foreground, XCB_GC_FOREGROUND)
		__GAL_XCB_DECLARE_MASK_VALUE(bool, graphics_exposures, XCB_GC_GRAPHICS_EXPOSURES)
	__GAL_XCB_DECLARE_PARAM_TRAITS_END

	template <typename T>
	class CTL_LOCAL_CLASS params_wrapper : private T
	{
	public:
		inline params_wrapper() noexcept
			: T{}
		{
		}

		template <typename ...Args>
		inline params_wrapper(Args && ...args) noexcept
			: T{}
		{ (set(std::forward<Args>(args)), ...); }

		inline T *operator&() noexcept
		{ return static_cast<T *>(this); }
		inline operator T &() noexcept
		{ return static_cast<T &>(*this); }
		inline std::uint32_t mask() const noexcept
		{ return mask_; }

		template <typename VB, typename V>
		inline void set(VB T::*var, V value) noexcept
		{
			(this->*var) = static_cast<VB>(value);
			mask_ |= params_traits<T>::mask(var);
		}

	private:
		template <typename VB, typename V>
		inline void set(std::pair<VB T::*, V> pair) noexcept
		{
			(this->*pair.first) = static_cast<VB>(pair.second);
			mask_ |= params_traits<T>::mask(pair.first);
		}

		std::uint32_t mask_;
	};
}
