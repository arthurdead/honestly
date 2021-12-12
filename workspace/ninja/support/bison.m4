m4_ifdef(`__BISON_SUPPORT_INCLUDED', `', `
	m4_define(`__BISON_SUPPORT_INCLUDED', `')

	m4_define(BISON, `
		m4_define(`__SRC_FILE', ABSOLUTE_PATH($1, m, false))
		m4_define(`__FIRST_OUT', ABSOLUTE_PATH($2, m, false))
		m4_define(`__DIR', __BASE_PATH(__FIRST_OUT))

cppflags=$cppflags -I __DIR

		FOREACH(`__FILES_IT', (m4_shift($@)), `
			m4_define(`__OUT_FILE', ABSOLUTE_PATH(__FILES_IT, m, false))
			m4_define(`__OUT_HASH', __HASH(__OUT_FILE))
			m4_define(`__TMP_OUTFILES', m4_defn(`__TMP_OUTFILES') __OUT_FILE)
			m4_define(__`'__OUT_HASH`'_CPP_FLAGS, __GENERATED_CPP_FLAGS)
			m4_define(__`'__OUT_HASH`'_CXX_FLAGS, __GENERATED_CXX_FLAGS)
			m4_undefine(`__OUT_FILE')
			m4_undefine(`__OUT_HASH')
		')

build __TMP_OUTFILES: bison __SRC_FILE
__HACK_SPACE`'dir=__DIR
m4_indir(`__COLLECT_WARNINGS_FILE__')
		m4_ifdef(`COLLECT_WARNED', `
__HACK_SPACE`'__COLLECT_WARNINGS_OUTPUT=__FIRST_OUT
		')

		m4_undefine(`__DIR')
		m4_undefine(`__FIRST_OUT')
		m4_undefine(`__TMP_OUTFILES')
		m4_undefine(`__SRC_FILE')
	')

rule bison
__HACK_SPACE`'command=cd $dir && m4_defn(`__COLLECT_WARNED_EXEC') bison -Wall -Wdangling-alias $in
')