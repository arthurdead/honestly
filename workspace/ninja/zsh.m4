m4_define(`PROJECT', zsh)

m4_include(ninja_project.m4)

DECLARE_DEPENDENCY(static_library, zsh, `
	m4_define(`LD_FILES', LIB_PATH(static_library, zsh))
')

PROJECT_FLAGS(`
	m4_define(`CPP_FLAGS', -I`'THIRDPARTY/zsh -I`'THIRDPARTY/zsh/git/Src)
	m4_define(`M4_FLAGS', -D__ZSH_DIR=THIRDPARTY/zsh)
')

m4_define(`M4_FLAGS', -DMODULE_PATH=THIRDPARTY/zsh/git/Src/zsh.mdd)
M4(
	THIRDPARTY/zsh/module_dep.m4,
	THIRDPARTY/zsh/zsh.mdh
)

STATIC_LIBRARY(zsh,
	THIRDPARTY/zsh/git/Src/builtin.c,
	THIRDPARTY/zsh/git/Src/compat.c,
	THIRDPARTY/zsh/git/Src/cond.c,
	THIRDPARTY/zsh/git/Src/context.c,
	THIRDPARTY/zsh/git/Src/exec.c,
	THIRDPARTY/zsh/git/Src/glob.c,
	THIRDPARTY/zsh/git/Src/hashnameddir.c,
	THIRDPARTY/zsh/git/Src/hashtable.c,
	THIRDPARTY/zsh/git/Src/hist.c,
	THIRDPARTY/zsh/git/Src/init.c,
	THIRDPARTY/zsh/git/Src/input.c,
	THIRDPARTY/zsh/git/Src/jobs.c,
	THIRDPARTY/zsh/git/Src/lex.c,
	THIRDPARTY/zsh/git/Src/linklist.c,
	THIRDPARTY/zsh/git/Src/loop.c,
	THIRDPARTY/zsh/git/Src/main.c,
	THIRDPARTY/zsh/git/Src/math.c,
	THIRDPARTY/zsh/git/Src/mem.c,
	THIRDPARTY/zsh/git/Src/modentry.c,
	THIRDPARTY/zsh/git/Src/module.c,
	THIRDPARTY/zsh/git/Src/openssh_bsd_setres_id.c,
	THIRDPARTY/zsh/git/Src/options.c,
	THIRDPARTY/zsh/git/Src/params.c,
	THIRDPARTY/zsh/git/Src/parse.c,
	THIRDPARTY/zsh/git/Src/pattern.c,
	THIRDPARTY/zsh/git/Src/prompt.c,
	THIRDPARTY/zsh/git/Src/signals.c,
	THIRDPARTY/zsh/git/Src/sort.c,
	THIRDPARTY/zsh/git/Src/string.c,
	THIRDPARTY/zsh/git/Src/subst.c,
	THIRDPARTY/zsh/git/Src/text.c,
	THIRDPARTY/zsh/git/Src/utils.c
)