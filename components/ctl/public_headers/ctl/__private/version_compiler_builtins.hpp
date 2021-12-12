#define CTL_NOTHING

#define CTL_OPEN_PARENTHESIS (
#define CTL_CLOSE_PARENTHESIS )

#define __CTL_CONCAT_EXPAND2(x1, x2) x1##x2
#define CTL_CONCAT2(x1, x2) __CTL_CONCAT_EXPAND2(x1, x2)

#define __CTL_CONCAT_EXPAND3(x1, x2, x3) x1##x2##x3
#define CTL_CONCAT3(x1, x2, x3) __CTL_CONCAT_EXPAND3(x1, x2, x3)

#define __CTL_STR_EXPAND(x) #x
#define CTL_STR(x) __CTL_STR_EXPAND(x)

#if CTL_COMPILER & CTL_COMPILER_FLAG_CLANG
	#define CTL_COMPILER_PRAGMA_ID clang
#elif CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#define CTL_COMPILER_PRAGMA_ID GCC
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_MSVC
	#if defined _MSVC_TRADITIONAL && _MSVC_TRADITIONAL == 0
		#define __CTL_MSVC_NEW_PREPROCESSOR
	#endif
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#define CTL_PRAGMA(...) _Pragma(CTL_STR(__VA_ARGS__))
#elif CTL_COMPILER & CTL_COMPILER_FLAG_MSVC
	#ifdef __CTL_MSVC_NEW_PREPROCESSOR
		#define CTL_PRAGMA(...) _Pragma(CTL_STR(__VA_ARGS__))
	#else
		#define CTL_PRAGMA(...) __pragma(__VA_ARGS__)
	#endif
#else
	#error
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#define CTL_GCC_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
	#define CTL_GCC_PRAGMA(...) _Pragma(CTL_STR(__VA_ARGS__))
	#define CTL_GCC_WARNING_PUSH _Pragma("GCC diagnostic push")
	#define CTL_GCC_WARNING_DISABLE(text) _Pragma(CTL_STR(GCC diagnostic ignored text))
	#define CTL_GCC_WARNING_POP _Pragma("GCC diagnostic pop")
#else
	#define CTL_GCC_ATTRIBUTE(...)
	#define CTL_GCC_PRAGMA(...)
	#define CTL_GCC_WARNING_PUSH
	#define CTL_GCC_WARNING_DISABLE(text)
	#define CTL_GCC_WARNING_POP
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_CLANG
	#define CTL_CLANG_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
	#define CTL_CLANG_PRAGMA(...) _Pragma(CTL_STR(__VA_ARGS__))
	#define CTL_CLANG_WARNING_PUSH _Pragma("clang diagnostic push")
	#define CTL_CLANG_WARNING_DISABLE(text) _Pragma(CTL_STR(clang diagnostic ignored text))
	#define CTL_CLANG_WARNING_POP _Pragma("clang diagnostic pop")
#else
	#define CTL_CLANG_ATTRIBUTE(...)
	#define CTL_CLANG_PRAGMA(...)
	#define CTL_CLANG_WARNING_PUSH
	#define CTL_CLANG_WARNING_DISABLE(text)
	#define CTL_CLANG_WARNING_POP
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_MSVC
	#define CTL_MSVC_DECLSPEC(x) __declspec(x)
	#define CTL_MSVC_PRAGMA(...) __pragma(__VA_ARGS__)
	#define CTL_MSVC_WARNING_PUSH __pragma(warning(push))
	#define CTL_MSVC_WARNING_DISABLE(text) __pragma(warning(disable: text))
	#define CTL_MSVC_WARNING_POP __pragma(warning(pop))
#else
	#define CTL_MSVC_DECLSPEC(x)
	#define CTL_MSVC_PRAGMA(...)
	#define CTL_MSVC_WARNING_PUSH
	#define CTL_MSVC_WARNING_DISABLE(text)
	#define CTL_MSVC_WARNING_POP
#endif

#ifdef __CTL_DISABLE_ALL_COMMENTS
	#define CTL_COMMENT(text)
#elif CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#define CTL_COMMENT(text) _Pragma(CTL_STR(GCC warning text))
#else
	#error
#endif

#if defined __COMPILING_CTL || defined __CTL_ENABLE_COMMENTS
	#define __CTL_COMMENT(text) CTL_COMMENT(text)
#else
	#define __CTL_COMMENT(text)
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_CLANG
	#define CTL_DEBUGTRAP __builtin_debugtrap()
#elif CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#if CTL_TARGET_ARCHITECTURE & CTL_ARCHITECTURE_FLAG_X86
		#define CTL_DEBUGTRAP __asm__ volatile("int $0x03")
	#else
		#define CTL_DEBUGTRAP __builtin_trap()
	#endif
#elif CTL_COMPILER & CTL_COMPILER_FLAG_MSVC
	#define CTL_DEBUGTRAP __debugbreak()
#else
	#error
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#define CTL_OFFSETOF(cls, mbr) __builtin_offsetof(cls, mbr)
	#define CTL_BITCAST(type, var) __builtin_bit_cast(type, var)
