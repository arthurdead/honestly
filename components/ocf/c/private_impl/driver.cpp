#include "driver.hpp"
#include <osal/terminal.hpp>

namespace ocf::__private
{
	void driver::clear() noexcept
	{
		__ctxs.clear();
		__sections.clear();
		__tmpgroupvec.clear();
		root = nullptr;
		__nsdepth = 0;
		usr_frnt = nullptr;
	}

	bool driver::push(ctl::literal_variant &&name) noexcept
	{
		return for_each_parent_2([&name](std::vector<object *> &vec, object &parent) noexcept -> bool {
			ctl::literal_variant tmpname{name};
			object &child{parent.find_or_emplace(std::move(tmpname))};
			vec.emplace_back(&child);
			return true;
		});
	}

	bool driver::push_namespace(ctl::literal_variant &&name) noexcept
	{
		if(!push(std::move(name))) {
			CPA_TRAP;
			return false;
		}
		++__nsdepth;
		return true;
	}

	bool driver::end_namespace() noexcept
	{
		parent_ctx cpy{__ctxs.top()};
		while(--__nsdepth) {
			__ctxs.pop();
		}
		parent_ctx &ctx{__ctxs.top()};
		ctx = std::move(cpy);
		return true;
	}

	bool driver::pre_section(bool inl) noexcept
	{
		if(!inl) {
			if(__ctxs.empty()) {
				CPA_TRAP;
				return false;
			}
			parent_ctx &ctx{__ctxs.top()};
			if(ctx.__issection) {
				__ctxs.pop();
			}
		}
		return true;
	}

	bool driver::after_section(bool inl) noexcept
	{
		if(__ctxs.empty()) {
			CPA_TRAP;
			return false;
		}
		parent_ctx &ctx{__ctxs.top()};
		ctx.__issection = true;
		ctx.__isinlsection = inl;
		if(!inl) {
			__sections.emplace(&ctx);
		}
		return true;
	}

	bool driver::end_section(bool inl) noexcept
	{
		if(!inl) {
			if(__sections.empty()) {
				CPA_TRAP;
				return false;
			}
			parent_ctx *target_ctx{__sections.top()};
			while(true) {
				if(__ctxs.empty()) {
					CPA_TRAP;
					return false;
				}
				parent_ctx &ctx{__ctxs.top()};
				if(&ctx == target_ctx) {
					break;
				} else {
					__ctxs.pop();
				}
			}
			__sections.pop();
			__ctxs.pop();
		} else {
			if(__ctxs.empty()) {
				CPA_TRAP;
				return false;
			}
			parent_ctx &ctx{__ctxs.top()};
			if(!ctx.__issection) {
				CPA_TRAP;
				return false;
			}
			__ctxs.pop();
		}
		return true;
	}

	bool driver::section_end() noexcept
	{
		parent_ctx &ctx{__ctxs.top()};
		if(ctx.__issection) {
			__ctxs.pop();
		}
		return true;
	}

	bool driver::push_attributes() noexcept
	{
		return for_each_parent_2([](std::vector<object *> &vec, object &parent) noexcept -> bool {
			object &attributes{parent.emplace_attributes()};
			vec.emplace_back(&attributes);
			return true;
		});
	}

	bool driver::pop() noexcept
	{
		if(__ctxs.empty()) {
			CPA_TRAP;
			return false;
		}
		__ctxs.pop();
		return true;
	}

	bool driver::push_this() noexcept
	{
		return for_each_parent_2([](std::vector<object *> &vec, object &parent) noexcept -> bool {
			vec.emplace_back(&parent);
			return true;
		});
	}

	bool driver::assign(ctl::literal_variant &&value) noexcept
	{
		return for_each_parent_1([&value](object &parent) noexcept -> bool {
			ctl::literal_variant tmpvalue{value};
			parent.value() = std::move(tmpvalue);
			return true;
		});
	}

	bool driver::array_value(ctl::literal_variant &&name) noexcept
	{
		return for_each_parent_1([&name](object &parent) noexcept -> bool {
			ctl::literal_variant tmpname{name};
			parent.emplace(std::move(tmpname));
			return true;
		});
	}

	bool driver::array_value(ctl::literal_variant &&name, ctl::literal_variant &&value) noexcept
	{
		return for_each_parent_1([&name, &value](object &parent) noexcept -> bool {
			ctl::literal_variant tmpname{name};
			ctl::literal_variant tmpvalue{value};
			parent.emplace(std::move(tmpname), std::move(tmpvalue));
			return true;
		});
	}

	bool driver::push_group(ctl::literal_variant &&name) noexcept
	{
		return for_each_parent_1([&name, this](object &parent) noexcept -> bool {
			ctl::literal_variant tmpname{name};
			object &child{parent.find_or_emplace(std::move(tmpname))};
			__tmpgroupvec.emplace_back(&child);
			return true;
		});
	}

	bool driver::push_this_group() noexcept
	{
		return for_each_parent_1([this](object &parent) noexcept -> bool {
			__tmpgroupvec.emplace_back(&parent);
			return true;
		});
	}

	bool driver::end_group() noexcept
	{
		__ctxs.emplace(std::move(__tmpgroupvec));
		return true;
	}

	bool driver::init() noexcept
	{
		if(!root) {
			CPA_TRAP;
			return false;
		}
		push(*root);
		return true;
	}

	void driver::push(object &child) noexcept
	{
		std::vector<object *> tmpvec;
		tmpvec.emplace_back(&child);
		__ctxs.emplace(std::move(tmpvec));
	}

	void driver::error(const location &loc, const std::string &msg) noexcept
	{
		using namespace std::literals::string_view_literals;

		std::string str;
		str += *loc.begin.filename;
		str += ':';
		str += ctl::to_string(loc.begin.line);
		str += ':';
		str += ctl::to_string(loc.begin.column);
		if(loc.end.filename == loc.begin.filename &&
			loc.end.line == loc.begin.line &&
			loc.end.column == loc.begin.column) {

		} else if(loc.end.filename == loc.begin.filename &&
					loc.end.line == loc.begin.line &&
					loc.end.column != loc.begin.column) {
			str += '-';
			str += ctl::to_string(loc.end.column);
		} else {
			CPA_TRAP;
		}
		str += ": "sv;
		str += msg;
		str += '\n';

		const frontend::print_func_t &err_print{usr_frnt->err_print()};
		if(err_print) {
			err_print(str);
		} else {
			osal::this_terminal::error(str);
		}
	}
}
