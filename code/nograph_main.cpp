#include "has_graphics.h"
#if HAS_GRAPHICS == 0


#include <iostream>
#include <string>
#include <map>

#include "weightedlist.hpp"
#include "hash.h"
#include "biome_noise.hpp"

#include "biome.hpp"
#include "gtest_lite.h"

using namespace std;



void hash_test();
void perlin_test();
void weighted_list_test();

int main() {
	std::cout << "Nagyhazi tesztek:" << endl;
	hash_test();
	perlin_test();
	weighted_list_test();
}

void hash_test() {
	std::cout << "Hash fgv" << endl;
	long seed = 1235;


	int beg = -100000;
	int end = 100000;
	double count = end - beg;

	int beg2 = -1000;
	int end2 = 1000;
	double side = (double)(end2 - beg2);
	double count2 = side* side;

	double h_eps = 0.005;
	int h_eps_i = (int)(2147483647 * h_eps);

	double h_avg_x_f = 0;
	double h_avg_xy_f = 0;
	double h_avg_f_exp = 0.5;

	double h_min_x_f = 10;
	double h_min_xy_f = 10;
	double h_min_f_exp = 0.0;

	double h_max_x_f = -10;
	double h_max_xy_f = -10;
	double h_max_f_exp = 1.0;



	double h_avg_x_sf = 0;
	double h_avg_xy_sf = 0;
	double h_avg_sf_exp = 0.0;

	double h_min_x_sf = 10;
	double h_min_xy_sf = 10;
	double h_min_sf_exp = -1.0;

	double h_max_x_sf = -10;
	double h_max_xy_sf = -10;
	double h_max_sf_exp = 1.0;



	double h_avg_x_i = 0;
	double h_avg_xy_i = 0;
	double h_avg_i_exp = 0.0;

	double h_min_x_i = 2147483647;
	double h_min_xy_i = 2147483647;
	double h_min_i_exp = -2147483647 - 1;

	double h_max_x_i = -2147483647 - 1;
	double h_max_xy_i = -2147483647 - 1;
	double h_max_i_exp = 2147483647;

	for (int x = beg; x < end; x++) {
		float f = Hash::get_float(x, seed);
		h_avg_x_f += f / count;
		if (f < h_min_x_f) h_min_x_f = f;
		if (f > h_max_x_f) h_max_x_f = f;

		float sf = Hash::get_sg_float(x, seed);
		h_avg_x_sf += sf / count;
		if (sf < h_min_x_sf) h_min_x_sf = sf;
		if (sf > h_max_x_sf) h_max_x_sf = sf;

		double i = Hash::get_int(x, seed);
		h_avg_x_i += i / count;
		if (i < h_min_x_i) h_min_x_i = i;
		if (i > h_max_x_i) h_max_x_i = i;
	}

	for (int x = beg2; x < end2; x++) {

		for (int y = beg2; y < end2; y++) {
			float xy_f = Hash::get_float(x, y, seed);
			h_avg_xy_f += xy_f / count2;
			if (xy_f < h_min_xy_f) h_min_xy_f = xy_f;
			if (xy_f > h_max_xy_f) h_max_xy_f = xy_f;


			float xy_sf = Hash::get_sg_float(x, y, seed);
			h_avg_xy_sf += xy_sf / count2;
			if (xy_sf < h_min_xy_sf) h_min_xy_sf = xy_sf;
			if (xy_sf > h_max_xy_sf) h_max_xy_sf = xy_sf;

			int xy_i = Hash::get_int(x, y, seed);
			h_avg_xy_i += xy_i / count2;
			if (xy_i < h_min_xy_i) h_min_xy_i = xy_i;
			if (xy_i > h_max_xy_i) h_max_xy_i = xy_i;
		}
	}

	std::cout << "---------" << endl;
	TEST(Hash, eloszlas_teszt) {

		std::cout << "\tHash X atlag: " << h_avg_x_f << ", elvart: " << h_avg_f_exp << endl;
		EXPECT_GE(h_eps, abs(h_avg_x_f - h_avg_f_exp)) << "Hash fgv. x eloszlasa nem megfelelo!" << endl;

		std::cout << "\tHash XY atlag: " << h_avg_xy_f << ", elvart: " << h_avg_f_exp << endl;
		EXPECT_GE(h_eps, abs(h_avg_xy_f - h_avg_f_exp)) << "Hash fgv. xy eloszlasa nem megfelelo!" << endl;


		std::cout << "\tElojeles Hash X atlag: " << h_avg_x_sf << ", elvart: " << h_avg_sf_exp << endl;
		EXPECT_GE(h_eps, abs(h_avg_x_sf - h_avg_sf_exp)) << "El. Hash fgv. x eloszlasa nem megfelelo!" << endl;

		std::cout << "\tElojeles Hash XY atlag: " << h_avg_xy_sf << ", elvart: " << h_avg_sf_exp << endl;
		EXPECT_GE(h_eps, abs(h_avg_xy_sf - h_avg_sf_exp)) << "El. Hash fgv. x eloszlasa nem megfelelo!" << endl;


		std::cout << "\tInteger Hash X atlag: " << h_avg_x_i << ", elvart: " << h_avg_i_exp << endl;
		EXPECT_GE(h_eps_i, abs(h_avg_x_i - h_avg_i_exp)) << "I. Hash fgv. x eloszlasa nem megfelelo!" << endl;

		std::cout << "\tInteger Hash XY atlag: " << h_avg_xy_i << ", elvart: " << h_avg_i_exp << endl;
		EXPECT_GE(h_eps_i, abs(h_avg_xy_i - h_avg_i_exp)) << "I. Hash fgv. xy eloszlasa nem megfelelo!" << endl;


	} ENDM;
	std::cout << "---------" << endl;
	TEST(Hash, glob_min_test) {

		std::cout << "\tHash X min: " << h_min_x_f << ", elvart: " << h_min_f_exp << endl;
		EXPECT_GE(h_eps, abs(h_min_x_f - h_min_f_exp)) << "Hash fgv. x szelsoert. nem megfelelo!" << endl;

		std::cout << "\tHash XY minimuma: " << h_min_xy_f << ", elvart: " << h_min_f_exp << endl;
		EXPECT_GE(h_eps, abs(h_min_xy_f - h_min_f_exp)) << "Hash fgv. xy szelsoert. nem megfelelo!" << endl;


		std::cout << "\tElojeles Hash X minimuma: " << h_min_x_sf << ", elvart: " << h_min_sf_exp << endl;
		EXPECT_GE(h_eps, abs(h_min_x_sf - h_min_sf_exp)) << "El. Hash fgv. x szelsoert. nem megfelelo!" << endl;

		std::cout << "\tElojeles Hash XY minimuma: " << h_min_xy_sf << ", elvart: " << h_min_sf_exp << endl;
		EXPECT_GE(h_eps, abs(h_min_xy_sf - h_min_sf_exp)) << "El. Hash fgv. x szelsoert. nem megfelelo!" << endl;


		std::cout << "\tInteger Hash X minimuma: " << h_min_x_i << ", elvart: " << h_min_i_exp << endl;
		EXPECT_GE(h_eps_i, abs(h_min_x_i - h_min_i_exp)) << "I. Hash fgv. x szelsoert. nem megfelelo!" << endl;

		std::cout << "\tInteger Hash XY minimuma: " << h_min_xy_i << ", elvart: " << h_min_i_exp << endl;
		EXPECT_GE(h_eps_i, abs(h_min_xy_i - h_min_i_exp)) << "I. Hash fgv. xy szelsoert. nem megfelelo!" << endl;
	} ENDM;
	std::cout << "---------" << endl;


	TEST(Hash, glob_max_test) {

		std::cout << "\tHash X max: " << h_max_x_f << ", elvart: " << h_max_f_exp << endl;
		EXPECT_GE(h_eps, abs(h_max_x_f - h_max_f_exp)) << "Hash fgv. x szelsoert. nem megfelelo!" << endl;

		std::cout << "\tHash XY maximuma: " << h_max_xy_f << ", elvart: " << h_max_f_exp << endl;
		EXPECT_GE(h_eps, abs(h_max_xy_f - h_max_f_exp)) << "Hash fgv. xy szelsoert. nem megfelelo!" << endl;


		std::cout << "\tElojeles Hash X maximuma: " << h_max_x_sf << ", elvart: " << h_max_sf_exp << endl;
		EXPECT_GE(h_eps, abs(h_max_x_sf - h_max_sf_exp)) << "El. Hash fgv. x szelsoert. nem megfelelo!" << endl;

		std::cout << "\tElojeles Hash XY maximuma: " << h_max_xy_sf << ", elvart: " << h_max_sf_exp << endl;
		EXPECT_GE(h_eps, abs(h_max_xy_sf - h_max_sf_exp)) << "El. Hash fgv. x szelsoert. nem megfelelo!" << endl;


		std::cout << "\tInteger Hash X maximuma: " << h_max_x_i << ", elvart: " << h_max_i_exp << endl;
		EXPECT_GE(h_eps_i, abs(h_max_x_i - h_max_i_exp)) << "I. Hash fgv. x szelsoert. nem megfelelo!" << endl;

		std::cout << "\tInteger Hash XY maximuma: " << h_max_xy_i << ", elvart: " << h_max_i_exp << endl;
		EXPECT_GE(h_eps_i, abs(h_max_xy_i - h_max_i_exp)) << "I. Hash fgv. xy szelsoert. nem megfelelo!" << endl;
	} ENDM;


}


