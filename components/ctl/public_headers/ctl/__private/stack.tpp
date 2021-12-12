namespace ctl
{
	template <typename T, typename C>
	void stack<T, C>::clear() noexcept
	{
		while(!__base::empty()) {
			__base::pop();
		}
	}
}
