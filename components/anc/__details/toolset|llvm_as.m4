m4_define(__AS_EXT, ll)
m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -emit-llvm)

m4_ifdef(`__LLVM_OPT_AS', `
rule opt_as
__HACK_SPACE`'command=opt -S $in -o $out
')

m4_ifdef(`__USE_LLVM_BITCODE', `
	m4_include(__details/toolset|llvm_as|llvm_bitcode.m4)
', `
	m4_define(__OBJ_EXT, o)
	m4_define(__AR_EXT, a)

rule as
__HACK_SPACE`'command=m4_defn(`__COLLECT_WARNED_EXEC') llc $in -o $out
rule ar
__HACK_SPACE`'command=llvm-ar -rcs $out $in
')