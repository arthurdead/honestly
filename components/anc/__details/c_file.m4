m4_ifdef(`__SEPARATE_AS', `
m4_include(__details/c_file|separate_as.m4)
', `
	m4_ifdef(`EMSCRIPTEN', `
m4_include(__details/c_file|emscripten.m4)
	', `
build __TMP_OBJ_FILENAME.__OBJ_EXT: __LANG_LOWER __C_SRC_FILE __C_DEPS
__C_CPPFLAGS
__C_RULE_BITS
__C_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=__LANG_UPPER __SRC_FILE
	')
')