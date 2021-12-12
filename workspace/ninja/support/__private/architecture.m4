m4_ifelse(ARCHITECTURE, x86-64, `
	m4_define(__VALID_ARCHITECTURE, `')

	m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS') -m elf_x86_64)
	m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -march=x86-64)
')

m4_ifelse(ARCHITECTURE, wasm-32, `
	m4_define(__VALID_ARCHITECTURE, `')
')

m4_ifelse(ARCHITECTURE, wasm-64, `
	ERROR(wasm64 is not currently supported)
')

m4_ifdef(`__VALID_ARCHITECTURE', `m4_undefine(`__VALID_ARCHITECTURE')', `ERROR(invalid architecture value: ARCHITECTURE)')