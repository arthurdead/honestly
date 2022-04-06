#include <cpa/kernels.h>
#include <osal/main.hpp>

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
	#ifdef _WINDOWS
		#include <windows.h>
	#endif
#endif

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
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
	return application_main(argc, argv, envp);
}
		#endif
	#endif
#elif CPA_TARGET_KERNEL == CPA_KERNEL_LINUX
int main(int argc, char *argv[], char *envp[])
{
	return application_main(argc, argv, envp);
}
#elif CPA_TARGET_KERNEL == CPA_KERNEL_EMSCRIPTEN
	#error
#endif
