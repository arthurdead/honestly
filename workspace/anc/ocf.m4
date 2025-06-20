m4_define(`PROJECT', ocf)

m4_include(ninja_project.m4)

m4_include(bison.m4)
m4_include(reflex.m4)

PROJECT_FLAGS(`
	m4_define(`CPP_FLAGS', -D__COMPILING_OCF)
')

CXX_BISON(
	COMPONENTS/ocf/bison/ocf.bison,
	COMPONENTS/ocf/cpp/private_impl/bison.gen.cpp,
	COMPONENTS/ocf/cpp/private_impl/bison.gen.hpp
)

REFLEX(
	COMPONENTS/ocf/reflex/ocf.reflex,
	COMPONENTS/ocf/cpp/private_impl/reflex.gen.cpp,
	COMPONENTS/ocf/cpp/private_impl/reflex.gen.hpp,
	COMPONENTS/ocf/cpp/private_impl/reflex_tables.gen.cpp
)

DECLARE_DEPENDENCY(project, `
	m4_define(`CPP_FLAGS', -I`'COMPONENTS/ocf/cpp/public_headers)
')

DECLARE_DEPENDENCY(static_library, ocf, `
	m4_define(`CPP_FLAGS', -D__OCF_IS_STATIC)
	m4_define(`LD_FILES', CXX_LIB_PATH(static_library, ocf))
	m4_define(`LD_LIBS', -lreflexmin)
')

PROJECT_DEPENDENCY(ocf, project)

PROJECT_DEPENDENCY(ctl, project)
PROJECT_DEPENDENCY(ctl, static_library, ctl)

PROJECT_DEPENDENCY(osal, project)
PROJECT_DEPENDENCY(osal, static_library, osal)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__OCF_IS_STATIC)
')
CXX_STATIC_LIBRARY(ocf,
	COMPONENTS/ocf/cpp/private_impl/driver.cpp,
	COMPONENTS/ocf/cpp/private_impl/object.cpp,
	COMPONENTS/ocf/cpp/private_impl/frontend.cpp,
	COMPONENTS/ocf/cpp/private_impl/bison.gen.cpp,
	COMPONENTS/ocf/cpp/private_impl/reflex.gen.cpp,
	COMPONENTS/ocf/cpp/private_impl/reflex_tables.gen.cpp
)