namespace osal
{
	template <typename T, std::size_t S, typename ...Args>
	auto &commandline::opt(Args && ...args) noexcept
	{
		auto *hlpr{new opt_helper<T, S, valued_named_opt>{std::forward<Args>(args)...}};
		handle_opt(hlpr);
		return *hlpr;
	}

	template <typename T, typename ...Args>
	auto &commandline::opt(Args && ...args) noexcept
	{
		auto *hlpr{new opt_helper<T, ~0u, valued_named_opt>{std::forward<Args>(args)...}};
		handle_opt(hlpr);
		return *hlpr;
	}

	template <typename ...Args>
	auto &commandline::opt(Args && ...args) noexcept
	{
		auto *hlpr{new opt_helper<void, 0, named_opt>{std::forward<Args>(args)...}};
		handle_opt(hlpr);
		return *hlpr;
	}

	template <typename T, std::size_t S>
	auto &commandline::opt() noexcept
	{
		auto *hlpr{new opt_helper<T, S, valued_opt>{}};
		handle_opt(hlpr);
		return *hlpr;
	}

	template <typename T>
	auto &commandline::opt() noexcept
	{
		auto *hlpr{new opt_helper<T, ~0u, valued_opt>{}};
		handle_opt(hlpr);
		return *hlpr;
	}

	template <typename T>
	auto &commandline::opt(std::size_t pos) noexcept
	{
		auto *hlpr{new opt_helper<T, 1, valued_opt>{}};
		handle_opt(hlpr, pos);
		return *hlpr;
	}
}
