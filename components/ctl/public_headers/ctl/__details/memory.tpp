namespace ctl
{
	template <typename T, typename ...Args>
	T &unique_ptr_opaque::emplace(Args && ...args) noexcept
	{
		if(del_func && ptr) {
			del_func(ptr);
		}
		ptr = new T{std::forward<Args>(args)...};
		del_func = del_hlpr<T>;
		return *static_cast<T *>(ptr);
	}

	template <typename T>
	void unique_ptr_opaque::reset(T *new_ptr) noexcept
	{
		if(del_func && ptr) {
			del_func(ptr);
		}
		ptr = new_ptr;
		del_func = del_hlpr<T>;
	}
}
