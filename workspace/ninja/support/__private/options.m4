m4_ifdef(`VERBOSE_BUILD', `
	m4_define(__SEPARATE_PP, `')
	m4_define(__SEPARATE_AS, `')
	m4_ifdef(`EMSCRIPTEN', `
		m4_undefine(`__SEPARATE_AS')
	')
	m4_undefine(`__UNIFIED_CXX')
	m4_define(`INFO_COMMENT', `')
')

m4_ifdef(`FAST_BUILD', `
	m4_undefine(`__SEPARATE_PP')
	m4_undefine(`__SEPARATE_AS')
	m4_define(__UNIFIED_CXX, `')
	m4_divert(-1)
	#m4_define(`ZAPCC', `')
	m4_divert
	m4_ifdef(`WINE', `
		m4_undefine(`ZAPCC')
	')
	m4_ifdef(`MINGW', `
		m4_undefine(`ZAPCC')
	')
	m4_ifdef(`EMSCRIPTEN', `
		m4_undefine(`ZAPCC')
	')
	m4_ifelse(TOOLSET, gnu, `
		m4_undefine(`ZAPCC')
	')
	m4_define(`CCACHE', `')
')

m4_ifdef(`COMPDB_COMPATIBLE', `
	m4_undefine(`CCACHE')
	m4_undefine(`COLLECT_WARNED')
	m4_undefine(`__SEPARATE_PP')
')

m4_ifdef(`CCACHE', `
	m4_ifelse(CCACHE, `', `
		m4_define(`CCACHE', ccache)
	')
	m4_ifelse(CCACHE, `sccache', `
		m4_define(__VALID_CCACHE, `')
		m4_define(__CCACHE_EXEC, sccache)
	')
	m4_ifelse(CCACHE, `ccache', `
		m4_define(__VALID_CCACHE, `')
		m4_define(__CCACHE_EXEC, ccache)
	')
	m4_ifdef(`__VALID_CCACHE', `m4_undefine(`__VALID_CCACHE')', `ERROR(invalid ccache value: CCACHE)')
')

m4_ifdef(`TOOLSET', `', `
	m4_ifdef(`EMSCRIPTEN', `
		m4_define(TOOLSET, llvm)
	')
	m4_ifdef(`ZAPCC', `
		m4_define(TOOLSET, llvm)
	')
	m4_ifdef(`TOOLSET', `', `
		m4_define(TOOLSET, gnu)
	')
')

m4_ifdef(`ARCHITECTURE', `', `
	m4_ifdef(`EMSCRIPTEN', `
		m4_define(ARCHITECTURE, wasm-64)
	')
	m4_ifdef(`ARCHITECTURE', `', `
		m4_define(ARCHITECTURE, x86-64)
	')
')

m4_ifdef(`LIBRT', `', `
	m4_ifelse(TOOLSET, llvm, `
		m4_define(LIBRT, compiler-rt)
	')
	m4_ifdef(`LIBRT', `', `
		m4_define(LIBRT, libgcc)
	')
')

m4_ifdef(`LIBCPP', `', `
	m4_ifelse(TOOLSET, llvm, `
		m4_define(LIBCPP, libc++)
	')
	m4_ifdef(`LIBCPP', `', `
		m4_define(LIBCPP, libstdc++)
	')
')

m4_ifdef(`LIBCPP_ABI', `', `
	m4_ifelse(LIBCPP, libc++, `
		m4_define(LIBCPP_ABI, libc++abi)
	')
	m4_ifdef(`LIBCPP_ABI', `', `
		m4_define(LIBCPP_ABI, libsupc++)
	')
')

m4_ifdef(`LIBC', `', `
	m4_ifdef(`EMSCRIPTEN', `
		m4_define(LIBC, musl)
	')
	m4_ifdef(`LIBC', `', `
		m4_define(LIBC, glibc)
	')
')

m4_ifdef(`LIBUNWIND', `', `
	m4_ifelse(LIBRT, libgcc, `
		m4_define(LIBUNWIND, libgcc)
	')
	m4_ifdef(`LIBUNWIND', `', `
		m4_define(LIBUNWIND, libgcc)
	')
')

m4_ifdef(`LD', `', `
	m4_ifelse(TOOLSET, llvm, `
		m4_ifdef(`EMSCRIPTEN', `
			m4_define(LD, wasm-lld)
		', `
			m4_define(LD, lld)
		')
	')
	m4_ifdef(`LD', `', `
		m4_define(LD, gold)
	')
')

m4_ifdef(`CONFIGURATION', `', `
	m4_define(CONFIGURATION, release)
')