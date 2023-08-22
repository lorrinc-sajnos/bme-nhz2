#ifndef OPENGL_MAIN_LORINC
#define OPENGL_MAIN_LORINC

#include "has_graphics.h"

#if HAS_GRAPHICS == 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "opengl_obj.h"
#include "game_setting.h"
#include "uniform_cont.h"


class OpenGLObj {
	//--------------------
	GameSettings* gameSettings;

	float Angle;
	float AngleSpeed;

	const float SpeedMin;
	const float SpeedMax;
	const float Acceleration;

	//funkcionális tagok


	const char* tileMapFile = "tilemap.png";
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 aTexCoord;\n"
		"\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0);\n"
		"	ourColor = aColor;\n"
		"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
		"}\n";


	GLuint Resolution_loc;
	GLuint Texture_smpl_loc;
	GLuint TileData_smpl_loc;

	float Speed = SpeedMin;

	Uniform<vec2> Dir;
	Uniform<vec2> Pos;

	Uniform<float*> DirMtx;
	double deltaTime;
	double newAngle;

	int opengl_main();
	void calcPos();
	void updateAngle(double newAngle);
	void processInput(GLFWwindow* window);

public:

	OpenGLObj(GameSettings* gameSettings, float Angle = 0, float AngleSpeed = 0.0005f, const float SpeedMin = 128, const float SpeedMax = 512, const float Acceleration = 0.5) :
		gameSettings(gameSettings), Angle(Angle), AngleSpeed(AngleSpeed), SpeedMin(SpeedMin), SpeedMax(SpeedMax), Acceleration(Acceleration),
		Speed(SpeedMin), Resolution_loc(0), Texture_smpl_loc(0), TileData_smpl_loc(0), Dir(vec2(0, 1)), Pos(vec2(0, 0)), DirMtx(nullptr), deltaTime(0), newAngle(0)
	{}
	void run_gui();
};


#endif
#endif