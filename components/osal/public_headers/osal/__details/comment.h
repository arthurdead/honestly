#pragma once

#include <cpa/compiler_builtins.h>

#ifdef __OSAL_ENABLE_COMMENTS
	#define __OSAL_COMMENT(text) CPA_COMMENT(text)
#else
	#define __OSAL_COMMENT(text)
#endif
