#include <osal/environment.hpp>

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#include <windows.h>
#elif CTL_TARGET_OS & CTL_OS_FLAG_POSIX
	#include <cstdlib>
#else
	#error
#endif

namespace osal::environment
{
	OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, std::string &value) noexcept
	{
	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		std::size_t len{0};
		value.resize(len);
		len = static_cast<std::size_t>(GetEnvironmentVariableA(name.data(), value.data(), static_cast<long>(len)));
		value.resize(len);
		if(len == 0) {
			return false;
		}
	#elif CTL_TARGET_OS & CTL_OS_FLAG_POSIX
		char *ptr{std::getenv(name.data())};
		if(!ptr) {
			return false;
		}
		value = ptr;
	#else
		#error
	#endif
		return true;
	}

	OSAL_SHARED_API bool OSAL_SHARED_API_CALL get(std::string_view name, bool &value) noexcept
	{
		using namespace std::literals::string_view_literals;
		std::string str;
		if(!get(name, str)) {
			return false;
		}
		std::transform(str.begin(), str.end(), str.begin(), 
			[](char c) noexcept {
				return std::tolower(c);
			}
		);
		if(str == "true"sv) {
			value = true;
		} else if(str == "false"sv) {
			value = false;
		} else {
			std::error_code ec;
			unsigned char i{ctl::to_integer<unsigned char>(str, ec)};
			if(ec) {
				value = false;
			} else {
				value = static_cast<bool>(i);
			}
		}
		return true;
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL remove(std::string_view name) noexcept
	{
	#if CTL_TARGET_OS & CTL_OS_FLAG_POSIX
		unsetenv(name.data());
	#else
		#error
	#endif
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL set(std::string_view name, std::string_view value) noexcept
	{
	#if CTL_TARGET_OS & CTL_OS_FLAG_POSIX
		setenv(name.data(), value.data(), 1);
	#else
		#error
	#endif
	}
}
