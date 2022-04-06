#pragma once

#define CPA_OS_FLAG_WINDOWS     (1 << 0)
#define CPA_OS_FLAG_NIX         (1 << 1)
#define CPA_OS_FLAG_POSIX       (1 << 2)
#define __CPA_OS_FLAGS_LAST_BIT       2

#define __CPA_OS_FLAGS_NIX (CPA_OS_FLAG_NIX|CPA_OS_FLAG_POSIX)

#define CPA_OS_GNU     ((1 << (__CPA_OS_FLAGS_LAST_BIT+1))|__CPA_OS_FLAGS_NIX)
#define CPA_OS_ANDROID ((1 << (__CPA_OS_FLAGS_LAST_BIT+2))|__CPA_OS_FLAGS_NIX)
#define CPA_OS_WINDOWS ((1 << (__CPA_OS_FLAGS_LAST_BIT+3))|CPA_OS_FLAG_WINDOWS)
#define CPA_OS_CYGWIN  ((1 << (__CPA_OS_FLAGS_LAST_BIT+4))|CPA_OS_FLAG_WINDOWS|__CPA_OS_FLAGS_NIX)

#ifdef __ANDROID__
	#define CPA_TARGET_OS CPA_OS_ANDROID
#elif defined __CYGWIN__
	#define CPA_TARGET_OS CPA_OS_CYGWIN
#elif defined __gnu_linux__ || defined __GNU__
	#define CPA_TARGET_OS CPA_OS_GNU
#elif defined _WIN32
	#define CPA_TARGET_OS CPA_OS_WINDOWS
#else
	#error
#endif
