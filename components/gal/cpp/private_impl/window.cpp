#include <gal/window.hpp>
#include "window.hpp"

namespace gal
{
	namespace __win
	{
		impl::~impl() noexcept
		{
		}

		extern create_impl_t create_impl;
	}

	namespace __pen
	{
		impl::~impl() noexcept
		{
		}
	}

	namespace __rndr
	{
		extern bool initalized;
	}

	GAL_SHARED_API GAL_SHARED_API_CALL pen::pen(window &win) noexcept
		: impl{win.impl.ref<__win::impl>().create_pen()}
	{

	}

	GAL_SHARED_API GAL_SHARED_API_CALL window::window(absolute_rectangle rect) noexcept
		: impl{__win::create_impl(*this, rect)}
	{
		if(__rndr::initalized) {
			impl.ref<__win::impl>().create_renderer();
		}
	}

	window::~window() noexcept
	{
	}

	#define __API_BRIDGE_IMPLEMENTATION
	#include "__private/pen_funcs.priv.gen.hpp"
}
