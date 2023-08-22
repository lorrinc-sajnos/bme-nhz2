#ifndef BIOME
#define BIOME

#include "weightedlist.hpp"
#include <string>
#include "memory_test.h"

class Biome {
	const char* _name;
	int _id;
public:
	//Biome() : _id(-1), _name("NULL") {}
	Biome(int id, const char* name) : _id(id), _name(name) {}
	Biome(Biome& biome) : _id(biome._id), _name(biome._name) {}
	virtual ~Biome() {};

	int get_id() { return _id; }
	const char* get_name() { return _name; }

	virtual int get_tile(int x, int y, int seed) { return -1; }
};



class SimpleBiome : public Biome {
	int _tile;
public:
	SimpleBiome(int id, const char* name, int tile) : Biome(id, name), _tile(tile) {}
	SimpleBiome(SimpleBiome& s_bme) : Biome(s_bme), _tile(s_bme._tile) {}
	int get_tile(int x, int y, int seed) { return _tile; }
};

class SimpleListBiome : public Biome {
	WeightedList<int>* _tiles;
public:
	SimpleListBiome(int id, const char* name, WeightedList<int> tiles) : Biome(id, name), _tiles(new WeightedList<int>(tiles)) {}
	SimpleListBiome(SimpleListBiome& s_bme) : Biome(s_bme), _tiles(s_bme._tiles) {}
	~SimpleListBiome() { delete _tiles; }
	int get_tile(int x, int y, int seed) {
		return _tiles->get_rand(Hash::get_int(x, y, seed));
	}

};


class PlantBiome : public Biome {
	int _ground;
	WeightedList<int>* _plants;
	float _plant_freq;
	float _plant_trh;
	float mod;
public:
	PlantBiome(int id, const char* name, int ground, WeightedList<int> plants, float plant_freq, float plant_trh, float map_size) :
		Biome(id, name), _ground(ground), _plants(new WeightedList<int>(plants)), _plant_freq(plant_freq), _plant_trh(plant_trh), mod(map_size / plant_freq) {}
	PlantBiome(PlantBiome& p_bme) :
		Biome(p_bme), _ground(p_bme._ground), _plants(p_bme._plants), _plant_freq(p_bme._plant_freq), _plant_trh(p_bme._plant_trh), mod(p_bme.mod) {}
	~PlantBiome() { delete _plants; }
	int get_tile(int x, int y, int seed) {
		if (Perlin::get_float(x / _plant_freq, y / _plant_freq, mod, seed) < _plant_trh)
			return _ground;

		return _plants->get_rand(Hash::get_int(x, y, seed));
	}

};



class City : public Biome {
	WeightedList<int> _street;
	WeightedList<int> _court;

public:
	City(int id, const char* name, WeightedList<int> street, WeightedList<int> court) :
		Biome(id, name), _street(street), _court(court) {}
	City(City& city) :
		Biome(city), _street(city._street), _court(city._court) {}


	int get_tile(int x, int y, int seed) {

		int rx = x % 4, ry = y % 4;

		if (rx == 0 && ry == 0) return Cross;
		/* {


			tile = _inters.get_rand(rand);
			//Ha nem keresztezõdés, akkor kert
			if (tile != NULLTILE) return tile;

			return _court.get_rand(rand);
		}*/

		if (rx == 0) return RoadNS;

		if (ry == 0) return RoadWE;

		int rand = Hash::get_int(x, y, seed);

		if (rx == 2 && ry == 2) return _court.get_rand(rand);


		return _street.get_rand(rand);
	}

};

#endif