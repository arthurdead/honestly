#pragma once

#include <ctl/version>
#include <ctl/memory>
#include <ctl/variant>
#include <ctl/vector>
#include <ctl/optional>
#include <ctl/string>

#include "__private/api.hpp"

namespace ocf
{
	class CTL_VISIBILITY_LOCAL object
	{
		using __childvec = ctl::ptr_vector<object>;

	public:
		object() noexcept = default;

		inline object(ctl::literal_variant &&name) noexcept
			: __name{std::move(name)} {}
		template <typename T>
		inline object(T &&name) noexcept
			: __name{std::move(name)} {}

		inline object(ctl::literal_variant &&name, ctl::literal_variant &&value) noexcept
			: __name{std::move(name)}, __value{std::move(value)} {}
		template <typename N, typename V>
		inline object(N &&name, V &&value) noexcept
			: __name{std::move(name)}, __value{std::move(value)} {}

		template <typename T = std::string>
		inline T name() const noexcept
		{ return __name.convert<T>(); }
		inline ctl::literal_variant &name() noexcept
		{ return __name; }

		template <typename T = std::string>
		inline T value() const noexcept
		{ return __value.convert<T>(); }
		inline ctl::literal_variant &value() noexcept
		{ return __value; }

		OCF_SHARED_API std::string OCF_SHARED_API_CALL to_string() const noexcept;

		OCF_SHARED_API void OCF_SHARED_API_CALL clear() noexcept;

		ctl::optional_ref<object> attributes() noexcept;
		ctl::optional_cref<object> attributes() const noexcept;

		inline bool has_attributes() const noexcept
		{ return static_cast<bool>(__attributes); }

		template <typename ...Args>
		inline object &emplace_attributes(Args && ...args) noexcept {
			object &child{__attributes.emplace(std::forward<Args>(args)...)};
			child.__parent = this;
			return child;
		}

		CTL_REMAP_VECTOR_ACCESSORS_NOSUBSCRIPT(__childvec, __childs)

		reference operator[](size_type pos) = delete;
		const_reference operator[](size_type pos) const = delete;

		inline void clear_children() noexcept
		{ __childs.clear(); }

		inline iterator erase(iterator pos)
		{ return __childs.erase(pos); }
		inline iterator erase(iterator first, iterator last)
		{ return __childs.erase(first, last); }

		inline iterator erase(const_iterator pos)
		{ return __childs.erase(pos); }
		inline iterator erase(const_iterator first, const_iterator last)
		{ return __childs.erase(first, last); }

		template <typename ...Args>
		inline object &emplace(Args && ...args) noexcept {
			object &child{__childs.emplace_back(std::forward<Args>(args)...)};
			child.__parent = this;
			return child;
		}

		inline object &operator[](ctl::literal_variant &&name)
		{ return find_or_emplace(std::move(name)); }
		inline ctl::optional_cref<object> operator[](const ctl::literal_variant &name) const
		{ return find(name); }
		template <typename T>
		inline object &operator[](T &&name) {
			ctl::literal_variant tmp{std::move(name)};
			return find_or_emplace(std::move(tmp));
		}
		template <typename T>
		inline ctl::optional_cref<object> operator[](const T &name) const {
			ctl::literal_variant tmp{name};
			return find(tmp);
		}

		ctl::optional_ref<object> find(const ctl::literal_variant &name) noexcept;
		ctl::optional_cref<object> find(const ctl::literal_variant &name) const noexcept;
		template <typename T>
		inline ctl::optional_ref<object> find(const T &name) noexcept {
			ctl::literal_variant tmp{name};
			return find(tmp);
		}
		template <typename T>
		inline ctl::optional_cref<object> find(const T &name) const noexcept {
			ctl::literal_variant tmp{name};
			return find(tmp);
		}

		object &find_or_emplace(ctl::literal_variant &&name) noexcept;
		template <typename T>
		inline object &find_or_emplace(T &&name) noexcept {
			ctl::literal_variant tmp{std::move(name)};
			return find_or_emplace(std::move(tmp));
		}

	private:
		void __to_string(std::string &str, std::size_t depth, bool root) const noexcept;

		ctl::literal_variant __name;
		ctl::literal_variant __value;
		std::string __condition;
		ctl::unique_ptr<object> __attributes;
		__childvec __childs;
		object *__parent;
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
			if(it->__name == name) {
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
			if(it->__name == name) {
				return ctl::make_optional_cref(*it);
			}
			++it;
		}
		return std::nullopt;
	}

	inline ctl::optional_ref<object> object::attributes() noexcept
	{
		if(__attributes) {
			return ctl::make_optional_ref(*__attributes);
		} else {
			return std::nullopt;
		}
	}

	inline ctl::optional_cref<object> object::attributes() const noexcept
	{
		if(__attributes) {
			return ctl::make_optional_cref(*__attributes);
		} else {
			return std::nullopt;
		}
	}
}
