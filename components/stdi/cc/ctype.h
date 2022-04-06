#pragma once

#include <cpa/compilers.h>

#ifndef __STDI_CTYPE_H
	#include "features.h"

	#if STDI_C_STDLIB == STDI_STDLIB_MUSL
		#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			#define __STDI_IS_BIT(bit) (1 << (bit))
		#else
			#define __STDI_IS_BIT(bit) ((bit) < 8 ? ((1 << (bit)) << 8) : ((1 << (bit)) >> 8))
		#endif

enum
{
	_ISupper  = __STDI_IS_BIT(0),
	_ISlower  = __STDI_IS_BIT(1),
	_ISalpha  = __STDI_IS_BIT(2),
	_ISdigit  = __STDI_IS_BIT(3),
	_ISxdigit = __STDI_IS_BIT(4),
	_ISspace  = __STDI_IS_BIT(5),
	_ISprint  = __STDI_IS_BIT(6),
	_ISgraph  = __STDI_IS_BIT(7),
	_ISblank  = __STDI_IS_BIT(8),
	_IScntrl  = __STDI_IS_BIT(9),
	_ISpunct  = __STDI_IS_BIT(10),
	_ISalnum  = __STDI_IS_BIT(11)
};
	#endif
#define __STDI_CTYPE_H
#endif

#define __STDI_INCLUDE_NEXT_HEADER <ctype.h>
#include "__details/include_next.h"
