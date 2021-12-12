#include <ctl/version>
#include <osal/main.hpp>

#if CTL_TARGET_KERNEL == CTL_KERNEL_WINDOWS
	#include <windows.h>
#endif

#if CTL_TARGET_KERNEL & CTL_KERNEL_FLAG_UNIX
int main(int argc, char *argv[], char *envp[])
{
	return application_main(argc, argv, envp);
}
#elif CTL_TARGET_KERNEL == CTL_KERNEL_EMSCRIPTEN
int main(int argc, char *argv[])
{
	char *envp[]{nullptr};
	return application_main(argc, argv, envp);
}
#elif CTL_TARGET_KERNEL == CTL_KERNEL_WINDOWS
	#ifdef _WINDOWS
		#ifdef _UNICODE
			#error
		#else
			#error
		#endif
	#else
		#ifdef _UNICODE
			#error
		#else
int main(int argc, char *argv[])
{
	char *envp[]{nullptr};
	int ret{application_main(argc, argv, envp)};
	return ret;
}
		#endif
	#endif
#else
	#error
#endif
