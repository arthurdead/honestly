m4_define(__SUPPORT_SCRIPT, __SUPPORT_DIR/$1.sh)

m4_define(__HOST_ARCH, m4_esyscmd(__SUPPORT_SCRIPT(host_arch)))
m4_define(__HOST_DIST, m4_esyscmd(__SUPPORT_SCRIPT(host_dist)))

m4_ifelse(__HOST_ARCH, x86-64, `
	m4_define(__VALID_ARCHITECTURE, `')
')

m4_ifdef(`__VALID_ARCHITECTURE', `m4_undefine(`__VALID_ARCHITECTURE')', `m4_errprint(unsupported host archtecture: __HOST_ARCH
) m4_m4exit(1)')

m4_ifelse(__HOST_DIST, Arch Linux, `
	m4_define(__VALID_DISTRIBUTION, `')
')

m4_ifdef(`__VALID_DISTRIBUTION', `m4_undefine(`__VALID_DISTRIBUTION')', `m4_errprint(unsupported host distribution: __HOST_DIST
) m4_m4exit(1)')

m4_undefine(`__SUPPORT_SCRIPT')
m4_include(helpers.m4)

m4_define(__HASH, `m4_esyscmd(__SUPPORT_SCRIPT(hash) "$1")')
m4_define(__C_VERSION, `m4_esyscmd(__SUPPORT_SCRIPT(c_version) $1)')
m4_define(__BASE_PATH, `m4_esyscmd(dirname $1)')
m4_define(__REVERSE, `m4_esyscmd(__SUPPORT_SCRIPT(reverse) $@)')
m4_define(__REMOVE_WHITESPACE, `m4_esyscmd(__SUPPORT_SCRIPT(remove_whitespace) $1)')

m4_define(__HACK_SPACE, £)

m4_divert(-1)
#TODO!!! implement unified mode
m4_divert

m4_include(__private/options.m4)
m4_include(__private/sanity.m4)

m4_define(__BASE_PROJECT_BUILDDIR, __OUTPUT_DIR)

m4_define(__THIS_PROJECT_BUILDDIR, `__PROJECT_BUILDDIR(PROJECT)')

m4_ifdef(`COLLECT_WARNED', `
	m4_define(__COLLECT_WARNED_EXEC, __COLLECT_WARNINGS_FILE=$__COLLECT_WARNINGS_FILE __COLLECT_WARNINGS_OUTPUT=$__COLLECT_WARNINGS_OUTPUT __SUPPORT_SCRIPT(collect_warned))

	m4_define(__COLLECT_WARNINGS_FILE__, `__HACK_SPACE`'__COLLECT_WARNINGS_FILE=m4_indir(`__THIS_PROJECT_BUILDDIR')/warned.txt')
', `
	m4_define(__COLLECT_WARNINGS_FILE__, `')
')

m4_ifdef(`EMSCRIPTEN', `
	m4_define(`EMSCRIPTEN_LLVM_ROOT', /opt/emscripten-llvm)
	m4_define(__EMSCRIPTEN_CACHE, m4_esyscmd(echo -n $HOME/.emscripten_cache))
')

m4_ifdef(`WASI', `
	m4_define(`WASI_SDK_ROOT', /opt/wasi-sdk)
')

m4_ifdef(`MINGW', `
	m4_ifelse(ARCHITECTURE, x86-64, `
		m4_define(__MINGW_PREFIX, x86_64-w64-mingw32)
	')
')

m4_include(__private/architecture.m4)
m4_include(__private/librt.m4)
m4_include(__private/libcpp.m4)
m4_include(__private/libc.m4)

m4_ifelse(TOOLSET, llvm, `
	m4_divert(-1)
	#m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -nobuiltininc -nostdlibinc)
	m4_divert
')
m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -nostdinc)
m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -nostdinc++)

m4_define(`PCH_IS_SUPPORTED', `')

m4_ifdef(`EMSCRIPTEN', `
	m4_undefine(`PCH_IS_SUPPORTED')
')

m4_ifdef(`WINE', `
	m4_undefine(`PCH_IS_SUPPORTED')
')

m4_include(__private/default_flags.m4)

m4_include(__private/toolset_mods.m4)

m4_ifdef(`WASI', `
	m4_define(`__LIBC_MOD', m4_defn(`__LIBC_MOD')~wasi)
	m4_define(`__LIBCPP_MOD', m4_defn(`__LIBCPP_MOD')~wasi)
')

m4_ifdef(`INFO_COMMENT', `
	m4_define(__MSG_AND_COMMENT, `
		MSG($1)
`#'m4_patsubst(`$1', `
', `
#')
	')

__MSG_AND_COMMENT(ccache = m4_defn(`CCACHE')
toolset = TOOLSET
  cpp mod = m4_defn(`__TOOLSET_CPP_MOD')
  as mod = m4_defn(`__TOOLSET_AS_MOD')
  ar mod = m4_defn(`__TOOLSET_AR_MOD')
  obj mod = m4_defn(`__TOOLSET_OBJ_MOD')
ld = LD`'m4_ifdef(`LSB', `~lsb')
configuration = CONFIGURATION
architecture = ARCHITECTURE
librt = LIBRT
libunwind = LIBUNWIND
libcpp = LIBCPP
  mod = m4_defn(`__LIBCPP_MOD')
libcpp_abi = LIBCPP_ABI
libc = LIBC
  mod = m4_defn(`__LIBC_MOD'))
')

builddir=__OUTPUT_DIR

m4_include(__private/toolset.m4)

m4_ifdef(`EMSCRIPTEN', `
	m4_define(`__SYSTEM_INC_DIRS', -isystem /usr/lib/emscripten/system/include)
')

m4_ifdef(`MINGW', `
	m4_define(`__SYSTEM_INC_DIRS', `')
')

m4_ifdef(`__SYSTEM_INC_DIRS', `', `
	m4_ifelse(LIBC, glibc, `
		m4_define(`__SYSTEM_INC_DIRS', `')
	', `
		m4_define(`__SYSTEM_INC_DIRS', -isystem /usr/include)
	')
')

m4_ifdef(`WINE', `
	m4_define(`__SYSTEM_INC_DIRS', m4_defn(`__SYSTEM_INC_DIRS') -isystem /usr/include/wine/windows)
')

m4_define(`__CC_CPP_FLAGS', m4_defn(`__CC_CPP_FLAGS') __SYSTEM_INC_DIRS __LIBC_INC_DIRS __TOOLSET_INC_DIRS)
m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') __SYSTEM_INC_DIRS __LIBCPP_INC_DIRS __LIBC_INC_DIRS __TOOLSET_INC_DIRS)

m4_define(`__OPTIONAL_LIB_DIR', `m4_ifdef(`$1', `-L` '$1', `')')

m4_define(`__CC_LD_FLAGS', m4_defn(`__CC_LD_FLAGS') -L`'__LIBC_LIB_DIR -L`'__LIBRT_LIB_DIR)
m4_define(`__CXX_LD_FLAGS', m4_defn(`__CXX_LD_FLAGS') -L`'__LIBCPP_LIB_DIR -L`'__LIBCPP_ABI_LIB_DIR __OPTIONAL_LIB_DIR(`__LIBUNWIND_LIB_DIR') -L`'__LIBC_LIB_DIR -L`'__LIBRT_LIB_DIR)

m4_define(__CC_INTERNAL_LIBS, __LIBRT_LIB)
m4_define(__CXX_INTERNAL_LIBS, __LIBRT_LIB m4_defn(`__LIBUNWIND_LIB'))

m4_ifdef(`EMSCRIPTEN', `
	m4_define(`__LD_IN_DEFINED')

	m4_define(__CXX_LD_IN_FLAGS_BASE, $1 $ldflags $cxx_ldflags __LIBCPP_LIBS __LIBCPP_ABI_LIBS __CXX_INTERNAL_LIBS -lc __CXX_INTERNAL_LIBS)
	m4_define(__CC_LD_IN_FLAGS_BASE, $1 $ldflags $cc_ldflags __CC_INTERNAL_LIBS -lc __CC_INTERNAL_LIBS)

	m4_define(__CXX_LD_IN_FLAGS_EXEC, __CXX_LD_IN_FLAGS_BASE($1))
	m4_define(__CC_LD_IN_FLAGS_EXEC, __CC_LD_IN_FLAGS_BASE($1))
')

m4_ifdef(`__LD_IN_DEFINED', `
	m4_undefine(`__LD_IN_DEFINED')
', `
	m4_define(__CXX_LD_IN_FLAGS_BASE, __LIBC_LIB_DIR/crti.o __LIBRT_LIB_DIR/__LIBRT_CRTBEGIN $1 $ldflags $cxx_ldflags __LIBCPP_LIBS __LIBCPP_ABI_LIBS -lm __CXX_INTERNAL_LIBS -lc __CXX_INTERNAL_LIBS __LIBRT_LIB_DIR/__LIBRT_CRTEND __LIBC_LIB_DIR/crtn.o)
	m4_define(__CC_LD_IN_FLAGS_BASE, __LIBC_LIB_DIR/crti.o __LIBRT_LIB_DIR/__LIBRT_CRTBEGIN $1 $ldflags $cc_ldflags -lm __CC_INTERNAL_LIBS -lc __CC_INTERNAL_LIBS __LIBRT_LIB_DIR/__LIBRT_CRTEND __LIBC_LIB_DIR/crtn.o)

	m4_define(__CXX_LD_IN_FLAGS_EXEC, __LIBC_LIB_DIR/Scrt1.o __CXX_LD_IN_FLAGS_BASE($1))
	m4_define(__CC_LD_IN_FLAGS_EXEC, __LIBC_LIB_DIR/Scrt1.o __CC_LD_IN_FLAGS_BASE($1))
')

m4_undefine(`__CC_INTERNAL_LIBS')
m4_undefine(`__CXX_INTERNAL_LIBS')

m4_define(__CXX_LD_IN_FLAGS_LIB, __CXX_LD_IN_FLAGS_BASE($1))
m4_define(__CC_LD_IN_FLAGS_LIB, __CC_LD_IN_FLAGS_BASE($1))

m4_ifelse(m4_defn(`CCACHE'), ccache, `
	m4_define(`__CCACHE_ENVVARS', m4_defn(`__CCACHE_ENVVARS') CCACHE_COMPILER=)

	m4_ifelse(TOOLSET, llvm, `
		m4_define(`__CCACHE_ENVVARS', m4_defn(`__CCACHE_ENVVARS') CCACHE_COMPILERTYPE=clang)
	')
	m4_ifelse(TOOLSET, gnu, `
		m4_define(`__CCACHE_ENVVARS', m4_defn(`__CCACHE_ENVVARS') CCACHE_COMPILERTYPE=gcc)
	')
')

m4_define(__BASE_CPP_RULE, m4_defn(`__COLLECT_WARNED_EXEC'))
m4_define(__BASE_C_RULE, m4_defn(`__CCACHE_ENVVARS') m4_defn(`__COLLECT_WARNED_EXEC') m4_defn(`__CCACHE_EXEC'))
m4_define(__BASE_LD_RULE, m4_defn(`__COLLECT_WARNED_EXEC') __LD_EXEC m4_defn(`__LD_FLAGS') -o $out)
m4_define(__CXX_LD_RULE, __BASE_LD_RULE m4_defn(`__CXX_LD_FLAGS'))
m4_define(__CC_LD_RULE, __BASE_LD_RULE m4_defn(`__CC_LD_FLAGS'))

m4_ifelse(TOOLSET, llvm, `
	m4_define(`THIRDPARTY_CPP_FLAGS', m4_defn(`THIRDPARTY_CPP_FLAGS') -Wno-documentation-unknown-command)
')
m4_define(`THIRDPARTY_CPP_FLAGS', m4_defn(`THIRDPARTY_CPP_FLAGS') -Wno-undef -include __SUPPORT_DIR/thirdparty_fixes.h)

m4_define(`THIRDPARTY_C_FLAGS', m4_defn(`THIRDPARTY_C_FLAGS') -Wno-sign-conversion -Wno-shadow-field -Wno-comma -Wno-unreachable-code -Wno-unreachable-code-break -Wno-missing-variable-declarations -Wno-implicit-function-declaration -Wno-cast-qual -Wno-int-to-pointer-cast -Wno-bad-function-cast -Wno-missing-prototypes -Wno-int-conversion -Wno-shorten-64-to-32 -Wno-disabled-macro-expansion)

m4_ifdef(`ZAPCC', `
	m4_define(`THIRDPARTY_C_FLAGS', m4_defn(`THIRDPARTY_C_FLAGS') -Wno-conversion)
', `
	m4_define(`THIRDPARTY_C_FLAGS', m4_defn(`THIRDPARTY_C_FLAGS') -Wno-extra-semi-stmt -Wno-implicit-int-conversion -Wno-deprecated-declarations)
	m4_define(`THIRDPARTY_CXX_FLAGS', m4_defn(`THIRDPARTY_CXX_FLAGS') -Wno-suggest-destructor-override -Wno-suggest-override)
')

m4_define(`THIRDPARTY_CXX_FLAGS', m4_defn(`THIRDPARTY_CXX_FLAGS') -Wno-zero-as-null-pointer-constant -Wno-non-virtual-dtor -Wno-shadow-field-in-constructor -Wno-weak-vtables -Wno-exit-time-destructors -Wno-old-style-cast)

m4_define(__CXX_PP_CMD_BITS, m4_defn(`__CPP_FLAGS') m4_defn(`__CPP_C_FLAGS') m4_defn(`__CXX_CPP_FLAGS') m4_defn(`__CPP_CXX_FLAGS') $cppflags $cxx_cppflags $cpp_c_flags $cpp_cxx_flags)
m4_define(__CC_PP_CMD_BITS, m4_defn(`__CPP_FLAGS') m4_defn(`__CPP_C_FLAGS') m4_defn(`__CC_CPP_FLAGS') m4_defn(`__CPP_CC_FLAGS') $cppflags $cc_cppflags $cpp_c_flags $cpp_cc_flags)
m4_define(__CXX_CMD_BITS, m4_defn(`__C_FLAGS') m4_defn(`__CXX_FLAGS') m4_defn(`__CPP_C_FLAGS') m4_defn(`__CPP_CXX_FLAGS') $cflags $cxxflags $cpp_c_flags $cpp_cxx_flags)
m4_define(__CC_CMD_BITS, m4_defn(`__C_FLAGS') m4_defn(`__CC_FLAGS') m4_defn(`__CPP_C_FLAGS') m4_defn(`__CPP_CC_FLAGS') $cflags $ccflags $cpp_c_flags $cpp_cc_flags)

m4_ifdef(`__SEPARATE_AS', `
	m4_define(__TMP_C_MODE, -S)
', `
	m4_define(__TMP_C_MODE, -c)
')

m4_ifelse(TOOLSET, llvm, `
	m4_define(__TMP_PCH_ARG, --precompile)
', `
	m4_define(__TMP_PCH_ARG, `')
')

m4_ifdef(`__SEPARATE_PP', `
	m4_ifelse(TOOLSET, llvm, `
		m4_divert(-1)
		#m4_define(__TMP_LANG_CXX_PCH_PP, c++-header-cpp-output)
		#m4_define(__TMP_LANG_CC_PCH_PP, c-header-cpp-output)
		m4_divert
		m4_define(__TMP_LANG_CXX_PCH_PP, c++-header)
		m4_define(__TMP_LANG_CC_PCH_PP, c-header)
		m4_define(__TMP_PP_ARG, --no-integrated-cpp)
	', `
		m4_define(__TMP_LANG_CXX_PCH_PP, c++-header)
		m4_define(__TMP_LANG_CC_PCH_PP, c-header)
		m4_define(__TMP_PP_ARG, -fpreprocessed -no-integrated-cpp)
	')

	m4_ifdef(`__PCH_NO_SEPARATE_PP', `
		m4_define(__TMP_PCH_PP_ARG, `')
		m4_define(__PCH_CXX_CMD_BITS, __CXX_PP_CMD_BITS -D__PCH__ __CXX_CMD_BITS)
		m4_define(__PCH_CC_CMD_BITS, __CC_PP_CMD_BITS -D__PCH__ __CC_CMD_BITS)
	', `
		m4_define(__TMP_PCH_PP_ARG, __TMP_PP_ARG)
		m4_define(__PCH_CXX_CMD_BITS, __CXX_CMD_BITS)
		m4_define(__PCH_CC_CMD_BITS, __CC_CMD_BITS)
		m4_define(__PCH_CXX_PP_CMD_BITS, __CXX_PP_CMD_BITS -D__PCH__)
		m4_define(__PCH_CC_PP_CMD_BITS, __CC_PP_CMD_BITS -D__PCH__)
	')

	m4_ifdef(`__CPP_IS_C', `
		m4_define(__TMP_CXX_CPP_EXEC, __CXX_EXEC)
		m4_define(__TMP_CC_CPP_EXEC, __CC_EXEC)
		m4_define(__TMP_CPP_MODE, -E)
	', `
		m4_define(__TMP_CXX_CPP_EXEC, __CPP_EXEC)
		m4_define(__TMP_CC_CPP_EXEC, __CPP_EXEC)
		m4_define(__TMP_CPP_MODE, `')
	')

rule cpp_cxx
__HACK_SPACE`'command=__BASE_CPP_RULE __TMP_CXX_CPP_EXEC __CXX_PP_CMD_BITS -MMD -x c++ __TMP_CPP_MODE $in -o $out
__HACK_SPACE`'deps=gcc
rule cpp_cc
__HACK_SPACE`'command=__BASE_CPP_RULE __TMP_CC_CPP_EXEC __CC_PP_CMD_BITS -MMD -x c __TMP_CPP_MODE $in -o $out
__HACK_SPACE`'deps=gcc
	m4_ifdef(`__PCH_NO_SEPARATE_PP', `', `
rule cpp_pch_cxx
__HACK_SPACE`'command=__BASE_CPP_RULE __TMP_CXX_CPP_EXEC __PCH_CXX_PP_CMD_BITS -x c++ __TMP_CPP_MODE $in -o $out
rule cpp_pch_cc
__HACK_SPACE`'command=__BASE_CPP_RULE __TMP_CC_CPP_EXEC __PCH_CC_PP_CMD_BITS -x c __TMP_CPP_MODE $in -o $out
	')
rule cxx
__HACK_SPACE`'command=__BASE_C_RULE __CXX_EXEC __CXX_CMD_BITS __TMP_PP_ARG -x c++-cpp-output __TMP_C_MODE $in -o $out
rule cc
__HACK_SPACE`'command=__BASE_C_RULE __CC_EXEC __CC_CMD_BITS __TMP_PP_ARG -x c-cpp-output __TMP_C_MODE $in -o $out
rule cxx_pch
__HACK_SPACE`'command=__BASE_C_RULE __CXX_EXEC __PCH_CXX_CMD_BITS __TMP_PCH_PP_ARG __TMP_PCH_ARG -x __TMP_LANG_CXX_PCH_PP $in -o $out
rule cc_pch
__HACK_SPACE`'command=__BASE_C_RULE __CC_EXEC __PCH_CC_CMD_BITS __TMP_PCH_PP_ARG __TMP_PCH_ARG -x __TMP_LANG_CC_PCH_PP $in -o $out

	m4_undefine(`__PCH_CXX_PP_CMD_BITS')
	m4_undefine(`__PCH_CC_PP_CMD_BITS')
	m4_undefine(`__PCH_CXX_CMD_BITS')
	m4_undefine(`__PCH_CC_CMD_BITS')
	m4_undefine(`__TMP_PCH_PP_ARG')
	m4_undefine(`__TMP_PP_ARG')
	m4_undefine(`__TMP_CPP_MODE')
	m4_undefine(`__TMP_LANG_CXX_PCH_PP')
	m4_undefine(`__TMP_LANG_CC_PCH_PP')
	m4_undefine(`__TMP_CXX_CPP_EXEC')
	m4_undefine(`__TMP_CC_CPP_EXEC')
', `
rule cxx
__HACK_SPACE`'command=__BASE_C_RULE __CXX_EXEC __CXX_PP_CMD_BITS __CXX_CMD_BITS -MMD -x c++ __TMP_C_MODE $in -o $out
__HACK_SPACE`'deps=gcc
rule cxx_pch
__HACK_SPACE`'command=__BASE_C_RULE __CXX_EXEC __CXX_PP_CMD_BITS -D__PCH__ __CXX_CMD_BITS __TMP_PCH_ARG -x c++-header $in -o $out
rule cc
__HACK_SPACE`'command=__BASE_C_RULE __CC_EXEC __CC_PP_CMD_BITS __CC_CMD_BITS -MMD -x c __TMP_C_MODE $in -o $out
__HACK_SPACE`'deps=gcc
rule cc_pch
__HACK_SPACE`'command=__BASE_C_RULE __CC_EXEC __CC_PP_CMD_BITS -D__PCH__ __CC_CMD_BITS __TMP_PCH_ARG -x c-header $in -o $out
')

m4_undefine(`__TMP_PCH_ARG')
m4_undefine(`__TMP_C_MODE')
m4_undefine(`__CXX_PP_CMD_BITS')
m4_undefine(`__CC_PP_CMD_BITS')
m4_undefine(`__CXX_CMD_BITS')
m4_undefine(`__CC_CMD_BITS')

rule ld_exec_cc
__HACK_SPACE`'command=__CC_LD_RULE m4_defn(`__LD_FLAGS_EXEC') __CC_LD_IN_FLAGS_EXEC($in)
rule ld_exec_cxx
__HACK_SPACE`'command=__CXX_LD_RULE m4_defn(`__LD_FLAGS_EXEC') __CXX_LD_IN_FLAGS_EXEC($in)
rule ld_lib_cc
__HACK_SPACE`'command=__CC_LD_RULE m4_defn(`__LD_FLAGS_LIB') __CC_LD_IN_FLAGS_LIB($in)
rule ld_lib_cxx
__HACK_SPACE`'command=__CXX_LD_RULE m4_defn(`__LD_FLAGS_LIB') __CXX_LD_IN_FLAGS_LIB($in)
rule symlink
__HACK_SPACE`'command=ln -sfT $in $out

m4_define(__CC_CPP_UNIQUE_ID, TOOLSET`'m4_defn(`__TOOLSET_CPP_MOD')`|'ARCHITECTURE`|'CONFIGURATION`|'LIBC`'m4_defn(`__LIBC_MOD'))
m4_define(__CC_CPP_HASH, __HASH(__CC_CPP_UNIQUE_ID))

m4_define(__CXX_CPP_UNIQUE_ID, __CC_CPP_UNIQUE_ID`|'LIBCPP`'m4_defn(`__LIBCPP_MOD'))
m4_define(__CXX_CPP_HASH, __HASH(__CXX_CPP_UNIQUE_ID))

m4_ifdef(`__SEPARATE_AS', `
	m4_define(__CXX_AS_UNIQUE_ID, __CXX_CPP_UNIQUE_ID`|'m4_defn(`__TOOLSET_AS_MOD'))
	m4_define(__CXX_AS_HASH, __HASH(__CXX_AS_UNIQUE_ID))

	m4_define(__CC_AS_UNIQUE_ID, __CC_CPP_UNIQUE_ID`|'m4_defn(`__TOOLSET_AS_MOD'))
	m4_define(__CC_AS_HASH, __HASH(__CC_AS_UNIQUE_ID))

	m4_define(__CXX_OBJ_UNIQUE_ID, __CXX_AS_UNIQUE_ID`|'m4_defn(`__TOOLSET_OBJ_MOD'))
	m4_define(__CC_OBJ_UNIQUE_ID, __CC_AS_UNIQUE_ID`|'m4_defn(`__TOOLSET_OBJ_MOD'))
', `
	m4_define(__CXX_OBJ_UNIQUE_ID, __CXX_CPP_UNIQUE_ID`|'m4_defn(`__TOOLSET_OBJ_MOD'))
	m4_define(__CC_OBJ_UNIQUE_ID, __CC_CPP_UNIQUE_ID`|'m4_defn(`__TOOLSET_OBJ_MOD'))
')

m4_define(__CXX_OBJ_HASH, __HASH(__CXX_OBJ_UNIQUE_ID))
m4_define(__CC_OBJ_HASH, __HASH(__CC_OBJ_UNIQUE_ID))

m4_define(__CXX_AR_UNIQUE_ID, __CXX_OBJ_UNIQUE_ID`|'m4_defn(`__TOOLSET_AR_MOD'))
m4_define(__CXX_AR_HASH, __HASH(__CXX_AR_UNIQUE_ID))

m4_define(__CC_AR_UNIQUE_ID, __CC_OBJ_UNIQUE_ID`|'m4_defn(`__TOOLSET_AR_MOD'))
m4_define(__CC_AR_HASH, __HASH(__CC_AR_UNIQUE_ID))

m4_define(__CXX_SO_UNIQUE_ID, __CXX_OBJ_UNIQUE_ID`|'LD)
m4_define(__CC_SO_UNIQUE_ID, __CC_OBJ_UNIQUE_ID`|'LD)
m4_ifdef(`LSB', `
	m4_define(`__CXX_SO_UNIQUE_ID', __CXX_SO_UNIQUE_ID`~lsb')
	m4_define(`__CC_SO_UNIQUE_ID', __CC_SO_UNIQUE_ID`~lsb')
')
m4_define(`__CXX_SO_UNIQUE_ID', __CXX_SO_UNIQUE_ID`|'LIBCPP_ABI`|'LIBRT`|'LIBUNWIND)
m4_define(__CXX_SO_HASH, __HASH(__CXX_SO_UNIQUE_ID))

m4_define(__CC_SO_HASH, __HASH(__CC_SO_UNIQUE_ID))

m4_define(__PROJECT_BUILDDIR, __BASE_PROJECT_BUILDDIR/$1)

m4_define(__BASE_C_PP_RULE_BITS, `__HACK_SPACE`'cppflags=$cppflags m4_defn(__`'PROJECT`'_CPP_FLAGS) m4_defn(`__LIBRARY_CPP_FLAGS') m4_defn(__`'__SRC_FILE_HASH`'_CPP_FLAGS)')
m4_define(__BASE_CXX_PP_RULE_BITS, `__HACK_SPACE`'cxx_cppflags=$cxx_cppflags m4_defn(__`'PROJECT`'_CXX_CPP_FLAGS) m4_defn(`__LIBRARY_CXX_CPP_FLAGS') m4_defn(__`'__SRC_FILE_HASH`'_CXX_CPP_FLAGS)
__BASE_C_PP_RULE_BITS')
m4_define(__BASE_CC_PP_RULE_BITS, `__HACK_SPACE`'cc_cppflags=$cc_cppflags m4_defn(__`'PROJECT`'_CC_CPP_FLAGS) m4_defn(`__LIBRARY_CC_CPP_FLAGS') m4_defn(__`'__SRC_FILE_HASH`'_CC_CPP_FLAGS)
__BASE_C_PP_RULE_BITS')

m4_define(__BASE_C_RULE_BITS, `__HACK_SPACE`'cflags=$cflags m4_defn(__`'PROJECT`'_C_FLAGS) m4_defn(`__LIBRARY_C_FLAGS') m4_defn(__`'__SRC_FILE_HASH`'_C_FLAGS)')
m4_define(__BASE_CXX_RULE_BITS, `__HACK_SPACE`'cxxflags=$cxxflags m4_defn(__`'PROJECT`'_CXX_FLAGS) m4_defn(`__LIBRARY_CXX_FLAGS') m4_defn(__`'__SRC_FILE_HASH`'_CXX_FLAGS)
__BASE_C_RULE_BITS')
m4_define(__BASE_CC_RULE_BITS, `__HACK_SPACE`'ccflags=$ccflags m4_defn(__`'PROJECT`'_CC_FLAGS) m4_defn(`__LIBRARY_CC_FLAGS') m4_defn(__`'__SRC_FILE_HASH`'_CC_FLAGS)
__BASE_C_RULE_BITS')

m4_include(__private/loop_files.m4)

m4_ifdef(`EMSCRIPTEN', `
	m4_define(`__SO_EXT', wasm)
	m4_define(`__EXEC_EXT', wasm)
')
m4_ifdef(`WINE', `
	m4_define(`__SO_EXT', dll.so)
	m4_define(`__EXEC_EXT', elf.exe)
')
m4_ifdef(`MINGW', `
	m4_define(`__SO_EXT', dll)
	m4_define(`__EXEC_EXT', exe)
')
m4_ifdef(`__SO_EXT', `', `
	m4_define(`__SO_EXT', so)
')
m4_ifdef(`__EXEC_EXT', `', `
	m4_define(`__EXEC_EXT', elf)
')

m4_define(CXX_LIB_PATH, `m4_ifelse($1, static_library, `__THIS_PROJECT_BUILDDIR/$1/$2/__CXX_AR_HASH/$2.__AR_EXT', `__THIS_PROJECT_BUILDDIR/$1/$2/__CXX_SO_HASH/$2.__SO_EXT')')
m4_define(CC_LIB_PATH, `m4_ifelse($1, static_library, `__THIS_PROJECT_BUILDDIR/$1/$2/__CC_AR_HASH/$2.__AR_EXT', `__THIS_PROJECT_BUILDDIR/$1/$2/__CC_SO_HASH/$2.__SO_EXT')')

m4_define(__STATIC_LIBRARY, `
	m4_define(__`'PROJECT`'_static_library_$1_PATH, __TMP_LIBRARY_PATH)

	m4_ifelse(TOOLSET, llvm, `
		m4_ifdef(`__LLVM_OPT_BITCODE', `
build __TMP_LIBRARY_PATH/$1.unopt.bc: ar __TMP_OBJLIST
__HACK_SPACE`'description=AR $1
build __TMP_LIBRARY_PATH/$1.opt.bc: opt_bc __TMP_LIBRARY_PATH/$1.unopt.bc
__HACK_SPACE`'description=OPT $1
build __TMP_LIBRARY_PATH/$1.bc: symlink __TMP_LIBRARY_PATH/$1.opt.bc
__HACK_SPACE`'description=LN $1
		', `
build __TMP_LIBRARY_PATH/$1.__AR_EXT: ar __TMP_OBJLIST
__HACK_SPACE`'description=AR $1
		')
	', `
build __TMP_LIBRARY_PATH/$1.__AR_EXT: ar __TMP_OBJLIST
__HACK_SPACE`'description=AR $1
	')

	m4_undefine(`__TMP_LIBRARY_PATH')
	m4_undefine(`__TMP_BUILDDIR')
	m4_undefine(`__TMP_OBJLIST')
')

m4_define(CXX_STATIC_LIBRARY, `
	__LOOP_CXX_FILES($1, static_library, m4_shift($@))

	m4_define(`__TMP_LIBRARY_PATH', __TMP_BUILDDIR/__CXX_AR_HASH)

	__STATIC_LIBRARY($1)
')

m4_define(CC_STATIC_LIBRARY, `
	__LOOP_CC_FILES($1, static_library, m4_shift($@))

	m4_define(`__TMP_LIBRARY_PATH', __TMP_BUILDDIR/__CC_AR_HASH)

	__STATIC_LIBRARY($1)
')

m4_define(CXX_SHARED_LIBRARY, `
	__LOOP_CXX_FILES($1, shared_library, m4_shift($@))

	m4_ifdef(`LIBRARY_PATH', `
		m4_define(`__TMP_LIBRARY_PATH', ABSOLUTE_PATH(LIBRARY_PATH, m, true))
	', `
		m4_define(`__TMP_LIBRARY_PATH', __TMP_BUILDDIR/__CXX_SO_HASH)
	')

	m4_define(__`'PROJECT`'_shared_library_$1_PATH, __TMP_LIBRARY_PATH)

build __TMP_LIBRARY_PATH/$1.__SO_EXT: ld_lib_cxx __TMP_OBJLIST | m4_defn(__`'PROJECT`'_LD_FILES) m4_defn(`__LIBRARY_LD_FILES')
__HACK_SPACE`'cxx_ldflags=$cxx_ldflags __REVERSE(m4_defn(__`'PROJECT`'_LD_FILES)) __REVERSE(m4_defn(`__LIBRARY_LD_FILES')) m4_defn(__`'PROJECT`'_LD_LIBS) m4_defn(`__LIBRARY_LD_LIBS')
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=`LD' $1

m4_ifdef(`LIBRARY_PATH', `
build __TMP_BUILDDIR/__CXX_SO_HASH/$1.__SO_EXT: symlink __TMP_LIBRARY_PATH/$1.__SO_EXT
__HACK_SPACE`'description=LN $1
')

	m4_undefine(`__TMP_LIBRARY_PATH')
	m4_undefine(`__TMP_BUILDDIR')
	m4_undefine(`__TMP_OBJLIST')
	m4_undefine(`__LIBRARY_LD_LIBS')
	m4_undefine(`__LIBRARY_LD_FILES')
	m4_undefine(`LIBRARY_PATH')
')

m4_define(__UNDEFINE_FLAGS, `
	m4_undefine($1`'_CPP_FLAGS)
	m4_undefine($1`'_CPP_CXX_FLAGS)
	m4_undefine($1`'_CPP_CC_FLAGS)
	m4_undefine($1`'_CPP_C_FLAGS)

	m4_undefine($1`'_CXX_CPP_FLAGS)
	m4_undefine($1`'_CC_CPP_FLAGS)

	m4_undefine($1`'_CXX_FLAGS)
	m4_undefine($1`'_CC_FLAGS)
	m4_undefine($1`'_C_FLAGS)

	m4_undefine($1`'_M4_FLAGS)
')

m4_define(__UNDEFINE_TMP_FLAGS, `
	m4_undefine(`CPP_FLAGS')
	m4_undefine(`CPP_CXX_FLAGS')
	m4_undefine(`CPP_CC_FLAGS')
	m4_undefine(`CPP_C_FLAGS')

	m4_undefine(`CXX_CPP_FLAGS')
	m4_undefine(`CC_CPP_FLAGS')

	m4_undefine(`CXX_FLAGS')
	m4_undefine(`CC_FLAGS')
	m4_undefine(`C_FLAGS')

	m4_undefine(`M4_FLAGS')
')

m4_define(CXX_EXECUTABLE, `
	__LOOP_CXX_FILES($1, executable, m4_shift($@))

	m4_ifdef(`LIBRARY_PATH', `
		m4_define(`__TMP_LIBRARY_PATH', ABSOLUTE_PATH(LIBRARY_PATH, m, true))
	', `
		m4_define(`__TMP_LIBRARY_PATH', __TMP_BUILDDIR/__CXX_SO_HASH)
	')

build __TMP_LIBRARY_PATH/$1.__EXEC_EXT: ld_exec_cxx __TMP_OBJLIST | m4_defn(__`'PROJECT`'_LD_FILES) m4_defn(`__LIBRARY_LD_FILES')
__HACK_SPACE`'cxx_ldflags=$cxx_ldflags __REVERSE(m4_defn(__`'PROJECT`'_LD_FILES)) __REVERSE(m4_defn(`__LIBRARY_LD_FILES')) m4_defn(__`'PROJECT`'_LD_LIBS) m4_defn(`__LIBRARY_LD_LIBS')
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=`LD' $1

	m4_undefine(`__TMP_LIBRARY_PATH')
	m4_undefine(`__TMP_BUILDDIR')
	m4_undefine(`__TMP_OBJLIST')
	m4_undefine(`__LIBRARY_LD_LIBS')
	m4_undefine(`__LIBRARY_LD_FILES')
	m4_undefine(`LIBRARY_PATH')
')

m4_ifdef(`PCH_IS_SUPPORTED', `
	m4_define(CXX_PCH, `
		m4_define(`__TMP_BUILDDIR', __THIS_PROJECT_BUILDDIR/pch/$1)

		m4_define(`__FILE_HASHES_PATH', __TMP_BUILDDIR/last_file_hashes.txt)
		m4_define(`__TOOLSET_HASHES_PATH', __TMP_BUILDDIR/last_toolset_hash.txt)

		m4_syscmd(mkdir -p __TMP_BUILDDIR)

		m4_syscmd(truncate -s 0 __TOOLSET_HASHES_PATH)

		m4_syscmd(echo "__CXX_CPP_UNIQUE_ID = __CXX_CPP_HASH" >> __TOOLSET_HASHES_PATH)

		m4_syscmd(truncate -s 0 __FILE_HASHES_PATH)

		FOREACH(`__FILES_IT', (m4_shift($@)), `
			m4_define(`__SRC_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
			m4_define(`__SRC_FILE_HASH', __HASH(__SRC_FILE))
			m4_define(`__TMP_CPP_FILENAME', __TMP_BUILDDIR/__CXX_CPP_HASH/__SRC_FILE_HASH)

			m4_syscmd(echo "__SRC_FILE = __SRC_FILE_HASH" >> __FILE_HASHES_PATH)

			m4_ifdef(__`'__SRC_FILE_HASH`'_DEPS, `
				m4_define(`__DEPS', | __`'__SRC_FILE_HASH`'_DEPS)
			', `
				m4_define(`__DEPS', `')
			')

			m4_ifdef(`__SEPARATE_PP', `
				m4_ifdef(`__PCH_NO_SEPARATE_PP', `', `
					m4_define(__PCH_SEPARATE_PP, `')
				')
			')

			m4_ifdef(`__PCH_SEPARATE_PP', `
				m4_define(`__CXX_SRC_FILE', __TMP_CPP_FILENAME.ii)
			', `
				m4_define(`__CXX_SRC_FILE', __SRC_FILE)
			')

			m4_define(`__CXX_DEPS', __DEPS)
			m4_define(`__CXX_CPPFLAGS', __BASE_CXX_PP_RULE_BITS)

			m4_ifdef(`__PCH_SEPARATE_PP', `
build __CXX_SRC_FILE: cpp_pch_cxx __SRC_FILE __CXX_DEPS
__CXX_CPPFLAGS
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=CPP __SRC_FILE

				m4_define(`__CXX_CPPFLAGS', `')
				m4_define(`__CXX_DEPS', `')
			')

build __TMP_CPP_FILENAME.gch: cxx_pch __CXX_SRC_FILE __CXX_DEPS
__CXX_CPPFLAGS
__BASE_CXX_RULE_BITS
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=`CXX' __SRC_FILE

build __SRC_FILE.gch: symlink __TMP_CPP_FILENAME.gch
__HACK_SPACE`'description=LN __SRC_FILE

			m4_undefine(`__PCH_SEPARATE_PP')
			m4_undefine(`__DEPS')
			m4_undefine(`__SRC_FILE')
			m4_undefine(`__SRC_FILE_HASH')
			m4_undefine(`__CXX_DEPS')
			m4_undefine(`__CXX_SRC_FILE')
			m4_undefine(`__CXX_CPPFLAGS')
			m4_undefine(`__TMP_CPP_FILENAME')
		')

		m4_undefine(`__TOOLSET_HASHES_PATH')
		m4_undefine(`__FILE_HASHES_PATH')

		__UNDEFINE_FLAGS(__LIBRARY)
	')
', `
	m4_divert(-1)
	#TODO!!! remove old pch files
	m4_divert

	m4_define(CXX_PCH, `

	')
')

m4_define(__HANDLE_LOAD_FLAGS, `
	m4_ifdef($2`'_CPP_FLAGS, `
		m4_define($1`'_CPP_FLAGS, m4_defn($1`'_CPP_FLAGS) m4_defn($2`'_CPP_FLAGS))
	')
	m4_ifdef($2`'_CPP_CXX_FLAGS, `
		m4_define($1`'_CPP_CXX_FLAGS, m4_defn($1`'_CPP_CXX_FLAGS) m4_defn($2`'_CPP_CXX_FLAGS))
	')
	m4_ifdef($2`'_CPP_CC_FLAGS, `
		m4_define($1`'_CPP_CC_FLAGS, m4_defn($1`'_CPP_CC_FLAGS) m4_defn($2`'_CPP_CC_FLAGS))
	')
	m4_ifdef($2`'_CPP_C_FLAGS, `
		m4_define($1`'_CPP_C_FLAGS, m4_defn($1`'_CPP_C_FLAGS) m4_defn($2`'_CPP_C_FLAGS))
	')

	m4_ifdef($2`'_CXX_CPP_FLAGS, `
		m4_define($1`'_CXX_CPP_FLAGS, m4_defn($1`'_CXX_CPP_FLAGS) m4_defn($2`'_CXX_CPP_FLAGS))
	')
	m4_ifdef($2`'_CC_CPP_FLAGS, `
		m4_define($1`'_CC_CPP_FLAGS, m4_defn($1`'_CC_CPP_FLAGS) m4_defn($2`'_CC_CPP_FLAGS))
	')

	m4_ifdef($2`'_CXX_FLAGS, `
		m4_define($1`'_CXX_FLAGS, m4_defn($1`'_CXX_FLAGS) m4_defn($2`'_CXX_FLAGS))
	')
	m4_ifdef($2`'_CC_FLAGS, `
		m4_define($1`'_CC_FLAGS, m4_defn($1`'_CC_FLAGS) m4_defn($2`'_CC_FLAGS))
	')
	m4_ifdef($2`'_C_FLAGS, `
		m4_define($1`'_C_FLAGS, m4_defn($1`'_C_FLAGS) m4_defn($2`'_C_FLAGS))
	')

	m4_ifdef($2`'_M4_FLAGS, `
		m4_define($1`'_M4_FLAGS, m4_defn($1`'_M4_FLAGS) m4_defn($2`'_M4_FLAGS))
	')

	__UNDEFINE_TMP_FLAGS
')

m4_define(__HANDLE_STORE_FLAGS, `
	m4_ifdef(`CPP_FLAGS', `
		m4_define($1`'_CPP_FLAGS, m4_defn($1`'_CPP_FLAGS) m4_defn(`CPP_FLAGS'))
	')
	m4_ifdef(`CPP_CXX_FLAGS', `
		m4_define($1`'_CXX_FLAGS, m4_defn($1`'_CXX_FLAGS) m4_defn(`CPP_CXX_FLAGS'))
	')
	m4_ifdef(`CPP_CC_FLAGS', `
		m4_define($1`'_CC_FLAGS, m4_defn($1`'_CC_FLAGS) m4_defn(`CPP_CC_FLAGS'))
	')
	m4_ifdef(`CPP_C_FLAGS', `
		m4_define($1`'_C_FLAGS, m4_defn($1`'_C_FLAGS) m4_defn(`CPP_C_FLAGS'))
	')

	m4_ifdef(`CXX_CPP_FLAGS', `
		m4_define($1`'_CXX_CPP_FLAGS, m4_defn($1`'_CXX_CPP_FLAGS) m4_defn(`CXX_CPP_FLAGS'))
	')
	m4_ifdef(`CC_CPP_FLAGS', `
		m4_define($1`'_CC_CPP_FLAGS, m4_defn($1`'_CC_CPP_FLAGS) m4_defn(`CC_CPP_FLAGS'))
	')

	m4_ifdef(`CXX_FLAGS', `
		m4_define($1`'_CXX_FLAGS, m4_defn($1`'_CXX_FLAGS) m4_defn(`CXX_FLAGS'))
	')
	m4_ifdef(`CC_FLAGS', `
		m4_define($1`'_CC_FLAGS, m4_defn($1`'_CC_FLAGS) m4_defn(`CC_FLAGS'))
	')
	m4_ifdef(`C_FLAGS', `
		m4_define($1`'_C_FLAGS, m4_defn($1`'_C_FLAGS) m4_defn(`C_FLAGS'))
	')

	m4_ifdef(`M4_FLAGS', `
		m4_define($1`'_M4_FLAGS, m4_defn($1`'_M4_FLAGS) m4_defn(`M4_FLAGS'))
	')

	__UNDEFINE_TMP_FLAGS
')

m4_define(LIBRARY_FLAGS, `
	$1

	__HANDLE_STORE_FLAGS(__LIBRARY)
')

m4_define(PROJECT_FLAGS, `
	$1

	__HANDLE_STORE_FLAGS(__`'PROJECT`')
')

m4_define(FILE_FLAGS, `
	m4_define(`__1_SRC_FILE', ABSOLUTE_PATH($1, m, false))
	m4_define(`__SRC_HASH', __HASH(__1_SRC_FILE))

	$2

	__HANDLE_STORE_FLAGS(__`'__SRC_HASH)

	m4_undefine(`__1_SRC_FILE')
	m4_undefine(`__SRC_HASH')
')

m4_define(__BASE_DEP_DEFINE_NAME, `m4_ifelse($2, project, `__DEP_$1', `__DEP_$1_$2_$3')')

m4_define(DECLARE_DEPENDENCY, `
	m4_ifelse($1, project, `
		$2
		m4_define(`__DEP_DEFINE_NAME', __BASE_DEP_DEFINE_NAME(PROJECT, project, `'))
	', `
		$3
		m4_define(`__DEP_DEFINE_NAME', __BASE_DEP_DEFINE_NAME(PROJECT, $1, $2))
	')

	__HANDLE_STORE_FLAGS(__DEP_DEFINE_NAME)

	m4_ifdef(`LD_LIBS', `
		m4_define(__DEP_DEFINE_NAME`'_LD_LIBS, m4_defn(`LD_LIBS'))
	')
	m4_ifdef(`LD_LIBS', `
		m4_define(__DEP_DEFINE_NAME`'_LD_FILES, m4_defn(`LD_FILES'))
	')

	m4_undefine(`__DEP_DEFINE_NAME')
	m4_undefine(`LD_LIBS')
	m4_undefine(`LD_FILES')
')

m4_define(__DEPENDENCY, `
	m4_ifelse($3, project, `
		m4_define(`__DEP_DEFINE_NAME', __BASE_DEP_DEFINE_NAME($2, project, `'))
	', `
		m4_define(`__DEP_DEFINE_NAME', __BASE_DEP_DEFINE_NAME($2, $3, $4))
	')

	__HANDLE_LOAD_FLAGS($1, __DEP_DEFINE_NAME)

	m4_ifdef(__DEP_DEFINE_NAME`'_LD_LIBS, `
		m4_define($1`'_LD_LIBS, m4_defn($1`'_LD_LIBS) m4_defn(__DEP_DEFINE_NAME`'_LD_LIBS))
	')
	m4_ifdef(__DEP_DEFINE_NAME`'_LD_FILES, `
		m4_define($1`'_LD_FILES, m4_defn($1`'_LD_FILES) m4_defn(__DEP_DEFINE_NAME`'_LD_FILES))
	')

	m4_undefine(`__DEP_DEFINE_NAME')
')

m4_define(LIBRARY_DEPENDENCY, `__DEPENDENCY(__LIBRARY, $@)')
m4_define(PROJECT_DEPENDENCY, `__DEPENDENCY(__`'PROJECT, $@)')

m4_define(FILE_DEPENDENCIES, `
	m4_define(`__SRC_FILE', ABSOLUTE_PATH($1, m, false))
	m4_define(`__SRC_HASH', __HASH(__SRC_FILE))
	FOREACH(`__FILES_IT', (m4_shift($@)), `
		m4_define(`__OUT_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
		m4_define(`__TMP_OUTFILES', m4_defn(`__TMP_OUTFILES') __OUT_FILE)
	')
	m4_define(__`'__SRC_HASH`'_DEPS, m4_defn(__`'__SRC_HASH`'_DEPS) __TMP_OUTFILES)
	m4_undefine(`__SRC_FILE')
	m4_undefine(`__SRC_HASH')
	m4_undefine(`__TMP_OUTFILES')
')

m4_define(FILE_DEPENDENCIES_INVERSE, `
	m4_define(`__OUT_FILE', ABSOLUTE_PATH($1, m, false))
	FOREACH(`__FILES_IT', (m4_shift($@)), `
		m4_define(`__SRC_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
		m4_define(`__SRC_HASH', __HASH(__SRC_FILE))
		m4_define(__`'__SRC_HASH`'_DEPS, m4_defn(__`'__SRC_HASH`'_DEPS) __OUT_FILE)
		m4_undefine(`__SRC_FILE')
		m4_undefine(`__SRC_HASH')
	')
	m4_undefine(`__OUT_FILE')
')

m4_define(PHONY, `
	m4_define(`__SRC_FILE', ABSOLUTE_PATH($1, m, false))

	FOREACH(`__FILES_IT', (m4_shift($@)), `
		m4_define(`__OUT_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
		m4_define(`__TMP_OUTFILES', m4_defn(`__TMP_OUTFILES') __OUT_FILE)
		m4_undefine(`__OUT_FILE')
	')

build __SRC_FILE: phony __TMP_OUTFILES

	m4_undefine(`__TMP_OUTFILES')
	m4_undefine(`__SRC_FILE')
')
