#include <osal/process.hpp>

#if CTL_TARGET_PLATFORM == CTL_PLATFORM_WEB
	#error
#endif

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#include <windows.h>
#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
	#include <ctl/charconv>
	#include <unistd.h>
	#include <climits>
	#include <signal.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <cstring>
	#include <fcntl.h>
#else
	#error
#endif

#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
	#if CTL_LIBC == CTL_LIBC_GLIBC
		#define __OSAL_SI_STATUS _sifields._sigchld.si_status
		#define __OSAL_SA_HANDLER __sigaction_handler.sa_handler
	#elif CTL_LIBC == CTL_LIBC_MUSL
		#define __OSAL_SI_STATUS __si_fields.__si_common.__second.__sigchld.si_status
		#define __OSAL_SA_HANDLER __sa_handler.sa_handler
	#else
		#error
	#endif
#endif

#define __OSAL_EXITSTATUS_SIGNAL 128

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#define __OSAL_EXITSTATUS_KILL (__OSAL_EXITSTATUS_SIGNAL+9)
	#define __OSAL_EXITSTATUS_ABORT (__OSAL_EXITSTATUS_SIGNAL+6)
#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
	#define __OSAL_EXITSTATUS_KILL (__OSAL_EXITSTATUS_SIGNAL+SIGKILL)
	#define __OSAL_EXITSTATUS_ABORT (__OSAL_EXITSTATUS_SIGNAL+SIGABRT)
#endif

namespace osal
{
	namespace this_process
	{
		namespace __private
		{
		#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
			CTL_GLOBAL_CTOR_BEGIN
			static std::filesystem::path path;
			CTL_GLOBAL_CTOR_END

			static void child_handler(int) noexcept
			{
				siginfo_t info{};
				int ret{waitid(P_ALL, 0, &info, WEXITED|WSTOPPED|WNOHANG)};
				if(ret == -1 && errno == ECHILD) {
					return;
				}

				CTL_DEBUGTRAP;
			}

			static void getpath() noexcept
			{
				std::string tmp;
				tmp.resize(PATH_MAX);
			#if CTL_TARGET_KERNEL & CTL_KERNEL_FLAG_UNIX
				ssize_t len{readlink("/proc/self/exe", tmp.data(), PATH_MAX)};
			#else
				#error
			#endif
				if(len < 0) {
					return;
				}
				tmp.resize(static_cast<std::size_t>(len));
			#ifndef CTL_FILESYSTEM_PATH_WIDE
				path = std::move(tmp);
			#else
				path = std::move(tmp);
			#endif
			}

			CTL_STATIC_INIT_FUNC()
			{
				struct sigaction act{};
				sigemptyset(&act.sa_mask);
				act.sa_flags = 0;
				#pragma push_macro("sa_handler")
				#undef sa_handler
				act.__OSAL_SA_HANDLER = child_handler;
				#pragma pop_macro("sa_handler")
				sigaction(SIGCHLD, &act, nullptr);

				getpath();
			}
		#endif
		}

		OSAL_SHARED_API process::id_type OSAL_SHARED_API_CALL id() noexcept
		{
		#if CTL_TARGET_OS == CTL_OS_WINDOWS
			return GetCurrentProcessId();
		#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
			return getpid();
		#else
			#error
		#endif
		}

		OSAL_SHARED_API const std::filesystem::path & OSAL_SHARED_API_CALL path() noexcept
		{
			if(__private::path.empty()) {
				__private::getpath();
			}
			return __private::path;
		}

		OSAL_SHARED_API std::vector<std::string> OSAL_SHARED_API_CALL argv() noexcept
		{
			OSAL_COMMENT("TODO!!!")

			std::vector<std::string> tmp;
			return tmp;
		}
	}

