m4_define(`PROJECT', gal)

m4_include(ninja_project.m4)

m4_include(m4.m4)

PROJECT_FLAGS(`
	m4_define(`M4_FLAGS', -I`'COMPONENTS/api_bridge -I`'COMPONENTS/gal/m4)
')

M4(
	COMPONENTS/gal/m4/private_impl/xcb/__private/connection_atoms.hpp.m4,
	COMPONENTS/gal/cpp/private_impl/xcb/__private/connection_atoms.gen.hpp
)

FILE_DEPENDENCIES(
	COMPONENTS/gal/m4/shared/__private/pen_funcs.hpp.m4,
	COMPONENTS/api_bridge/api_bridge.m4
)

FILE_DEPENDENCIES(
	COMPONENTS/gal/m4/private_impl/__private/pen_funcs.hpp.m4,
	COMPONENTS/gal/m4/shared/__private/pen_funcs.hpp.m4
)

FILE_DEPENDENCIES(
	COMPONENTS/gal/cpp/public_headers/window.hpp,
	COMPONENTS/gal/cpp/public_headers/gal/__private/pen_funcs.pub.gen.hpp
)

FILE_DEPENDENCIES(
	COMPONENTS/gal/cpp/private_impl/window.hpp,
	COMPONENTS/gal/cpp/private_impl/__private/pen_funcs.priv.gen.hpp
)

m4_define(`M4_FLAGS', -DAPI_BRIDGE_TYPE=PUBLIC)
m4_define(M4_NO_WHITESPACE, `')
M4(
	COMPONENTS/gal/m4/shared/__private/pen_funcs.hpp.m4,
	COMPONENTS/gal/cpp/public_headers/gal/__private/pen_funcs.pub.gen.hpp
)

m4_define(`M4_FLAGS', -DAPI_BRIDGE_TYPE=PRIVATE)
m4_define(M4_NO_WHITESPACE, `')
M4(
	COMPONENTS/gal/m4/private_impl/__private/pen_funcs.hpp.m4,
	COMPONENTS/gal/cpp/private_impl/__private/pen_funcs.priv.gen.hpp
)

DECLARE_DEPENDENCY(project, `
	m4_define(`CPP_FLAGS', -I`'COMPONENTS/gal/cpp/public_headers)
')

DECLARE_DEPENDENCY(static_library, gal, `
	m4_define(`CPP_FLAGS', -D__GAL_IS_STATIC)
	m4_define(`LD_FILES', CXX_LIB_PATH(static_library, gal))
	m4_define(`LD_LIBS', -lpci -lfontconfig -lfreetype)
')

DECLARE_DEPENDENCY(static_library, xcb, `
	m4_define(`CPP_FLAGS', -D__GAL_XCB_IS_STATIC)
	m4_define(`LD_FILES', CXX_LIB_PATH(static_library, xcb))
	m4_define(`LD_LIBS', -lxcb -lxcb-util -lxcb-icccm -lxcb-ewmh -lxcb-randr -lxcb-render -lxcb-render-util -lxcb-errors)
')

DECLARE_DEPENDENCY(static_library, vulkan, `
	m4_define(`CPP_FLAGS', -D__GAL_VULKAN_IS_STATIC)
	m4_define(`LD_FILES', CXX_LIB_PATH(static_library, vulkan))
	m4_define(`LD_LIBS', -ldl)
')

PROJECT_DEPENDENCY(gal, project)

PROJECT_DEPENDENCY(ctl, project)
PROJECT_DEPENDENCY(ctl, static_library, ctl)

PROJECT_DEPENDENCY(osal, project)
PROJECT_DEPENDENCY(osal, static_library, osal)

PROJECT_DEPENDENCY(gal, static_library, xcb)
PROJECT_DEPENDENCY(gal, static_library, vulkan)

FILE_FLAGS(COMPONENTS/gal/cpp/private_impl/font.cpp, `
	m4_define(`CPP_FLAGS', -I/usr/include/freetype2)
')

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__COMPILING_GAL -D__GAL_IS_STATIC)
')
CXX_STATIC_LIBRARY(gal,
	COMPONENTS/gal/cpp/private_impl/window.cpp,
	COMPONENTS/gal/cpp/private_impl/renderer.cpp,
	COMPONENTS/gal/cpp/private_impl/font.cpp,
	COMPONENTS/gal/cpp/private_impl/gal.cpp
)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__COMPILING_GAL_XCB -D__GAL_XCB_IS_STATIC -D__COMPILING_GAL_INTERNAL_MODULE -D__GAL_IS_STATIC)
')
CXX_STATIC_LIBRARY(xcb,
	COMPONENTS/gal/cpp/private_impl/xcb/window.cpp,
	COMPONENTS/gal/cpp/private_impl/xcb/pen.cpp,
	COMPONENTS/gal/cpp/private_impl/xcb/font.cpp,
	COMPONENTS/gal/cpp/private_impl/xcb/connection.cpp,
	COMPONENTS/gal/cpp/private_impl/xcb/screen.cpp,
	COMPONENTS/gal/cpp/private_impl/xcb/atom.cpp,
	COMPONENTS/gal/cpp/private_impl/xcb/api.cpp
)

LIBRARY_FLAGS(`
	m4_define(`CPP_FLAGS', -D__COMPILING_GAL_VULKAN -D__GAL_VULKAN_IS_STATIC -D__GAL_IS_STATIC)
')
CXX_STATIC_LIBRARY(vulkan,
	COMPONENTS/gal/cpp/private_impl/vulkan/vulkan.cpp,
	COMPONENTS/gal/cpp/private_impl/vulkan/api.cpp,
	COMPONENTS/gal/cpp/private_impl/vulkan/renderer.cpp,
	COMPONENTS/gal/cpp/private_impl/vulkan/instance.cpp,
	COMPONENTS/gal/cpp/private_impl/vulkan/device.cpp,
	COMPONENTS/gal/cpp/private_impl/vulkan/swapchain.cpp
)