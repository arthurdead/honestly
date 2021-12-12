#pragma once

#include <ctl/version>
#include <ctl/memory>
#include <ctl/optional>
#include <cstddef>

#include <gal/__private/api.hpp>
#include <gal/window.hpp>
#include "renderer.hpp"
#include "gal.hpp"

namespace gal
{
	namespace __rndr
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl;
	}

	namespace __pen
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl
		{
		public:
			virtual ~impl() noexcept;

			impl() noexcept = default;
			impl(impl &&) noexcept = default;
			impl &operator=(impl &&) noexcept = default;

			#define __API_BRIDGE_INTERFACE
			#include "__private/pen_funcs.priv.gen.hpp"

		private:
			impl(const impl &) = delete;
			impl &operator=(const impl &) = delete;
		};
	}

	namespace __win
	{
		class CTL_LOCAL_CLASS CTL_NOVTABLE impl
		{
		public:
			virtual ~impl() noexcept;

			impl() noexcept = default;
			impl(impl &&) noexcept = default;
			impl &operator=(impl &&) noexcept = default;

			inline void create_renderer() noexcept
			{ rndr.reset(__private::create_rndr_impl(*this)); }

			virtual __pen::impl *create_pen() noexcept = 0;

		private:
			impl(const impl &) = delete;
			impl &operator=(const impl &) = delete;

		protected:
			ctl::unique_ptr<__rndr::impl> rndr;
		};

		using create_impl_t = impl *(*)(ctl::optional_ref<window>, std::size_t, std::size_t, std::size_t, std::size_t);
	}
}
