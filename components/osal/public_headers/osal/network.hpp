#pragma once

#include <ctl/version>
#include <ctl/string>

#include "__private/api.hpp"

namespace osal
{
	extern OSAL_SHARED_API std::string OSAL_SHARED_API_CALL hostname() noexcept;
}
