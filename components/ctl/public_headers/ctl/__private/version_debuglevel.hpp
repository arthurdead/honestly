#if CTL_LIBCPP == CTL_LIBCPP_GLIBCXX
	#if defined _GLIBCXX_DEBUG || defined _GLIBCPP_DEBUG
		#if defined _GLIBCXX_PARALLEL || defined _GLIBCPP_PARALLEL
			#error
		#endif

		#if defined _GLIBCXX_CONCEPT_CHECKS || defined _GLIBCPP_CONCEPT_CHECKS
			#define CTL_DEBUG_LEVEL 2
		#else
			#define CTL_DEBUG_LEVEL 1
		#endif
	#elif defined _GLIBCXX_PARALLEL || defined _GLIBCPP_PARALLEL
		#define CTL_DEBUG_LEVEL 0
	#endif
#elif CTL_LIBCPP == CTL_LIBCPP_LIBCPP
	#if defined _LIBCPP_DEBUG
		#if _LIBCPP_DEBUG == 0
			#define CTL_DEBUG_LEVEL 1
		#elif _LIBCPP_DEBUG == 1
			#define CTL_DEBUG_LEVEL 2
		#else
			#error
		#endif
	#endif
#else
	#error
#endif

#if CTL_LIBC & CTL_LIBC_FLAG_GNU
	#ifdef _FORTIFY_SOURCE
		#if defined CTL_DEBUG_LEVEL && CTL_DEBUG_LEVEL == 0
			#error
		#elif !defined CTL_DEBUG_LEVEL
			#if _FORTIFY_SOURCE == 1
				#define CTL_DEBUG_LEVEL 1
			#elif _FORTIFY_SOURCE == 2
				#define CTL_DEBUG_LEVEL 2
			#else
				#error
			#endif
		#endif
	#endif
#endif

#ifdef NDEBUG
	#if defined CTL_DEBUG_LEVEL && CTL_DEBUG_LEVEL > 0
		#error
	#elif !defined CTL_DEBUG_LEVEL
		#define CTL_DEBUG_LEVEL 0
	#endif
#endif

#ifndef CTL_DEBUG_LEVEL
	#define CTL_DEBUG_LEVEL -1
#endif
