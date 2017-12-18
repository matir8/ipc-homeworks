#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

#include "gen.h"
#include <stdint.h>

struct cyclic_buf
{
	volatile uint64_t pos;
	volatile uint64_t array[512][GEN_BLOCK_SIZE];
};

#endif
