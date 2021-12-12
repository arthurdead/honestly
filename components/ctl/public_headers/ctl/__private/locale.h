#pragma once

#if CTL_LIBC == CTL_LIBC_MUSL
	#include <locale.h>

using __locale_t = locale_t;
#endif
