class CTL_LOCAL_CLASS base_opt;

class CTL_LOCAL_CLASS CTL_NOVTABLE opt_val_impl
{
public:
	virtual ~opt_val_impl() noexcept;

protected:
	opt_val_impl() noexcept = default;
	opt_val_impl(opt_val_impl &&) noexcept = default;

	template <typename T>
	static CTL_STATIC_LINKAGE exit_codes parse_impl(std::string_view preamble, std::string_view str, std::decay_t<T> &value) noexcept
	{
		using namespace std::literals::string_view_literals;
		using decayed_t = std::decay_t<T>;
		if constexpr(std::is_integral_v<decayed_t>) {
			std::error_code ec;
			value = ctl::to_integer<decayed_t>(str, ec);
			if(ec) {
				this_terminal::error(preamble, "invalid integer value '"sv, str, "'\n"sv);
				return exit_codes::usage_error;
			}
		} else if constexpr(std::is_floating_point_v<decayed_t>) {
			std::error_code ec;
			value = ctl::to_floating<decayed_t>(str, ec);
			if(ec) {
				this_terminal::error(preamble, "invalid floating point value '"sv, str, "'\n"sv);
				return exit_codes::usage_error;
			}
		} else if constexpr(std::is_same_v<decayed_t, bool>) {
			if(str.empty() || str == "true"sv) {
				value = true;
			} else if(str == "false"sv) {
				value = false;
			} else {
				this_terminal::error(preamble, "invalid value for boolean '"sv, str, "'\n"sv);
				return exit_codes::usage_error;
			}
		} else if constexpr(std::is_same_v<decayed_t, std::string>) {
			value = str;
		} else if constexpr(std::is_same_v<decayed_t, std::filesystem::path>) {
			value = str;
			value = std::filesystem::weakly_canonical(value);
			if constexpr(std::is_const_v<T> || std::is_reference_v<T>) {
				if(!value.is_absolute()) {
					value = (std::filesystem::current_path() / value);
				}
			}
			if constexpr(std::is_reference_v<T>) {
				if(!std::filesystem::exists(value)) {
					this_terminal::error(preamble, "file does not exist ('"sv, value, "')\n"sv);
					return exit_codes::input_unavailable;
				}
			}
		} else {
			CTL_DEBUGTRAP;
			return exit_codes::resource_unavailable;
		}
		return exit_codes::success;
	}

private:
	friend class commandline;

	opt_val_impl(const opt_val_impl &) noexcept = delete;

	virtual std::size_t num_values() const noexcept = 0;
	virtual CTL_VIRTUAL_CONSTEXPR std::size_t max_values() const noexcept = 0;
	virtual CTL_VIRTUAL_CONSTEXPR base_opt *get_base() noexcept = 0;
	virtual exit_codes parse(std::string_view preamble, std::string_view arg) noexcept = 0;
};

class CTL_LOCAL_CLASS CTL_NOVTABLE opt_pos_impl
{
public:
	virtual ~opt_pos_impl() noexcept;

	inline operator bool() const noexcept
	{ return !pos.empty(); }
	inline bool operator!() const noexcept
	{ return pos.empty(); }
	inline bool present() const noexcept
	{ return !pos.empty(); }
	inline bool present(std::size_t i) const noexcept {
		return std::any_of(pos.cbegin(), pos.cend(), 
			[i](std::size_t c) noexcept -> bool {
				return (i == c);
		});
	}
	inline bool present_after(std::size_t i) const noexcept {
		return std::any_of(pos.cbegin(), pos.cend(), 
			[i](std::size_t c) noexcept -> bool {
				return (c > i);
		});
	}
	inline bool present_before(std::size_t i) const noexcept {
		return std::any_of(pos.cbegin(), pos.cend(), 
			[i](std::size_t c) noexcept -> bool {
				return (c < i);
		});
	}
	inline bool present_after(const opt_pos_impl &i) const noexcept
	{ return (present() && (i.present() && present_after(i.position()))); }
	inline bool present_before(const opt_pos_impl &i) const noexcept
	{ return (present() && (i.present() && present_before(i.position()))); }

	inline std::size_t position() const noexcept
	{ return pos.empty() ? ~0u : pos.back(); }
	inline const std::vector<std::size_t> &positions() const noexcept
	{ return pos; }

protected:
	opt_pos_impl() noexcept = default;
	opt_pos_impl(opt_pos_impl &&) noexcept = default;

private:
	friend class commandline;

	opt_pos_impl(const opt_pos_impl &) noexcept = delete;

	virtual CTL_VIRTUAL_CONSTEXPR base_opt *get_base() noexcept = 0;

	std::vector<std::size_t> pos;
};

class CTL_LOCAL_CLASS CTL_NOVTABLE opt_name_impl
{
public:
	virtual ~opt_name_impl() noexcept;

