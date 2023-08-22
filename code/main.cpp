#include "has_graphics.h"
#if HAS_GRAPHICS == 1
//-----------------------------------------------------
//#include "memory_test.h"


#include <iostream>
#include <string>
#include "weightedlist.hpp"
#include "hash.h"
#include "biome_noise.hpp"
#include "game_setting.h"
#include "opengl_obj.h"

#include "biome.hpp"




using namespace std;

int get_seed_from_console();
BYTE* flatten_2d(int** pp, int size);
int** create_intP(int size);
void free_intP(int** p_p, int size);
void fillBiomes(WeightedList<Biome*>& biomes, long seed, int map_size);


int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtMemState start, fin, dif;
	_CrtMemCheckpoint(&start);

	int seed = get_seed_from_console();

	int map_size = 256;

	WeightedList<Biome*> biomes(32);

	fillBiomes(biomes, seed, map_size);

	BiomeNoise biomeNoise((long)seed, 16.0f, 256.0f, 8.0f, 6.0f);

	int** tiles = create_intP(map_size);

	//int* leak = new int[100];

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			int biomeRand = biomeNoise.getNoise(i, j);
			//biomeRand = i + j*1000000;
			Biome* pntr = biomes.get_rand(biomeRand);
			tiles[i][j] = pntr->get_tile(i, j, seed);
		}
	}

	GameSettings settings;

	settings.width = 800; settings.height = 600;
	settings.tileCount = map_size;
	settings.tiles = flatten_2d(tiles, map_size);


	settings.fragFile = (char*)"shader.frag";

	OpenGLObj game(&settings);

	try {
		game.run_gui();
	}
	catch (char* err) {
		std::cout << "\ERR: \n";
		std::cout << err;
	}

	/* Zárás*/

	free_intP(tiles, map_size);
	biomes.freeMem();




	_CrtMemCheckpoint(&fin);


	//int* leak = new int[100];

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
	cin.get();
}


void fillBiomes(WeightedList<Biome*>& biomes, long seed, int map_size) {

	long rseed = seed;
	//Óceán
	biomes.put(new SimpleBiome(0, "ocean", Water), range(20, 6, seed++));

	//Mezõ
	WeightedList<int> fieldTiles(16);
	fieldTiles.put(Grass, range(150, 50, seed++));
	fieldTiles.put(Tree0, 3);
	fieldTiles.put(Flowers, 5);
	biomes.put(new SimpleListBiome(1, "plains", fieldTiles), range(20, 6, seed++));

	//Erdõ
	WeightedList<int> forest(16);
	forest.put(Tree0, range(150, 50, seed++));
	forest.put(Tree1, range(30, 15, seed++));
	forest.put(Tree2, range(15, 7, seed++));
	forest.put(Grass, range(50, 30, seed++));
	forest.put(AMOGUS, 1);
	forest.put(ORBAN, 1);
	biomes.put(new SimpleListBiome(2, "forest", forest), range(20, 6, seed++));

	//Virágos
	WeightedList<int> flowers(16);
	flowers.put(Flowers, range(150, 30, seed++));
	flowers.put(Grass, 30);
	flowers.put(TreeP, 15);
	biomes.put(new PlantBiome(3, "flowerField", Grass, flowers, 8.0 + Hash::get_sg_float(seed, seed++) * 4.0, Hash::get_sg_float(seed, seed++) * 0.4, map_size), range(20, 6, seed++));

	//Farm
	WeightedList<int> farm(16);
	farm.put(Wheat, 100);
	farm.put(FarmHouse, 1);
	farm.put(FarmTree, 3);
	farm.put(Silo, 1);
	biomes.put(new SimpleListBiome(4, "farm", farm), range(20, 6, seed++));

	//Sivatag
	WeightedList<int> desert(16);
	desert.put(Sand, range(100, 60, seed++));
	desert.put(Cactus, range(8, 6, seed++));
	desert.put(DeadBush, 3);
	biomes.put(new SimpleListBiome(5, "desert", desert), range(20, 6, seed++));

	//Város

	WeightedList<int> street(16);
	street.put(House0, 10);
	street.put(House1, 10);
	street.put(House2, 10);
	street.put(House3, 10);
	street.put(House4, 10);
	street.put(House5, 10);
	street.put(House6, 10);
	street.put(House7, 10);
	street.put(House8, 10);
	street.put(Hospital, 1);

	WeightedList<int> court(16);
	court.put(House0, 10);
	court.put(House1, 10);
	court.put(House2, 10);
	court.put(House3, 10);
	court.put(House4, 10);
	court.put(House5, 10);
	court.put(House6, 10);
	court.put(House7, 10);
	court.put(House8, 10);
	court.put(Grass, 60);
	court.put(Tree0, 30);

	biomes.put(new City(6, "city", street, court), range(20, 6, seed++));
}


int get_seed_from_console() {

	char* seed_str = new char[32 + 1];
	long seed = 69;

	while (true) {
		std::cout << "Enter the country you would like to visit:" << std::endl;
		cin >> seed_str;

		for (int i = 0; i < 33; i++) {
			if (seed_str[i] == '\0' || seed_str[i] == '\n') {

				delete seed_str;
				return seed;
			}
			seed = Hash::get_int(seed_str[i], seed);
		}
		cout << "Error! Too large name!" << "\n";
	} 
}

BYTE* flatten_2d(int** pp, int size) {
	BYTE* p_1d = new BYTE[size * size];

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			//p_1d[size * y + x] = (BYTE)pp[x][y];
			p_1d[size * y + x] = (BYTE)pp[x][y];
		}
	}
	return p_1d;
}


int** create_intP(int size) {
	int** p_p = new int* [size];
	for (int i = 0; i < size; i++)
		p_p[i] = new int[256];
	return p_p;
}

void free_intP(int** p_p, int size) {
	for (int i = 0; i < size; i++)
		delete p_p[i];
	delete p_p;
}

#endif