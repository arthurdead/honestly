//keep this in-sync with ctl/public_headers/ctl/__private/version_(pre|post)fixes.hpp
#pragma once

#define __THIRDPARTY_FIXES_HPP

#ifdef __MUSL__
	#define _LIBCPP_HAS_MUSL_LIBC
	#define __GLIBC_PREREQ(j,m) (0)
	#define __BEGIN_DECLS extern "C" {
	#define __END_DECLS }
#endif

#ifdef __ZAPCC__
	#undef __cpp_char8_t
	#undef __cpp_aligned_new
	#undef __cpp_impl_three_way_comparison
	#undef __cpp_deduction_guides
	#undef __cpp_concepts
	#undef __cpp_constexpr_dynamic_alloc
	#define _LIBCPP_HAS_NO_BUILTIN_IS_CONSTANT_EVALUATED
	#define _LIBCPP_HAS_NO_CHAR8_T
	#define _LIBCPP_NO_HAS_CHAR8_T
#endif

#if defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0
	#pragma push_macro("__OPTIMIZE__")
	#ifndef __OPTIMIZE__
		#define __OPTIMIZE__ 1
	#endif
#endif

#include <features.h>

#if defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0
	#pragma pop_macro("__OPTIMIZE__")
#endif

#include <version>

#ifdef __ZAPCC__
	#undef __cpp_lib_is_constant_evaluated
	#undef __cpp_lib_concepts
	#undef __cpp_lib_three_way_comparison
	#ifdef _LIBCPP_VERSION
		#undef _LIBCPP_COMPILER_HAS_BUILTIN_LAUNDER
	#elif defined __GLIBCXX__
		#undef _GLIBCXX_USE_CHAR8_T
		#undef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED
		#undef _GLIBCXX_HAVE_BUILTIN_LAUNDER
		#define __builtin_is_constant_evaluated() (false)
	#endif
#endif

#ifdef __MUSL__
	#ifdef __GLIBCXX__
		#undef _GLIBCXX_USE_PTHREAD_COND_CLOCKWAIT
	#endif
#endif

//keep this in-sync with ctl/public_headers/ctl/cstdio

#ifdef __MUSL__
	#include <stdio.h>

	#undef stdout
	#undef stdin
	#undef stderr
#endif

//keep this in-sync with ctl/public_headers/ctl/__private/locale.h

#ifdef __MUSL__
	#include <locale.h>

using __locale_t = locale_t;
#endif

//keep this in-sync with ctl/public_headers/ctl/__private/ctype.h

#ifdef __MUSL__
	#ifndef __CTYPE_ALREADY_DEFINED
		#if !defined __BYTE_ORDER__ || !defined __ORDER_BIG_ENDIAN__
			#error
		#endif

		#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			#define __CTYPE_BIT(bit) (1 << (bit))
		#else
			#define __CTYPE_BIT(bit) ((bit) < 8 ? ((1 << (bit)) << 8) : ((1 << (bit)) >> 8))
		#endif

enum
{
	_ISupper = __CTYPE_BIT(0),
	_ISlower = __CTYPE_BIT(1),
	_ISalpha = __CTYPE_BIT(2),
	_ISdigit = __CTYPE_BIT(3),
	_ISxdigit = __CTYPE_BIT(4),
	_ISspace = __CTYPE_BIT(5),
	_ISprint = __CTYPE_BIT(6),
	_ISgraph = __CTYPE_BIT(7),
	_ISblank = __CTYPE_BIT(8),
	_IScntrl = __CTYPE_BIT(9),
	_ISpunct = __CTYPE_BIT(10),
	_ISalnum = __CTYPE_BIT(11)
};

		#define __CTYPE_ALREADY_DEFINED
	#endif
#endif
