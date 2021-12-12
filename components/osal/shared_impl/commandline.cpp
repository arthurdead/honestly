#include <osal/commandline.hpp>

namespace osal
{
	commandline::base_opt::~base_opt() noexcept
	{
	}

	commandline::opt_name_impl::~opt_name_impl() noexcept
	{
	}

	commandline::opt_pos_impl::~opt_pos_impl() noexcept
	{
	}

	commandline::opt_val_impl::~opt_val_impl() noexcept
	{
	}

	commandline::valued_named_opt::~valued_named_opt() noexcept
	{
	}

#if CTL_TARGET_PLATFORM != CTL_PLATFORM_WEB
	std::string commandline::help_msg() const noexcept
	{
		std::filesystem::path path{this_process::path()};
		path = path.filename();
	#ifndef CTL_FILESYSTEM_PATH_WIDE
		return help_msg(path.native());
	#else
		return help_msg(ctl::to_string(path.native()));
	#endif
	}

	exit_codes commandline::parse() noexcept
	{
		const std::vector<std::string> argv{this_process::argv()};
		std::vector<std::string_view> argv_vec;
		argv_vec.insert(argv_vec.begin(), argv.data(), argv.data() + argv.size());
		return parse_impl(argv_vec.size(), argv_vec.data());
	}
#endif

	exit_codes commandline::parse(int argc, char *argv[]) noexcept
	{
		std::vector<std::string_view> argv_vec;
		argv_vec.insert(argv_vec.begin(), argv, argv + argc);
		return parse_impl(argv_vec.size(), argv_vec.data());
	}

	exit_codes commandline::parse(std::string_view argv) noexcept
	{
		std::vector<std::string_view> argv_vec{to_argv(argv)};
		return parse_impl(argv_vec.size(), argv_vec.data());
	}
}
