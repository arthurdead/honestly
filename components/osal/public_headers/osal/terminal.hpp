#pragma once

#include <ctl/version>
#include <ctl/optional>
#include <ctl/charconv>
#include <ctl/filesystem>

#include "__private/api.hpp"

#if CTL_TARGET_OS == CTL_OS_WINDOWS
	#include <windows.h>
#endif

namespace osal
{
	namespace __term
	{
		#define __OSAL_TERM_CLRS \
			black = 1, \
			red, \
			green, \
			yellow, \
			blue, \
			magenta, \
			cyan, \
			white, \
			default_ = 9, \
			bright_black = 10, \
			bright_red, \
			bright_green, \
			bright_yellow, \
			bright_blue, \
			bright_magenta, \
			bright_cyan, \
			bright_white,

		enum class colors : unsigned char
		{
			__OSAL_TERM_CLRS
		};
		enum class fg_colors : unsigned char
		{
			__OSAL_TERM_CLRS
		};
		enum class bg_colors : unsigned char
		{
			__OSAL_TERM_CLRS
		};
		enum class underline_colors : unsigned char
		{
			__OSAL_TERM_CLRS
		};

		#define __OSAL_TERM_EFFCTS \
			bold = 1, \
			dim, \
			italic, \
			underline, \
			slow_blink, \
			rapid_blink, \
			invert, \
			conceal, \
			strike,

		enum class effects : unsigned char
		{
			__OSAL_TERM_EFFCTS
		};
		enum class enable_effect_t : unsigned char
		{
			__OSAL_TERM_EFFCTS
		};
		enum class disable_effect_t : unsigned char
		{
			__OSAL_TERM_EFFCTS
		};

		struct reset_effects_t final
		{
		};

		union CTL_LOCAL_CLASS bits_t final {
		public:
			constexpr bits_t() noexcept = default;
			constexpr inline operator bool() const noexcept
			{ return (packed != 0); }
			constexpr inline bool operator!() const noexcept
			{ return (packed == 0); }
			constexpr inline operator fg_colors() const noexcept
			{ return fg_colors{static_cast<fg_colors>(data[0])}; }
			constexpr inline operator bg_colors() const noexcept
			{ return bg_colors{static_cast<bg_colors>(data[1])}; }
			constexpr inline operator enable_effect_t() const noexcept
			{ return enable_effect_t{static_cast<enable_effect_t>(data[2])}; }
			constexpr inline operator disable_effect_t() const noexcept
			{ return disable_effect_t{static_cast<disable_effect_t>(data[3])}; }
			constexpr inline operator underline_colors() const noexcept
			{ return underline_colors{static_cast<underline_colors>(data[4])}; }
			constexpr inline bits_t &operator|=(fg_colors clr) noexcept
			{ data[0] = static_cast<unsigned char>(clr); return *this; }
			constexpr inline bits_t &operator|=(bg_colors clr) noexcept
			{ data[1] = static_cast<unsigned char>(clr); return *this; }
			constexpr inline bits_t &operator=(reset_effects_t) noexcept
			{ packed = 0; return *this; }
			constexpr inline bits_t &operator|=(enable_effect_t clr) noexcept
			{ data[2] = static_cast<unsigned char>(clr); return *this; }
			constexpr inline bits_t &operator|=(disable_effect_t clr) noexcept
			{ data[3] = static_cast<unsigned char>(clr); return *this; }
			constexpr inline bits_t &operator|=(underline_colors clr) noexcept
			{ data[4] = static_cast<unsigned char>(clr); return *this; }
			constexpr inline unsigned char operator[](std::size_t i) const noexcept
			{ return data[i]; }
			constexpr inline void clear() noexcept
			{ packed = 0; }
			constexpr void error() noexcept
			{
				data[0] = static_cast<unsigned char>(fg_colors::bright_white);
				data[1] = static_cast<unsigned char>(bg_colors::bright_red);
			}
			constexpr inline void warning() noexcept
			{ data[0] = static_cast<unsigned char>(fg_colors::yellow); }
			constexpr inline void success() noexcept
			{ data[0] = static_cast<unsigned char>(fg_colors::green); }
			constexpr inline void info() noexcept
			{ data[0] = static_cast<unsigned char>(fg_colors::cyan); }
		private:
			unsigned long long packed{0};
			unsigned char data[8];
		};

