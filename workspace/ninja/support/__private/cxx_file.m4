m4_ifdef(`__SEPARATE_AS', `
m4_include(__private/cxx_file|separate_as.m4)
', `
	m4_ifdef(`EMSCRIPTEN', `
m4_include(__private/cxx_file|emscripten.m4)
	', `
build __TMP_OBJ_FILENAME.__OBJ_EXT: cxx __CXX_SRC_FILE __CXX_DEPS
__CXX_CPPFLAGS
__BASE_CXX_RULE_BITS
__CXX_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=CXX __SRC_FILE
	')
')