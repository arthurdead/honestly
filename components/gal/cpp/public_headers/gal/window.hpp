#pragma once

#include <ctl/version>
#include <ctl/memory>
#include <ctl/functional>
#include <initializer_list>

#include "gal.hpp"
#include "geometry.hpp"

#include "__private/api.hpp"

namespace gal
{
	class CTL_LOCAL_CLASS window;

	class CTL_LOCAL_CLASS pen
	{
	public:
		pen(pen &&) noexcept = default;
		pen &operator=(pen &&) noexcept = default;

		GAL_SHARED_API GAL_SHARED_API_CALL pen(window &win) noexcept;

		#include "__private/pen_funcs.pub.gen.hpp"

	private:
		pen() = delete;
		pen(const pen &) = delete;
		pen &operator=(const pen &) = delete;

	__GAL_PRIVATE:
		ctl::unique_ptr_opaque impl;
	};

	class CTL_LOCAL_CLASS window
	{
	public:
		window(window &&) noexcept = default;
		window &operator=(window &&) noexcept = default;

		GAL_SHARED_API GAL_SHARED_API_CALL window(std::size_t x, std::size_t y, std::size_t w, std::size_t h) noexcept;
		inline window(std::size_t w, std::size_t h) noexcept
			: window{~0u, ~0u, w, h}
		{
		}
		inline window() noexcept
			: window{~0u, ~0u, ~0u, ~0u}
		{
		}
		virtual ~window() noexcept;

		std::function<void()> on_close;
		std::function<void()> draw;

	private:
		window(const window &) = delete;
		window &operator=(const window &) = delete;

	__GAL_PRIVATE:
		ctl::unique_ptr_opaque impl;
	};
}
