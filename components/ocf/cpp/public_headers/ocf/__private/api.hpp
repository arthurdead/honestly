#pragma once

#include <ctl/version>

#ifdef __OCF_IS_STATIC
	#define OCF_SHARED_API
	#define OCF_SHARED_API_CALL
#elif defined __OCF_IS_SHARED
	#ifdef __COMPILING_OCF
		#define OCF_SHARED_API CTL_SHARED_EXPORT
	#else
		#define OCF_SHARED_API CTL_SHARED_IMPORT
	#endif
	#define OCF_SHARED_API_CALL CTL_SHARED_CALL
#else
	#error
#endif
