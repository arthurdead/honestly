#pragma once

#ifdef __OSAL_IS_STATIC
	#define OSAL_SHARED_API
	#define OSAL_SHARED_API_CALL
#elif defined __OSAL_IS_SHARED
	#include <cpa/compiler_builtins.h>

	#ifdef __COMPILING_OSAL
		#define OSAL_SHARED_API CPA_SHARED_EXPORT
	#else
		#define OSAL_SHARED_API CPA_SHARED_IMPORT
	#endif
	#define OSAL_SHARED_API_CALL CPA_SHARED_CALL
#else
	#error
#endif
