#pragma once
#ifndef HAS_GRAPHICS_H
#define HAS_GRAPHICS_H

//Cport�n automatikusan kikapcsolja a grafikus m�dot.
#if  defined(CPORTA)
#define HAS_GRAPHICS 0
#else

//A grafikus m�d�rt �ll�tsa 1-re!
#define HAS_GRAPHICS 1

#endif
#endif
