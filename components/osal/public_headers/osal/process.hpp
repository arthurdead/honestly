#pragma once

#include <cpa/platforms.h>

#if CPA_TARGET_PLATFORM == CPA_PLATFORM_WEB
	#error
#endif

#include <filesystem>
#include <vector>
#include <optional>
#include <string>
#include <string_view>
#include <cpa/kernels.h>

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
	#include <windows.h>
#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
	#include <sys/types.h>
#else
	#error
#endif

#include "__details/api.h"

namespace osal
{
	class CPA_LOCAL_CLASS process
	{
	public:
		process(process &&) noexcept = default;
		process &operator=(process &&) noexcept = default;

		OSAL_SHARED_API OSAL_SHARED_API_CALL ~process() noexcept;

	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		using id_type = long;
	#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
		using id_type = pid_t;
	#else
		#error
	#endif

		static constexpr id_type invalid_id{static_cast<id_type>(0)};

		inline process(char *argv[]) noexcept
		{ spawn(argv); }

		process(std::initializer_list<std::string_view> argv) noexcept;

	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		#error
	#else
		inline id_type id() const noexcept
		{ return pid; }
	#endif

		enum class signals : unsigned char
		{
			kill,
			terminate,
			interrupt,
			abort,
			unknown,
		};

		OSAL_SHARED_API void OSAL_SHARED_API_CALL signal(signals sig) noexcept;

		OSAL_SHARED_API bool OSAL_SHARED_API_CALL running() noexcept;
		inline const std::optional<int> &exit_code() const noexcept
		{ return last_return; }
		inline const std::optional<signals> &signal() const noexcept
		{ return last_signal; }

	private:
		process() noexcept = delete;
		process(const process &) noexcept = delete;
		process &operator=(const process &) noexcept = delete;

		OSAL_SHARED_API void OSAL_SHARED_API_CALL spawn(char *argv[]) noexcept;

		std::optional<int> last_return;
		std::optional<signals> last_signal;

	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		HANDLE handle;
	#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
		pid_t pid;
	#else
		#error
	#endif
	};

	namespace this_process
	{
		extern OSAL_SHARED_API process::id_type OSAL_SHARED_API_CALL id() noexcept;
		extern OSAL_SHARED_API std::filesystem::path OSAL_SHARED_API_CALL path() noexcept;
		extern OSAL_SHARED_API std::vector<std::string> OSAL_SHARED_API_CALL argv() noexcept;
		extern OSAL_SHARED_API std::string OSAL_SHARED_API_CALL cmdline() noexcept;
	}
}
