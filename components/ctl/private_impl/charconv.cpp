#include <ctl/charconv>
#include <ctl/utility>
#include <cstring>

namespace ctl
{
	template <>
	CTL_SHARED_API std::wstring CTL_SHARED_API_CALL to_string<std::wstring>(std::string_view value) noexcept
	{
		std::wstring tmp;
		std::mbstate_t state{};
		const char *cstr{value.data()};
		const std::size_t len{std::mbsrtowcs(nullptr, &cstr, 0, &state)+1};
		tmp.resize(len);
		std::mbsrtowcs(tmp.data(), &cstr, len, &state);
		return tmp;
	}

	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_string(std::wstring_view value) noexcept
	{
		std::string tmp;
		std::mbstate_t state{};
		const wchar_t *wstr{value.data()};
		const std::size_t len{std::wcsrtombs(nullptr, &wstr, 0, &state)+1};
		tmp.resize(len);
		std::wcsrtombs(tmp.data(), &wstr, len, &state);
		return tmp;
	}

#ifdef __cpp_char8_t
	template <>
	CTL_SHARED_API std::u8string CTL_SHARED_API_CALL to_string<std::u8string>(std::string_view value) noexcept
	{ return std::u8string{type_cast<std::u8string_view>(value)}; }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_string(std::u8string_view value) noexcept
	{ return std::string{type_cast<std::string_view>(value)}; }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_char(std::u8string_view value) noexcept
	{ return std::string{type_cast<std::string_view>(value)}; }
	CTL_SHARED_API std::u8string CTL_SHARED_API_CALL to_u8char(std::string_view value) noexcept
	{ return std::u8string{type_cast<std::u8string_view>(value)}; }
#endif

#if CTL_LIBCPP == CTL_LIBCPP_LIBCPP
	#if __CTL_WCHAR_WIDTH == 32
	template <>
	CTL_SHARED_API char32_t CTL_SHARED_API_CALL to_char<char32_t>(std::string_view value) noexcept
	{ return static_cast<char32_t>(to_char<wchar_t>(value)); }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_char(char32_t value) noexcept
	{ return to_char(static_cast<wchar_t>(value)); }
	template <>
	CTL_SHARED_API std::u32string CTL_SHARED_API_CALL to_string<std::u32string>(std::string_view value) noexcept
	{ return type_cast<std::u32string>(to_string<std::wstring>(value)); }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_string(std::u32string_view value) noexcept
	{ return to_string(type_cast<std::wstring_view>(value)); }

	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_char([[maybe_unused]] char16_t value) noexcept
	{ CTL_DEBUGTRAP; return std::string{}; }
	template <>
	CTL_SHARED_API std::u16string CTL_SHARED_API_CALL to_string<std::u16string>([[maybe_unused]] std::string_view value) noexcept
	{ CTL_DEBUGTRAP; return std::u16string{}; }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_string([[maybe_unused]] std::u16string_view value) noexcept
	{ CTL_DEBUGTRAP; return std::string{}; }
	template <>
	CTL_SHARED_API char16_t CTL_SHARED_API_CALL to_char<char16_t>([[maybe_unused]] std::string_view value) noexcept
	{ CTL_DEBUGTRAP; return char16_t{}; }
	#elif __CTL_WCHAR_WIDTH == 16
	template <>
	CTL_SHARED_API char16_t CTL_SHARED_API_CALL to_char<char16_t>(std::string_view value) noexcept
	{ return static_cast<char16_t>(to_char<wchar_t>(value)); }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_char(char16_t value) noexcept
	{ return to_char(static_cast<wchar_t>(value)); }
	template <>
	CTL_SHARED_API std::u16string CTL_SHARED_API_CALL to_string<std::u16string>(std::string_view value) noexcept
	{ return type_cast<std::u16string>(to_string<std::wstring>(value)); }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_string(std::u16string_view value) noexcept
	{ return to_string(type_cast<std::wstring_view>(value)); }

	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_char([[maybe_unused]] char32_t value) noexcept
	{ CTL_DEBUGTRAP; return std::string{}; }
	template <>
	CTL_SHARED_API std::u32string CTL_SHARED_API_CALL to_string<std::u32string>([[maybe_unused]] std::string_view value) noexcept
	{ CTL_DEBUGTRAP; return std::u32string{}; }
	CTL_SHARED_API std::string CTL_SHARED_API_CALL to_string([[maybe_unused]] std::u32string_view value) noexcept
	{ CTL_DEBUGTRAP; return std::string{}; }
	template <>
	CTL_SHARED_API char32_t CTL_SHARED_API_CALL to_char<char32_t>([[maybe_unused]] std::string_view value) noexcept
	{ CTL_DEBUGTRAP; return char32_t{}; }
	#else
		#error
	#endif
#endif
}
