m4_ifelse(LIBRT, libgcc, `
	m4_define(__VALID_LIBRT, `')

	m4_ifdef(`MINGW', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__LIBRT_LIB_DIR, /usr/lib/gcc/x86_64-w64-mingw32/__CXX_VERSION(mingw-64))
		')

		m4_define(__LIBRT_CRTBEGIN, crtbegin.o)
		m4_define(__LIBRT_CRTEND, crtend.o)
		m4_define(__LIBRT_LIB, -lgcc)
	', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__LIBRT_LIB_DIR, /usr/lib/gcc/x86_64-pc-linux-gnu/__CXX_VERSION(gcc))
		')

		m4_define(__LIBRT_CRTBEGIN, crtbeginS.o)
		m4_define(__LIBRT_CRTEND, crtendS.o)
		m4_define(__LIBRT_LIB, -lgcc)
	')
')

m4_ifelse(LIBRT, compiler-rt, `
	m4_define(__VALID_LIBRT, `')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(__LIBRT_LIB, -lcompiler_rt)
		m4_define(__LIBRT_LIB_DIR, __EMSCRIPTEN_CACHE/sysroot/lib/wasm32-emscripten)
	', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__LIBRT_LIB_DIR, /usr/lib/clang/__CXX_VERSION(clang)/lib/linux)
			m4_define(__LIBRT_CRTBEGIN, clang_rt.crtbegin-x86_64.o)
			m4_define(__LIBRT_CRTEND, clang_rt.crtend-x86_64.o)
			m4_define(__LIBRT_LIB, -lclang_rt.builtins-x86_64)
		')
	')
')

m4_ifdef(`__VALID_LIBRT', `m4_undefine(`__VALID_LIBRT')', `ERROR(invalid librt value: LIBRT)')

m4_ifelse(LIBUNWIND, libgcc, `
	m4_define(__VALID_LIBUNWIND, `')

	m4_ifdef(`MINGW', `
		m4_define(__LIBUNWIND_LIB_DIR, /usr/__MINGW_PREFIX/lib)
	', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__LIBUNWIND_LIB_DIR, /usr/lib/gcc/x86_64-pc-linux-gnu/__CXX_VERSION(gcc))
		')
	')

	m4_define(__LIBUNWIND_LIB, -lgcc_s)
')

m4_ifelse(LIBUNWIND, libunwind, `
	m4_define(__VALID_LIBUNWIND, `')

	m4_ifelse(ARCHITECTURE, x86-64, `
		m4_define(__LIBUNWIND_LIB_DIR, /usr/lib)
		m4_define(__LIBUNWIND_LIB, -lunwind-x86_64)
	')
')

m4_ifelse(LIBUNWIND, none, `
	m4_define(__VALID_LIBUNWIND, `')
')

m4_ifdef(`__VALID_LIBUNWIND', `m4_undefine(`__VALID_LIBUNWIND')', `ERROR(invalid libunwind value: LIBUNWIND)')