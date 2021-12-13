m4_ifdef(`__REFLEX_SUPPORT_INCLUDED', `', `
	m4_define(`__REFLEX_SUPPORT_INCLUDED', `')

	m4_ifdef(`EMSCRIPTEN', `', `
		m4_ifdef(`__LLD_LIKE', `
			m4_define(__REFLEX_RPATH, --rpath=)
		', `
			m4_define(__REFLEX_RPATH, -rpath` ')
		')

		m4_define(`__REFLEX_RPATH', m4_defn(`__REFLEX_RPATH')m4_esyscmd(echo -n $__TMP_HACK_REFLEX_LIB_DIR))
	')

ldflags=$ldflags -L`'m4_esyscmd(echo -n $__TMP_HACK_REFLEX_LIB_DIR) m4_defn(`__REFLEX_RPATH')
cppflags=$cppflags -I`'m4_esyscmd(echo -n $__TMP_HACK_REFLEX_INC_DIR)

	m4_undefine(`__REFLEX_RPATH')

	m4_define(REFLEX, `
		m4_define(`__SRC_FILE', ABSOLUTE_PATH($1, m, false))
		m4_define(`__FIRST_OUT', ABSOLUTE_PATH($2, m, false))
		m4_define(`__SECOND_OUT', ABSOLUTE_PATH($3, m, false))
		m4_define(`__THIRD_OUT', ABSOLUTE_PATH($4, m, false))

		FILE_FLAGS(__FIRST_OUT, `
			m4_define(`CPP_FLAGS', m4_defn(`THIRDPARTY_CPP_FLAGS'))
			m4_define(`CXX_FLAGS', m4_defn(`THIRDPARTY_CXX_FLAGS'))
			m4_define(`C_FLAGS', m4_defn(`THIRDPARTY_C_FLAGS'))
		')

		FILE_FLAGS(__THIRD_OUT, `
			m4_define(`CPP_FLAGS', m4_defn(`THIRDPARTY_CPP_FLAGS'))
			m4_define(`CXX_FLAGS', m4_defn(`THIRDPARTY_CXX_FLAGS'))
			m4_define(`C_FLAGS', m4_defn(`THIRDPARTY_C_FLAGS'))
		')

build __FIRST_OUT __SECOND_OUT __THIRD_OUT: reflex __SRC_FILE
__HACK_SPACE`'reflexflags=$reflexflags --outfile=__FIRST_OUT --header-file=__SECOND_OUT --tables-file=__THIRD_OUT
__HACK_SPACE`'dir=__BASE_PATH(__FIRST_OUT)
m4_indir(`__COLLECT_WARNINGS_FILE__')
		m4_ifdef(`COLLECT_WARNED', `
__HACK_SPACE`'__COLLECT_WARNINGS_OUTPUT=__FIRST_OUT
		')

		m4_undefine(`__FIRST_OUT')
		m4_undefine(`__SECOND_OUT')
		m4_undefine(`__THIRD_OUT')
		m4_undefine(`__SRC_FILE')
	')

rule reflex
__HACK_SPACE`'command=cd $dir && m4_defn(`__COLLECT_WARNED_EXEC') reflex $reflexflags $in
')