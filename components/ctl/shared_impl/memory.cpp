#include <ctl/memory>

namespace ctl
{
	unique_ptr_opaque::~unique_ptr_opaque() noexcept
	{
		if(__deleter && __ptr) {
			__deleter(__ptr);
		}
	}

	void unique_ptr_opaque::reset(std::nullptr_t) noexcept
	{
		if(__deleter && __ptr) {
			__deleter(__ptr);
		}
		__deleter = nullptr;
		__ptr = nullptr;
	}
}