	template <typename ...Args>
	opt_name_impl(Args && ...args) noexcept
	{ (process_ctor_arg(std::forward<Args>(args)), ...); }

protected:
	opt_name_impl(opt_name_impl &&) noexcept = default;

private:
	friend class commandline;

	opt_name_impl() noexcept = delete;
	opt_name_impl(const opt_name_impl &) noexcept = delete;

	virtual CTL_VIRTUAL_CONSTEXPR base_opt *get_base() noexcept = 0;

	template <typename T>
	CTL_STATIC_LINKAGE void process_ctor_arg(T &&arg) noexcept
	{
		using decayed_t = std::decay_t<T>;
		if constexpr(std::is_same_v<decayed_t, std::string>) {
			longs.emplace_back(std::forward<T>(arg));
		} else if constexpr(std::is_same_v<decayed_t, std::string_view>) {
			longs.emplace_back(std::forward<T>(arg));
		} else if constexpr(std::is_same_v<decayed_t, char>) {
			shorts.emplace_back(std::forward<T>(arg));
		} else {
			CTL_DEBUGTRAP;
		}
	}

	std::vector<std::string> longs;
	std::vector<char> shorts;
};

class CTL_LOCAL_CLASS base_opt
{
public:
	virtual ~base_opt() noexcept;

protected:
	base_opt() noexcept = default;
	base_opt(base_opt &&) noexcept = default;

private:
	friend class commandline;

	virtual CTL_VIRTUAL_CONSTEXPR inline opt_val_impl *get_value() noexcept
	{ return nullptr; }
	virtual CTL_VIRTUAL_CONSTEXPR inline opt_name_impl *get_name() noexcept
	{ return nullptr; }
	virtual CTL_VIRTUAL_CONSTEXPR inline opt_pos_impl *get_pos() noexcept
	{ return nullptr; }

	base_opt(const base_opt &) noexcept = delete;
};

