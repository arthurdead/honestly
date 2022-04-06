m4_ifelse(ARCHITECTURE, x86-64, `
	m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS') -m elf_x86_64)
	m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -march=x86-64)
', ARCHITECTURE, x86-32, `
	ERROR(x86-32 is not currently supported)
', ARCHITECTURE, wasm-32, `

', ARCHITECTURE, wasm-64, `
	ERROR(wasm-64 is not currently supported)
', `
	ERROR(invalid `ARCHITECTURE' value: ARCHITECTURE)
')
