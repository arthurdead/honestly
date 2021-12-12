m4_ifelse(LIBC, glibc, `
	m4_define(__VALID_LIBC, `')

	m4_ifelse(ARCHITECTURE, x86-64, `
		m4_define(__LIBC_LIB_DIR, /usr/lib)
	')

	m4_define(__LIBC_INC_DIRS, -isystem /usr/include)
')

m4_ifelse(LIBC, musl, `
	m4_define(__VALID_LIBC, `')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(__LIBC_INC_DIRS, -isystem /usr/lib/emscripten/system/lib/libc/musl/include -isystem /usr/lib/emscripten/system/include/compat -isystem /usr/lib/emscripten/system/lib/libc/musl/arch/emscripten -isystem /usr/lib/emscripten/system/lib/libc/musl/arch/generic)

		m4_define(__LIBC_LIB_DIR, __EMSCRIPTEN_CACHE/sysroot/lib/wasm32-emscripten)
	', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__LIBC_LIB_DIR, /usr/lib/musl/lib)
		')

		m4_define(__LIBC_INC_DIRS, -isystem /usr/lib/musl/include)
	')

	m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -D__MUSL__)
')

m4_ifelse(LIBC, cloudlibc, `
	m4_define(__VALID_LIBC, `')

	m4_ifdef(`WASI', `
		m4_define(__LIBC_INC_DIRS, -isystem WASI_SDK_ROOT/wasi-sysroot/include)

		m4_define(__LIBC_LIB_DIR, WASI_SDK_ROOT/wasi-sysroot/lib/wasm32-wasi)
	', `
		ERROR(no)
	')
')

m4_ifelse(LIBC, crt, `
	m4_define(__VALID_LIBC, `')

	m4_define(__LIBC_INC_DIRS, -isystem /usr/__MINGW_PREFIX/include)
	m4_define(__LIBC_LIB_DIR, /usr/__MINGW_PREFIX/lib)
')

m4_ifdef(`__VALID_LIBC', `m4_undefine(`__VALID_LIBC')', `ERROR(invalid libc value: LIBC)')

m4_define(__NEEDS_DYNAMIC_LINKER, `')

m4_ifdef(`EMSCRIPTEN', `
	m4_undefine(`__NEEDS_DYNAMIC_LINKER')
')
m4_ifdef(`MINGW', `
	m4_undefine(`__NEEDS_DYNAMIC_LINKER')
')

m4_ifdef(`__NEEDS_DYNAMIC_LINKER', `
	m4_undefine(`__NEEDS_DYNAMIC_LINKER')

	m4_ifelse(ARCHITECTURE, x86-64, `
		m4_ifelse(LIBC, musl, `
			m4_define(__DYNAMIC_LINKER, /usr/lib/ld-musl-x86_64.so.1)
		')
		m4_ifelse(LIBC, glibc, `
			m4_ifdef(`LSB', `
				m4_define(__DYNAMIC_LINKER, /usr/lib/ld-lsb-x86-64.so.3)
			', `
				m4_define(__DYNAMIC_LINKER, /usr/lib/ld-linux-x86-64.so.2)
			')
		')
	')

	m4_ifdef(`__LLD_LIKE', `
		m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS')  --dynamic-linker=__DYNAMIC_LINKER)
	', `
		m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS')  --dynamic-linker __DYNAMIC_LINKER)
	')

	m4_undefine(`__DYNAMIC_LINKER')
')