		template <typename T, typename PF, typename BF>
		static void process_arg(std::string &str, const T &arg, PF &&pf, BF &&bf) noexcept
		{
			using decayed_t = std::decay_t<T>;
			if constexpr(std::is_same_v<decayed_t, char> ||
							std::is_same_v<decayed_t, std::string> ||
							std::is_same_v<decayed_t, std::string_view>) {
				str += arg;
			} else if constexpr(std::is_same_v<decayed_t, const char *> ||
								std::is_same_v<decayed_t, char *>) {
				str += std::string_view{arg};
			} else if constexpr(std::is_same_v<decayed_t, bool>) {
				using namespace std::literals::string_view_literals;
				str += (arg ? "true"sv : "false"sv);
			} else if constexpr(std::is_same_v<decayed_t, std::filesystem::path>) {
			#ifndef CTL_FILESYSTEM_PATH_WIDE
				str += arg.native();
			#else
				str += ctl::to_string(arg.native());
			#endif
			} else if constexpr(std::is_same_v<decayed_t, std::error_code>) {
				std::string tmp;
				tmp += arg.category().name();
				tmp += ':';
				tmp += ctl::to_string(arg.value());
				str += tmp;
			} else if constexpr(std::is_same_v<decayed_t, colors> ||
								std::is_same_v<decayed_t, effects>) {
				CTL_DEBUGTRAP;
			} else if constexpr(std::is_same_v<decayed_t, fg_colors> ||
								std::is_same_v<decayed_t, bg_colors> ||
								std::is_same_v<decayed_t, underline_colors> ||
								std::is_same_v<decayed_t, enable_effect_t> ||
								std::is_same_v<decayed_t, disable_effect_t>) {
				bits_t bits;
				bits |= arg;
				pf(str);
				bf(bits);
				str.clear();
			} else if constexpr(std::is_same_v<decayed_t, reset_effects_t>) {
				bits_t bits;
				bits = arg;
				pf(str);
				bf(bits);
				str.clear();
			} else {
				str += ctl::to_string(arg);
			}
		}
	}

	class CTL_LOCAL_CLASS terminal
	{
	public:
		using colors = __term::colors;
		using fg_colors = __term::fg_colors;
		using bg_colors = __term::bg_colors;
		using underline_colors = __term::underline_colors;

		using effects = __term::effects;
		using enable_effect_t = __term::enable_effect_t;
		using disable_effect_t = __term::disable_effect_t;
		static constexpr __term::reset_effects_t reset_effects_{};

		template <typename T>
		terminal &operator<<(const T &arg) noexcept;

		template <typename ...Args>
		void operator()(Args && ...args) noexcept;

		void print() noexcept = delete;
		void error() noexcept;
		void warning() noexcept;
		void info() noexcept;
		void success() noexcept;

		template <typename ...Args>
		void print(Args && ...args) noexcept;

		template <typename ...Args>
		void error(Args && ...args) noexcept;

		template <typename ...Args>
		void warning(Args && ...args) noexcept;

		template <typename ...Args>
		void info(Args && ...args) noexcept;

		template <typename ...Args>
		void success(Args && ...args) noexcept;

		void set_fg_color(colors clr) noexcept;
		void set_bg_color(colors clr) noexcept;
		void set_underline_color(colors clr) noexcept;

		void enable_effect(effects efct) noexcept;
		void disable_effect(effects efct) noexcept;
		void reset_effects() noexcept;

