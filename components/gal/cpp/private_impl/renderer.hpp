#pragma once

#include <ctl/version>

#include "window.hpp"

namespace gal
{
	namespace __win
	{
		class CTL_LOCAL_CLASS impl;
	}

	namespace __rndr
	{
		class CTL_LOCAL_CLASS impl
		{
		public:
			virtual ~impl() noexcept;
		};
	}
}
