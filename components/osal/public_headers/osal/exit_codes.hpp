#pragma once

#include <ctl/version>
#include <cstdlib>

#if CTL_LIBC & CTL_LIBC_FLAG_GNU
	#include <sysexits.h>
#endif

namespace osal
{
	enum class exit_codes : unsigned char
	{
		success = EXIT_SUCCESS,
		unknown_failure = EXIT_FAILURE,
	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		usage_error = 64,
		input_invalid = 65,
		input_unavailable = 66,
		user_unavailable = 67,
		host_unavailable = 68,
		resource_unavailable = 69,
		internal_failure = 70,
		os_error = 71,
		os_resource_unavailable = 72,
		output_unavailable = 73,
		io_error = 74,
		tryagain = 75,
		remote_error = 76,
		permission_error = 77,
		config_error = 78,
	#elif CTL_LIBC & CTL_LIBC_FLAG_GNU
		usage_error = EX_USAGE,
		input_invalid = EX_DATAERR,
		input_unavailable = EX_NOINPUT,
		user_unavailable = EX_NOUSER,
		host_unavailable = EX_NOHOST,
		resource_unavailable = EX_UNAVAILABLE,
		internal_failure = EX_SOFTWARE,
		os_error = EX_OSERR,
		os_resource_unavailable = EX_OSFILE,
		output_unavailable = EX_CANTCREAT,
		io_error = EX_IOERR,
		tryagain = EX_TEMPFAIL,
		remote_error = EX_PROTOCOL,
		permission_error = EX_NOPERM,
		config_error = EX_CONFIG,
	#else
		#error
	#endif
	};
}
