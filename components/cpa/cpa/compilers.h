#pragma once

#define CPA_COMPILER_FLAG_MSVC        (1 << 0)
#define CPA_COMPILER_FLAG_CLANG       (1 << 1)
#define CPA_COMPILER_FLAG_GCC         (1 << 2)
#define CPA_COMPILER_FLAG_ZAPCC       (1 << 3)
#define CPA_COMPILER_FLAG_MINGW       (1 << 4)
#define __CPA_COMPILER_FLAGS_LAST_BIT       4

#define __CPA_CLANG_FLAGS (CPA_COMPILER_FLAG_GCC|CPA_COMPILER_FLAG_CLANG)
#define __CPA_CLANG_CL_FLAGS (__CPA_CLANG_FLAGS|CPA_COMPILER_FLAG_MSVC)

#define CPA_COMPILER_GCC              ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+1))|CPA_COMPILER_FLAG_GCC)
#define CPA_COMPILER_CLANG            ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+2))|__CPA_CLANG_FLAGS)
#define CPA_COMPILER_CLANG_CL         ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+3))|__CPA_CLANG_CL_FLAGS)
#define CPA_COMPILER_MSVC             ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+4))|CPA_COMPILER_FLAG_MSVC)
#define CPA_COMPILER_MINGW            ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+5))|CPA_COMPILER_FLAG_GCC|CPA_COMPILER_FLAG_MSVC)
#define CPA_COMPILER_WINEGCC          ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+6))|CPA_COMPILER_FLAG_GCC)
#define CPA_COMPILER_ZAPCC            ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+7))|__CPA_CLANG_FLAGS)
#define CPA_COMPILER_ZAPCC_CL         ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+8))|__CPA_CLANG_CL_FLAGS)
#define CPA_COMPILER_CLANG_EMSCRIPTEN ((1 << (__CPA_COMPILER_FLAGS_LAST_BIT+9))|__CPA_CLANG_FLAGS)

#if defined __clang__ && !defined __ZAPCC__
	#if __clang_major__ == 7 && __clang_minor__ == 0 && __clang_patchlevel__ == 0
		#define __CPA_ASSUME_ZAPCC
	#endif
#endif

#ifdef __clang__
	#if defined __ZAPCC__ || defined __CPA_ASSUME_ZAPCC
		#ifdef _MSC_VER
			#define CPA_COMPILER CPA_COMPILER_ZAPCC_CL
		#else
			#define CPA_COMPILER CPA_COMPILER_ZAPCC
		#endif
	#elif defined __EMSCRIPTEN__
		#define CPA_COMPILER CPA_COMPILER_CLANG_EMSCRIPTEN
	#else
		#ifdef _MSC_VER
			#define CPA_COMPILER CPA_COMPILER_CLANG_CL
		#else
			#define CPA_COMPILER CPA_COMPILER_CLANG
		#endif
	#endif
#elif defined __GNUC__
	#ifdef __WINE__
		#define CPA_COMPILER CPA_COMPILER_WINEGCC
	#elif defined __MINGW32__ || defined __MINGW64__
		#define CPA_COMPILER CPA_COMPILER_MINGW
	#else
		#define CPA_COMPILER CPA_COMPILER_GCC
	#endif
#elif defined _MSC_VER
	#define CPA_COMPILER CPA_COMPILER_MSVC
#else
	#error
#endif

#define __CPA_MAKE_GCC_VERSION(j, m, p) (((j * 10000) + (m * 100)) + p)
#define __CPA_MAKE_CLANG_VERSION(j, m, p) (((j * 10000) + (m * 100)) + p)
#define __CPA_MAKE_MSVC_VERSION(j, m, p) (((j * 100000) + (m * 10)) + p)

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#if __GNUC__ >= 3
		#define __CPA_GCC_PATCHLEVEL __GNUC_PATCHLEVEL__
	#else
		#define __CPA_GCC_PATCHLEVEL 0
	#endif

	#define __CPA_GCC_VERSION __CPA_MAKE_GCC_VERSION(__GNUC__, __GNUC_MINOR__, __CPA_GCC_PATCHLEVEL)
#else
	#define __CPA_GCC_VERSION 0
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
	#define __CPA_CLANG_VERSION __CPA_MAKE_CLANG_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
	#define __CPA_CLANG_VERSION 0
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#define __CPA_MSVC_VERSION _MSC_FULL_VER
#else
	#define __CPA_MSVC_VERSION 0
#endif

#define CPA_CLANG_VERSION_CMP(op, j, m, p) (__CPA_CLANG_VERSION op __CPA_MAKE_CLANG_VERSION(j, m, p))
#define CPA_GCC_VERSION_CMP(op, j, m, p) (__CPA_GCC_VERSION op __CPA_MAKE_GCC_VERSION(j, m, p))
#define CPA_MSVC_VERSION_CMP(op, j, m, p) (__CPA_MSVC_VERSION op __CPA_MAKE_MSVC_VERSION(j, m, p))
