#pragma once

#include <cpa/compiler_builtins.h>

#ifdef __CTL_ENABLE_COMMENTS
	#define __CTL_COMMENT(text) CPA_COMMENT(text)
#else
	#define __CTL_COMMENT(text)
#endif
