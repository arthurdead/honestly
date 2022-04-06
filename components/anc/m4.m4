m4_ifdef(`__M4_SUPPORT_INCLUDED', `', `
	m4_define(`__M4_SUPPORT_INCLUDED', `')

	m4_define(M4, `
		m4_define(`__SRC_FILE', ABSOLUTE_PATH($1, m, false))
		m4_define(`__FIRST_OUT', ABSOLUTE_PATH($2, m, false))
		m4_define(`__SRC_HASH', __HASH(__SRC_FILE))
		m4_ifdef(__`'__SRC_HASH`'_DEPS, `
			m4_define(`__DEPS', | __`'__SRC_HASH`'_DEPS)
		', `
			m4_define(`__DEPS', `')
		')
build __FIRST_OUT: m4_ifdef(`M4_NO_WHITESPACE', `m4_rem_white', `m4') __SRC_FILE __DEPS
__HACK_SPACE`'m4flags=$m4flags m4_defn(__`'PROJECT`'_M4_FLAGS) m4_defn(`__LIBRARY_M4_FLAGS') m4_defn(__`'__SRC_HASH`'_M4_FLAGS) m4_defn(`M4_FLAGS')
__HACK_SPACE`'dir=__BASE_PATH(__SRC_FILE)
m4_indir(`__COLLECT_WARNINGS_FILE__')
		m4_ifdef(`COLLECT_WARNED', `
__HACK_SPACE`'__COLLECT_WARNINGS_OUTPUT=__FIRST_OUT
		')
__HACK_SPACE`'description=`M4' __SRC_FILE
		m4_undefine(`__FIRST_OUT')
		m4_undefine(`__SRC_FILE')
		m4_undefine(`__SRC_HASH')
		m4_undefine(`__DEPS')
		m4_undefine(`__LIBRARY_M4_FLAGS')
		m4_undefine(`M4_NO_WHITESPACE')
		m4_undefine(`M4_FLAGS')
	')

rule m4
__HACK_SPACE`'command=m4 -EE -P $m4flags -I`'__ANC_DIR -I$dir -D`__ANC_DIR'=__ANC_DIR $in > $out
rule m4_rem_white
__HACK_SPACE`'command=m4 -EE -P $m4flags -I`'__ANC_DIR -I$dir -D`__ANC_DIR'=__ANC_DIR $in > $out && __DETAIL_SCRIPT(remove_whitespace) $out
')