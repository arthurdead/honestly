#pragma once

#include <cpa/compiler_builtins.h>
#include <ctl/memory>
#include <ctl/variant>
#include <ctl/vector>
#include <ctl/optional>
#include <string>

#include "__private/api.h"

namespace ocf
{
	class CPA_VISIBILITY_LOCAL object
	{
		using child_vec_type = ctl::ptr_vector<object>;

	public:
		object() noexcept = default;

		inline object(ctl::literal_variant &&name) noexcept
			: name_{std::move(name)}
		{
		}
		template <typename T>
		inline object(T &&name) noexcept
			: name_{std::move(name)}
		{
		}

		inline object(ctl::literal_variant &&name, ctl::literal_variant &&value) noexcept
			: name_{std::move(name)}, value_{std::move(value)}
		{
		}
		template <typename N, typename V>
		inline object(N &&name, V &&value) noexcept
			: name_{std::move(name)}, value_{std::move(value)}
		{
		}

		template <typename T = std::string>
		inline T name() const noexcept
		{ return name_.convert<T>(); }
		inline ctl::literal_variant &name() noexcept
		{ return name_; }

		template <typename T = std::string>
		inline T value() const noexcept
		{ return value_.convert<T>(); }
		inline ctl::literal_variant &value() noexcept
		{ return value_; }

		OCF_SHARED_API std::string OCF_SHARED_API_CALL to_string() const noexcept;

		OCF_SHARED_API void OCF_SHARED_API_CALL clear() noexcept;

		ctl::optional_ref<object> attributes() noexcept;
		ctl::optional_cref<object> attributes() const noexcept;

		inline bool has_attributes() const noexcept
		{ return static_cast<bool>(attr); }

		template <typename ...Args>
		inline object &emplace_attributes(Args &&...args) noexcept
		{
			object &child{attr.emplace(std::forward<Args>(args)...)};
			child.parent_ = this;
			return child;
		}

		CTL_REMAP_VECTOR_ACCESSORS_NOSUBSCRIPT(child_vec_type, childs)

		reference operator[](size_type pos) = delete;
		const_reference operator[](size_type pos) const = delete;

		inline void clear_children() noexcept
		{ childs.clear(); }

		inline iterator erase(iterator pos)
		{ return childs.erase(pos); }
		inline iterator erase(iterator first, iterator last)
		{ return childs.erase(first, last); }

		inline iterator erase(const_iterator pos)
		{ return childs.erase(pos); }
		inline iterator erase(const_iterator first, const_iterator last)
		{ return childs.erase(first, last); }

		template <typename ...Args>
		inline object &emplace(Args &&...args) noexcept
		{
			object &child{childs.emplace_back(std::forward<Args>(args)...)};
			child.parent_ = this;
			return child;
		}

		inline object &operator[](ctl::literal_variant &&name)
		{ return find_or_emplace(std::move(name)); }
		inline ctl::optional_cref<object> operator[](const ctl::literal_variant &name) const
		{ return find(name); }
		template <typename T>
		inline object &operator[](T &&name)
		{ return find_or_emplace(ctl::literal_variant{std::move(name)}); }
		template <typename T>
		inline ctl::optional_cref<object> operator[](const T &name) const
		{ return find(ctl::literal_variant{name}); }

		ctl::optional_ref<object> find(const ctl::literal_variant &name) noexcept;
		ctl::optional_cref<object> find(const ctl::literal_variant &name) const noexcept;
		template <typename T>
		inline ctl::optional_ref<object> find(const T &name) noexcept
		{ return find(ctl::literal_variant{name}); }
		template <typename T>
		inline ctl::optional_cref<object> find(const T &name) const noexcept
		{ return find(ctl::literal_variant{name}); }

		object &find_or_emplace(ctl::literal_variant &&name) noexcept;
		template <typename T>
		inline object &find_or_emplace(T &&name) noexcept
		{ return find_or_emplace(ctl::literal_variant{std::move(name)}); }

	private:
		void to_string(std::string &str, std::size_t depth, bool root) const noexcept;

		ctl::literal_variant name_;
		ctl::literal_variant value_;
		std::string cond;
		ctl::unique_ptr<object> attr;
		child_vec_type childs;
		object *parent_;
	};

	inline object &object::find_or_emplace(ctl::literal_variant &&name) noexcept
	{
		if(ctl::optional_ref<object> child{find(name)}; child.has_value()) {
			return *child;
		} else {
			return emplace(std::move(name));
		}
	}

	inline ctl::optional_ref<object> object::find(const ctl::literal_variant &name) noexcept
	{
		iterator it{begin()};
		iterator end_{end()};
		while(it != end_) {
			if(it->name_ == name) {
				return ctl::make_optional_ref(*it);
			}
			++it;
		}
		return std::nullopt;
	}

	inline ctl::optional_cref<object> object::find(const ctl::literal_variant &name) const noexcept
	{
		const_iterator it{cbegin()};
		const_iterator end_{cend()};
		while(it != end_) {
			if(it->name_ == name) {
				return ctl::make_optional_cref(*it);
			}
			++it;
		}
		return std::nullopt;
	}

	inline ctl::optional_ref<object> object::attributes() noexcept
	{
		if(attr) {
			return ctl::make_optional_ref(*attr);
		} else {
			return std::nullopt;
		}
	}

	inline ctl::optional_cref<object> object::attributes() const noexcept
	{
		if(attr) {
			return ctl::make_optional_cref(*attr);
		} else {
			return std::nullopt;
		}
	}
}
