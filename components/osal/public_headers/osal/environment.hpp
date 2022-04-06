#pragma once

#include <cpa/os.h>
#include <ctl/filesystem>
#include <ctl/charconv>

#include "__details/api.h"

namespace osal
{
	#if CPA_TARGET_OS & CPA_OS_FLAG_NIX
		#define __OSAL_ENV_PATH_SEP ':'
	#elif CPA_TARGET_OS & CPA_OS_FLAG_WINDOWS
		#define __OSAL_ENV_PATH_SEP ';'
	#else
		#error
	#endif

	namespace environment
	{
		extern OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, std::string &value) noexcept;
		extern OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, bool &value) noexcept;

		template <typename T>
		inline T get(std::string_view name) noexcept
		{
			T tmp;
			get(name, tmp);
			return tmp;
		}

		extern OSAL_SHARED_API void OSAL_SHARED_API_CALL set(std::string_view name, std::string_view value) noexcept;

		inline void set(std::string_view name, const std::string &value) noexcept
		{ set(name, static_cast<std::string_view>(value)); }

		inline void set(std::string_view name, ctl::filesystem::path_view value) noexcept
		{ set(name, value.native()); }

		void set(std::string_view name, bool value) noexcept = delete;

		template <typename T>
		inline void set(std::string_view name, T &&value) noexcept
		{ set(name, ctl::to_string<T>(std::forward<T>(value))); }

		extern OSAL_SHARED_API void OSAL_SHARED_API_CALL remove(std::string_view name) noexcept;
	}
}
