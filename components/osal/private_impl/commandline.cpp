#include <osal/commandline.hpp>
#include <osal/terminal.hpp>

namespace osal
{
	OSAL_SHARED_API exit_codes OSAL_SHARED_API_CALL commandline::parse_impl(std::size_t argc, std::string_view argv[]) noexcept
	{
		if(!cached) {
			for(opt_name_impl *impl : named_opts_cache.impls) {
				for(char shrt : impl->shorts) {
					named_opts_cache.shorts[shrt] = impl;
				}
				for(const std::string &long_ : impl->longs) {
					named_opts_cache.longs[static_cast<std::string_view>(long_)] = impl;
				}
			}
			nameless_max_values = (nameless_opt ? nameless_opt->max_values() : 0);
			cached = true;
		}

		std::string_view program{argv[0]};

		std::size_t strpos{program.length()+1};

		for(std::size_t i{1}; i < argc; ++i) {
			std::string_view arg{argv[i]};
			if(arg.empty()) {
				continue;
			}

			strpos += (arg.length()+1);

			using namespace std::literals::string_view_literals;

			static auto preamble{[program,&i,&strpos]() noexcept -> std::string {
				std::string preamble_str{program};
				preamble_str += ':';
				preamble_str += ctl::to_string(strpos);
				preamble_str += '#';
				preamble_str += ctl::to_string(i);
				preamble_str += ": "sv;
				return preamble_str;
			}};

			if(positional_cache_t::iterator it{positional_opts_cache.find(i)}; it != positional_opts_cache.end()) {
				if(exit_codes code{it->second->parse(preamble(), arg)}; code != exit_codes::success) {
					return code;
				}
				continue;
			}

			using namespace osal::this_terminal;

			static auto get_value_1{[&i,argc](std::string_view &name, std::string_view &value) noexcept -> bool {
				std::size_t validx{name.find('=')};
				if(validx == 0) {
					error(preamble(), "invalid position for =\n"sv);
					return false;
				} else if(validx != std::string_view::npos) {
					if((validx == (name.length()-1)) && (i == (argc-1))) {
						error(preamble(), "invalid position for =\n"sv);
						return false;
					}
					value = name.substr(validx+1);
					name = name.substr(0, validx);
				}
				return true;
			}};

			static auto get_value_2_opt{[&i,&strpos,argv,argc](auto name, std::string_view &value) noexcept -> bool {
				if(value.empty()) {
					if(i == argc-1) {
						error(preamble(), "option "sv, name, " needs a value\n"sv);
						return false;
					} else {
						++i;
						value = argv[i];
						strpos += value.length()+1;
						if(std::size_t validx{value.find('=')}; validx != std::string_view::npos) {
							value = value.substr(validx+1);
							strpos += validx;
							if(value.empty()) {
								if(i == argc-1) {
									error(preamble(), "option "sv, name, " needs a value\n"sv);
									return false;
								} else {
									++i;
									value = argv[i];
									strpos += value.length()+1;
									if(value.empty()) {
										error(preamble(), "option "sv, name, " needs a value\n"sv);
										return false;
									}
								}
							}
						}
					}
				}
				return true;
			}};

			static auto get_value_2_flag{[&i,&strpos,argv,argc](std::string_view &value) noexcept -> bool {
				if(value.empty()) {
					if(i == argc-1) {
						return false;
					} else {
						++i;
						value = argv[i];
						strpos += value.length()+1;
						if(std::size_t validx{value.find('=')}; validx != std::string_view::npos) {
							value = value.substr(validx+1);
							strpos += validx;
							if(value.empty()) {
								if(i == argc-1) {
									return false;
								} else {
									++i;
									value = argv[i];
									strpos += value.length()+1;
									if(value.empty()) {
										return false;
									}
								}
							}
						}
					}
				}
				return true;
			}};

			static auto handlevalue_opt{[](opt_val_impl *val, auto name, std::string_view value_str, std::size_t maxvalues) noexcept -> exit_codes {
				if(!value_str.empty()) {
					if(!val || maxvalues == 0) {
						error(preamble(), "option "sv, name, " does not take any values\n"sv);
						return exit_codes::usage_error;
					}
					std::size_t comma{value_str.find(',')};
					if(comma == 0) {
						error(preamble(), "option "sv, name, " invalid positon for ,\n"sv);
						return exit_codes::usage_error;
					} else if(comma != std::string_view::npos) {
						if(value_str[comma-1] == '\\') {
							comma = std::string_view::npos;
						}
					}
					std::size_t numvalues{val->num_values()};
					if(comma == std::string_view::npos) {
						if(numvalues == maxvalues) {
							error(preamble(), "option "sv, name, " only takes "sv, maxvalues, " values but "sv, numvalues+1, " were provided\n"sv);
							return exit_codes::usage_error;
						}
						if(exit_codes code{val->parse(preamble(), value_str)}; code != exit_codes::success) {
							return code;
						}
					} else {
						if(maxvalues == 1) {
							error(preamble(), "option "sv, name, " only takes 1 value\n"sv);
							return exit_codes::usage_error;
						}
						do {
							std::string_view actual_value{value_str.substr(0, comma)};
							if(exit_codes code{val->parse(preamble(), actual_value)}; code != exit_codes::success) {
								return code;
							} else {
								if(numvalues = val->num_values(); numvalues == maxvalues) {
									error(preamble(), "option "sv, name, " only takes "sv, maxvalues, " values but "sv, numvalues+1, " were provided\n"sv);
									return exit_codes::usage_error;
								}
							}
							value_str = value_str.substr(comma+1);
							comma = value_str.find(',');
							if(comma == value_str.length()-1) {
								error(preamble(), "option "sv, name, " invalid comma position\n"sv);
								return exit_codes::usage_error;
							}
						} while(comma != std::string_view::npos);
						if(numvalues == maxvalues) {
							error(preamble(), "option "sv, name, " only takes "sv, maxvalues, " values but "sv, numvalues+1, " were provided\n"sv);
							return exit_codes::usage_error;
						} else if(exit_codes code{val->parse(preamble(), value_str)}; code != exit_codes::success) {
							return code;
						}
					}
				} else {
					if(maxvalues > 0) {
						error(preamble(), "option "sv, name, " needs a value\n"sv);
						return exit_codes::usage_error;
					}
				}
				return exit_codes::success;
			}};

			static auto handlevalue_flag{[](std::vector<std::string> &val, std::string_view value_str) noexcept -> exit_codes {
				if(!value_str.empty()) {
					std::size_t comma{value_str.find(',')};
					if(comma == 0) {
						error(preamble(), "invalid positon for ,\n"sv);
						return exit_codes::usage_error;
					} else {
						if(value_str[comma-1] == '\\') {
							comma = std::string_view::npos;
						}
					}
					if(comma == std::string_view::npos) {
						val.emplace_back() = value_str;
					} else {
						do {
							std::string_view actual_value{value_str.substr(0, comma)};
							val.emplace_back() = actual_value;
							value_str = value_str.substr(comma+1);
							comma = value_str.find(',');
							if(comma == value_str.length()-1) {
								error(preamble(), "invalid comma position\n"sv);
								return exit_codes::usage_error;
							}
						} while(comma != std::string_view::npos);
						val.emplace_back() = value_str;
					}
				}
				return exit_codes::success;
			}};

			if(arg[0] == '-') {
				if(arg.length() > 2) {
					if(arg[1] == '-') {
						std::string_view name_str{arg.substr(2)};
						std::string_view value;
						if(!get_value_1(name_str, value)) {
							return exit_codes::usage_error;
						}
						named_cache_t::long_t::iterator it{named_opts_cache.longs.find(name_str)};
						if(it == named_opts_cache.longs.end()) {
							error(preamble(), "unknown long option: "sv, name_str, '\n');
							return exit_codes::usage_error;
						}
						opt_name_impl *name{it->second};
						base_opt *opt{name->get_base()};
						opt_val_impl *val{opt->get_value()};
						opt_pos_impl *pos{opt->get_pos()};
						if(pos) {
							pos->pos.emplace_back(i);
						}
						const std::size_t maxvalues{val ? val->max_values() : 0};
						if(maxvalues > 0) {
							if(!get_value_2_opt(name_str, value)) {
								return exit_codes::usage_error;
							}
						}
						if(exit_codes code{handlevalue_opt(val, name_str, value, maxvalues)}; code != exit_codes::success) {
							return code;
						}
						continue;
					}
				}

				std::string_view names{arg.substr(1)};
				std::string_view value;
				if(!get_value_1(names, value)) {
					return exit_codes::usage_error;
				}
				opt_val_impl *val{nullptr};
				std::size_t maxvalues{0};
				char c{'\0'};
				for(std::size_t j{0}, len{names.length()}; j < len; ++j) {
					c = names[j];
					named_cache_t::short_t::iterator it{named_opts_cache.shorts.find(c)};
					if(it == named_opts_cache.shorts.end()) {
						error(preamble(), "unknown short option: "sv, c, '\n');
						return exit_codes::usage_error;
					}
					opt_name_impl *name{it->second};
					base_opt *opt{name->get_base()};
					opt_pos_impl *pos{opt->get_pos()};
					if(pos) {
						pos->pos.emplace_back(i);
					}
					val = opt->get_value();
					maxvalues = (val ? val->max_values() : 0);
					if(maxvalues > 0) {
						break;
					}
				}
				if(maxvalues > 0) {
					if(!get_value_2_opt(c, value)) {
						return exit_codes::usage_error;
					}
				}
				if(exit_codes code{handlevalue_opt(val, c, value, maxvalues)}; code != exit_codes::success) {
					return code;
				}
			} else if(arg[0] == '+') {
				if(!flags_enabled) {
					error(preamble(), "this program does not accept flags\n"sv);
					return exit_codes::usage_error;
				} else {
					std::string_view names{arg.substr(1)};
					std::string_view value;
					if(!get_value_1(names, value)) {
						return exit_codes::usage_error;
					}

					get_value_2_flag(value);

					OSAL_COMMENT("TODO!!! overload std::unordered_map<std::string, ....>::find so it accepts string_view")

					flags_type::iterator it{flags_.find(std::string{names})};
					if(it == flags_.end()) {
						flag_t flag;
						flag.first = names;
						it = flags_.emplace(std::move(flag)).first;
					}

					std::vector<std::string> &vec{it->second};

					if(exit_codes code{handlevalue_flag(vec, value)}; code != exit_codes::success) {
						return code;
					}
				}
			} else if(arg[0] == '@') {
				error(preamble(), "file reading is not supported yet\n"sv);
				return exit_codes::resource_unavailable;
			} else if(arg[0] == '=') {
				error(preamble(), "invalid position for =\n"sv);
				return exit_codes::usage_error;
			} else {
				if(!nameless_opt) {
					error(preamble(), "nameless options are not accepted by this program\n"sv);
					return exit_codes::usage_error;
				} else {
					if(const std::size_t numvalues{nameless_opt->num_values()}; numvalues == nameless_max_values) {
						if(nameless_max_values == 1) {
							error(preamble(), "nameless option only takes 1 value\n"sv);
						} else {
							error(preamble(), "nameless option only takes "sv, nameless_max_values, " values but "sv, numvalues+1, " were provided\n"sv);
						}
						return exit_codes::usage_error;
					}
					if(exit_codes code{nameless_opt->parse(preamble(), arg)}; code != exit_codes::success) {
						return code;
					}
					nameless_opt->pos.emplace_back(i);
				}
			}
		}

		return exit_codes::success;
	}