void perlin_test() {
	std::cout << "perlin fgv" << endl;
	long seed = 1235;


	int beg2 = 0;
	int end2 = 1000;
	float freq = 10;
	double count2 = (end2 - beg2) * (end2 - beg2);

	std::cout << "Perlin fgv" << endl;

	double p_avg = 0;
	double p_avg_exp = 0;
	
	double p_min = 10;
	double p_min_trh = -1.0;

	double p_max = -10;
	double p_max_trh = 1.0;


	for (int x = beg2; x < end2; x++) {

		for (int y = beg2; y < end2; y++) {
			float noise = Perlin::get_float(x / freq, y / freq, (float)end2, seed);
			p_avg += noise / count2;
			if (noise < p_min) p_min = noise;
			if (noise > p_max) p_max = noise;
		}
	}

	std::cout << "---------" << endl;
	TEST(Perlin, glob_min_test) {

		std::cout << "\tPerlin min: " << p_min << ", korlat min: " << p_min_trh << endl;
		EXPECT_LE(p_min_trh, p_min) << "Perlin fgv. szelsoert. nem megfelelo!" << endl;
	} ENDM;
	std::cout << "---------" << endl;


	TEST(Perlin, glob_max_test) {
		std::cout << "\tPerlin max: " << p_max << ", korlat max: " << p_max_trh << endl;
		EXPECT_GE(p_max_trh, p_max) << "Perlin fgv. szelsoert. nem megfelelo!" << endl;
	} ENDM;


	int monTestC = 10000;
	float monFreq = 1000;
	double pD_max = -1;
	double pD_trh = 0.005;
	double prev = Perlin::get_float(0 / monFreq, 0 / monFreq, (float)monTestC, seed);

	for (int i = 1; i < monTestC; i++) {
		double curr = Perlin::get_float(i / monFreq, i / monFreq, (float)monTestC, seed);
		double delta = abs(curr - prev);
		if (delta > pD_max) pD_max = delta;
		prev = curr;
	}
	TEST(Perlin, monoton_test) {
		std::cout << "\tPerlin max delta: " << pD_max << ", elvart max delta: " << pD_trh << endl;
		EXPECT_GE(pD_trh, pD_max) << "Perlin fgv. delta nem megfelelo!" << endl;
	} ENDM;

}

