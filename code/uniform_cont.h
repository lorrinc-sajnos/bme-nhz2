#ifndef UNIFORM_CONT_H
#define UNIFORM_CONT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "util.hpp"


template <class T>
struct Uniform {
	T data;
	GLuint loc;


	Uniform(T Data) : data(Data), loc(0) {}
	Uniform(const Uniform& unif) : data(unif.data), loc(unif.loc) {}

	Uniform(T D, GLuint Loc) : data(D), loc(Loc) {}
	Uniform(T D, const char* name, unsigned int shader) : data(D), loc(glGetUniformLocation(shader, name)) {}
};

/*class UniCont {
public:
	static Uniform<float> time;
	static Uniform<Vec2> resolution;
	static Uniform<Vec2> direction;
};


struct UniformCont_C {
public:
	float time;
	GLuint time_L;

	Vec2 res;
	GLuint res_L;

	Vec2 dir;
	Vec2 dir_L;
};*/
#endif