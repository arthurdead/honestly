#if CTL_COMPILER & CTL_COMPILER_FLAG_ZAPCC
	#undef __cpp_lib_is_constant_evaluated
	#undef __cpp_lib_concepts
	#undef __cpp_lib_three_way_comparison
	#if CTL_LIBCPP == CTL_LIBCPP_LIBCPP
		#undef _LIBCPP_COMPILER_HAS_BUILTIN_LAUNDER
	#elif CTL_LIBCPP == CTL_LIBCPP_GLIBCXX
		#undef _GLIBCXX_USE_CHAR8_T
		#undef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED
		#undef _GLIBCXX_HAVE_BUILTIN_LAUNDER
		#define __builtin_is_constant_evaluated() (false)
	#endif
#endif

#if CTL_LIBC == CTL_LIBC_MUSL
	#if CTL_LIBCPP == CTL_LIBCPP_GLIBCXX
		#undef _GLIBCXX_USE_PTHREAD_COND_CLOCKWAIT
	#elif CTL_LIBCPP == CTL_LIBCPP_LIBCPP
		#undef _LIBCPP_HAS_COND_CLOCKWAIT
	#endif
#endif
