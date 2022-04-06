namespace ctl
{
	template <typename T>
	T literal_variant::convert_impl() const noexcept
	{
		using decayed_t = std::decay_t<T>;

		const indexes curr_idx{index()};
	#ifdef __cpp_lib_constexpr_typeinfo
		constexpr indexes trgt_idx{type_to_index<decayed_t>()};
	#else
		const indexes trgt_idx{type_to_index<decayed_t>()};
	#endif

		#define __CTL_LITVAR_CVRT_HLPR(idx) \
			const auto &arg{std::get<static_cast<std::size_t>(idx)>(*static_cast<const base_type *>(this))}; \
			if(trgt_idx == curr_idx) { \
				return type_cast<decayed_t>(arg); \
			}

		#define __CTL_LITVAR_CVRT_ARITH_HLPR(idx) \
			__CTL_LITVAR_CVRT_HLPR(idx) \
			if constexpr(std::is_arithmetic_v<decayed_t>) { \
				return static_cast<decayed_t>(arg); \
			} else if constexpr(is_string_v<decayed_t>) { \
				if constexpr(std::is_same_v<decayed_t, std::string>) { \
					return to_string(arg); \
				} else { \
					std::string tmp1{to_string(arg)}; \
					decayed_t tmp2{to_string<decayed_t>(tmp1)}; \
					return tmp2; \
				} \
			}

		#define __CTL_LITVAR_CVRT_BOOL_HLPR_1 \
			__CTL_LITVAR_CVRT_HLPR(indexes::bool_) \
			if constexpr(std::is_arithmetic_v<decayed_t>) { \
				return static_cast<decayed_t>(arg); \
			} else if constexpr(is_string_v<decayed_t>) { \
				using namespace std::literals::string_view_literals; \
				if constexpr(std::is_same_v<decayed_t, std::string>) { \
					return decayed_t{arg ? "true"sv : "false"sv}; \
				}

		#define __CTL_LITVAR_CVRT_BOOL_HLPR_2 \
				else if constexpr(std::is_same_v<decayed_t, std::u16string>) { \
					return decayed_t{arg ? u"true"sv : u"false"sv}; \
				} else if constexpr(std::is_same_v<decayed_t, std::u32string>) { \
					return decayed_t{arg ? U"true"sv : U"false"sv}; \
				} else if constexpr(std::is_same_v<decayed_t, std::wstring>) { \
					return decayed_t{arg ? L"true"sv : L"false"sv}; \
				} \
			}

	#ifdef __cpp_char8_t
		#define __CTL_LITVAR_CVRT_BOOL_HLPR \
			__CTL_LITVAR_CVRT_BOOL_HLPR_1 \
			else if constexpr(std::is_same_v<decayed_t, std::u8string>) { \
				return decayed_t{arg ? u8"true"sv : u8"false"sv}; \
			} \
			__CTL_LITVAR_CVRT_BOOL_HLPR_2
	#else
		#define __CTL_LITVAR_CVRT_BOOL_HLPR \
			__CTL_LITVAR_CVRT_BOOL_HLPR_1 \
			__CTL_LITVAR_CVRT_BOOL_HLPR_2
	#endif

		#define __CTL_LITVAR_CVRT_STR_HLPR(idx) \
			__CTL_LITVAR_CVRT_HLPR(idx) \
			if constexpr(std::is_integral_v<decayed_t>) { \
				return to_integer<decayed_t>(arg); \
			} else if constexpr(std::is_floating_point_v<decayed_t>) { \
				return to_floating<decayed_t>(arg); \
			}

		#define __CTL_LITVAR_CVRT_USTR_HLPR(idx) \
			__CTL_LITVAR_CVRT_HLPR(idx) \
			if constexpr(std::is_integral_v<decayed_t>) { \
				std::string tmp{to_string(arg)}; \
				return to_integer<decayed_t>(tmp); \
			} else if constexpr(std::is_floating_point_v<decayed_t>) { \
				std::string tmp{to_string(arg)}; \
				return to_floating<decayed_t>(tmp); \
			}

		switch(curr_idx) {
			case indexes::bool_: { __CTL_LITVAR_CVRT_BOOL_HLPR } break;
			case indexes::int_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::int_) } break;
			case indexes::unsigned_int: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::unsigned_int) } break;
			case indexes::unsigned_long: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::unsigned_long) } break;
			case indexes::long_long: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::long_long) } break;
			case indexes::unsigned_long_long: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::unsigned_long_long) } break;
		#ifdef __cpp_size_t_suffix
			case indexes::ssize_t_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::ssize_t_) } break;
			case indexes::size_t_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::size_t_) } break;
		#endif
			case indexes::double_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::double_) } break;
			case indexes::long_double: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::long_double) } break;
			case indexes::float_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::float_) } break;
			case indexes::char_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::char_) } break;
		#ifdef __cpp_char8_t
			case indexes::char8_t_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::char8_t_) } break;
		#endif
			case indexes::char16_t_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::char16_t_) } break;
			case indexes::char32_t_: { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::char32_t_) } break;
			case indexes::wchar_t_:  { __CTL_LITVAR_CVRT_ARITH_HLPR(indexes::wchar_t_) } break;
			case indexes::string: { __CTL_LITVAR_CVRT_STR_HLPR(indexes::string) } break;
		#ifdef __cpp_char8_t
			case indexes::u8string: { __CTL_LITVAR_CVRT_USTR_HLPR(indexes::u8string) } break;
		#endif
			case indexes::u16string: { __CTL_LITVAR_CVRT_USTR_HLPR(indexes::u16string) } break;
			case indexes::u32string: { __CTL_LITVAR_CVRT_USTR_HLPR(indexes::u32string) } break;
			case indexes::wstring: { __CTL_LITVAR_CVRT_USTR_HLPR(indexes::wstring) } break;
		}

		CPA_TRAP;
		return decayed_t{};
	}
}
