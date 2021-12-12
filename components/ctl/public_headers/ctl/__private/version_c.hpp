#define CTL_C_89 0
#define CTL_C_90 0
#define CTL_C_94 199409L
#define CTL_C_99 199901L
#define CTL_C_11 201112L
#define CTL_C_18 201710L

#ifdef __STDC_VERSION__
	#define CTL_C_VERSION __STDC_VERSION__
#elif defined __STDC__
	#define CTL_C_VERSION 0
#else
	#error
#endif