class CTL_LOCAL_CLASS named_opt : public base_opt, public opt_name_impl, public opt_pos_impl
{
public:
	using opt_name_impl::opt_name_impl;

private:
	CTL_VIRTUAL_CONSTEXPR inline opt_name_impl *get_name() noexcept override final
	{ return static_cast<opt_name_impl *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline base_opt *get_base() noexcept override final
	{ return static_cast<base_opt *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline opt_pos_impl *get_pos() noexcept override final
	{ return static_cast<opt_pos_impl *>(this); }
};

class CTL_LOCAL_CLASS valued_opt : public base_opt, public opt_val_impl, public opt_pos_impl
{
public:
	using opt_val_impl::opt_val_impl;

private:
	CTL_VIRTUAL_CONSTEXPR inline opt_val_impl *get_value() noexcept override final
	{ return static_cast<opt_val_impl *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline base_opt *get_base() noexcept override final
	{ return static_cast<base_opt *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline opt_pos_impl *get_pos() noexcept override final
	{ return static_cast<opt_pos_impl *>(this); }
};

class CTL_LOCAL_CLASS valued_named_opt : public base_opt, public opt_name_impl, public opt_val_impl, public opt_pos_impl
{
public:
	using opt_name_impl::opt_name_impl;

	~valued_named_opt() noexcept override;

private:
	CTL_VIRTUAL_CONSTEXPR inline opt_val_impl *get_value() noexcept override final
	{ return static_cast<opt_val_impl *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline opt_name_impl *get_name() noexcept override final
	{ return static_cast<opt_name_impl *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline base_opt *get_base() noexcept override final
	{ return static_cast<base_opt *>(this); }
	CTL_VIRTUAL_CONSTEXPR inline opt_pos_impl *get_pos() noexcept override final
	{ return static_cast<opt_pos_impl *>(this); }
};

template <typename T, std::size_t S, typename B>
class CTL_LOCAL_CLASS opt_helper final : public B
{
	using __base = B;
	using decayed_t = std::decay_t<T>;

	struct values_t final
	{
	private:
		friend class opt_helper;

		constexpr decayed_t &emplace_back(decayed_t &&val) noexcept
		{
			decayed_t &tmp{arr[idx++]};
			tmp = std::move(val);
			return tmp;
		}
		constexpr inline std::size_t size() const noexcept
		{ return idx; }
		constexpr inline bool empty() const noexcept
		{ return (idx == 0); }

		std::size_t idx{0};
		decayed_t arr[S];
	};

	static CTL_STATIC_LINKAGE exit_codes def_parse_impl(std::string_view preamble, std::string_view str, values_t &arr) noexcept
	{
		decayed_t tmp;
		if(exit_codes code{__base::template parse_impl<T>(preamble, str, tmp)}; code != exit_codes::success) {
			return code;
		}
		arr.emplace_back(std::move(tmp));
		return exit_codes::success;
	}

	using func_t = std::function<exit_codes(std::string_view, std::string_view, values_t &)>;

public:
	static inline exit_codes default_parse(std::string_view preamble, std::string_view str, values_t &arr) noexcept
	{ return def_parse_impl(preamble, str, arr); }

	using __base::__base;

	inline bool present() const noexcept
	{ return !values.empty(); }

private:
	friend class commandline;

	values_t values;
	func_t parse_func{def_parse_impl};

	inline std::size_t num_values() const noexcept override
	{ return values.size(); }
	CTL_VIRTUAL_CONSTEXPR inline std::size_t max_values() const noexcept override
	{ return S; }

	inline exit_codes parse(std::string_view preamble, std::string_view arg) noexcept override
	{ return parse_func(preamble, arg, values); }
};

template <typename T, typename B>
class CTL_LOCAL_CLASS opt_helper<T, ~0u, B> final : public B
{
	using __base = B;
	using decayed_t = std::decay_t<T>;
	using values_t = std::vector<decayed_t>;

	static CTL_STATIC_LINKAGE exit_codes def_parse_impl(std::string_view preamble, std::string_view str, values_t &vec) noexcept
	{
		decayed_t tmp;
		if(exit_codes code{__base::template parse_impl<T>(preamble, str, tmp)}; code != exit_codes::success) {
			return code;
		}
		vec.emplace_back(std::move(tmp));
		return exit_codes::success;
	}

	using func_t = std::function<exit_codes(std::string_view, std::string_view, values_t &)>;

public:
	static inline exit_codes default_parse(std::string_view preamble, std::string_view str, values_t &vec) noexcept
	{ return def_parse_impl(preamble, str, vec); }

	using __base::__base;

	CTL_REMAP_VECTOR_ACCESSORS(values_t, values)

	inline bool present() const noexcept
	{ return !values.empty(); }

private:
	friend class commandline;

	values_t values;
	func_t parse_func{def_parse_impl};

	inline std::size_t num_values() const noexcept override
	{ return values.size(); }
	CTL_VIRTUAL_CONSTEXPR inline std::size_t max_values() const noexcept override
	{ return ~0u; }

	inline exit_codes parse(std::string_view preamble, std::string_view arg) noexcept override
	{ return parse_func(preamble, arg, values); }
};

template <typename B>
class CTL_LOCAL_CLASS opt_helper<void, 0, B> : public B
{
	using __base = B;
	friend class commandline;

public:
	using __base::__base;
};

template <typename T, typename B>
class CTL_LOCAL_CLASS opt_helper<T, 1, B> : public B
{
	using __base = B;
	using decayed_t = std::decay_t<T>;

	static CTL_STATIC_LINKAGE inline exit_codes def_parse_impl(std::string_view preamble, std::string_view str, decayed_t &value) noexcept
	{ return __base::template parse_impl<T>(preamble, str, value); }

	using func_t = std::function<exit_codes(std::string_view, std::string_view, decayed_t &)>;

public:
	static inline exit_codes default_parse(std::string_view preamble, std::string_view str, decayed_t &value) noexcept
	{ return def_parse_impl(preamble, str, value); }

	using __base::__base;

	inline bool present() const noexcept
	{ return parsed; }

	inline bool operator==(const decayed_t &other) const noexcept
	{ return value == other; }
	inline bool operator!=(const decayed_t &other) const noexcept
	{ return value != other; }
	inline bool operator>=(const decayed_t &other) const noexcept
	{ return value >= other; }
	inline bool operator<=(const decayed_t &other) const noexcept
	{ return value <= other; }
	inline bool operator>(const decayed_t &other) const noexcept
	{ return value > other; }
	inline bool operator<(const decayed_t &other) const noexcept
	{ return value < other; }

	inline opt_helper &operator=(const decayed_t &other) noexcept
	{ value = other; return *this; }
	inline opt_helper &operator=(decayed_t &&other) noexcept
	{ value = std::move(other); return *this; }

	inline operator const decayed_t &() const noexcept
	{ return value; }
	inline operator decayed_t &() noexcept
	{ return value; }

private:
	friend class commandline;

	decayed_t value;
	func_t parse_func{def_parse_impl};
	bool parsed;

	inline std::size_t num_values() const noexcept override final
	{ return parsed ? 1 : 0; }
	CTL_VIRTUAL_CONSTEXPR inline std::size_t max_values() const noexcept override final
	{ return 1; }

	inline exit_codes parse(std::string_view preamble, std::string_view arg) noexcept override final
	{ parsed = true; return parse_func(preamble, arg, value); }
};

template <typename T, typename B>
class CTL_LOCAL_CLASS opt_helper<T, 0, B>;
template <std::size_t S, typename B>
class CTL_LOCAL_CLASS opt_helper<void, S, B>;
