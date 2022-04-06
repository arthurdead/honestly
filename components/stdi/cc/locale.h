#pragma once

#include <cpa/compilers.h>

#define __STDI_INCLUDE_NEXT_HEADER <locale.h>
#include "__details/include_next.h"

#ifndef __STDI_STDIO_H
	#include "features.h"

	#if STDI_C_STDLIB == STDI_STDLIB_MUSL
typedef locale_t __locale_t;
	#endif
#define __STDI_STDIO_H
#endif
