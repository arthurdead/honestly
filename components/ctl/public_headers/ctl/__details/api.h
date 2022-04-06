#pragma once

#ifdef __CTL_IS_STATIC
	#define CTL_SHARED_API
	#define CTL_SHARED_API_CALL
#elif defined __CTL_IS_SHARED
	#include <cpa/compiler_builtins.h>

	#ifdef __COMPILING_CTL
		#define CTL_SHARED_API CPA_SHARED_EXPORT
	#else
		#define CTL_SHARED_API CPA_SHARED_IMPORT
	#endif
	#define CTL_SHARED_API_CALL CPA_SHARED_CALL
#else
	#error
#endif
