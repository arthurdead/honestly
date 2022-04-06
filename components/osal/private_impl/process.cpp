#include <cpa/platforms.h>

#if CPA_TARGET_PLATFORM == CPA_PLATFORM_WEB
	#error
#endif

#include <osal/process.hpp>
#include <cpa/kernels.h>

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
	#include <windows.h>
#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
	#include <unistd.h>
	#include <climits>
	#include <signal.h>
	#include <sys/types.h>
	#include <sys/wait.h>
#else
	#error
#endif

#include <osal/__details/comment.h>

#if CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
	#if STDI_C_STDLIB == STDI_STDLIB_GLIBC
		#define __OSAL_SI_STATUS _sifields._sigchld.si_status
		#define __OSAL_SA_HANDLER __sigaction_handler.sa_handler
	#elif STDI_C_STDLIB == STDI_STDLIB_MUSL
		#define __OSAL_SI_STATUS __si_fields.__si_common.__second.__sigchld.si_status
		#define __OSAL_SA_HANDLER __sa_handler.sa_handler
	#else
		#error
	#endif
#endif

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
	#define __OSAL_SIGNAL_KILL 9
	#define __OSAL_SIGNAL_ABORT 6
#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
	#define __OSAL_SIGNAL_KILL SIGKILL
	#define __OSAL_SIGNAL_ABORT SIGABRT
#else
	#error
#endif

#define __OSAL_EXITSTATUS_SIGNAL 128

namespace osal
{
	namespace this_process
	{
		OSAL_SHARED_API process::id_type OSAL_SHARED_API_CALL id() noexcept
		{
		#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
			return GetCurrentProcessId();
		#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
			return getpid();
		#else
			#error
		#endif
		}

		OSAL_SHARED_API std::filesystem::path OSAL_SHARED_API_CALL path() noexcept
		{
		#if CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
			std::string tmp;
			tmp.reserve(PATH_MAX);
			ssize_t len{readlink("/proc/self/exe", tmp.data(), PATH_MAX)};
			if(len < 0) {
				return std::filesystem::path{};
			}
			tmp.resize(static_cast<std::size_t>(len));
			tmp.shrink_to_fit();
			return std::filesystem::path{std::move(tmp)};
		#else
			#error
		#endif
		}
	}

	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		#define __OSAL_KILL_BASE(sig) \
			TerminateProcess(handle, __OSAL_EXITSTATUS_SIGNAL+sig);
		#define __OSAL_KILL(sig) \
			__OSAL_KILL_BASE(sig) \
			handle = nullptr; \
			last_return.emplace(__OSAL_EXITSTATUS_SIGNAL+sig);
	#elif CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
		#define __OSAL_KILL_BASE(sig) \
			kill(pid, sig);
		#define __OSAL_KILL(sig) \
			__OSAL_KILL_BASE(sig) \
			pid = 0; \
			last_return.emplace(__OSAL_EXITSTATUS_SIGNAL+sig);
	#else
		#error
	#endif

	OSAL_SHARED_API OSAL_SHARED_API_CALL process::~process() noexcept
	{
		if(running()) {
			__OSAL_KILL_BASE(__OSAL_SIGNAL_KILL)
		}
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL process::signal(signals sig) noexcept
	{
		if(!running()) {
			return;
		}

		last_signal.emplace(sig);

		switch(sig) {
			case signals::kill: {
				__OSAL_KILL(__OSAL_SIGNAL_KILL)
			} break;
			case signals::abort: {
				__OSAL_KILL(__OSAL_SIGNAL_ABORT)
			} break;
			case signals::terminate: {
			#if CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
				kill(pid, SIGTERM);
			#else
				#error
			#endif
			} break;
			case signals::interrupt: {
			#if CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
				kill(pid, SIGINT);
			#else
				#error
			#endif
			} break;
		}
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL process::spawn(char *argv[]) noexcept
	{
	#if CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
		pid = vfork();
		if(pid == -1) {
			pid = 0;
		} else if(pid == 0) {
			if(execve(argv[0], argv, environ) == -1) {
				std::exit(126);
			}
		}
	#else
		#error
	#endif
	}

	OSAL_SHARED_API bool OSAL_SHARED_API_CALL process::running() noexcept
	{
	#if CPA_TARGET_KERNEL & CPA_KERNEL_FLAG_POSIX
		if(pid == 0) {
			return false;
		}

		siginfo_t info{};
		if(waitid(P_PID, static_cast<id_t>(pid), &info, WEXITED|WSTOPPED|WNOHANG) == 0 &&
			info.si_signo == 0) {
			return true;
		}

		pid = 0;

		switch(info.si_code) {
			case CLD_EXITED: {
				#pragma push_macro("si_status")
				#undef si_status
				last_return.emplace(info.__OSAL_SI_STATUS);
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
						last_signal.emplace(signals::kill);
						#pragma push_macro("si_status")
						#undef si_status
						last_return.emplace(__OSAL_EXITSTATUS_SIGNAL+info.__OSAL_SI_STATUS);
						#pragma pop_macro("si_status")
						break;
					}
					case SIGABRT: {
						last_signal.emplace(signals::abort);
						#pragma push_macro("si_status")
						#undef si_status
						last_return.emplace(__OSAL_EXITSTATUS_SIGNAL+info.__OSAL_SI_STATUS);
						#pragma pop_macro("si_status")
						break;
					}
					case SIGTERM: {
						last_signal.emplace(signals::terminate);
						break;
					}
					case SIGINT: {
						last_signal.emplace(signals::interrupt);
						break;
					}
					default: {
						CPA_TRAP;
						last_signal.emplace(signals::unknown);
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
