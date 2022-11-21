#pragma once
#include "freeglut.h"
struct axis
{
	float x;
	float y;
	float z;
};
class Planet
{
public:

	float x, y, z, size;
	float angle;
	float offset;

	static bool wiremode;
	Planet();
	Planet(float X, float Y, float Z, float SIZE, float OFFSET);
	void draw(float SIZE, float r, float g, float b);
	void rotate(Planet& orbital,  axis My_Axis = { 0,1,0 });
	//void self_Rotate();
};