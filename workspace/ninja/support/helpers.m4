m4_divert(-1)
m4_ifdef(`__HELPERS_INCLUDED', `', `
	m4_define(`__HELPERS_INCLUDED', `')

	m4_define(FOREACH, `m4_pushdef(`$1')__FOREACH_IMPL($@)m4_popdef(`$1')')
	m4_define(__ARG1, `$1')
	m4_define(__FOREACH_IMPL, `m4_ifelse(`$2', (), `',
	  `m4_define(`$1', __ARG1$2)$3`'$0(`$1', (m4_shift$2), `$3')')')

	m4_define(__SUPPORT_SCRIPT, __SUPPORT_DIR/$1.sh)

	m4_define(REMOVE_NEWLINE, `m4_esyscmd(__SUPPORT_SCRIPT(remove_newline) $1)')
	m4_define(ABSOLUTE_PATH, `m4_esyscmd(__SUPPORT_SCRIPT(absolute_path) $1)')

	m4_define(CWD, m4_esyscmd(echo -n $PWD))

	m4_define(BEGIN_NO_OUTPUT, `m4_divert(-1)')
	m4_define(END_NO_OUTPUT, `m4_divert`'m4_dnl')
	m4_define(WRAP_OUTPUT, `END_NO_OUTPUT`'$@`'BEGIN_NO_OUTPUT')

	m4_define(ERROR, `
		m4_errprint(m4___file__:m4___line__: $@
)
		m4_m4exit(1)
	')

	m4_define(WARNING, `
		m4_errprint(m4___file__:m4___line__: $@
)
	')

	m4_define(MSG, `
		m4_errprint($@
)
	')

	m4_define(PRINT, `
		m4_errprint($@)
	')
')
m4_divert`'m4_dnl