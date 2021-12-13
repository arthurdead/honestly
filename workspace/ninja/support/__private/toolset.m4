m4_ifdef(`ZAPCC', `
	m4_define(__CXX_LATEST_VER, 2a)

	m4_ifdef(`__CPP_IS_C', `
		m4_define(__CXX_CPP_LATEST_VER, 2a)
	')
')

m4_ifdef(`__CXX_LATEST_VER', `', `
	m4_define(__CXX_LATEST_VER, 2b)
')
m4_ifdef(`__CXX_CPP_LATEST_VER', `', `
	m4_define(__CXX_CPP_LATEST_VER, 2b)
')

m4_ifdef(`__CC_LATEST_VER', `', `
	m4_define(__CC_LATEST_VER, 2x)
')
m4_ifdef(`__CC_CPP_LATEST_VER', `', `
	m4_define(__CC_CPP_LATEST_VER, 2x)
')

m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -std=gnu++`'__CXX_LATEST_VER)
m4_define(`__CC_FLAGS', m4_defn(`__CC_FLAGS') -std=gnu`'__CC_LATEST_VER)

m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -std=gnu++`'__CXX_CPP_LATEST_VER)
m4_define(`__CC_CPP_FLAGS', m4_defn(`__CC_CPP_FLAGS') -std=gnu`'__CC_CPP_LATEST_VER)

m4_undefine(`__CXX_LATEST_VER')
m4_undefine(`__CC_LATEST_VER')
m4_undefine(`__CXX_CPP_LATEST_VER')
m4_undefine(`__CC_CPP_LATEST_VER')

m4_ifelse(TOOLSET, llvm, `
	m4_define(__VALID_TOOLSET, `')

	m4_ifdef(`__SEPARATE_PP', `
		m4_define(__CPP_EXEC, clang-cpp)
	')

	m4_ifdef(`ZAPCC', `
		m4_define(__CXX_EXEC, zapcc++)
		m4_define(__CC_EXEC, zapcc)

		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__TOOLSET_INC_DIRS, -isystem /usr/lib/zapcc/__C_VERSION(zapcc)/include)
		')

		m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -D__ZAPCC__)
	')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(__CXX_EXEC, em++)
		m4_define(__CC_EXEC, em)

		m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -s DEFAULT_TO_CXX=1)
		m4_define(`__CC_FLAGS', m4_defn(`__CC_FLAGS') -s DEFAULT_TO_CXX=0)

		m4_ifdef(`__LD_IS_CXX', `
			m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS') -s AUTO_JS_LIBRARIES=0 -s AUTO_NATIVE_LIBRARIES=0 -s AUTO_ARCHIVE_INDEXES=1)
			m4_define(`__CXX_LD_FLAGS', m4_defn(`__CXX_LD_FLAGS') -s DEFAULT_TO_CXX=1)
			m4_define(`__CC_LD_FLAGS', m4_defn(`__CC_LD_FLAGS') -s DEFAULT_TO_CXX=0)
		')

		m4_define(__TOOLSET_INC_DIRS, -isystem EMSCRIPTEN_LLVM_ROOT/lib/clang/__C_VERSION(emscripten-clang)/include)

		m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -D__EMSCRIPTEN__)
	')

	m4_ifdef(`__CXX_EXEC', `', `
		m4_ifelse(LIBC, musl, `
			m4_divert(-1)
			#m4_define(__CXX_EXEC, musl-clang)
			#m4_define(__CC_EXEC, musl-clang)
			#m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -Wno-unused-command-line-argument -Wno-poison-system-directories)
			m4_divert
			m4_define(__CXX_EXEC, clang++)
			m4_define(__CC_EXEC, clang)
		', `
			m4_define(__CXX_EXEC, clang++)
			m4_define(__CC_EXEC, clang)
		')

		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__TOOLSET_INC_DIRS, -isystem /usr/lib/clang/__C_VERSION(clang)/include)
		')
	')

	m4_ifdef(`ZAPCC', `', `
		m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -fintegrated-cc1)
	')

	m4_include(__private/sanity|llvm.m4)

	m4_ifdef(`__SEPARATE_AS', `
		m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -fno-integrated-as)
	', `
		m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -fintegrated-as)
	')

	m4_divert(-1)
	#TODO!!! if using bitcode remove need for lld
	#TODO!!! option for archives to not be bitcode
	m4_divert

	m4_ifdef(`__USE_LLVM_AS', `
		m4_include(__private/toolset|llvm_as.m4)
	', `
		m4_ifdef(`EMSCRIPTEN', `
			m4_define(__OBJ_EXT, wasm)
		', `
			m4_define(__OBJ_EXT, o)
		')
		m4_define(__AR_EXT, a)

		m4_ifdef(`__SEPARATE_AS', `
			m4_ifdef(`EMSCRIPTEN', `
				m4_define(__AS_EXT, wat)
				m4_define(__AS_EXEC, wasm-as)
			', `
				m4_define(__AS_EXT, s)
				m4_define(__AS_EXEC, as)
			')

rule as
__HACK_SPACE`'command=m4_defn(`__COLLECT_WARNED_EXEC') __AS_EXEC $in -o $out

			m4_undefine(`__AS_EXEC')
		')

		m4_ifdef(`EMSCRIPTEN', `
rule wasm_ctor_eval
__HACK_SPACE`'command=wasm-ctor-eval $in -o $out

rule wasm_opt
__HACK_SPACE`'command=wasm-opt $in -o $out
		')

		m4_ifdef(`EMSCRIPTEN', `
			m4_define(__AR_EXEC, emar)
		', `
			m4_define(__AR_EXEC, llvm-ar)
		')

rule ar
__HACK_SPACE`'command=__AR_EXEC -rcs $out $in

		m4_undefine(`__AR_EXEC')
	')
')

m4_ifelse(TOOLSET, gnu, `
	m4_define(__VALID_TOOLSET, `')

	m4_ifdef(`__SEPARATE_PP', `
		m4_ifdef(`MINGW', `
			m4_define(__CPP_EXEC, __MINGW_PREFIX-cpp)
		', `
			m4_ifdef(`WINE', `
				m4_define(__CPP_EXEC, winecpp)
			', `
				m4_define(__CPP_EXEC, cpp)
			')
		')
	')

	m4_ifdef(`MINGW', `
		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__MINGW_VER, __C_VERSION(mingw-64))

			m4_define(__TOOLSET_INC_DIRS, -isystem /usr/lib/gcc/__MINGW_PREFIX/__MINGW_VER/include -isystem /usr/lib/gcc/__MINGW_PREFIX/__MINGW_VER/include-fixed)
		')

		m4_undefine(`__MINGW_VER')
	', `
		m4_define(__GCC_VER, __C_VERSION(gcc))

		m4_ifelse(ARCHITECTURE, x86-64, `
			m4_define(__TOOLSET_INC_DIRS, -isystem /usr/lib/gcc/x86_64-pc-linux-gnu/__GCC_VER/include -isystem /usr/lib/gcc/x86_64-pc-linux-gnu/__GCC_VER/include-fixed)
		')

		m4_undefine(`__GCC_VER')
	')

	m4_ifelse(LIBC, musl, `
		m4_divert(-1)
		#m4_define(__CXX_EXEC, musl-gcc)
		#m4_define(__CC_EXEC, musl-gcc)
		m4_divert
		m4_define(__CXX_EXEC, g++)
		m4_define(__CC_EXEC, gcc)
	', `
		m4_ifdef(`MINGW', `
			m4_define(__CXX_EXEC, __MINGW_PREFIX-g++)
			m4_define(__CC_EXEC, __MINGW_PREFIX-gcc)
		', `
			m4_ifdef(`WINE', `
				m4_define(__CXX_EXEC, wineg++)
				m4_define(__CC_EXEC, winegcc)
			', `
				m4_define(__CXX_EXEC, g++)
				m4_define(__CC_EXEC, gcc)
			')
		')
	')

	m4_ifdef(`__SEPARATE_AS', `
		m4_define(__AS_EXT, s)
		m4_define(`__TOOLSET_AS_MOD', s)

		m4_ifdef(`MINGW', `
			m4_define(__AS_EXEC, __MINGW_PREFIX-as)
		', `
			m4_define(__AS_EXEC, as)
		')

rule as
__HACK_SPACE`'command=m4_defn(`__COLLECT_WARNED_EXEC') __AS_EXEC $in -o $out

		m4_undefine(`__AS_EXEC')
	')

	m4_define(__OBJ_EXT, o)
	m4_define(__AR_EXT, a)

	m4_ifdef(`MINGW', `
		m4_define(__AR_EXEC, __MINGW_PREFIX-gcc-ar)
	', `
		m4_define(__AR_EXEC, gcc-ar)
	')

rule ar
__HACK_SPACE`'command=__AR_EXEC -rcs $out $in

	m4_undefine(`__AR_EXEC')
')

m4_ifdef(`__VALID_TOOLSET', `m4_undefine(`__VALID_TOOLSET')', `ERROR(invalid toolset value: TOOLSET)')

m4_ifelse(LD, lld, `
	m4_define(__LD_EXEC, ld.lld)
	m4_define(__LLD_LIKE, `')
')

m4_ifelse(LD, wasm-lld, `
	m4_define(__LD_EXEC, wasm-ld)
	m4_define(__LLD_LIKE, `')

	m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS') --no-entry)
')

m4_ifdef(`__LLD_LIKE', `
	m4_define(__VALID_LD, `')

	m4_ifdef(`EMSCRIPTEN', `', `
		m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS') --nostdlib)
	')
	m4_define(`__LD_FLAGS_EXEC', m4_defn(`__LD_FLAGS_EXEC') --pie)
	m4_define(`__LD_FLAGS_LIB', m4_defn(`__LD_FLAGS_LIB') --shared)
')

m4_ifelse(LD, gold, `
	m4_define(__LD_EXEC, ld.gold)
	m4_define(__LD_LIKE, `')
')

m4_ifelse(LD, bfd, `
	m4_ifdef(`MINGW', `
		m4_define(__LD_EXEC, __MINGW_PREFIX-ld.bfd)
	', `
		m4_define(__LD_EXEC, ld.bfd)
	')
	m4_define(__LD_LIKE, `')
')

m4_ifelse(LD, ld, `
	m4_ifelse(LIBC, musl, `
		m4_ifelse(TOOLSET, llvm, `
			m4_divert(-1)
			#m4_define(__LD_EXEC, ld.musl-clang)
			m4_divert
		')
	')

	m4_ifdef(`MINGW', `
		m4_define(__LD_EXEC, __MINGW_PREFIX-ld)
	')

	m4_ifdef(`__LD_EXEC', `', `
		m4_define(__LD_EXEC, ld)
	')

	m4_define(__LD_LIKE, `')
')

m4_ifdef(`__LD_LIKE', `
	m4_define(__VALID_LD, `')

	m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS') -nostdlib)
	m4_define(`__LD_FLAGS_EXEC', m4_defn(`__LD_FLAGS_EXEC') -pie)
	m4_define(`__LD_FLAGS_LIB', m4_defn(`__LD_FLAGS_LIB') -shared)
')

m4_ifdef(`__VALID_LD', `m4_undefine(`__VALID_LD')', `ERROR(invalid ld value: LD)')