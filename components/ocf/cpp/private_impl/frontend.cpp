#include <ocf/frontend.hpp>
#include <ocf/object.hpp>

CTL_CLANG_WARNING_PUSH
#if CTL_COMPILER & CTL_COMPILER_FLAG_ZAPCC
	CTL_CLANG_WARNING_DISABLE("-Wconversion")
#else
	CTL_CLANG_WARNING_DISABLE("-Wsuggest-destructor-override")
	CTL_CLANG_WARNING_DISABLE("-Wsuggest-override")
	CTL_CLANG_WARNING_DISABLE("-Wimplicit-int-conversion")
	CTL_CLANG_WARNING_DISABLE("-Wextra-semi-stmt")
#endif
CTL_CLANG_WARNING_DISABLE("-Wdocumentation-unknown-command")
CTL_CLANG_WARNING_DISABLE("-Wzero-as-null-pointer-constant")
CTL_CLANG_WARNING_DISABLE("-Wsign-conversion")
CTL_CLANG_WARNING_DISABLE("-Wnon-virtual-dtor")
CTL_CLANG_WARNING_DISABLE("-Wshadow-field-in-constructor")
CTL_CLANG_WARNING_DISABLE("-Wshadow-field")
CTL_CLANG_WARNING_DISABLE("-Wcomma")
CTL_CLANG_WARNING_DISABLE("-Wweak-vtables")
CTL_CLANG_WARNING_DISABLE("-Wold-style-cast")
CTL_CLANG_WARNING_DISABLE("-Wformat-pedantic")
CTL_CLANG_WARNING_DISABLE("-Wundef")
CTL_CLANG_WARNING_DISABLE("-Wdeprecated-declarations")
#pragma push_macro("stdin")
#undef stdin
#include "generated/ocf.reflex.hpp"
#include "generated/ocf.bison.hpp"
#pragma pop_macro("stdin")
CTL_CLANG_WARNING_POP

#include "driver.hpp"

namespace ocf
{
	namespace __private
	{
		class CTL_LOCAL_CLASS CTL_STATIC_LINKAGE fontend_impl final
		{
		public:
			fontend_impl() noexcept
				: __psr{__lxr, __drv} {}

			bool parse_str(object &obj, std::string_view str, const frontend &usr_frnt) noexcept
			{
				if(str.empty()) {
					CTL_DEBUGTRAP;
					return false;
				}
				using namespace std::literals::string_view_literals;
				reflex::Input input{str.data(), str.length()};
				__lxr.filename = "<<inline>>"sv;
				return __parse_input(obj, std::move(input), usr_frnt);
			}

			bool parse_file(object &obj, ctl::filesystem::path_view path, const frontend &usr_frnt) noexcept
			{
				if(path.empty()) {
					CTL_DEBUGTRAP;
					return false;
				}
			#if CTL_LIBC & CTL_LIBC_FLAG_POSIX
				#ifndef CTL_FILESYSTEM_PATH_WIDE
				FILE *fptr{fopen(path.c_str(), "r")};
				if(!fptr) {
					CTL_DEBUGTRAP;
					obj.clear();
					return false;
				}
				#else
					#error
				#endif
				reflex::Input input{fptr};
				__lxr.filename = path.native();
				bool ret{__parse_input(obj, std::move(input), usr_frnt)};
				fclose(fptr);
				return ret;
			#else
				#error
			#endif
			}

		private:
			bool __parse_input(object &obj, reflex::Input &&input, const frontend &usr_frnt) noexcept
			{
				__lxr.in(std::move(input));

				__drv.root = &obj;
				__drv.usr_frnt = &usr_frnt;

				int ret{__psr.parse()};
				if(ret != 0) {
					obj.clear();
				}

				__drv.clear();
				__lxr.filename.clear();

				return (ret == 0);
			}

			lexer __lxr;
			driver __drv;
			parser __psr;
		};

		CTL_GLOBAL_CTOR_BEGIN
		static fontend_impl frnt;
		CTL_GLOBAL_CTOR_END
	}

	OCF_SHARED_API bool OCF_SHARED_API_CALL frontend::parse(object &obj, std::string_view str) const noexcept
	{ return __private::frnt.parse_str(obj, str, *this); }

	OCF_SHARED_API bool OCF_SHARED_API_CALL frontend::parse(object &obj, ctl::filesystem::path_view path) const noexcept
	{ return __private::frnt.parse_file(obj, path, *this); }
}
