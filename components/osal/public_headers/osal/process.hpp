#pragma once

#include <ctl/version>

#if CTL_TARGET_PLATFORM == CTL_PLATFORM_WEB
	#error
#endif

#include <ctl/filesystem>
#include <ctl/vector>
#include <ctl/optional>
#include <ctl/string>
#include <ctl/string_view>

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#include <windows.h>
#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
	#include <sys/types.h>
#endif

#include "__private/api.hpp"

namespace osal
{
	class CTL_LOCAL_CLASS process
	{
	public:
		process(process &&) noexcept = default;
		process &operator=(process &&) noexcept = default;

		OSAL_SHARED_API OSAL_SHARED_API_CALL ~process() noexcept;

	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		using id_type = long;
	#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
		using id_type = pid_t;
	#else
		#error
	#endif

		static constexpr id_type invalid_id{static_cast<id_type>(0)};

		inline process(char *argv[]) noexcept
		{ spawn(argv); }

		process(std::initializer_list<std::string_view> argv) noexcept;

	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		#error
	#else
		inline id_type id() const noexcept
		{ return id_; }
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

		OSAL_SHARED_API bool OSAL_SHARED_API_CALL running() const noexcept;
		inline std::optional<int> exit_code() const noexcept
		{ return ret; }
		inline std::optional<signals> signal() const noexcept
		{ return sig; }

		#pragma push_macro("stdout")
		#undef stdout
		inline const std::string &stdout() const noexcept
		#pragma pop_macro("stdout")
		{ return stdout_; }

	private:
		process() noexcept = delete;
		process(const process &) noexcept = delete;
		process &operator=(const process &) noexcept = delete;

		OSAL_SHARED_API void OSAL_SHARED_API_CALL spawn(char *argv[]) noexcept;

		std::optional<int> ret;
		std::optional<signals> sig;
		std::string stdout_;

	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		HANDLE handle;
	#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
		id_type id_;
	#else
		#error
	#endif

	#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
		int stdout_fd;
	#endif
	};

	namespace this_process
	{
		extern OSAL_SHARED_API process::id_type OSAL_SHARED_API_CALL id() noexcept;
		extern OSAL_SHARED_API const std::filesystem::path & OSAL_SHARED_API_CALL path() noexcept;
		extern OSAL_SHARED_API std::vector<std::string> OSAL_SHARED_API_CALL argv() noexcept;
		extern OSAL_SHARED_API std::string OSAL_SHARED_API_CALL cmdline() noexcept;
	}
}
