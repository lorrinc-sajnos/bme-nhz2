#include <iostream>
#include <fstream>

#include "game_setting.h"

using namespace std;

int GameSettings::createShader() {
	//Fajlbol beolvasás
	ifstream filestrm;
	filestrm.open(fragFile);

	if (!filestrm.is_open()) {
		cout << "HIBA! NEM LETEZIK A FAJL!";
		return -1;
	}

	filestrm.seekg(0, std::ios::end);
	std::streamsize size = filestrm.tellg();
	filestrm.seekg(0, std::ios::beg);

	char* temp = new char[size + 1];
	filestrm.read(temp, size);
	temp[size] = '\0';

	fragmentShader = (const char*)temp;

	filestrm.close();
	return 0;
}

GameSettings::~GameSettings() {
	delete[] tiles;
	delete[] fragmentShader;
}


