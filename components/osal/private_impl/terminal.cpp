#include <osal/terminal.hpp>
#include <ctl/memory>

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#include <windows.h>
#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
	#include <unistd.h>
	#include <ctl/cstdio>
#else
	#error
#endif

namespace osal
{
	namespace __term
	{
		static std::string bits_to_str(bits_t bits) noexcept
		{
			using namespace std::literals::string_view_literals;
			std::string code_str{"\033["sv};
			if(!bits) {
				code_str += "0m"sv;
			} else {
				if(bits[0] > 0) {
					unsigned bit{static_cast<unsigned>(bits[0])};
					if(bit < 10) {
						bit -= 1;
						code_str += '3';
					} else {
						bit -= 10;
						code_str += '9';
					}
					code_str += static_cast<char>(48 + bit);
					code_str += ';';
				}
				if(bits[1] > 0) {
					unsigned bit{static_cast<unsigned>(bits[1])};
					if(bit < 10) {
						bit -= 1;
						code_str += '4';
					} else {
						bit -= 10;
						code_str += "10"sv;
					}
					code_str += static_cast<char>(48 + bit);
					code_str += ';';
				}
				if(bits[2] > 0) {
					const unsigned bit{static_cast<unsigned>(bits[2])};
					code_str += static_cast<char>(48 + bit);
					code_str += ';';
				}
				if(bits[3] > 0) {
					unsigned bit{static_cast<unsigned>(bits[3])};
					if(bit == 6) {
						bit = 5;
					}
					code_str += '2';
					code_str += static_cast<char>(48 + bit);
					code_str += ';';
				}
				if(bits[4] > 0) {
					unsigned bit{static_cast<unsigned>(bits[0])};
					if(bit < 10) {
						--bit;
					} else {
						bit -= 2;
					}
					code_str += "58;5;"sv;
					code_str += static_cast<char>(48 + bit);
					code_str += ';';
				}
				code_str.pop_back();
				code_str += 'm';
			}
			return code_str;
		}
	}

	namespace this_terminal::__private
	{
		OSAL_SHARED_API void OSAL_SHARED_API_CALL print_impl(std::string_view str) noexcept
		{
		#if CTL_TARGET_OS == CTL_OS_WINDOWS
			static HANDLE out{GetStdHandle(STD_OUTPUT_HANDLE)};
			#error
			WriteConsoleA(out, str.data(), str.length(), nullptr, nullptr);
		#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
			#pragma push_macro("stdout")
			#undef stdout
			fwrite(str.data(), sizeof(char), str.length(), stdout);
			#pragma pop_macro("stdout")
		#else
			#error
		#endif
		}

		OSAL_SHARED_API void OSAL_SHARED_API_CALL handle_bits(__term::bits_t bits) noexcept
		{
			print_impl(__term::bits_to_str(bits));
		#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
			if(!bits) {
				#pragma push_macro("stdout")
				#undef stdout
				fflush(stdout);
				#pragma pop_macro("stdout")
			}
		#endif
		}
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL terminal::print_impl(std::string_view str) noexcept
	{
	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		WriteConsoleA(output, str.data(), str.length(), nullptr, nullptr);
	#elif CTL_LIBC & CTL_LIBC_FLAG_POSIX
		fwrite(str.data(), sizeof(char), str.length(), output);
	#else
		#error
	#endif
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL terminal::handle_bits(__term::bits_t bits) noexcept
	{ print_impl(__term::bits_to_str(bits)); }
}
