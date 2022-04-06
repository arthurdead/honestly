#include <cpa/compilers.h>

#if CPA_COMPILER & CPA_COMPILER_FLAG_GCC
	#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wgnu-include-next"
	#else
		#pragma GCC system_header
	#endif
	#include_next __STDI_INCLUDE_NEXT_HEADER
	#if CPA_COMPILER & CPA_COMPILER_FLAG_CLANG
		#pragma clang diagnostic pop
	#endif
#else
	#error
#endif

#undef __STDI_INCLUDE_NEXT_HEADER
