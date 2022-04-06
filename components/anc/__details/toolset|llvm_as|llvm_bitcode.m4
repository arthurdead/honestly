m4_define(__OBJ_EXT, bc)

m4_ifdef(`__LLVM_OPT_BITCODE', `
rule opt_bc
__HACK_SPACE`'command=opt $in -o $out
')

rule as
__HACK_SPACE`'command=m4_defn(`__COLLECT_WARNED_EXEC') llvm-as $in -o $out

m4_ifelse(LD, lld, `
	m4_define(__AR_EXT, bc)
rule ar
__HACK_SPACE`'command=llvm-link $in -o $out
	', `
		m4_define(__AR_EXT, a)
rule link
__HACK_SPACE`'command=llvm-link $in -o $out
rule llc
__HACK_SPACE`'command=m4_defn(`__COLLECT_WARNED_EXEC') llc $in -o $out
rule ar
__HACK_SPACE`'command=llvm-ar -rcs $out $in
')