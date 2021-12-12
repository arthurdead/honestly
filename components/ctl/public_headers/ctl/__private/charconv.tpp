namespace ctl
{
	template <typename T>
	T to_integer(std::string_view str, int base) noexcept
	{
		T tmp{};
		__chrconv::from_chars(str, tmp, base);
		return tmp;
	}

	template <typename T>
	T to_integer(std::string_view str, std::error_code &ec, int base) noexcept
	{
		T tmp{};
		ec = std::make_error_code(__chrconv::from_chars(str, tmp, base));
		return tmp;
	}

#if CTL_LIBCPP != CTL_LIBCPP_LIBCPP
	template <typename T>
	T to_floating(std::string_view str, std::chars_format fmt) noexcept
	{
		T tmp{};
		__chrconv::from_chars(str, tmp, fmt);
		return tmp;
	}

	template <typename T>
	T to_floating(std::string_view str, std::error_code &ec, std::chars_format fmt) noexcept
	{
		T tmp{};
		ec = std::make_error_code(__chrconv::from_chars(str, tmp, fmt));
		return tmp;
	}
#else
	template <typename T>
	T to_floating(std::string_view str, [[maybe_unused]] std::chars_format fmt) noexcept
	{
		T tmp{};
		__chrconv::from_chars_flt_strto(str, tmp);
		return tmp;
	}

	template <typename T>
	T to_floating(std::string_view str, [[maybe_unused]] std::error_code &ec, [[maybe_unused]] std::chars_format fmt) noexcept
	{
		T tmp{};
		__chrconv::from_chars_flt_strto(str, tmp);
		return tmp;
	}
#endif
}
