#ifndef __STDI_FEATURES_H
	#if defined _LIBCPP_HAS_MUSL_LIBC || defined __MUSL__
		#define __GLIBC_PREREQ(j,m) (0)
		#define __BEGIN_DECLS extern "C" {
		#define __END_DECLS }
	#endif
#endif

#include <cpa/compilers.h>

#pragma push_macro("__STDI_FEATURES_H")
#define __STDI_FEATURES_H

#if defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0
	#pragma push_macro("__OPTIMIZE__")
	#ifndef __OPTIMIZE__
		#define __OPTIMIZE__ 1
	#endif
#endif

#define __STDI_INCLUDE_NEXT_HEADER <features.h>
#include "__details/include_next.h"

#if defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0
	#pragma pop_macro("__OPTIMIZE__")
#endif

#undef __STDI_FEATURES_H
#pragma pop_macro("__STDI_FEATURES_H")

#ifndef __STDI_FEATURES_H
	#define STDI_C_STDLIB_FLAG_NIX         (1 << 0)
	#define STDI_C_STDLIB_FLAG_POSIX       (1 << 1)
	#define __STDI_C_STDLIB_FLAGS_LAST_BIT       1

	#define __STDI_C_STDLIB_FLAGS_NIX (STDI_C_STDLIB_FLAG_NIX|STDI_C_STDLIB_FLAG_POSIX)

	#define STDI_STDLIB_GLIBC ((1 << (__STDI_C_STDLIB_FLAGS_LAST_BIT+1))|__STDI_C_STDLIB_FLAGS_NIX)
	#define STDI_STDLIB_MUSL  ((1 << (__STDI_C_STDLIB_FLAGS_LAST_BIT+2))|__STDI_C_STDLIB_FLAGS_NIX)
	#define STDI_STDLIB_CRT   ((1 << (__STDI_C_STDLIB_FLAGS_LAST_BIT+3)))

	#if defined _LIBCPP_HAS_MUSL_LIBC || defined __MUSL__
		#define STDI_C_STDLIB STDI_STDLIB_MUSL
	#elif defined __GLIBC__
		#define STDI_C_STDLIB STDI_STDLIB_GLIBC
	#elif defined _WIN32_C_LIB
		#define STDI_C_STDLIB STDI_STDLIB_CRT
	#else
		#error
	#endif
#endif

#ifndef __STDI_FEATURES_H
	#define __STDI_FEATURES_H
#endif
