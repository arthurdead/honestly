m4_ifelse(TOOLSET, llvm, `
	m4_ifdef(`__SEPARATE_AS', `
		m4_define(__LLVM_AS_SUPPORTED, `')

		m4_ifdef(`ZAPCC', `
			m4_undefine(`__LLVM_AS_SUPPORTED')
		')

		m4_ifdef(`EMSCRIPTEN', `
			m4_undefine(`__LLVM_AS_SUPPORTED')
		')

		m4_ifdef(`__LLVM_AS_SUPPORTED', `
			m4_undefine(`__LLVM_AS_SUPPORTED')

			m4_define(`__USE_LLVM_AS')
			m4_define(`__USE_LLVM_BITCODE', `')
			m4_define(`__LLVM_OPT_AS', `')
			m4_define(`__LLVM_OPT_BITCODE', `')
		')
	')

	m4_ifdef(`ZAPCC', `
		m4_define(`__TOOLSET_CPP_MOD', m4_defn(`__TOOLSET_CPP_MOD')~zapcc)
	')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(`__TOOLSET_CPP_MOD', m4_defn(`__TOOLSET_CPP_MOD')~emscripten)

		m4_ifdef(`WASI', `
			m4_define(`__TOOLSET_CPP_MOD', m4_defn(`__TOOLSET_CPP_MOD')~wasi)
		')

		m4_define(`__OPT_WASM', `')
	')

	m4_ifdef(`__USE_LLVM_AS', `
		m4_define(`__TOOLSET_AS_MOD', ll)
	', `
		m4_ifdef(`__SEPARATE_AS', `
			m4_define(`__TOOLSET_AS_MOD', s)
		')
	')

	m4_ifdef(`__USE_LLVM_BITCODE', `
		m4_define(`__TOOLSET_OBJ_MOD', bc)
		m4_define(`__TOOLSET_AR_MOD', bc)
	', `
		m4_ifdef(`EMSCRIPTEN', `
			m4_define(`__TOOLSET_OBJ_MOD', wasm)
		', `
			m4_define(`__TOOLSET_OBJ_MOD', o)
		')
		m4_define(`__TOOLSET_AR_MOD', a)
	')

	m4_ifdef(`EMSCRIPTEN', `
		m4_define(`__TOOLSET_AR_MOD', m4_defn(`__TOOLSET_AR_MOD')~wasm)
	')

	m4_ifdef(`__LLVM_OPT_AS', `
		m4_define(`__TOOLSET_AS_MOD', m4_defn(`__TOOLSET_AS_MOD')~opt_ll)
	')

	m4_ifdef(`__LLVM_OPT_BITCODE', `
		m4_define(`__TOOLSET_OBJ_MOD', m4_defn(`__TOOLSET_OBJ_MOD')~opt_bc)
		m4_define(`__TOOLSET_AR_MOD', m4_defn(`__TOOLSET_AR_MOD')~opt_bc)
	')
')

m4_ifelse(TOOLSET, gnu, `
	m4_ifdef(`MINGW', `
		m4_define(`__TOOLSET_CPP_MOD', m4_defn(`__TOOLSET_CPP_MOD')~mingw)
	', `
		m4_ifdef(`WINE', `
			m4_define(`__TOOLSET_CPP_MOD', m4_defn(`__TOOLSET_CPP_MOD')~wine)
		')
	')

	m4_define(`__TOOLSET_OBJ_MOD', o)
	m4_define(`__TOOLSET_AR_MOD', a)
')