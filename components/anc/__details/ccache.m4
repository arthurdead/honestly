m4_ifdef(`CCACHE', `
	m4_ifelse(CCACHE, sccache, `
		m4_define(__CCACHE_EXEC, sccache)
	', CCACHE, ccache, `
		m4_define(__CCACHE_EXEC, ccache)

		m4_define(`__CCACHE_ENVVARS', m4_defn(`__CCACHE_ENVVARS') CCACHE_COMPILER=)

		m4_ifelse(TOOLSET, llvm, `
			m4_define(`__CCACHE_ENVVARS', m4_defn(`__CCACHE_ENVVARS') CCACHE_COMPILERTYPE=clang)
		', TOOLSET, gnu, `
			m4_define(`__CCACHE_ENVVARS', m4_defn(`__CCACHE_ENVVARS') CCACHE_COMPILERTYPE=gcc)
		')
	', CCACHE, buildcache, `
		m4_define(__CCACHE_EXEC, buildcache)
	', `
		ERROR(invalid `CCACHE' value: CCACHE)
	')
')