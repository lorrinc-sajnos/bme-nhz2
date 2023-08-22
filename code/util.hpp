#ifndef UTIL
#define UTIL

#include <cmath>
#include "hash.h"

#define BYTE unsigned char

enum Tile {
	Water,
	Grass,
	Sand,
	Cactus,
	DeadBush,
	Tree0,
	Tree1,
	Tree2,
	Flowers,
	Wheat,
	FarmHouse,
	FarmTree,
	Silo,
	Pavement,
	TurnSE,
	TurnSW,
	TurnNE,
	TurnNW,
	Cross,
	RoadWE,
	RoadNS,
	House0,
	House1,
	House2,
	House3,
	House4,
	House5,
	House6,
	House7,
	House8,
	Hospital,
	TreeP,
	Cat0,
	Cat1,
	Cat2,
	AMOGUS,
	ORBAN,

	NULLTILE = 63
};


struct vec2 {
public:
	float x, y;

	vec2() : x(0), y(0) {}
	vec2(float X, float Y) : x(X), y(Y) {}

	vec2(const vec2 &v) : x(v.x), y(v.y) {}

	float length() { return sqrtf(x * x + y * y); }

	float dist(vec2 v) {
		float dx = x - v.x;
		float dy = y - v.y;
		return sqrtf(dx*dx+dy*dy);
	}
	static vec2 normalize(vec2 vect) {
		float length = vect.length();
		return vec2(vect.x / length, vect.y / length);
	}

	vec2 operator+(const vec2& rht_v) {
		return vec2(x + rht_v.x, y + rht_v.y);
	}
	vec2 operator-(const vec2& rht_v) {
		return vec2(x - rht_v.x, y - rht_v.y);
	}
	vec2 operator*(const float rht_f) {
		return vec2(x * rht_f,y * rht_f);
	}
};

inline int range(int base, int var, long seed) { return base + (int)(var * Hash::get_sg_float((int)seed, seed)); }


inline int p_mod(int i, int n) { return (i % n + n) % n; }
inline float p_modf(float i, float n) {
	float m = fmod(i, n);
	return m >= 0 ? m : m + n;
}

inline float linint(float x, float y, float t) { return x + (y - x) * t; }
inline float easef(float t) { return t * t * (3 - 2 * t); }

inline float sc01(float x) { return x * 0.5f + 0.5f; }
inline float sc11(float x) { return x * 2 - 1; }

inline int pos_index(float f) { return f > 0 ? (int)f : (int)f - 1; }

inline void assignMtx_row(float* mtx, float a11, float a12, float a21, float a22) { 
	mtx[0] = a11; 
	mtx[1] = a12; 
	mtx[2] = a21; 
	mtx[3] = a22; 
}
#endif