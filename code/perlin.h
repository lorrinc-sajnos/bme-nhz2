//Prog 1 nagyházimból másolva

#ifndef PERLIN
#define PERLIN

class Perlin {

public:
	static float get_float(float x, float y, float modulo, long seed);
	static float get_float_layered(float x, float y, float modulo, long seed, float layerWeights[], float layerScales[], int layerCount);

};
#endif