#pragma once

#include <features.h>
#include <cstdlib>

#if STDI_C_STDLIB & STDI_C_STDLIB_FLAG_NIX
	#include <sysexits.h>

	#define __OSAL_EX_USAGE EX_USAGE
	#define __OSAL_EX_DATAERR EX_DATAERR
	#define __OSAL_EX_NOINPUT EX_NOINPUT
	#define __OSAL_EX_NOUSER EX_NOUSER
	#define __OSAL_EX_NOHOST EX_NOHOST
	#define __OSAL_EX_UNAVAILABLE EX_UNAVAILABLE
	#define __OSAL_EX_SOFTWARE EX_SOFTWARE
	#define __OSAL_EX_OSERR EX_OSERR
	#define __OSAL_EX_OSFILE EX_OSFILE
	#define __OSAL_EX_CANTCREAT EX_CANTCREAT
	#define __OSAL_EX_IOERR EX_IOERR
	#define __OSAL_EX_TEMPFAIL EX_TEMPFAIL
	#define __OSAL_EX_PROTOCOL EX_PROTOCOL
	#define __OSAL_EX_NOPERM EX_NOPERM
	#define __OSAL_EX_CONFIG EX_CONFIG
#else
	#define __OSAL_EX_USAGE       64
	#define __OSAL_EX_DATAERR     65
	#define __OSAL_EX_NOINPUT     66
	#define __OSAL_EX_NOUSER      67
	#define __OSAL_EX_NOHOST      68
	#define __OSAL_EX_UNAVAILABLE 69
	#define __OSAL_EX_SOFTWARE    70
	#define __OSAL_EX_OSERR       71
	#define __OSAL_EX_OSFILE      72
	#define __OSAL_EX_CANTCREAT   73
	#define __OSAL_EX_IOERR       74
	#define __OSAL_EX_TEMPFAIL    75
	#define __OSAL_EX_PROTOCOL    76
	#define __OSAL_EX_NOPERM      77
	#define __OSAL_EX_CONFIG      78
#endif

namespace osal
{
	enum class exit_codes : unsigned char
	{
		success = EXIT_SUCCESS,
		unknown_failure = EXIT_FAILURE,
		usage_error = __OSAL_EX_USAGE,
		input_invalid = __OSAL_EX_DATAERR,
		input_unavailable = __OSAL_EX_NOINPUT,
		user_unavailable = __OSAL_EX_NOUSER,
		host_unavailable = __OSAL_EX_NOHOST,
		resource_unavailable = __OSAL_EX_UNAVAILABLE,
		internal_failure = __OSAL_EX_SOFTWARE,
		os_error = __OSAL_EX_OSERR,
		os_resource_unavailable = __OSAL_EX_OSFILE,
		output_unavailable = __OSAL_EX_CANTCREAT,
		io_error = __OSAL_EX_IOERR,
		try_again = __OSAL_EX_TEMPFAIL,
		remote_error = __OSAL_EX_PROTOCOL,
		permission_error = __OSAL_EX_NOPERM,
		config_error = __OSAL_EX_CONFIG
	};
}
