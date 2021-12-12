#pragma once

#ifdef __CTL_IS_STATIC
	#define CTL_SHARED_API
	#define CTL_SHARED_API_CALL
#elif defined __CTL_IS_SHARED
	#ifdef __COMPILING_CTL
		#define CTL_SHARED_API CTL_SHARED_EXPORT
	#else
		#define CTL_SHARED_API CTL_SHARED_IMPORT
	#endif
	#define CTL_SHARED_API_CALL CTL_SHARED_CALL
#else
	#error
#endif
