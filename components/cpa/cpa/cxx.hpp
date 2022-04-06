#pragma once

#define CPA_CXX_11 201103L
#define CPA_CXX_14 201402L
#define CPA_CXX_17 201703L
#define CPA_CXX_20 202002L

#include "compilers.h"

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_CXX_VERSION __cplusplus
#elif CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#define CPA_CXX_VERSION _MSVC_LANG
#else
	#define CPA_CXX_VERSION __cplusplus
#endif
