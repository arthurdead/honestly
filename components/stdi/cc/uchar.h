#pragma once

#include <cpa/compilers.h>

#define __STDI_INCLUDE_NEXT_HEADER <uchar.h>
#include "__details/include_next.h"

#ifndef __STDI_UCHAR_H
	#include "version"

	#if STDI_CXX_STDLIB == STDI_STDLIB_LIBCPP
		#define STDI_UCHAR_MB_UNSUPPORTED
	#endif
#define __STDI_UCHAR_H
#endif
