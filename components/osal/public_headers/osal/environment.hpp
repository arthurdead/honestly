#pragma once

#include <ctl/version>
#include <ctl/filesystem>
#include <ctl/vector>
#include <ctl/charconv>
#include <ctl/filesystem>

#include "__private/api.hpp"

namespace osal
{
	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		#define __OSAL_ENV_PATH_SEP ';'
	#else
		#define __OSAL_ENV_PATH_SEP ':'
	#endif

	namespace environment
	{
		extern OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, std::string &value) noexcept;
		extern OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, bool &value) noexcept;
		//extern OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, std::vector<std::filesystem::path> &value, char sep = __OSAL_ENV_PATH_SEP) noexcept;

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
		inline void set(std::string_view name, T value) noexcept
		{ set(name, ctl::to_string<T>(value)); }

		extern OSAL_SHARED_API void OSAL_SHARED_API_CALL remove(std::string_view name) noexcept;
	}
}
