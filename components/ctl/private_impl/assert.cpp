#include <ctl/assert>
#include <cstdio>

namespace ctl::__details_assert
{
	CTL_SHARED_API fail CTL_SHARED_API_CALL impl(std::string_view nms, std::string msg, std::source_location loc) noexcept
	{
		std::fprintf(stderr,
			"%s:%s(%zu,%zu): %s\n",
			loc.file_name(), loc.function_name(), loc.line(), loc.column(),
			msg.c_str()
		);
		return fail::fatal;
	}
}
