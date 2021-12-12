#pragma once

#include <ctl/version>

#ifdef __GAL_IS_STATIC
	#define GAL_SHARED_API
	#define GAL_SHARED_API_CALL
#elif defined __GAL_IS_SHARED
	#ifdef __COMPILING_GAL
		#define GAL_SHARED_API CTL_SHARED_EXPORT
	#else
		#define GAL_SHARED_API CTL_SHARED_IMPORT
	#endif
	#define GAL_SHARED_API_CALL CTL_SHARED_CALL
#else
	#error
#endif

#if defined __COMPILING_GAL || defined __COMPILING_GAL_INTERNAL_MODULE
	#define __GAL_PRIVATE public
	#define __GAL_DELETE default
#else
	#define __GAL_PRIVATE private
	#define __GAL_DELETE delete
#endif
