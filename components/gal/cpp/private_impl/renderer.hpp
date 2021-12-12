#pragma once

#include <ctl/version>

#include "window.hpp"

namespace gal
{
	namespace __win
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl;
	}

	namespace __rndr
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl
		{
		public:
			virtual ~impl() noexcept;
		};
	}
}