	private:
		template <typename T>
		CTL_LOCAL_FUNCTION void process_arg(std::string &str, const T &arg) noexcept
		{
			static constexpr auto pf{[this](std::string_view view) noexcept -> void { print_impl(view); }};
			static constexpr auto bf{[this](__term::bits_t bits) noexcept -> void { handle_bits(bits); }};
			__term::process_arg(str, arg, pf, bf);
		}

		OSAL_SHARED_API void OSAL_SHARED_API_CALL handle_bits(__term::bits_t bits) noexcept;
		OSAL_SHARED_API void OSAL_SHARED_API_CALL print_impl(std::string_view str) noexcept;

	#if CTL_TARGET_OS == CTL_OS_WINDOWS
		HANDLE output;
	#elif CTL_TARGET_OS & CTL_OS_FLAG_POSIX
		FILE *output;
	#else
		#error
	#endif
	};

	namespace this_terminal
	{
		namespace __private
		{
			extern OSAL_SHARED_API void OSAL_SHARED_API_CALL handle_bits(__term::bits_t bits) noexcept;
			extern OSAL_SHARED_API void OSAL_SHARED_API_CALL print_impl(std::string_view str) noexcept;

			template <typename T>
			static inline void process_arg(std::string &str, const T &arg) noexcept
			{ __term::process_arg(str, arg, print_impl, handle_bits); }
		}

		void set_fg_color(terminal::colors clr) noexcept;
		void set_bg_color(terminal::colors clr) noexcept;
		void set_underline_color(terminal::colors clr) noexcept;

		void enable_effect(terminal::effects efct) noexcept;
		void disable_effect(terminal::effects efct) noexcept;
		void reset_effects() noexcept;

		void print() = delete;
		void error() noexcept;
		void warning() noexcept;
		void info() noexcept;
		void success() noexcept;

		template <typename ...Args>
		void print(Args && ...args) noexcept;

		template <typename ...Args>
		void error(Args && ...args) noexcept;

		template <typename ...Args>
		void warning(Args && ...args) noexcept;

		template <typename ...Args>
		void info(Args && ...args) noexcept;

		template <typename ...Args>
		void success(Args && ...args) noexcept;
	}

	namespace __private
	{
		struct tout
		{
			template <typename ...Args>
			void operator()(Args && ...args) noexcept;

			template <typename T>
			tout &operator<<(const T &arg) noexcept;
		};
	}

	inline __private::tout tout;

	namespace literals::terminal_literals
	{
		using fg_colors = terminal::fg_colors;
		using bg_colors = terminal::bg_colors;
		using underline_colors = terminal::underline_colors;
		using enable_effect = terminal::enable_effect_t;
		using disable_effect = terminal::disable_effect_t;
		constexpr __term::reset_effects_t reset_effects;

		OSAL_COMMENT("TODO!!! implement missing")

		#define __OSAL_TERM_LIT_FNCS_BEGIN(fnc, nm) \
			inline void operator"" nm (const char *str, std::size_t len) noexcept \
			{ this_terminal:: fnc (std::string_view{str, len}); } \
			void operator"" nm (const char16_t *str, std::size_t len) = delete; \
			void operator"" nm (const char32_t *str, std::size_t len) = delete; \
			void operator"" nm (const wchar_t *str, std::size_t len) = delete;

	#ifndef __cpp_char8_t
		#define __OSAL_TERM_LIT_FNCS(fnc, nm) \
			__OSAL_TERM_LIT_FNCS_BEGIN(fnc, nm)
	#else
		#define __OSAL_TERM_LIT_FNCS(fnc, nm) \
			__OSAL_TERM_LIT_FNCS_BEGIN(fnc, nm) \
			void operator"" nm (const char8_t *str, std::size_t len) = delete;
	#endif

		__OSAL_TERM_LIT_FNCS(print, _p)
		__OSAL_TERM_LIT_FNCS(error, _e)
		__OSAL_TERM_LIT_FNCS(info, _i)
		__OSAL_TERM_LIT_FNCS(success, _s)
		__OSAL_TERM_LIT_FNCS(warning, _w)
	}
}

#include "__private/terminal.tpp"
