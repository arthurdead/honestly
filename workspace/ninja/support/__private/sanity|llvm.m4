m4_ifdef(`__USE_LLVM_AS', `
	m4_ifdef(`__SEPARATE_AS', `', `
		ERROR(llvm assembly requires out of process assembler)
	')
')

m4_ifdef(`__USE_LLVM_BITCODE', `
	m4_ifdef(`__USE_LLVM_AS', `', `
		ERROR(llvm bitcode requires llvm assembly)
	')
	m4_ifelse(LD, lld, `', `
		ERROR(llvm bitcode requires `LD'=lld)
	')
')

m4_ifdef(`__LLVM_OPT_AS', `
	m4_ifdef(`__USE_LLVM_AS', `', `
		ERROR(optimizing llvm assembly requires llvm assembly)
	')
')

m4_ifdef(`__LLVM_OPT_BITCODE', `
	m4_ifdef(`__USE_LLVM_BITCODE', `', `
		ERROR(optimizing llvm bitcode requires llvm bitcode)
	')
')

m4_ifdef(`ZAPCC', `
	m4_ifdef(`__USE_LLVM_BITCODE', `
		ERROR(llvm bitcode is incompatible with `ZAPCC')
	')
	m4_ifdef(`__USE_LLVM_AS', `
		ERROR(llvm assembly is incompatible with `ZAPCC')
	')
')

m4_ifdef(`EMSCRIPTEN', `
	m4_ifdef(`__USE_LLVM_BITCODE', `
		ERROR(llvm bitcode is incompatible with `EMSCRIPTEN')
	')
	m4_ifdef(`__USE_LLVM_AS', `
		ERROR(llvm assembly is incompatible with `EMSCRIPTEN')
	')
	m4_ifdef(`__SEPARATE_AS', `
		ERROR(`EMSCRIPTEN' requires in process assembler)
	')
')

m4_ifdef(`__OPT_WASM', `
	m4_ifdef(`EMSCRIPTEN', `', `
		ERROR(optmizing wasm requires `EMSCRIPTEN')
	')
')