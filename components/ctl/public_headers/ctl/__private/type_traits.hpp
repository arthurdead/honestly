#pragma once

#if CTL_LIBCPP == CTL_LIBCPP_GLIBCXX && \
	CTL_COMPILER & CTL_COMPILER_FLAG_ZAPCC && \
	__cplusplus > 202002L
	#pragma push_macro("__cplusplus")
	#undef __cplusplus
	#define __cplusplus CTL_CPP_20
#endif
#include <type_traits>
#if CTL_LIBCPP == CTL_LIBCPP_GLIBCXX && \
	CTL_COMPILER & CTL_COMPILER_FLAG_ZAPCC && \
	__cplusplus > 202002L
	#pragma pop_macro("__cplusplus")
#endif
