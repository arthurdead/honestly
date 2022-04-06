namespace ctl
{
	template <typename T, typename C>
	void stack<T, C>::clear() noexcept
	{
		while(!base_type::empty()) {
			base_type::pop();
		}
	}
}
