#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include "util.hpp"
#include "memory_test.h"

struct GameSettings {
	unsigned int width;
	unsigned int height;


	int tileCount;
	BYTE* tiles;
	char* fragFile;
	const char* fragmentShader;

	int createShader();

	~GameSettings();
};
#endif