	OSAL_SHARED_API std::string OSAL_SHARED_API_CALL commandline::help_msg(std::string_view program) const noexcept
	{
		using namespace std::literals::string_view_literals;
		std::string tmp{"Usage: "sv};
		tmp += program;
		tmp += " [options] "sv;
		if(nameless_max_values > 0) {
			tmp += "argument "sv;
			if(nameless_max_values > 1) {
				tmp += "s... "sv;
			}
		}
		tmp += '\n';
		if(flags_enabled) {
			tmp += "[flags]\n"sv;
		}
		tmp += "Options:\n"sv;
		for(const ctl::unique_ptr<base_opt> &opt_ptr : opts) {
			base_opt &opt{opt_ptr.ref()};
			opt_name_impl *name{opt.get_name()};
			if(!name) {
				continue;
			}
			tmp += "  "sv;
			for(char shrt : name->shorts) {
				tmp += "-"sv;
				tmp += shrt;
				tmp += ", "sv;
			}
			for(const std::string &lng : name->longs) {
				tmp += "--"sv;
				tmp += lng;
				tmp += ", "sv;
			}
			tmp.erase(tmp.end()-2, tmp.end()-1);
			opt_val_impl *val{opt.get_value()};
			if(val) {
				const std::size_t max{val->max_values()};
				if(max > 0) {
					tmp += "= value"sv;
					if(max > 1) {
						tmp += "s..."sv;
					}
				}
			}
			tmp += '\n';
		}
		if(flags_enabled) {
			tmp += "Flags:\n"sv;
		} else {
			tmp.pop_back();
		}
		return tmp;
	}

	OSAL_SHARED_API std::vector<std::string_view> OSAL_SHARED_API_CALL commandline::to_argv(std::string_view) noexcept
	{
		OSAL_COMMENT("TODO!!!")

		std::vector<std::string_view> tmp;
		return tmp;
	}
}
