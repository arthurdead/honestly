#include <osal/terminal.hpp>
#include <cpa/kernels.h>
#include <cpa/os.h>

#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
	#include <windows.h>
#else
	#include <cstdio>
#endif

#if CPA_TARGET_OS & CPA_OS_FLAG_NIX || CPA_TARGET_OS & CPA_OS_FLAG_WINDOWS
	#define __OSAL_ANSI_CODES_SUPPORTED
#endif

namespace osal
{
	namespace __details_terminal
	{
	#ifdef __OSAL_ANSI_CODES_SUPPORTED
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
	#endif
	}

	namespace this_terminal::__private
	{
		OSAL_SHARED_API void OSAL_SHARED_API_CALL print_impl(std::string_view str) noexcept
		{
		#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
			static HANDLE out{GetStdHandle(STD_OUTPUT_HANDLE)};
			#error
			WriteConsoleA(out, str.data(), str.length(), nullptr, nullptr);
		#else
			fwrite(str.data(), sizeof(char), str.length(), stdout);
		#endif
		}

		OSAL_SHARED_API void OSAL_SHARED_API_CALL handle_bits(__details_terminal::bits_t bits) noexcept
		{
		#ifdef __OSAL_ANSI_CODES_SUPPORTED
			print_impl(__details_terminal::bits_to_str(bits));
		#else
			#error
		#endif
		#if CPA_TARGET_KERNEL != CPA_KERNEL_WINDOWS
			if(!bits) {
				fflush(stdout);
			}
		#endif
		}
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL terminal::print_impl(std::string_view str) noexcept
	{
	#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
		WriteConsoleA(output, str.data(), str.length(), nullptr, nullptr);
	#else
		fwrite(str.data(), sizeof(char), str.length(), output);
	#endif
	}

	OSAL_SHARED_API void OSAL_SHARED_API_CALL terminal::handle_bits(__details_terminal::bits_t bits) noexcept
	{
	#ifdef __OSAL_ANSI_CODES_SUPPORTED
		print_impl(__details_terminal::bits_to_str(bits));
	#else
		#error
	#endif
	#if CPA_TARGET_KERNEL != CPA_KERNEL_WINDOWS
		if(!bits) {
			fflush(output);
		}
	#endif
	}
}
