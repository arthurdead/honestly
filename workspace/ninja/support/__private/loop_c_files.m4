m4_define(__LOOP_FILES, `
	m4_define(`__LANG_UPPER', UPPERCASE(__LANG))
	m4_define(`__LANG_LOWER', __LANG)

	m4_undefine(`__TMP_OBJLIST')

	m4_define(`__TMP_BUILDDIR', __THIS_PROJECT_BUILDDIR/$2/$1)
	m4_define(`__FILE_HASHES_PATH', __TMP_BUILDDIR/last_file_hashes.txt)
	m4_define(`__TOOLSET_HASHES_PATH', __TMP_BUILDDIR/last_toolset_hash.txt)

	m4_syscmd(mkdir -p __TMP_BUILDDIR)

	m4_define(`__C_CPP_UNIQUE_ID', m4_defn(__`'__LANG_UPPER`'_CPP_UNIQUE_ID))
	m4_define(`__C_CPP_HASH', m4_defn(__`'__LANG_UPPER`'_CPP_HASH))
	m4_ifdef(`__SEPARATE_AS', `
		m4_define(`__C_AS_UNIQUE_ID', m4_defn(__`'__LANG_UPPER`'_AS_UNIQUE_ID))
		m4_define(`__C_AS_HASH', m4_defn(__`'__LANG_UPPER`'_AS_HASH))
	')
	m4_define(`__C_OBJ_UNIQUE_ID', m4_defn(__`'__LANG_UPPER`'_OBJ_UNIQUE_ID))
	m4_define(`__C_OBJ_HASH', m4_defn(__`'__LANG_UPPER`'_OBJ_HASH))
	m4_define(`__C_AR_UNIQUE_ID', m4_defn(__`'__LANG_UPPER`'_AR_UNIQUE_ID))
	m4_define(`__C_AR_HASH', m4_defn(__`'__LANG_UPPER`'_AR_HASH))
	m4_define(`__C_SO_UNIQUE_ID', m4_defn(__`'__LANG_UPPER`'_SO_UNIQUE_ID))
	m4_define(`__C_SO_HASH', m4_defn(__`'__LANG_UPPER`'_SO_HASH))

	m4_ifdef(`__SEPARATE_PP', `', `
		m4_syscmd(mkdir -p __TMP_BUILDDIR/m4_defn(__C_CPP_HASH))
	')

	m4_syscmd(truncate -s 0 __TOOLSET_HASHES_PATH)

	m4_syscmd(echo "__C_CPP_UNIQUE_ID = __C_CPP_HASH" >> __TOOLSET_HASHES_PATH)
	m4_ifdef(`__SEPARATE_AS', `
		m4_syscmd(echo "__C_AS_UNIQUE_ID = __C_AS_HASH" >> __TOOLSET_HASHES_PATH)
	')
	m4_syscmd(echo "__C_OBJ_UNIQUE_ID = __C_OBJ_HASH" >> __TOOLSET_HASHES_PATH)
	m4_syscmd(echo "__C_AR_UNIQUE_ID = __C_AR_HASH" >> __TOOLSET_HASHES_PATH)
	m4_syscmd(echo "__C_SO_UNIQUE_ID = __C_SO_HASH" >> __TOOLSET_HASHES_PATH)

	m4_syscmd(truncate -s 0 __FILE_HASHES_PATH)

	m4_define(`__C_RULE_BITS', `m4_indir(__BASE_`'__LANG_UPPER`'_RULE_BITS)')
	m4_define(`__C_PP_RULE_BITS', `m4_indir(__BASE_`'__LANG_UPPER`'_PP_RULE_BITS)')

	FOREACH(`__FILES_IT', (m4_shift(m4_shift($@))), `
		m4_define(`__SRC_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
		m4_define(`__SRC_FILE_HASH', __HASH(__SRC_FILE))
		m4_define(`__TMP_CPP_FILENAME', __TMP_BUILDDIR/__C_CPP_HASH/__SRC_FILE_HASH)
		m4_ifdef(`__SEPARATE_AS', `
			m4_define(`__TMP_AS_FILENAME', __TMP_BUILDDIR/__C_AS_HASH/__SRC_FILE_HASH)
		')
		m4_define(`__TMP_OBJ_FILENAME', __TMP_BUILDDIR/__C_OBJ_HASH/__SRC_FILE_HASH)

		m4_syscmd(echo "__SRC_FILE = __SRC_FILE_HASH" >> __FILE_HASHES_PATH)

		m4_define(`__TMP_OBJLIST', m4_defn(`__TMP_OBJLIST') __TMP_OBJ_FILENAME.__OBJ_EXT)

		m4_ifdef(__`'__SRC_FILE_HASH`'_DEPS, `
			m4_define(`__DEPS', | __`'__SRC_FILE_HASH`'_DEPS)
		', `
			m4_define(`__DEPS', `')
		')

		m4_ifdef(`__SEPARATE_PP', `
			m4_define(`__C_SRC_FILE', __TMP_CPP_FILENAME`'m4_ifelse(__LANG_LOWER, `cxx', `.ii', `.i'))
		', `
			m4_define(`__C_SRC_FILE', __SRC_FILE)
		')

		m4_define(`__C_DEPS', __DEPS)
		m4_define(`__C_DEPFILE', __HACK_SPACE`'depfile=__TMP_CPP_FILENAME.d)
		m4_define(`__C_CPPFLAGS', __HACK_SPACE`'cppflags=$cppflags -MQ __C_SRC_FILE -MF __TMP_CPP_FILENAME.d
__C_PP_RULE_BITS
)

		m4_ifdef(`__SEPARATE_PP', `
build __C_SRC_FILE: cpp_`'__LANG_LOWER __SRC_FILE __C_DEPS
__C_CPPFLAGS
__C_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=CPP __SRC_FILE

			m4_define(`__C_CPPFLAGS', `')
			m4_define(`__C_DEPFILE', `')
			m4_define(`__C_DEPS', `')
		')

m4_include(__private/c_file.m4)

		m4_undefine(`__DEPS')
		m4_undefine(`__SRC_FILE')
		m4_undefine(`__SRC_FILE_HASH')
		m4_undefine(`__C_DEPS')
		m4_undefine(`__C_SRC_FILE')
		m4_undefine(`__C_CPPFLAGS')
		m4_undefine(`__C_DEPFILE')
		m4_ifdef(`__SEPARATE_AS', `', `
			m4_undefine(`__TMP_AS_FILENAME')
		')
		m4_undefine(`__TMP_CPP_FILENAME')
		m4_undefine(`__TMP_OBJ_FILENAME')
	')

	m4_undefine(`__TOOLSET_HASHES_PATH')
	m4_undefine(`__FILE_HASHES_PATH')
	m4_undefine(`__LIBRARY_CPP_FLAGS')

	m4_undefine(`__C_CPP_UNIQUE_ID')
	m4_undefine(`__C_CPP_HASH')
	m4_ifdef(`__SEPARATE_AS', `
		m4_undefine(`__C_AS_UNIQUE_ID')
		m4_undefine(`__C_AS_HASH')
	')
	m4_undefine(`__C_OBJ_UNIQUE_ID')
	m4_undefine(`__C_OBJ_HASH')
	m4_undefine(`__C_AR_UNIQUE_ID')
	m4_undefine(`__C_AR_HASH')
	m4_undefine(`__C_SO_UNIQUE_ID')
	m4_undefine(`__C_SO_HASH')

	m4_undefine(`__C_RULE_BITS')
	m4_undefine(`__C_PP_RULE_BITS')
	m4_undefine(`__LANG_UPPER')
	m4_undefine(`__LANG_LOWER')
	m4_undefine(`__LANG')
')

m4_define(__LOOP_CXX_FILES, `
	m4_define(`__LANG', cxx)
	__LOOP_FILES($@)
')

m4_define(__LOOP_CC_FILES, `
	m4_define(`__LANG', cc)
	__LOOP_FILES($@)
')