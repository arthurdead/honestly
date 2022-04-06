#pragma once

#include <cpa/compilers.h>

#define __STDI_INCLUDE_NEXT_HEADER <stdio.h>
#include "__details/include_next.h"

#ifndef __STDI_STDIO_H
	#include "features.h"

	#if STDI_C_STDLIB == STDI_STDLIB_MUSL
		#undef stdin
		#undef stdout
		#undef stderr
	#endif
#define __STDI_STDIO_H
#endif
