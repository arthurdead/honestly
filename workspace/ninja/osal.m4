m4_define(`PROJECT', osal)

m4_include(ninja_project.m4)

PROJECT_FLAGS(`
	m4_define(`CPP_FLAGS', -D__COMPILING_OSAL)
')

DECLARE_DEPENDENCY(project, `
	m4_define(`CPP_FLAGS', -I`'COMPONENTS/osal/public_headers)
')

DECLARE_DEPENDENCY(static_library, osal, `
	m4_define(`CPP_FLAGS', -D__OSAL_IS_STATIC)
	m4_define(`LD_FILES', LIB_PATH(static_library, osal) LIB_PATH(static_library, osal_shared))
')

DECLARE_DEPENDENCY(static_library, main, `
	m4_define(`LD_FILES', LIB_PATH(static_library, main))
')

PROJECT_DEPENDENCY(osal, project)

PROJECT_DEPENDENCY(ctl, project)
PROJECT_DEPENDENCY(ctl, static_library, ctl)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__OSAL_IS_STATIC)
')
STATIC_LIBRARY(osal,
	COMPONENTS/osal/private_impl/terminal.cpp,
	COMPONENTS/osal/private_impl/process.cpp,
	COMPONENTS/osal/private_impl/commandline.cpp,
	COMPONENTS/osal/private_impl/environment.cpp,
	COMPONENTS/osal/private_impl/network.cpp
)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__OSAL_IS_STATIC)
')
STATIC_LIBRARY(osal_shared,
	COMPONENTS/osal/shared_impl/process.cpp,
	COMPONENTS/osal/shared_impl/commandline.cpp
)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__OSAL_IS_STATIC)
')
STATIC_LIBRARY(main,
	COMPONENTS/osal/shared_impl/main.cpp
)