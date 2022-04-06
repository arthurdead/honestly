m4_define(`PROJECT', cpa)

m4_include(ninja_project.m4)

DECLARE_DEPENDENCY(project, `
	m4_define(`CPP_FLAGS', -I`'COMPONENTS/cpa)
')

PROJECT_DEPENDENCY(cpa, project)

cppflags=$cppflags -I`'COMPONENTS/cpa