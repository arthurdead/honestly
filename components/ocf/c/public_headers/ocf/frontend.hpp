#pragma once

#include <cpa/compiler_builtins.h>
#include <ctl/filesystem>
#include <functional>
#include <string_view>

//#include "object.hpp"

#include "__private/api.h"

namespace ocf
{
	class object;

	class CPA_VISIBILITY_LOCAL frontend
	{
	public:
		using print_func_t = std::function<void(std::string_view)>;

		template <typename F>
		inline void out_print(F &&func) noexcept
		{ out_print_ = std::move(args); }
		template <typename F>
		inline void err_print(F &&func) noexcept
		{ err_print_ = std::move(args); }

		OCF_SHARED_API bool OCF_SHARED_API_CALL parse(object &obj, std::string_view str) const noexcept;
		OCF_SHARED_API bool OCF_SHARED_API_CALL parse(object &obj, ctl::filesystem::path_view path) const noexcept;

	private:
		print_func_t out_print_;
		print_func_t err_print_;
	};
}