void weighted_list_test() {
	std::cout << "WeightedList fgv" << endl;
	WeightedList<int> test(10);



	TEST(WList, sanity) {
		EXPECT_EQ(0, test.size()) << "size() nem jo!" << endl;
		EXPECT_EQ(0, test.weight_sum()) << "size() nem jo!" << endl;
		EXPECT_ANY_THROW(test.get_at(0)) << "nincs tulindex pajzs!" << endl;
		EXPECT_ANY_THROW(test.get_w_at(0)) << "nincs tulindex pajzs!" << endl;
	} ENDM;


	int weights[10] = { 20,30,1,13,8,21,9,17 };
	int sum = 0;
	for (int i = 0; i < 10; i++) { sum += weights[i]; }

	TEST(WList, put) {
		for (int i = 0; i < 10; i++)
			test.put(i, weights[i]);

		EXPECT_EQ(10, test.size()) << "size() nem jo!" << endl;
		EXPECT_EQ(sum, test.weight_sum()) << "size() nem jo!" << endl;


		EXPECT_ANY_THROW(test.put(999, 999)) << "nincs capacity pajzs!" << endl;
	} ENDM;

	int hits[10] = { 0,0,0,0,0,0,0,0,0,0 };

	long seed = 12325;
	int testC = 1000000;
	double prcEps = 5;
	for (int i = 0; i < testC; i++) {
		int ind = test.get_rand(Hash::get_int(i, seed));
		hits[ind]++;
	}
	TEST(WList, get_rand) {
		for (size_t i = 0; i < 10; i++) {
			double prc = (double)hits[i] / testC * 100;
			double prc_exp = (double)test.get_w_at(i) / sum * 100;

			std::cout << "\t" << i << ". elem elofordulasa: " << prc << "%, elvart: " << prc_exp << "%" << endl;
			EXPECT_GE(prcEps, abs(prc - prc_exp)) << i << ". elem eloszlasa nem megfelelo!" << endl;
		}


	} ENDM;

}

#endif