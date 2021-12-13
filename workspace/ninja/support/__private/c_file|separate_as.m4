m4_ifelse(TOOLSET, llvm, `
m4_include(__private/c_file|separate_as|llvm.m4)
', `
build __TMP_AS_FILENAME.__AS_EXT: __LANG_LOWER __C_SRC_FILE __C_DEPS
__C_CPPFLAGS
__C_RULE_BITS
__C_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=__LANG_UPPER __SRC_FILE
build __TMP_OBJ_FILENAME.__OBJ_EXT: as __TMP_AS_FILENAME.__AS_EXT
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=AS __SRC_FILE
')