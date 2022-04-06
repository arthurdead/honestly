m4_ifelse(TOOLSET, llvm, `', `
	m4_ifdef(`ZAPCC', `
		ERROR(`ZAPCC' requires `TOOLSET'=llvm)
	')
	m4_ifdef(`EMSCRIPTEN', `
		ERROR(`EMSCRIPTEN' requires `TOOLSET'=llvm)
	')
')

m4_ifdef(`ZAPCC', `
	m4_ifdef(`EMSCRIPTEN', `
		ERROR(`EMSCRIPTEN' and `ZAPCC' are incompatible)
	')
')

m4_ifdef(`LSB', `
	m4_ifelse(LIBC, glibc, `', `
		ERROR(`LSB' requires `LIBC'=glibc)
	')
')

m4_ifdef(`EMSCRIPTEN', `
	m4_ifelse(ARCHITECTURE, wasm-64, `',
	ARCHITECTURE, wasm-32, `', `
		ERROR(`EMSCRIPTEN' requires `ARCHITECTURE'=wasm-32 or `ARCHITECTURE'=wasm-64)
	')
	m4_ifelse(LD, wasm-lld, `', `
		ERROR(`EMSCRIPTEN' requires `LD'=wasm-lld)
	')
	m4_ifelse(LIBC, musl, `',
	LIBC, cloudlibc, `
		m4_ifdef(`WASI', `', `
			ERROR(`LIBC'=cloudlibc requires `WASI')
		')
	', `
		ERROR(`EMSCRIPTEN' requires `LIBC'=musl or `LIBC'=cloudlibc (with `WASI'))
	')
	m4_ifelse(LIBCPP, libc++, `', `
		ERROR(`EMSCRIPTEN' requires `LIBCPP'=libc++)
	')
	m4_ifelse(LIBCPP_ABI, libc++abi, `', `
		ERROR(`EMSCRIPTEN' requires `LIBCPP_ABI'=libc++abi)
	')
	m4_ifelse(LIBRT, compiler-rt, `', `
		ERROR(`EMSCRIPTEN' requires `LIBRT'=compiler-rt)
	')
	m4_ifelse(LIBUNWIND, none, `', `
		ERROR(`EMSCRIPTEN' requires `LIBUNWIND'=none)
	')
', `
	m4_ifelse(ARCHITECTURE, wasm-64, `
		ERROR(`ARCHITECTURE'=wasm-64 requires `EMSCRIPTEN')
	', ARCHITECTURE, wasm-32, `
		ERROR(`ARCHITECTURE'=wasm-32 requires `EMSCRIPTEN')
	')
	m4_ifelse(LD, wasm-lld, `
		ERROR(`LD'=wasm-lld requires `EMSCRIPTEN')
	')
')

m4_ifdef(`WASI', `
	m4_ifdef(`EMSCRIPTEN', `', `
		ERROR(`WASI' requires `EMSCRIPTEN')
	')
	ERROR(`WASI' is not currently supported)
', `
	m4_ifelse(LIBC, cloudlibc, `
		ERROR(`LIBC'=cloudlibc requires `WASI')
	')
')

m4_ifdef(`MINGW', `
	m4_ifelse(TOOLSET, gnu, `', `
		ERROR(`MINGW' requires `TOOLSET'=gnu)
	')
	m4_ifelse(LIBCPP, libstdc++, `', `
		ERROR(`MINGW' requires `LIBCPP'=libstdc++)
	')
	m4_ifelse(LIBCPP_ABI, libsupc++, `', `
		ERROR(`MINGW' requires `LIBCPP_ABI'=libsupc++)
	')
	m4_ifelse(LIBRT, libgcc, `', `
		ERROR(`MINGW' requires `LIBRT'=libgcc)
	')
	m4_ifelse(LIBUNWIND, libgcc, `', `
		ERROR(`MINGW' requires `LIBUNWIND'=libgcc)
	')
	m4_ifelse(LIBC, crt, `', `
		ERROR(`MINGW' requires `LIBC'=crt)
	')
	m4_ifelse(LD, ld, `',
	LD, bfd, `', `
		ERROR(`MINGW' requires `LD'=ld or `LD'=bfd)
	')
', `
	m4_ifelse(LIBC, crt, `
		ERROR(`LIBC'=crt requires `MINGW')
	')
')

m4_ifdef(`WINE', `
	m4_ifdef(`MINGW', `
		ERROR(`WINE' is incompatible with `MINGW')
	')
	m4_ifelse(TOOLSET, gnu, `', `
		ERROR(`WINE' requires `TOOLSET'=gnu)
	')
')

m4_divert(-1)
#m4_ifdef(`ZAPCC', `
#	m4_define(__CPP_IS_C, `')
#')
m4_divert

m4_ifdef(`__SEPARATE_PP', `
	m4_ifelse(TOOLSET, llvm, `
		m4_define(`__PCH_NO_SEPARATE_PP', `')
	')
')