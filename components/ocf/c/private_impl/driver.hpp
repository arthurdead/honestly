#pragma once

#include <cpa/compiler_builtins.hpp>
#include <ctl/variant>
#include <ctl/stack>
#include <ocf/object.hpp>
#include <ocf/frontend.hpp>

#include "location.hpp"

namespace ocf::__private
{
	class parser;

	class CPA_LOCAL_CLASS driver
	{
	public:
		void clear() noexcept;

		object *root;
		const frontend *usr_frnt;

	private:
		friend class parser;

		void error(const location &loc, const std::string &msg) noexcept;

		bool push(ctl::literal_variant &&name) noexcept;
		bool pop() noexcept;

		bool push_group(ctl::literal_variant &&name) noexcept;
		bool end_group() noexcept;

		bool push_namespace(ctl::literal_variant &&name) noexcept;
		bool end_namespace() noexcept;

		bool push_this() noexcept;
		bool push_this_group() noexcept;
		bool assign(ctl::literal_variant &&value) noexcept;

		bool array_value(ctl::literal_variant &&name) noexcept;
		bool array_value(ctl::literal_variant &&name, ctl::literal_variant &&value) noexcept;

		bool after_section(bool inl) noexcept;
		bool pre_section(bool inl) noexcept;
		bool end_section(bool inl) noexcept;
		bool section_end() noexcept;

		bool push_attributes() noexcept;

		bool init() noexcept;
		void push(object &child) noexcept;

		template <typename F>
		bool for_each_parent_1(F &&func) noexcept
		{
			if(__ctxs.empty()) {
				CPA_TRAP;
				return false;
			}
			std::vector<object *> &vec{__ctxs.top().__parents};
			if(vec.empty()) {
				CPA_TRAP;
				return false;
			}
			for(object *parent : vec) {
				if(!parent) {
					CPA_TRAP;
					return false;
				}
				if(!func(*parent)) {
					CPA_TRAP;
					return false;
				}
			}
			return true;
		}

		template <typename F>
		bool for_each_parent_2(F &&func) noexcept
		{
			if(__ctxs.empty()) {
				CPA_TRAP;
				return false;
			}
			std::vector<object *> &vec{__ctxs.top().__parents};
			if(vec.empty()) {
				CPA_TRAP;
				return false;
			}
			std::vector<object *> tmpvec;
			for(object *parent : vec) {
				if(!parent) {
					CPA_TRAP;
					return false;
				}
				if(!func(tmpvec, *parent)) {
					CPA_TRAP;
					return false;
				}
			}
			if(tmpvec.empty()) {
				CPA_TRAP;
				return false;
			}
			__ctxs.emplace(std::move(tmpvec));
			return true;
		}

		struct CPA_VISIBILITY_LOCAL parent_ctx final
		{
			parent_ctx() noexcept = default;
			inline parent_ctx(std::vector<object *> &&vec) noexcept
				: __parents{std::move(vec)} {}

		private:
			friend class driver;

			std::vector<object *> __parents;
			bool __issection;
			bool __isinlsection;
		};

		ctl::stack<parent_ctx> __ctxs;
		ctl::stack<parent_ctx *> __sections;
		std::vector<object *> __tmpgroupvec;
		std::size_t __nsdepth;
	};
}
