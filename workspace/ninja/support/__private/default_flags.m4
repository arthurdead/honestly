m4_ifelse(CONFIGURATION, release, `
	m4_define(`__CPP_C_FLAGS', m4_defn(`__CPP_C_FLAGS') -Ofast)
	m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -DNDEBUG)
')

m4_ifelse(CONFIGURATION, debug, `
	m4_define(`__CPP_C_FLAGS', m4_defn(`__CPP_C_FLAGS') -O0)
	m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -fno-omit-frame-pointer -ggdb3)
	m4_ifelse(LIBC, crt, `', `
		m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -D_FORTIFY_SOURCE=2)
	')
')

m4_ifelse(LIBCPP, libc++, `
	m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -D_LIBCPP_ENABLE_NODISCARD -D_LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS)

	m4_ifelse(CONFIGURATION, debug, `
		m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -D_LIBCPP_DEBUG=1)
	')
')

m4_ifelse(LIBCPP, libstdc++, `
	m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -D_GLIBCXX_CONCEPT_CHECKS -D_GLIBCPP_CONCEPT_CHECKS)

	m4_ifelse(CONFIGURATION, debug, `
		m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -D_GLIBCXX_DEBUG -D_GLIBCPP_DEBUG)
	')
	m4_ifelse(CONFIGURATION, release, `
		m4_define(`__CXX_CPP_FLAGS', m4_defn(`__CXX_CPP_FLAGS') -D_GLIBCXX_PARALLEL -D_GLIBCPP_PARALLEL)
	')
')

m4_ifelse(TOOLSET, llvm, `
	m4_ifdef(`ZAPCC', `', `
		m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -fpch-codegen -fpch-instantiate-templates)

		m4_ifelse(CONFIGURATION, debug, `
			m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -fpch-debuginfo)
		')
		m4_ifelse(CONFIGURATION, release, `
			m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -fno-pch-debuginfo)
		')
	')
')

m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -fpch-preprocess)

m4_define(`__CPP_C_FLAGS', m4_defn(`__CPP_C_FLAGS') -Wall -Wextra -pedantic -Wfatal-errors)
m4_ifelse(TOOLSET, llvm, `
	m4_define(`__CPP_C_FLAGS', m4_defn(`__CPP_C_FLAGS') -Weverything)
	m4_define(`__CPP_CXX_FLAGS', m4_defn(`__CPP_CXX_FLAGS') -Wno-c++98-compat-pedantic)
')

m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -Wno-unused-macros)
m4_ifelse(TOOLSET, llvm, `
	m4_define(`__CPP_FLAGS', m4_defn(`__CPP_FLAGS') -Wno-reserved-id-macro)
')

m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -Wno-padded -Wno-switch-enum)
m4_ifelse(TOOLSET, llvm, `
	m4_ifdef(`EMSCRIPTEN', `', `
		m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -Wno-reserved-identifier)
	')
	m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -Wno-c++98-compat -Wno-c++98-c++11-compat -Wno-c++98-c++11-c++14-compat)
	m4_define(`__CXX_FLAGS', m4_defn(`__CXX_FLAGS') -Wno-unused-template)
')

m4_define(`__C_FLAGS', m4_defn(`__C_FLAGS') -fpic -fvisibility=hidden)

m4_ifdef(`EMSCRIPTEN', `', `
	m4_define(`__LD_FLAGS', m4_defn(`__LD_FLAGS')  --eh-frame-hdr)
')