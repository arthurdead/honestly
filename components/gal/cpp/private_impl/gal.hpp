#pragma once

#include <ctl/version>
#include <gal/gal.hpp>
#include <gal/window.hpp>
#include <gal/__private/api.hpp>

//#include "window.hpp"
//#include "renderer.hpp"

namespace gal
{
	namespace __win
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl;
	}

	namespace __rndr
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl;
	}

	namespace __private
	{
		extern GAL_SHARED_API std::uintptr_t GAL_SHARED_API_CALL get_nat_win(__win::impl &win) noexcept;
		extern GAL_SHARED_API std::uintptr_t GAL_SHARED_API_CALL get_nat_conn(__win::impl &win) noexcept;

		extern GAL_SHARED_API __rndr::impl * GAL_SHARED_API_CALL create_rndr_impl(__win::impl &win) noexcept;

		extern GAL_SHARED_API window_backend GAL_SHARED_API_CALL get_win_backend() noexcept;
	}
}
