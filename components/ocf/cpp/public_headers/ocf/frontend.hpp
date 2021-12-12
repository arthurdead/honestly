#pragma once

#include <ctl/version>
#include <ctl/filesystem>
#include <ctl/functional>
#include <ctl/string_view>

//#include "object.hpp"

#include "__private/api.hpp"

namespace ocf
{
	class object;

	class CTL_VISIBILITY_LOCAL frontend
	{
	public:
		using print_func_t = std::function<void(std::string_view)>;
		inline const print_func_t &out_print() const noexcept
		{ return out_prnt_; }
		inline const print_func_t &err_print() const noexcept
		{ return err_prnt_; }

		template <typename F>
		inline frontend &out_print(F &&args) noexcept
		{ out_prnt_ = std::move(args); return *this; }
		template <typename F>
		inline frontend &err_print(F &&args) noexcept
		{ err_prnt_ = std::move(args); return *this; }

		OCF_SHARED_API bool OCF_SHARED_API_CALL parse(object &obj, std::string_view str) const noexcept;
		OCF_SHARED_API bool OCF_SHARED_API_CALL parse(object &obj, ctl::filesystem::path_view path) const noexcept;

	private:
		print_func_t out_prnt_;
		print_func_t err_prnt_;
	};
}
