m4_ifdef(`__BISON_SUPPORT_INCLUDED', `', `
	m4_define(`__BISON_SUPPORT_INCLUDED', `')

	m4_define(CXX_BISON, `
		m4_define(`__SRC_FILE', ABSOLUTE_PATH($1, m, false))
		m4_define(`__FIRST_OUT', ABSOLUTE_PATH($2, m, false))
		m4_define(`__SECOND_OUT', ABSOLUTE_PATH($3, m, false))
		m4_define(`__DIR', __BASE_PATH(__FIRST_OUT))

cppflags=$cppflags -I __DIR

		FILE_FLAGS(__FIRST_OUT, `
			m4_define(`CPP_FLAGS', m4_defn(`THIRDPARTY_CPP_FLAGS'))
			m4_define(`CXX_FLAGS', m4_defn(`THIRDPARTY_CXX_FLAGS'))
			m4_define(`C_FLAGS', m4_defn(`THIRDPARTY_C_FLAGS'))
		')

build __FIRST_OUT __SECOND_OUT: bison_cxx __SRC_FILE
__HACK_SPACE`'bisonflags=$bisonflags -o=__FIRST_OUT -H=__SECOND_OUT
__HACK_SPACE`'dir=__DIR
m4_indir(`__COLLECT_WARNINGS_FILE__')
		m4_ifdef(`COLLECT_WARNED', `
__HACK_SPACE`'__COLLECT_WARNINGS_OUTPUT=__FIRST_OUT
		')

		m4_undefine(`__DIR')
		m4_undefine(`__FIRST_OUT')
		m4_undefine(`__SECOND_OUT')
		m4_undefine(`__SRC_FILE')
	')

rule bison_cxx
__HACK_SPACE`'command=cd $dir && m4_defn(`__COLLECT_WARNED_EXEC') bison -Wall -Wdangling-alias -S lalr1.cc -L C++ $bisonflags $in
')