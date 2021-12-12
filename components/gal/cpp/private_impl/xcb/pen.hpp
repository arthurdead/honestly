#pragma once

#include <ctl/version>
#include <gal/window.hpp>
#include "../window.hpp"
#include "connection.hpp"

#include "xcb.hpp"

namespace gal::xcb
{
	class CTL_LOCAL_CLASS pen final : public __pen::impl
	{
	public:
		pen(connection &conn_, xcb_drawable_t draw_) noexcept;
		~pen() noexcept override final;

		#define __API_BRIDGE_DECLARATION
		#include "../__private/pen_funcs.priv.gen.hpp"

	private:
		connection *conn;
		xcb_gcontext_t id;
		xcb_drawable_t draw;
	};
}
