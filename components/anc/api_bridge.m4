m4_ifdef(`__API_BRIDGE_IN_FILE', `
	m4_include(__details/api_bridge_file.m4)
', `
	m4_ifdef(`__API_BRIDGE_SUPPORT_INCLUDED', `', `
		m4_define(`__API_BRIDGE_SUPPORT_INCLUDED', `')

		m4_include(m4.m4)

		m4_define(API_BRIDGE, `
			m4_ifdef(`API_BRIDGE_TYPE', `
				m4_define(`M4_FLAGS', m4_defn(`M4_FLAGS') -D`API_BRIDGE_TYPE'=API_BRIDGE_TYPE)
				m4_undefine(`API_BRIDGE_TYPE')
			')
			m4_define(`M4_FLAGS', m4_defn(`M4_FLAGS') -D__API_BRIDGE_IN_FILE -D__API_BRIDGE_PROJECT=PROJECT)
			m4_define(M4_NO_WHITESPACE, `')
			M4($@)
		')
	')
')