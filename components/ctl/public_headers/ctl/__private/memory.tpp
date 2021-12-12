namespace ctl
{
	template <typename T, typename D>
	template <typename ...Args>
	typename unique_ptr<T, D>::reference unique_ptr<T, D>::emplace(Args && ...args)
	{
		__base::reset(new T{std::forward<Args>(args)...});
		return *__base::get();
	}

	template <typename T>
	unique_ptr_opaque::unique_ptr_opaque(T *ptr) noexcept
		: __ptr{ptr}, __deleter{[](void *tmp) noexcept -> void {
			delete static_cast<T *>(tmp);
		}}
	{}

	template <typename T, typename ...Args>
	T &unique_ptr_opaque::emplace(Args && ...args) noexcept
	{
		if(__deleter && __ptr) {
			__deleter(__ptr);
		}
		T *__tmp{new T{std::forward<Args>(args)...}};
		__deleter = [](void *ptr) noexcept -> void {
			delete static_cast<T *>(ptr);
		};
		__ptr = __tmp;
		return *__tmp;
	}

	template <typename T>
	void unique_ptr_opaque::reset(T *ptr) noexcept
	{
		if(__deleter && __ptr) {
			__deleter(__ptr);
		}
		__deleter = [](void *tmp) noexcept -> void {
			delete static_cast<T *>(tmp);
		};
		__ptr = ptr;
	}
}
