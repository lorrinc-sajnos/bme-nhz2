#pragma once
#ifndef HAS_GRAPHICS_H
#define HAS_GRAPHICS_H

//Cportán automatikusan kikapcsolja a grafikus módot.
#if  defined(CPORTA)
#define HAS_GRAPHICS 0
#else

//A grafikus módért állítsa 1-re!
#define HAS_GRAPHICS 1

#endif
#endif
