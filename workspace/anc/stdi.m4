m4_define(`PROJECT', stdi)

m4_include(ninja_project.m4)

DECLARE_DEPENDENCY(project, `
	m4_define(`CPP_FLAGS', -I`'COMPONENTS/stdi/c)
')

PROJECT_DEPENDENCY(stdi, project)
PROJECT_DEPENDENCY(cpa, project)

c_inc_override=-I`'COMPONENTS/stdi/cc
cxx_inc_override=-I`'COMPONENTS/stdi/cxx
cppflags=$cppflags -I`'COMPONENTS/stdi/c