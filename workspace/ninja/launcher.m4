m4_define(`PROJECT', launcher)

m4_include(ninja_project.m4)

PROJECT_DEPENDENCY(ctl, project)
PROJECT_DEPENDENCY(ctl, static_library, ctl)

PROJECT_DEPENDENCY(osal, project)
PROJECT_DEPENDENCY(osal, static_library, osal)
PROJECT_DEPENDENCY(osal, static_library, main)

PROJECT_DEPENDENCY(ocf, project)
PROJECT_DEPENDENCY(ocf, static_library, ocf)

PROJECT_DEPENDENCY(gal, project)
PROJECT_DEPENDENCY(gal, static_library, gal)
PROJECT_DEPENDENCY(gal, static_library, xcb)
PROJECT_DEPENDENCY(gal, static_library, vulkan)

m4_define(LIBRARY_PATH, OUTPUT_DIR)
EXECUTABLE(launcher,
	COMPONENTS/launcher/main.cpp
)