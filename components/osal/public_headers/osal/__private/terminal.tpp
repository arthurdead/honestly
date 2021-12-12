namespace osal
{
	#define __OSAL_TERM_BASE_PRNT(spc) \
		std::string str; \
		(spc process_arg(str, std::forward<Args>(args)), ...); \
		if(!str.empty()) { \
			spc print_impl(str); \
		}

	#define __OSAL_TERM_BASE_CLR(spc, clr) \
		std::string str; \
		(spc process_arg(str, std::forward<Args>(args)), ...); \
		if(!str.empty()) { \
			__term::bits_t bits; \
			bits. clr (); \
			spc handle_bits(bits); \
			spc print_impl(str); \
			bits = terminal::reset_effects_; \
			spc handle_bits(bits); \
		}

	#define __OSAL_TERM_BASE_PRNT_1(spc) \
		std::string str; \
		spc process_arg(str, arg); \
		if(!str.empty()) { \
			spc print_impl(str); \
		}

	#define __OSAL_TERM_TERM_PRNT \
		__OSAL_TERM_BASE_PRNT(CTL_NOTHING)

	#define __OSAL_TERM_TERM_CLR(clr) \
		__OSAL_TERM_BASE_CLR(CTL_NOTHING, clr)

	#define __OSAL_TERM_THISTERM_PRNT \
		__OSAL_TERM_BASE_PRNT(::osal::this_terminal::__private::)

	#define __OSAL_TERM_THISTERM_CLR(clr) \
		__OSAL_TERM_BASE_CLR(::osal::this_terminal::__private::, clr)

	template <typename T>
	terminal &terminal::operator<<(const T &arg) noexcept
	{ __OSAL_TERM_BASE_PRNT_1(CTL_NOTHING) return *this; }

	template <typename ...Args>
	void terminal::operator()(Args && ...args) noexcept
	{ __OSAL_TERM_TERM_PRNT }

	template <typename ...Args>
	void terminal::print(Args && ...args) noexcept
	{ __OSAL_TERM_TERM_PRNT }

	template <typename ...Args>
	void terminal::error(Args && ...args) noexcept
	{ __OSAL_TERM_TERM_CLR(error) }

	template <typename ...Args>
	void terminal::warning(Args && ...args) noexcept
	{ __OSAL_TERM_TERM_CLR(warning) }

	template <typename ...Args>
	void terminal::info(Args && ...args) noexcept
	{ __OSAL_TERM_TERM_CLR(info) }

	template <typename ...Args>
	void terminal::success(Args && ...args) noexcept
	{ __OSAL_TERM_TERM_CLR(success) }

	namespace this_terminal
	{
		template <typename ...Args>
		void print(Args && ...args) noexcept
		{ __OSAL_TERM_THISTERM_PRNT }

		template <typename ...Args>
		void error(Args && ...args) noexcept
		{ __OSAL_TERM_THISTERM_CLR(error) }

		template <typename ...Args>
		void warning(Args && ...args) noexcept
		{ __OSAL_TERM_THISTERM_CLR(warning) }

		template <typename ...Args>
		void info(Args && ...args) noexcept
		{ __OSAL_TERM_THISTERM_CLR(info) }

		template <typename ...Args>
		void success(Args && ...args) noexcept
		{ __OSAL_TERM_THISTERM_CLR(success) }
	}

	namespace __private
	{
		template <typename ...Args>
		void tout::operator()(Args && ...args) noexcept
		{ __OSAL_TERM_THISTERM_PRNT }

		template <typename T>
		tout &tout::operator<<(const T &arg) noexcept
		{ __OSAL_TERM_BASE_PRNT_1(::osal::this_terminal::__private::) return *this; }
	}
}
