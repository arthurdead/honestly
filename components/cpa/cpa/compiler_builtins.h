#pragma once

#include "compilers.h"
#include "architectures.h"
#include "kernels.h"

#define CPA_NOTHING

#define __CPA_STR_EXPAND(x) #x
#define CPA_STR(x) __CPA_STR_EXPAND(x)

#define __CPA_CONCAT_EXPAND3(x1, x2, x3) x1##x2##x3
#define CPA_CONCAT3(x1, x2, x3) __CPA_CONCAT_EXPAND3(x1, x2, x3)

#if CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#if defined _MSVC_TRADITIONAL && _MSVC_TRADITIONAL == 0
		#define __CPA_MSVC_NEW_PREPROCESSOR
	#endif
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
	#define CPA_COMPILER_PRAGMA_ID clang
#elif CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_COMPILER_PRAGMA_ID GCC
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_GCC_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
	#define CPA_GCC_PRAGMA(...) _Pragma(CPA_STR(__VA_ARGS__))
	#define CPA_GCC_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define CPA_GCC_WARNING_DISABLE(name) _Pragma(CPA_STR(GCC diagnostic ignored name))
	#define CPA_GCC_WARNING_POP _Pragma("GCC diagnostic pop")
#else
	#define CPA_GCC_ATTRIBUTE(...)
	#define CPA_GCC_PRAGMA(...)
	#define CPA_GCC_WARNING_PUSH
	#define CPA_GCC_WARNING_DISABLE(text)
	#define CPA_GCC_WARNING_POP
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
	#define CPA_CLANG_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
	#define CPA_CLANG_PRAGMA(...) _Pragma(CPA_STR(__VA_ARGS__))
	#define CPA_CLANG_WARNING_PUSH _Pragma("clang diagnostic push")
	#define CPA_CLANG_WARNING_DISABLE(name) _Pragma(CPA_STR(clang diagnostic ignored name))
	#define CPA_CLANG_WARNING_POP _Pragma("clang diagnostic pop")
#else
	#define CPA_CLANG_ATTRIBUTE(...)
	#define CPA_CLANG_PRAGMA(...)
	#define CPA_CLANG_WARNING_PUSH
	#define CPA_CLANG_WARNING_DISABLE(text)
	#define CPA_CLANG_WARNING_POP
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#define CPA_MSVC_DECLSPEC(x) __declspec(x)
	#define CPA_MSVC_PRAGMA(...) __pragma(__VA_ARGS__)
	#define CPA_MSVC_WARNING_PUSH __pragma(warning(push))
	#define CPA_MSVC_WARNING_DISABLE(...) __pragma(warning(disable: __VA_ARGS__))
	#define CPA_MSVC_WARNING_POP __pragma(warning(pop))
#else
	#define CPA_MSVC_DECLSPEC(x)
	#define CPA_MSVC_PRAGMA(...)
	#define CPA_MSVC_WARNING_PUSH
	#define CPA_MSVC_WARNING_DISABLE(text)
	#define CPA_MSVC_WARNING_POP
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_PRAGMA(...) _Pragma(CPA_STR(__VA_ARGS__))
#elif CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#ifdef __CPA_MSVC_NEW_PREPROCESSOR
		#define CPA_PRAGMA(...) _Pragma(CPA_STR(__VA_ARGS__))
	#else
		#define CPA_PRAGMA(...) __pragma(__VA_ARGS__)
	#endif
#else
	#define CPA_PRAGMA(...) _Pragma(CPA_STR(__VA_ARGS__))
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_OFFSETOF(cls, mbr) __builtin_offsetof(cls, mbr)
	#define CPA_BITCAST(type, var) __builtin_bit_cast(type, var)
#else
	#error
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
	#define CPA_TRAP __builtin_debugtrap()
#elif CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#if CPA_TARGET_ARCHITECTURE & CPA_ARCHITECTURE_FLAG_X86
		#define CPA_TRAP __asm__ volatile("int $0x03")
	#else
		#define CPA_TRAP __builtin_trap()
	#endif
#elif CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#define CPA_TRAP __debugbreak()
#else
	#error
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		#define CPA_SHARED_EXPORT __attribute__((__visibility__("default"), __dllexport__))
		#define CPA_SHARED_IMPORT __attribute__((__visibility__("default"), __dllimport__))
		#define CPA_SHARED_CALL __attribute__((__ms_abi__, __stdcall__))
	#elif CPA_TARGET_KERNEL == CPA_KERNEL_LINUX
		#define CPA_SHARED_EXPORT __attribute__((__visibility__("default")))
		#define CPA_SHARED_IMPORT __attribute__((__visibility__("default")))
		#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
			#define CPA_SHARED_CALL __attribute__((__sysv_abi__, __cdecl__))
		#else
			#define CPA_SHARED_CALL __attribute__((__sysv_abi__))
		#endif
	#else
		#define CPA_SHARED_EXPORT __attribute__((__visibility__("default")))
		#define CPA_SHARED_IMPORT __attribute__((__visibility__("default")))
		#define CPA_SHARED_CALL __attribute__((__cdecl__))
	#endif
#elif CPA_COMPILER & CPA_COMPILER_FLAG_MSVC
	#define CPA_SHARED_EXPORT __declspec(dllexport)
	#define CPA_SHARED_IMPORT __declspec(dllimport)
	#define CPA_SHARED_CALL __declspec(stdcall)
#else
	#error
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_COMMENT(text) _Pragma(CPA_STR(GCC warning text))
#else
	#error
#endif

#define CPA_VISIBILITY_LOCAL CPA_GCC_ATTRIBUTE(__visibility__("internal"))
#define CPA_VISIBILITY_PUBLIC CPA_GCC_ATTRIBUTE(__visibility__("default"))

#define CPA_TYPE_VISIBILITY_LOCAL CPA_CLANG_ATTRIBUTE(__type_visibility__("internal"))
#define CPA_TYPE_VISIBILITY_PUBLIC CPA_CLANG_ATTRIBUTE(__type_visibility__("default"))

#define CPA_STATIC_LINKAGE CPA_CLANG_ATTRIBUTE(__internal_linkage__)

#define CPA_LOCAL_FUNCTION CPA_VISIBILITY_LOCAL CPA_STATIC_LINKAGE
#define CPA_PUBLIC_FUNCTION CPA_VISIBILITY_PUBLIC

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define __CPA_ATTR_CONSTRUCTOR(...) \
		__constructor__ __VA_OPT__(CPA_OPEN_PARENTHESIS) __VA_ARGS__ __VA_OPT__(CPA_CLOSE_PARENTHESIS)
	#define CPA_STATIC_INIT_FUNC(...) \
		static __attribute__((__CPA_ATTR_CONSTRUCTOR(__VA_ARGS__))) void CPA_CONCAT3(__, __LINE__, _initfunc) () noexcept
#else
	#error
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
	#define CPA_NO_DECL_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wmissing-variable-declarations\"")
	#define CPA_NO_DECL_END \
		_Pragma("clang diagnostic pop")
#elif CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_NO_DECL_BEGIN
	#define CPA_NO_DECL_END
#else
	#error
#endif

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#define CPA_WCHAR_WIDTH __WCHAR_WIDTH__
	#define CPA_LONG_WIDTH __LONG_WIDTH__
#else
	#error
#endif
