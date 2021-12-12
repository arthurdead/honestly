#pragma once

#if CTL_LIBC == CTL_LIBC_MUSL
	#ifndef __CTYPE_ALREADY_DEFINED
		#if !defined __BYTE_ORDER__ || !defined __ORDER_BIG_ENDIAN__
			#error
		#endif

		#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			#define __CTL_CTYPE_BIT(bit) (1 << (bit))
		#else
			#define __CTL_CTYPE_BIT(bit) ((bit) < 8 ? ((1 << (bit)) << 8) : ((1 << (bit)) >> 8))
		#endif

enum
{
	_ISupper = __CTL_CTYPE_BIT(0),
	_ISlower = __CTL_CTYPE_BIT(1),
	_ISalpha = __CTL_CTYPE_BIT(2),
	_ISdigit = __CTL_CTYPE_BIT(3),
	_ISxdigit = __CTL_CTYPE_BIT(4),
	_ISspace = __CTL_CTYPE_BIT(5),
	_ISprint = __CTL_CTYPE_BIT(6),
	_ISgraph = __CTL_CTYPE_BIT(7),
	_ISblank = __CTL_CTYPE_BIT(8),
	_IScntrl = __CTL_CTYPE_BIT(9),
	_ISpunct = __CTL_CTYPE_BIT(10),
	_ISalnum = __CTL_CTYPE_BIT(11)
};

		#define __CTYPE_ALREADY_DEFINED
	#endif
#endif
