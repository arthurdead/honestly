#include <ctl/memory>

namespace ctl
{
	void unique_ptr_opaque::reset(std::nullptr_t) noexcept
	{
		if(del_func && ptr) {
			del_func(ptr);
		}
		del_func = nullptr;
		ptr = nullptr;
	}
}
