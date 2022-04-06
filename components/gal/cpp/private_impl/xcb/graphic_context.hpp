#pragma once

#include <ctl/version>
#include <gal/window.hpp>
#include "../window.hpp"
#include "connection.hpp"

#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS graphic_context final : public __pen::impl
	{
	public:
		graphic_context(graphic_context &&) noexcept = default;
		graphic_context &operator=(graphic_context &&) noexcept = default;

		graphic_context(connection &conn_, xcb_drawable_t draw_, GAL_XCB_PARAMS(xcb_create_gc_value_list_t) params = {}) noexcept;
		inline ~graphic_context() noexcept override final
		{ GAL_XCB_CHECKED_FUNCTION(*conn, xcb_free_gc, id); }

		#define __API_BRIDGE_DECLARATION
		#include "../__private/pen_funcs.priv.gen.hpp"

	private:
		graphic_context() = delete;
		graphic_context(const graphic_context &) = delete;
		graphic_context &operator=(const graphic_context &) = delete;

		connection *conn;
		xcb_gcontext_t id;
		xcb_drawable_t draw;
	};
}