	OSAL_SHARED_API OSAL_SHARED_API_CALL process::~process() noexcept
	{
		if(id_ == invalid_id) {
			return;
		}

		if(running()) {
		#if CTL_TARGET_OS == CTL_OS_WINDOWS
			TerminateProcess(handle, __OSAL_EXITSTATUS_KILL);
		#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
			kill(id_, SIGKILL);
		#else
			#error
		#endif
		}
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL process::signal(signals sig__) noexcept
	{
		if(id_ == invalid_id) {
			return;
		}

		switch(sig__) {
			case signals::kill: {
			#if CTL_TARGET_OS == CTL_OS_WINDOWS
				TerminateProcess(handle, __OSAL_EXITSTATUS_KILL);
			#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
				kill(id_, SIGKILL);
			#else
				#error
			#endif
				ret.emplace(__OSAL_EXITSTATUS_KILL);
				sig.emplace(sig__);
				id_ = invalid_id;
				break;
			}
			case signals::abort: {
			#if CTL_TARGET_OS == CTL_OS_WINDOWS
				TerminateProcess(handle, __OSAL_EXITSTATUS_ABORT);
			#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
				kill(id_, SIGABRT);
			#else
				#error
			#endif
				ret.emplace(__OSAL_EXITSTATUS_ABORT);
				sig.emplace(sig__);
				id_ = invalid_id;
				break;
			}
			case signals::terminate: {
			#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
				kill(id_, SIGTERM);
			#else
				#error
			#endif
				sig.emplace(sig__);
				break;
			}
			case signals::interrupt: {
			#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
				kill(id_, SIGINT);
			#else
				#error
			#endif
				sig.emplace(sig__);
				break;
			}
			default: { break; }
		}
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL process::spawn(char *argv[]) noexcept
	{
	#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
		int fds[2]{-1};
		const bool piped{pipe(fds) == 0};
		if(piped) {
			fcntl(fds[0], F_SETFD, FD_CLOEXEC);
		}
		id_ = vfork();
		if(id_ == -1) {
			id_ = invalid_id;
		} else if(id_ == 0) {
			if(piped) {
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
				close(fds[0]);
			}
			if(execve(argv[0], argv, environ) == -1) {
				std::exit(126);
			}
		} else if(id_ > 0) {
			if(piped) {
				close(fds[1]);
				stdout_fd = fds[0];
			} else {
				stdout_fd = -1;
			}
		}
	#else
		#error
	#endif
	}

	OSAL_SHARED_API bool OSAL_SHARED_API_CALL process::running() const noexcept
	{
		if(id_ == invalid_id) {
			return false;
		}
	#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
		siginfo_t info{};
		if(waitid(P_PID, static_cast<id_t>(id_), &info, WEXITED|WSTOPPED|WNOHANG) == 0 &&
			info.si_signo == 0) {
			return true;
		}

		const_cast<process *>(this)->id_ = invalid_id;

		if(stdout_fd != -1) {
			while(true) {
				char c{'\0'};
				if(read(stdout_fd, &c, sizeof(char)) <= 0) {
					break;
				}
				const_cast<process *>(this)->stdout_ += c;
			}

			close(stdout_fd);
			const_cast<process *>(this)->stdout_fd = -1;
		}

		switch(info.si_code) {
			case CLD_EXITED: {
				#pragma push_macro("si_status")
				#undef si_status
				const_cast<process *>(this)->ret.emplace(info.__OSAL_SI_STATUS);
				#pragma pop_macro("si_status")
				break;
			}
			case CLD_DUMPED:
			case CLD_KILLED: {
				#pragma push_macro("si_status")
				#undef si_status
				switch(info.__OSAL_SI_STATUS) {
				#pragma pop_macro("si_status")
					case SIGKILL: {
						const_cast<process *>(this)->sig.emplace(signals::kill);
						#pragma push_macro("si_status")
						#undef si_status
						const_cast<process *>(this)->ret.emplace(__OSAL_EXITSTATUS_SIGNAL+info.__OSAL_SI_STATUS);
						#pragma pop_macro("si_status")
						break;
					}
					case SIGABRT: {
						const_cast<process *>(this)->sig.emplace(signals::abort);
						#pragma push_macro("si_status")
						#undef si_status
						const_cast<process *>(this)->ret.emplace(__OSAL_EXITSTATUS_SIGNAL+info.__OSAL_SI_STATUS);
						#pragma pop_macro("si_status")
						break;
					}
					case SIGTERM: {
						const_cast<process *>(this)->sig.emplace(signals::terminate);
						break;
					}
					case SIGINT: {
						const_cast<process *>(this)->sig.emplace(signals::interrupt);
						break;
					}
					default: {
						CTL_DEBUGTRAP;
						const_cast<process *>(this)->sig.emplace(signals::unknown);
						break;
					}
				}
				break;
			}
		}
		return false;
	#else
		#error
	#endif
	}
}
