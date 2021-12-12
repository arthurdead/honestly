#define CTL_CPP_98 199711L
#define CTL_CPP_11 201103L
#define CTL_CPP_14 201402L
#define CTL_CPP_17 201703L
#define CTL_CPP_20 202002L

#if !(CTL_COMPILER & CTL_COMPILER_FLAG_MINGW) && CTL_COMPILER & CTL_COMPILER_FLAG_MSVC
	#define CTL_CPP_VERSION _MSVC_LANG
#else
	#define CTL_CPP_VERSION __cplusplus
#endif

#define CTL_VA_OPT_SUPPORTED

#if CTL_CPP_VERSION >= CTL_CPP_20 && !(CTL_COMPILER & CTL_COMPILER_FLAG_ZAPCC)
	#define CTL_VIRTUAL_CONSTEXPR_SUPPORTED
#endif

#ifdef CTL_VIRTUAL_CONSTEXPR_SUPPORTED
	#define CTL_VIRTUAL_CONSTEXPR constexpr
#else
	#define CTL_VIRTUAL_CONSTEXPR
#endif

#ifndef __cpp_char8_t
	#ifndef __CLANG_CHECK__
enum char8_t : char
{
};
	#else
enum __char8_t : char
{
};
		#define char8_t __char8_t
	#endif
#endif
