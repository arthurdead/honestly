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
		FOREACH(`__FILES_IT', (m4_shift($@)), `
			m4_define(`__OUT_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
			m4_define(`__OUT_HASH', __HASH(__OUT_FILE))
			m4_define(`__TMP_OUTFILES', m4_defn(`__TMP_OUTFILES') __OUT_FILE)
			m4_define(__`'__OUT_HASH`'_CPP_FLAGS, __GENERATED_CPP_FLAGS)
			m4_define(__`'__OUT_HASH`'_CXX_FLAGS, __GENERATED_CXX_FLAGS)
			m4_undefine(`__OUT_FILE')
			m4_undefine(`__OUT_HASH')
		')
build __TMP_OUTFILES: reflex __SRC_FILE
__HACK_SPACE`'dir=__BASE_PATH(__FIRST_OUT)
	m4_undefine(`__FIRST_OUT')
	m4_undefine(`__TMP_OUTFILES')
	m4_undefine(`__SRC_FILE')
	')

rule reflex
__HACK_SPACE`'command=cd $dir && reflex.elf $in
')