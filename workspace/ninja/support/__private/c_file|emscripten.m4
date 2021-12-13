m4_ifdef(`__OPT_WASM', `
m4_include(__private/c_file|emscripten|opt_wasm.m4)
', `
build __TMP_OBJ_FILENAME.wasm: __LANG_LOWER __C_SRC_FILE __C_DEPS
__C_CPPFLAGS
__C_RULE_BITS
__C_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=__LANG_UPPER __SRC_FILE
')