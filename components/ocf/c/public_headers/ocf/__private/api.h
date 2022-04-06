#pragma once

#ifdef __OCF_IS_STATIC
	#define OCF_SHARED_API
	#define OCF_SHARED_API_CALL
#elif defined __OCF_IS_SHARED
	#include <cpa/compiler_builtins.h>

	#ifdef __COMPILING_OCF
		#define OCF_SHARED_API CPA_SHARED_EXPORT
	#else
		#define OCF_SHARED_API CPA_SHARED_IMPORT
	#endif
	#define OCF_SHARED_API_CALL CPA_SHARED_CALL
#else
	#error
#endif
