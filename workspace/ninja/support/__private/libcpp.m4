m4_divert(-1)
#m4_ifelse(TOOLSET, llvm, `
#	m4_ifdef(`EMSCRIPTEN', `', `
#		m4_ifdef(`ZAPCC', `', `
#			m4_define(__LIBCPP_INC_ARG, -stdlib++-isystem)
#		')
#	')
#')
m4_divert

m4_ifdef(`__LIBCPP_INC_ARG', `', `
	m4_define(__LIBCPP_INC_ARG, -isystem)
')

m4_divert(-1)
#m4_ifelse(TOOLSET, llvm, `
#	m4_ifdef(`EMSCRIPTEN', `', `
#		m4_ifdef(`ZAPCC', `', `
#			m4_define(__CXX_INC_ARG, -cxx-isystem)
#		')
#	')
#')
m4_divert

m4_ifdef(`__CXX_INC_ARG', `', `
	m4_define(__CXX_INC_ARG, -isystem)
')

m4_ifelse(LIBCPP, libstdc++, `
	m4_define(__VALID_LIBCPP, `')

	m4_define(__LIBCPP_LIBS, -lstdc++)

	m4_ifdef(`MINGW', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__MINGW_VER, __C_VERSION(mingw-64))
		')

		m4_define(__LIBCPP_INC_DIRS, __LIBCPP_INC_ARG /usr/__MINGW_PREFIX/include/c++/__MINGW_VER)

		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(`__LIBCPP_INC_DIRS', m4_defn(`__LIBCPP_INC_DIRS') __LIBCPP_INC_ARG /usr/__MINGW_PREFIX/include/c++/__MINGW_VER/x86_64-w64-mingw32)
		')

		m4_undefine(`__MINGW_VER')
	', `
		m4_define(__GCC_VER, __C_VERSION(gcc))

		m4_define(__LIBCPP_INC_DIRS, __LIBCPP_INC_ARG /usr/include/c++/__GCC_VER)

		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(`__LIBCPP_INC_DIRS', m4_defn(`__LIBCPP_INC_DIRS') __LIBCPP_INC_ARG /usr/include/c++/__GCC_VER/x86_64-pc-linux-gnu)
		')

		m4_undefine(`__GCC_VER')
	')
')

m4_ifelse(LIBCPP, libc++, `
	m4_define(__VALID_LIBCPP, `')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(`__LIBCPP_INC_DIRS', __LIBCPP_INC_ARG /usr/lib/emscripten/system/lib/libcxx/include)
		m4_define(`__LIBCPP_LIBS', -lc++-noexcept)
	')
	m4_ifdef(`WASI', `
		m4_define(`__LIBCPP_INC_DIRS', __LIBCPP_INC_ARG WASI_SDK_ROOT/wasi-sysroot/include/c++/v1)
		m4_undefine(`__LIBCPP_LIBS')
	')
	m4_ifdef(`__LIBCPP_INC_DIRS', `', `
		m4_define(__LIBCPP_INC_DIRS, __LIBCPP_INC_ARG /usr/include/c++/v1)
	')
	m4_ifdef(`__LIBCPP_LIBS', `', `
		m4_define(__LIBCPP_LIBS, -lc++)
	')
')

m4_ifdef(`__VALID_LIBCPP', `m4_undefine(`__VALID_LIBCPP')', `ERROR(invalid libcpp value: LIBCPP)')

m4_ifelse(LIBCPP_ABI, libc++abi, `
	m4_define(__VALID_LIBCPP_ABI, `')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(__LIBCPP_ABI_LIBS, -lc++abi-noexcept)
	', `
		m4_define(__LIBCPP_ABI_LIBS, -lc++abi)
	')
')

m4_ifelse(LIBCPP_ABI, libsupc++, `
	m4_define(__VALID_LIBCPP_ABI, `')
	m4_define(__LIBCPP_ABI_LIBS, -lsupc++)
')

m4_ifdef(`__VALID_LIBCPP_ABI', `m4_undefine(`__VALID_LIBCPP_ABI')', `ERROR(invalid libcpp_abi value: LIBCPP_ABI)')

m4_ifelse(ARCHITECTURE, x86-64, `
	m4_ifdef(`MINGW', `
		m4_define(`__LIBCPP_LIB_DIR', /usr/__MINGW_PREFIX/lib)
		m4_define(`__LIBCPP_ABI_LIB_DIR', /usr/__MINGW_PREFIX/lib)
	')
	m4_ifdef(`__LIBCPP_LIB_DIR', `', `
		m4_define(__LIBCPP_LIB_DIR, /usr/lib)
	')
	m4_ifdef(`__LIBCPP_ABI_LIB_DIR', `', `
		m4_define(__LIBCPP_ABI_LIB_DIR, /usr/lib)
	')
')

m4_ifelse(ARCHITECTURE, wasm-32, `
	m4_ifdef(`EMSCRIPTEN', `
		m4_define(`__LIBCPP_LIB_DIR', __EMSCRIPTEN_CACHE/sysroot/lib/wasm32-emscripten)
		m4_define(`__LIBCPP_ABI_LIB_DIR', __EMSCRIPTEN_CACHE/sysroot/lib/wasm32-emscripten)
	')
	m4_ifdef(`WASI', `
		m4_define(`__LIBCPP_LIB_DIR', WASI_SDK_ROOT/wasi-sysroot/lib/wasm32-wasi)
		m4_define(`__LIBCPP_ABI_LIB_DIR', WASI_SDK_ROOT/wasi-sysroot/lib/wasm32-wasi)
	')
	m4_ifdef(`__LIBCPP_LIB_DIR', `', `
		ERROR(no)
	')
	m4_ifdef(`__LIBCPP_ABI_LIB_DIR', `', `
		ERROR(no)
	')
')