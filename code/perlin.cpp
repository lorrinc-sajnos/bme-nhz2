
#include "perlin.h"
#include "hash.h"
#include "util.hpp"

//Perlin algoritumsa alapján, Prog1 nagyháziból implementálva
//https://en.wikipedia.org/wiki/Perlin_noise
//https://adrianb.io/2014/08/09/perlinnoise.html


const int PERLIN_X_PRIME = 353594023;
const int PERLIN_Y_PRIME = 1465077127;

float dotGrad(int indX, int indY, float x, float y, long seed);



float Perlin::get_float(float x, float y, float modulo, long seed) {
	int xi = pos_index(x);
	int yi = pos_index(y);

	float xr = x - xi;
	float yr = y - yi;

	//int xi1 = xi + 1, yi1 = yi + 1, zi1 = zi + 1;
	float xr_1 = xr - 1, yr_1 = yr - 1;

	//kiszámoljuk az összes vektor skaláris szorzatát
	float d00 = dotGrad(xi, yi, xr, yr, seed);
	float d10 = dotGrad(xi + 1, yi, xr_1, yr, seed);
	float d01 = dotGrad(xi, yi + 1, xr, yr_1, seed);
	float d11 = dotGrad(xi + 1, yi + 1, xr_1, yr_1, seed);
	float top, bot;

	/*
	float easeXT = xr * xr * (3 - 2 * xr);
	float easeYT = yr * yr * (3 - 2 * yr);
	float easeZT = zr * zr * (3 - 2 * zr);
	*/

	float easeXT = easef(xr);
	float easeYT = easef(yr);


	top = linint(d00, d10, easeXT);
	bot = linint(d01, d11, easeXT);



	//return linint(P, Q, zr);
	//return xi + yi % 64;
	return linint(top, bot, easeYT);
}

float dotGrad(int indX, int indY, float x, float y, long seed) {
	//const float sq2_2 = sqrt(2)/2.;
	int hash = Hash::get_int(indX, indY, seed);
	hash = (hash >> 4) % 8;
	hash = p_mod(hash, 8);
	switch (hash) {
	default:
	case 0:
		return x;

	case 1:
		//return sq2_2 * (x + y);
		return (x + y);

	case 2:
		return y;

	case 3:
		//return sq2_2 * (-x + y);
		return  (-x + y);

	case 4:
		return -x;

	case 5:
		//return sq2_2 * (-x - y);
		return (-x - y);

	case 6:
		return -y;

	case 7:
		//return sq2_2 * (x - y);
		return (x - y);
	}

}

float Perlin::get_float_layered(float x, float y, float modulo, long seed, float layerWeights[], float layerScales[], int layerCount) {
	float noise = 0;
	for (int i = 0; i < layerCount; i++) {
		float weight = layerWeights[i];
		float scale = layerScales[i];
		float nx = x / scale, ny = y / scale;
		noise += sc01(get_float(nx, ny, modulo, seed + 2 * i)) * weight;
	}
	return noise;
}
