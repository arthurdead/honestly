#if CTL_GCC_VERSION_CMP(<, 3, 4, 0)
	#error
#endif

#if !(CTL_COMPILER & CTL_COMPILER_FLAG_ZAPCC)
	#if CTL_CPP_VERSION < CTL_CPP_20
		#error
	#endif
#endif

#ifndef __has_include
	#error
#endif
