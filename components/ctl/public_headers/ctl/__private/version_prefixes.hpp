#ifdef __MUSL__
	#define _LIBCPP_HAS_MUSL_LIBC
	#define __GLIBC_PREREQ(j,m) (0)
	#define __BEGIN_DECLS extern "C" {
	#define __END_DECLS }
#endif

#ifdef __ZAPCC__
	#undef __cpp_char8_t
	#undef __cpp_aligned_new
	#undef __cpp_impl_three_way_comparison
	#undef __cpp_deduction_guides
	#undef __cpp_concepts
	#undef __cpp_constexpr_dynamic_alloc
	#define _LIBCPP_HAS_NO_BUILTIN_IS_CONSTANT_EVALUATED
	#define _LIBCPP_HAS_NO_CHAR8_T
	#define _LIBCPP_NO_HAS_CHAR8_T
#endif
