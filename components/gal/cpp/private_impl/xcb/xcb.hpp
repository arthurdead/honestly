#pragma once

#include <ctl/version>

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/randr.h>
#include <xcb/render.h>
#include <xcb/xcb_renderutil.h>
#if CTL_DEBUG_LEVEL > 0
	#include <xcb/xcb_errors.h>
#endif
