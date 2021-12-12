#include <ocf/object.hpp>
#include <ctl/charconv>

namespace ocf
{
	OCF_SHARED_API void OCF_SHARED_API_CALL object::clear() noexcept
	{
		__childs.clear();
		__condition.clear();
		__attributes.reset();
		__name.clear();
		__value.clear();
	}

	OCF_SHARED_API std::string OCF_SHARED_API_CALL object::to_string() const noexcept
	{
		std::string str;
		__to_string(str, 0, true);
		if(!str.empty()) {
			str.pop_back();
		}
		return str;
	}

	void object::__to_string(std::string &str, std::size_t depth, bool root) const noexcept
	{
		using namespace std::literals::string_view_literals;

		const std::size_t depth_spacing{depth * 2};

		static constexpr const auto process_str{[](std::string &tmpstr) noexcept -> void {
			std::string::iterator it{tmpstr.begin()};

			while(it != tmpstr.end()) {
				switch(*it) {
					case '\\': { tmpstr.erase(it); tmpstr.insert(it, {'\\','\\'}); it += 2; break; }
					case '\n': { tmpstr.erase(it); tmpstr.insert(it, {'\\','n'}); it += 2; break; }
					case '\t': { tmpstr.erase(it); tmpstr.insert(it, {'\\','t'}); it += 2; break; }
					case '\v': { tmpstr.erase(it); tmpstr.insert(it, {'\\','v'}); it += 2; break; }
					case '\f': { tmpstr.erase(it); tmpstr.insert(it, {'\\','f'}); it += 2; break; }
					case '\r': { tmpstr.erase(it); tmpstr.insert(it, {'\\','r'}); it += 2; break; }
					case '\a': { tmpstr.erase(it); tmpstr.insert(it, {'\\','a'}); it += 2; break; }
					case '\b': { tmpstr.erase(it); tmpstr.insert(it, {'\\','b'}); it += 2; break; }
					case '\"': { tmpstr.erase(it); tmpstr.insert(it, {'\\','"'}); it += 2; break; }
					case '\'': { tmpstr.erase(it); tmpstr.insert(it, {'\\','\''}); it += 2; break; }
					case '\?': { tmpstr.erase(it); tmpstr.insert(it, {'\\','?'}); it += 2; break; }
					default: { ++it; break; }
				}
			}
		}};

		bool was_empty{false};
		if(root && __name.empty()) {
			was_empty = true;
		} else {
			str.append(depth_spacing, ' ');
			std::string processed_name{static_cast<std::string>(__name)};
			process_str(processed_name);
			str += '"';
			str += std::move(processed_name);
			str += '"';
		}

		if(!__value.empty()) {
			if(was_empty) {
				str.append(depth_spacing, ' ');
				str += "this"sv;
				was_empty = false;
			}
			str += " = "sv;
			ctl::literal_variant::indexes validx{__value.index()};
			switch(validx) {
				case ctl::literal_variant::indexes::char_:
				{ str += '\''; break; }
			#ifdef __cpp_char8_t
				case ctl::literal_variant::indexes::char8_t_:
				{ str += "u8'"sv; break; }
			#endif
				case ctl::literal_variant::indexes::char16_t_:
				{ str += "u'"sv; break; }
				case ctl::literal_variant::indexes::char32_t_:
				{ str += "U'"sv; break; }
				case ctl::literal_variant::indexes::wchar_t_:
				{ str += "L'"sv; break; }
				case ctl::literal_variant::indexes::string:
				{ str += '"'; break; }
			#ifdef __cpp_char8_t
				case ctl::literal_variant::indexes::u8string:
				{ str += "u8\""sv; break; }
			#endif
				case ctl::literal_variant::indexes::u16string:
				{ str += "u\""sv; break; }
				case ctl::literal_variant::indexes::u32string:
				{ str += "U\""sv; break; }
				case ctl::literal_variant::indexes::wstring:
				{ str += "L\""sv; break; }
				default: { break; }
			}
			std::string tmp{static_cast<std::string>(__value)};
			switch(validx) {
				case ctl::literal_variant::indexes::float_:
				case ctl::literal_variant::indexes::double_:
				case ctl::literal_variant::indexes::long_double: {
					if(tmp.find('.') == std::string::npos) {
						tmp += '.';
					}
					break;
				}
				default: { break; }
			}
			process_str(tmp);
			str.append(std::move(tmp));
			switch(validx) {
				case ctl::literal_variant::indexes::char_:
			#ifdef __cpp_char8_t
				case ctl::literal_variant::indexes::char8_t_:
			#endif
				case ctl::literal_variant::indexes::char16_t_:
				case ctl::literal_variant::indexes::char32_t_:
				case ctl::literal_variant::indexes::wchar_t_:
				{ str += '\''; break; }
				case ctl::literal_variant::indexes::string:
			#ifdef __cpp_char8_t
				case ctl::literal_variant::indexes::u8string:
			#endif
				case ctl::literal_variant::indexes::u16string:
				case ctl::literal_variant::indexes::u32string:
				case ctl::literal_variant::indexes::wstring:
				{ str += '"'; break; }
				case ctl::literal_variant::indexes::float_:
				{ str += 'f'; break; }
				case ctl::literal_variant::indexes::long_double:
				case ctl::literal_variant::indexes::long_:
				{ str += 'l'; break; }
				case ctl::literal_variant::indexes::ssize_t_:
				{ str += 'z'; break; }
				case ctl::literal_variant::indexes::unsigned_int:
				{ str += 'u'; break; }
				case ctl::literal_variant::indexes::unsigned_long:
				{ str += "ul"sv; break; }
				case ctl::literal_variant::indexes::size_t_:
				{ str += "zu"sv; break; }
				case ctl::literal_variant::indexes::long_long:
				{ str += "ll"sv; break; }
				case ctl::literal_variant::indexes::unsigned_long_long:
				{ str += "ull"sv; break; }
				default: { break; }
			}
		}

		if(__attributes) {
			str += '\n';
			str.append(depth_spacing, ' ');
			str += "[[\n"sv;
			__attributes->__to_string(str, depth+1, true);
			str.append(depth_spacing, ' ');
			str += "]]"sv;
		}

		if(!was_empty) {
			str += '\n';
		}

		if(!__childs.empty()) {
			if(!was_empty) {
				str.append(depth_spacing, ' ');
				str += "{\n"sv;
			}

			if(!was_empty) {
				++depth;
			}

			for(const object &child : __childs) {
				child.__to_string(str, depth, false);
			}

			if(!was_empty) {
				str.append(depth_spacing, ' ');
				str += "}\n";
			}
		}
	}
}
