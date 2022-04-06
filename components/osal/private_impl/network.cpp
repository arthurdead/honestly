#include <osal/network.hpp>
#include <cpa/kernels.h>

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
	#include <windows.h>

	#define __OSAL_HOST_NAME_MAX 256
#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
	#include <unistd.h>
	#include <climits>

	#define __OSAL_HOST_NAME_MAX HOST_NAME_MAX
#else
	#error
#endif

namespace osal
{
	OSAL_SHARED_API std::string OSAL_SHARED_API_CALL hostname() noexcept
	{
		char tmp[__OSAL_HOST_NAME_MAX];
		gethostname(tmp, std::size(tmp));
		return std::string{std::move(tmp)};
	}
}
