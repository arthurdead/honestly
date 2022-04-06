m4_define(`PROJECT', testwtf)

m4_include(ninja_project.m4)

m4_define(LIBRARY_PATH, OUTPUT_DIR)
CXX_EXECUTABLE(testwtf,
	/home/arthurdead/Desktop/temp/test.cpp
)