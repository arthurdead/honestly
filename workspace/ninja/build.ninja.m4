m4_include(ninja_file.m4)

m4_divert(-1)
#cppflags=$cppflags -D__OSAL_ENABLE_COMMENTS -D__CTL_ENABLE_COMMENTS
m4_divert

cppflags=$cppflags -D__CTL_DISABLE_ALL_COMMENTS

m4_define(ROOT_DIR, ABSOLUTE_PATH(CWD/../.., e, true))
m4_define(COMPONENTS, ROOT_DIR/components)
m4_define(THIRDPARTY, ROOT_DIR/thirdparty)
m4_define(OUTPUT_DIR, ROOT_DIR/test)

m4_include(ctl.m4)
m4_include(osal.m4)
m4_include(gal.m4)
m4_include(ocf.m4)
m4_include(launcher.m4)