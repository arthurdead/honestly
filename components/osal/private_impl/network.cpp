#include <osal/network.hpp>

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#include <windows.h>
#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
	#include <unistd.h>
	#include <climits>
#else
	#error
#endif

namespace osal
{
	OSAL_SHARED_API std::string OSAL_SHARED_API_CALL hostname() noexcept
	{
	#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
		char tmp[HOST_NAME_MAX]{'\0'};
	#else
		#error
	#endif
		gethostname(tmp, std::size(tmp));
		return std::string{tmp};
	}
}
