#include <ocf/frontend.hpp>
#include <ocf/object.hpp>

CPA_CLANG_WARNING_PUSH
#if CPA_COMPILER & CPA_COMPILER_FLAG_ZAPCC
	CPA_CLANG_WARNING_DISABLE("-Wconversion")
#else
	CPA_CLANG_WARNING_DISABLE("-Wsuggest-destructor-override")
	CPA_CLANG_WARNING_DISABLE("-Wsuggest-override")
	CPA_CLANG_WARNING_DISABLE("-Wimplicit-int-conversion")
	CPA_CLANG_WARNING_DISABLE("-Wextra-semi-stmt")
#endif
CPA_CLANG_WARNING_DISABLE("-Wdocumentation-unknown-command")
CPA_CLANG_WARNING_DISABLE("-Wzero-as-null-pointer-constant")
CPA_CLANG_WARNING_DISABLE("-Wsign-conversion")
CPA_CLANG_WARNING_DISABLE("-Wnon-virtual-dtor")
CPA_CLANG_WARNING_DISABLE("-Wshadow-field-in-constructor")
CPA_CLANG_WARNING_DISABLE("-Wshadow-field")
CPA_CLANG_WARNING_DISABLE("-Wcomma")
CPA_CLANG_WARNING_DISABLE("-Wweak-vtables")
CPA_CLANG_WARNING_DISABLE("-Wold-style-cast")
CPA_CLANG_WARNING_DISABLE("-Wformat-pedantic")
CPA_CLANG_WARNING_DISABLE("-Wundef")
CPA_CLANG_WARNING_DISABLE("-Wdeprecated-declarations")
#include "reflex.gen.hpp"
#include "bison.gen.hpp"
CPA_CLANG_WARNING_POP

#include "driver.hpp"

namespace ocf
{
	namespace __private
	{
		class CPA_LOCAL_CLASS CPA_STATIC_LINKAGE fontend_impl final
		{
		public:
			fontend_impl() noexcept
				: __psr{__lxr, __drv} {}

			bool parse_str(object &obj, std::string_view str, const frontend &usr_frnt) noexcept
			{
				if(str.empty()) {
					CPA_TRAP;
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
					CPA_TRAP;
					return false;
				}
			#if CPA_TARGET_KERNEL == CPA_KERNEL_WINDOWS
				#error
			#else
				#ifndef STDI_FILESYSTEM_PATH_WIDE
				FILE *fptr{fopen(path.c_str(), "r")};
				if(!fptr) {
					CPA_TRAP;
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

		CPA_GLOBAL_CTOR_BEGIN
		static fontend_impl frnt;
		CPA_GLOBAL_CTOR_END
	}

	OCF_SHARED_API bool OCF_SHARED_API_CALL frontend::parse(object &obj, std::string_view str) const noexcept
	{ return __private::frnt.parse_str(obj, str, *this); }

	OCF_SHARED_API bool OCF_SHARED_API_CALL frontend::parse(object &obj, ctl::filesystem::path_view path) const noexcept
	{ return __private::frnt.parse_file(obj, path, *this); }
}
