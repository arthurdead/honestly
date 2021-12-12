#pragma once

#include <ctl/version>

#ifdef __OSAL_IS_STATIC
	#define OSAL_SHARED_API
	#define OSAL_SHARED_API_CALL
#elif defined __OSAL_IS_SHARED
	#ifdef __COMPILING_OSAL
		#define OSAL_SHARED_API CTL_SHARED_EXPORT
	#else
		#define OSAL_SHARED_API CTL_SHARED_IMPORT
	#endif
	#define OSAL_SHARED_API_CALL CTL_SHARED_CALL
#else
	#error
#endif

#if defined __COMPILING_OSAL || defined __OSAL_ENABLE_COMMENTS
	#define OSAL_COMMENT(text) CTL_COMMENT(text)
#else
	#define OSAL_COMMENT(text)
#endif
