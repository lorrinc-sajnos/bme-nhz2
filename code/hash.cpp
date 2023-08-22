#include "hash.h"


const int hash_x_prime = 758875231;
const int  hash_y_prime = 2001288571;
const int  hash_z_prime = 1134440171;

const float float_2_int = 2.328306158982940132773364894092082977294921875e-10f; //=almostOne / 4294967295L;
const float sFloat2int = 4.65661231796588026554672978818416595458984375e-10f;//= almostOne / 2147483647;

int Hash::get_int(int x, long seed) {
	int _seed = (int)seed;
	_seed ^= hash_x_prime * x;

	return _seed * _seed * _seed;
}

int Hash::get_int(int x, int y, long seed) {
	int _seed = (int)seed;
	_seed ^= hash_x_prime * x;
	_seed ^= hash_y_prime * y;

	return _seed * _seed * _seed;
}

int Hash::get_int(int x, int y, int z, long seed) {
	int _seed = (int)seed;
	_seed ^= hash_x_prime * x;
	_seed ^= hash_y_prime * y;
	_seed ^= hash_z_prime * z;

	return _seed * _seed * _seed;
}


float Hash::get_float(int x, long seed) { return get_int(seed, x) * float_2_int + 0.5f; }
float Hash::get_float(int x, int y, long seed) { return get_int(seed, x, y) * float_2_int + 0.5f; }
float Hash::get_float(int x, int y, int z, long seed) { return get_int(seed, x, y, z) * float_2_int + 0.5f; }


float Hash::get_sg_float(int x, long seed) { return get_int(seed, x) * sFloat2int; }
float Hash::get_sg_float(int x, int y, long seed) { return get_int(seed, x, y) * sFloat2int; }
float Hash::get_sg_float(int x, int y, int z, long seed) { return get_int(seed, x, y, z) * sFloat2int; }