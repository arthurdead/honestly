m4_ifdef(`__LLVM_OPT_AS', `
build __TMP_AS_FILENAME.unopt.ll: cxx __CXX_SRC_FILE __CXX_DEPS
__CXX_CPPFLAGS
__BASE_CXX_RULE_BITS
__CXX_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=CXX __SRC_FILE
build __TMP_AS_FILENAME.opt.ll: opt_as __TMP_AS_FILENAME.unopt.ll
__HACK_SPACE`'description=OPT __SRC_FILE
build __TMP_AS_FILENAME.ll: symlink __TMP_AS_FILENAME.opt.ll
__HACK_SPACE`'description=LN $1
', `
build __TMP_AS_FILENAME.__AS_EXT: cxx __CXX_SRC_FILE __CXX_DEPS
__CXX_CPPFLAGS
__BASE_CXX_RULE_BITS
__CXX_DEPFILE
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=CXX __SRC_FILE
')

m4_ifdef(`__LLVM_OPT_BITCODE', `
build __TMP_OBJ_FILENAME.unopt.bc: as __TMP_AS_FILENAME.ll
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=AS __SRC_FILE
build __TMP_OBJ_FILENAME.opt.bc: opt_bc __TMP_OBJ_FILENAME.unopt.bc
__HACK_SPACE`'description=OPT __SRC_FILE
build __TMP_OBJ_FILENAME.bc: symlink __TMP_OBJ_FILENAME.opt.bc
__HACK_SPACE`'description=LN $1
', `
build __TMP_OBJ_FILENAME.__OBJ_EXT: as __TMP_AS_FILENAME.__AS_EXT
m4_indir(`__COLLECT_WARNINGS_FILE__')
__HACK_SPACE`'description=AS __SRC_FILE
')