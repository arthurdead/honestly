#pragma once

#include <ctl/version>
#include <ctl/functional>
#include <ctl/vector>
#include <ctl/memory>
#include <ctl/type_traits>
#include <ctl/charconv>
#include <ctl/filesystem>
#include <ctl/string_view>
#include <ctl/string>
#include <algorithm>
#include <unordered_map>
#include "terminal.hpp"
#include "process.hpp"
#include "exit_codes.hpp"

#include "__private/api.hpp"

namespace osal
{
	class CTL_LOCAL_CLASS commandline
	{
		#include "__private/cmdline_opts.hpp"

		template <typename T>
		CTL_STATIC_LINKAGE void handle_opt(T *opt, std::size_t pos = ~0u) noexcept
		{
			opts.emplace_back().reset(static_cast<base_opt *>(opt));

			using base = typename T::__base;
			if constexpr(std::is_same_v<base, valued_named_opt> ||
							std::is_same_v<base, named_opt>) {
				named_opts_cache.impls.emplace_back(static_cast<opt_name_impl *>(opt));
			} else if constexpr(std::is_same_v<base, valued_opt>) {
				if(pos == ~0u) {
					nameless_opt = static_cast<valued_opt *>(opt);
				} else {
					positional_opts_cache[pos] = static_cast<valued_opt *>(opt);
				}
			} else {
				CTL_DEBUGTRAP;
			}
		}

	public:
		static OSAL_SHARED_API std::vector<std::string_view> OSAL_SHARED_API_CALL to_argv(std::string_view str) noexcept;
		static OSAL_SHARED_API std::vector<char *> OSAL_SHARED_API_CALL to_argv_cstr(std::string_view str) noexcept;
		static OSAL_SHARED_API std::string OSAL_SHARED_API_CALL from_argv(const std::vector<std::string_view> &argv) noexcept;
		static OSAL_SHARED_API std::string OSAL_SHARED_API_CALL from_argv(const std::vector<std::string> &argv) noexcept;
		static OSAL_SHARED_API std::string OSAL_SHARED_API_CALL from_argv(const std::vector<char *> &argv) noexcept;

		exit_codes parse(int argc, char *argv[]) noexcept;
		exit_codes parse(std::string_view argv) noexcept;
	#if CTL_TARGET_PLATFORM != CTL_PLATFORM_WEB
		exit_codes parse() noexcept;
	#endif

		template <typename T, std::size_t S, typename ...Args>
		auto &opt(Args && ...args) noexcept;
		template <typename T, typename ...Args>
		auto &opt(Args && ...args) noexcept;
		template <typename ...Args>
		auto &opt(Args && ...args) noexcept;
		template <typename T, std::size_t S>
		auto &opt() noexcept;
		template <typename T>
		auto &opt() noexcept;
		template <typename T>
		auto &opt(std::size_t pos) noexcept;

		OSAL_SHARED_API std::string OSAL_SHARED_API_CALL help_msg(std::string_view program) const noexcept;

	#if CTL_TARGET_PLATFORM != CTL_PLATFORM_WEB
		std::string help_msg() const noexcept;
	#endif

		inline void enable_flags() noexcept
		{ flags_enabled = true; }

		using flags_type = std::unordered_map<std::string, std::vector<std::string>>;
		inline const flags_type &flags() const noexcept
		{ return flags_; }

	private:
		OSAL_SHARED_API exit_codes OSAL_SHARED_API_CALL parse_impl(std::size_t argc, std::string_view argv[]) noexcept;

		std::vector<ctl::unique_ptr<base_opt>> opts;

		using flag_t = std::pair<std::string, std::vector<std::string>>;
		flags_type flags_;
		bool flags_enabled{false};

		bool cached{false};

		struct named_cache_t final
		{
			std::vector<opt_name_impl *> impls;

			using long_t = std::unordered_map<std::string_view, opt_name_impl *>;
			long_t longs;
			using short_t = std::unordered_map<char, opt_name_impl *>;
			short_t shorts;
		};
		named_cache_t named_opts_cache;

		using positional_cache_t = std::unordered_map<std::size_t, valued_opt *>;
		positional_cache_t positional_opts_cache;

		valued_opt *nameless_opt{nullptr};
		std::size_t nameless_max_values;
	};
}

#include "__private/commandline.tpp"
