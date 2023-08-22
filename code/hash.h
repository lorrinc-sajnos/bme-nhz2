#ifndef HASH
#define HASH


class Hash {
	/*
	const static int hash_x_prime = 758875231;
	const static int  hash_y_prime = 2001288571;
	const static int  hash_z_prime = 1134440171;

	const static float almost_one;// = 0.9999999f;
	const static float  float_2_int;// = 2.328306158982940132773364894092082977294921875e-10f; //=almostOne / 4294967295L;
	const static float  sFloat2int;// = 4.65661231796588026554672978818416595458984375e-10f;//= almostOne / 2147483647;*/

public:
	static int get_int(int x, long seed);
	static int get_int(int x, int y, long seed);
	static int get_int(int x, int y, int z, long seed);

	static float get_float(int x, long seed);
	static float get_float(int x, int y, long seed);
	static float get_float(int x, int y, int z, long seed);

	static float get_sg_float(int x, long seed);
	static float get_sg_float(int x, int y, long seed);
	static float get_sg_float(int x, int y, int z, long seed);

};

#endif