#else
	#error
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#ifdef CTL_VA_OPT_SUPPORTED
		#define __CTL_ATTR_CONSTRUCTOR(...) \
			__constructor__ __VA_OPT__(CTL_OPEN_PARENTHESIS) __VA_ARGS__ __VA_OPT__(CTL_CLOSE_PARENTHESIS)
	#else
		#define __CTL_ATTR_CONSTRUCTOR(...) \
			__constructor__
	#endif
	#define CTL_STATIC_INIT_FUNC(...) \
		static __attribute__((__CTL_ATTR_CONSTRUCTOR(__VA_ARGS__))) void CTL_CONCAT3(__, __LINE__, _initfunc) () noexcept
#else
	#error
#endif

#if CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#if CTL_TARGET_KERNEL == CTL_KERNEL_WINDOWS
		#define CTL_SHARED_EXPORT __attribute__((__visibility__("default"), __dllexport__))
		#define CTL_SHARED_IMPORT __attribute__((__visibility__("default"), __dllimport__))
		#define CTL_SHARED_CALL __attribute__((__ms_abi__, __stdcall__))
	#elif CTL_TARGET_KERNEL == CTL_KERNEL_LINUX
		#define CTL_SHARED_EXPORT __attribute__((__visibility__("default")))
		#define CTL_SHARED_IMPORT __attribute__((__visibility__("default")))
		#if CTL_COMPILER & CTL_COMPILER_FLAG_GCC && !(CTL_COMPILER & CTL_COMPILER_FLAG_CLANG)
			#define CTL_SHARED_CALL __attribute__((__sysv_abi__))
		#else
			#define CTL_SHARED_CALL __attribute__((__sysv_abi__, __cdecl__))
		#endif
	#elif CTL_TARGET_KERNEL == CTL_KERNEL_EMSCRIPTEN
		#define CTL_SHARED_EXPORT __attribute__((__visibility__("default")))
		#define CTL_SHARED_IMPORT __attribute__((__visibility__("default")))
		#define CTL_SHARED_CALL __attribute__((__cdecl__))
	#else
		#error
	#endif
#elif CTL_COMPILER & CTL_COMPILER_FLAG_MSVC
	#define CTL_SHARED_EXPORT __declspec(dllexport)
	#define CTL_SHARED_IMPORT __declspec(dllimport)
	#define CTL_SHARED_CALL __declspec(stdcall)
#else
	#error
#endif

#define CTL_VISIBILITY_LOCAL CTL_GCC_ATTRIBUTE(__visibility__("internal"))
#define CTL_VISIBILITY_PUBLIC CTL_GCC_ATTRIBUTE(__visibility__("default"))

#define CTL_TYPE_VISIBILITY_LOCAL CTL_CLANG_ATTRIBUTE(__type_visibility__("internal"))
#define CTL_TYPE_VISIBILITY_PUBLIC CTL_CLANG_ATTRIBUTE(__type_visibility__("default"))

#define CTL_LOCAL_CLASS CTL_VISIBILITY_LOCAL CTL_TYPE_VISIBILITY_LOCAL
#define CTL_PUBLIC_CLASS CTL_VISIBILITY_PUBLIC CTL_TYPE_VISIBILITY_PUBLIC

#define CTL_STATIC_LINKAGE CTL_CLANG_ATTRIBUTE(__internal_linkage__)

#define CTL_LOCAL_FUNCTION CTL_VISIBILITY_LOCAL CTL_STATIC_LINKAGE
#define CTL_PUBLIC_FUNCTION CTL_VISIBILITY_PUBLIC

#if CTL_COMPILER & CTL_COMPILER_FLAG_CLANG
	#if CTL_TARGET_KERNEL == CTL_KERNEL_WINDOWS
		#define CTL_NOVTABLE __attribute__((__novtable__))
	#else
		#define CTL_NOVTABLE
	#endif
	#define CTL_GLOBAL_CTOR_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wglobal-constructors\"") \
		_Pragma("clang diagnostic ignored \"-Wexit-time-destructors\"")
	#define CTL_GLOBAL_CTOR_END \
		_Pragma("clang diagnostic pop")
	#define CTL_EXIT_DTOR_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wexit-time-destructors\"")
	#define CTL_EXIT_DTOR_END \
		_Pragma("clang diagnostic pop")
	#define CTL_NO_DECL_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wmissing-variable-declarations\"")
	#define CTL_NO_DECL_END \
		_Pragma("clang diagnostic pop")
#elif CTL_COMPILER & CTL_COMPILER_FLAG_GCC
	#define CTL_NOVTABLE
	#define CTL_GLOBAL_CTOR_BEGIN
	#define CTL_GLOBAL_CTOR_END
	#define CTL_EXIT_DTOR_BEGIN
	#define CTL_EXIT_DTOR_END
	#define CTL_NO_DECL_BEGIN
	#define CTL_NO_DECL_END
#else
	#error
#endif
