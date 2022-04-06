#pragma once

#include <cpa/compiler_builtins.h>

#ifdef __STDI_ENABLE_COMMENTS
	#define __STDI_COMMENT(text) CPA_COMMENT(text)
#else
	#define __STDI_COMMENT(text)
#endif
