m4_ifelse(TOOLSET, llvm, `
m4_include(__private/cxx_file|separate_as|llvm.m4)
', `
build __TMP_AS_FILENAME.__AS_EXT: cxx __CXX_SRC_FILE __CXX_DEPS
__CXX_CPPFLAGS
__BASE_CXX_RULE_BITS
__CXX_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=CXX __SRC_FILE
build __TMP_OBJ_FILENAME.__OBJ_EXT: as __TMP_AS_FILENAME.__AS_EXT
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=AS __SRC_FILE
')