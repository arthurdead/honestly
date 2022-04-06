#pragma once

#include "compiler_builtins.h"

#define CPA_LOCAL_CLASS CPA_VISIBILITY_LOCAL CPA_TYPE_VISIBILITY_LOCAL
#define CPA_PUBLIC_CLASS CPA_VISIBILITY_PUBLIC CPA_TYPE_VISIBILITY_PUBLIC

#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		#define CPA_NOVTABLE __attribute__((__novtable__))
	#else
		#define CPA_NOVTABLE
	#endif
	#define CPA_GLOBAL_CTOR_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wglobal-constructors\"") \
		_Pragma("clang diagnostic ignored \"-Wexit-time-destructors\"")
	#define CPA_GLOBAL_CTOR_END \
		_Pragma("clang diagnostic pop")
	#define CPA_EXIT_DTOR_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wexit-time-destructors\"")
	#define CPA_EXIT_DTOR_END \
		_Pragma("clang diagnostic pop")
#elif CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_NOVTABLE
	#define CPA_GLOBAL_CTOR_BEGIN
	#define CPA_GLOBAL_CTOR_END
	#define CPA_EXIT_DTOR_BEGIN
	#define CPA_EXIT_DTOR_END
#else
	#error
#endif
