#ifndef BIOME_NOISE
#define BIOME_NOISE

#include "hash.h"
#include "perlin.h"
#include "util.hpp"

class BiomeNoise {
private:
	long seed;
	long x_seed;
	long y_seed;
	long p_x_seed;
	long p_y_seed;
	float cell_size;
	int map_size;
	float _perlinFreq;
	float offs_ampl;
public:
	BiomeNoise(long seed, float cell_size, int map_Size, float perlinFreq, float offset_ampl) : seed(seed), cell_size(cell_size), map_size(map_Size), _perlinFreq(perlinFreq), offs_ampl(offset_ampl) {

		x_seed = Hash::get_int((int)seed, seed);
		y_seed = Hash::get_int((int)x_seed, x_seed);
		p_x_seed = Hash::get_int((int)y_seed, y_seed);
		p_y_seed = Hash::get_int((int)p_x_seed, p_x_seed);
	}

	vec2 from_ind(int x, int y) {

		vec2 v;
		return v;
	}

	int getNoise(float x, float y) {

		//Loopolás:
		float mx = p_modf(x, (float)map_size);
		float my = p_modf(y, (float)map_size);

		//Perlin-torzítás

		float new_x = mx + offs_ampl * Perlin::get_float(mx / _perlinFreq, my / _perlinFreq, map_size / _perlinFreq, p_x_seed);
		float new_y = my + offs_ampl * Perlin::get_float(mx / _perlinFreq, my / _perlinFreq, map_size / _perlinFreq, p_y_seed);

		//new_x = mx;// +offs_ampl * Perlin::get_float(mx, my, 0, p_x_seed);
		//new_y = my;// +offs_ampl * Perlin::get_float(mx, my, 0, p_y_seed);

		//Legközelebbi cella-kzp

		vec2 rel_pos(p_modf(new_x, cell_size) / cell_size, p_modf(new_y, cell_size) / cell_size);

		int xi = pos_index(new_x / cell_size);
		int yi = pos_index(new_y / cell_size);


		//return Hash::get_int(xi, yi, seed);


		int min_indX = -1;
		int min_indY = -1;
		float min_dst = 999;

		//minimum indexének kiszámítása
		// A mostani pont kzp-en van, a környezõ cellákhoz tartozó kzp-et kiszámítjuk
		// A visszatérési érték a legközelebbi közepû cellához rendelt integer
		//	_____________
		//	|	|	|	|
		//	|___|___|___|
		//	|	|.	|	|
		//	|___|___|___|
		//	|	|	|	|
		//	|___|___|___|
		// 
		//
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				vec2 curr_cnt;

				int curr_xi = p_mod(xi + i, (int)(map_size / cell_size));
				int curr_yi = p_mod(yi + j, (int)(map_size / cell_size));

				curr_cnt.x = i + Hash::get_float(curr_xi, curr_yi, x_seed);
				curr_cnt.y = j + Hash::get_float(curr_xi, curr_yi, y_seed);

				float curr_dst = rel_pos.dist(curr_cnt);
				if (curr_dst < min_dst) {
					min_indX = curr_xi;
					min_indY = curr_yi;
					min_dst = curr_dst;
				}
			}
		}

		//return 0;
		return Hash::get_int(min_indX, min_indY, seed);
	}


	int getNoise_old(float x, float y) {

		float mod_size = (float)map_size;

		//Loopolás:
		float mx = p_modf(x, mod_size);
		float my = p_modf(y, mod_size);

		float new_x = mx;// +offs_ampl * Perlin::get_float(mx, my, 0, p_x_seed);
		float new_y = my;// +offs_ampl * Perlin::get_float(mx, my, 0, p_y_seed);

		int xi = pos_index(new_x / cell_size);
		int yi = pos_index(new_y / cell_size);

		//return xi + yi;
		int hash = Hash::get_int(xi, yi, seed);
		//std::cout << hash << "\n";
		return hash;
	}

};

#endif
