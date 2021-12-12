#pragma once

#include <ctl/version>
#include <ctl/cstddef>

namespace gal
{
	enum class shape_type : unsigned char
	{
		complex,
		non_convex,
		convex
	};

	struct point
	{
		ctl::ssize_t x;
		ctl::ssize_t y;
	};

	struct absolute_point
	{
		std::size_t x;
		std::size_t y;
	};

	struct segment
	{
		ctl::ssize_t x[2];
		ctl::ssize_t y[2];
	};

	struct rectangle
	{
		ctl::ssize_t x;
		ctl::ssize_t y;
		std::size_t width;
		std::size_t height;
	};

	struct absolute_rectangle
	{
		std::size_t x;
		std::size_t y;
		std::size_t width;
		std::size_t height;
	};

	struct arc
	{
		ctl::ssize_t x;
		ctl::ssize_t y;
		std::size_t width;
		std::size_t height;
		ctl::ssize_t angle[2];
	};

	struct dimension
	{
		std::size_t width;
		std::size_t height;
	};
}
