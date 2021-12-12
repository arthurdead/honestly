#include <osal/process.hpp>

namespace osal
{
	process::process(std::initializer_list<std::string_view> argv) noexcept
	{
		std::vector<char *> argv_vec;
		for(std::string_view view : argv) {
			argv_vec.emplace_back(const_cast<char *>(view.data()));
		}
		if(argv_vec.back()) {
			argv_vec.emplace_back(nullptr);
		}
		spawn(argv_vec.data());
	}
}
