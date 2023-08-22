#ifndef MEMORY_TEST_LORINC_H
#define MEMORY_TEST_LORINC_H

#include "has_graphics.h"
#if HAS_GRAPHICS==1

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW
#endif

#ifdef _DEBUG
#define new DBG_NEW
#endif


#endif
#endif
