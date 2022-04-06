m4_define(`PROJECT', ctl)

m4_include(ninja_project.m4)

DECLARE_DEPENDENCY(project, `
	m4_define(`CPP_FLAGS', -I`'COMPONENTS/ctl/public_headers)
')

DECLARE_DEPENDENCY(static_library, ctl, `
	m4_define(`CPP_FLAGS', -D__CTL_IS_STATIC)
	m4_define(`LD_FILES', CXX_LIB_PATH(static_library, ctl) CXX_LIB_PATH(static_library, ctl_shared))
')

PROJECT_FLAGS(`
	m4_define(`CPP_FLAGS', -D__COMPILING_CTL)
')

PROJECT_DEPENDENCY(ctl, project)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__CTL_IS_STATIC)
')
CXX_STATIC_LIBRARY(ctl,
	COMPONENTS/ctl/private_impl/charconv.cpp
)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__CTL_IS_STATIC)
')
CXX_STATIC_LIBRARY(ctl_shared,
	COMPONENTS/ctl/shared_impl/memory.cpp
)