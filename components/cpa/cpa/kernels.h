#pragma once

#define CPA_KERNEL_FLAG_NIX         (1 << 0)
#define CPA_KERNEL_FLAG_POSIX       (1 << 1)
#define __CPA_KERNEL_FLAGS_LAST_BIT       1

#define CPA_KERNEL_LINUX      ((1 << (__CPA_KERNEL_FLAGS_LAST_BIT+1))|CPA_KERNEL_FLAG_NIX|CPA_KERNEL_FLAG_POSIX)
#define CPA_KERNEL_WINDOWS    ((1 << (__CPA_KERNEL_FLAGS_LAST_BIT+2)))
#define CPA_KERNEL_EMSCRIPTEN ((1 << (__CPA_KERNEL_FLAGS_LAST_BIT+3))|CPA_KERNEL_FLAG_POSIX)

#if defined __linux__ || defined __linux || defined linux
	#define CPA_TARGET_KERNEL CPA_KERNEL_LINUX
#elif defined _WIN32
	#define CPA_TARGET_KERNEL CPA_KERNEL_WINDOWS
#elif defined __EMSCRIPTEN__
	#define CPA_TARGET_KERNEL CPA_KERNEL_EMSCRIPTEN
#else
	#error
#endif
