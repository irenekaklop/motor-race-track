#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "gl/glut.h"   // - An interface and windows management library

#define PI 3.14159265

using namespace std;

#pragma once
struct vertex
{
	float x;
	float y;
	float z;
	float i;
	float j;
	float k;
};

struct normal {
	float x;
	float y;
	float z;
};

struct face
{
	int vtx[3];
	int vn[3];
};

struct model
{
	vector<vertex> vertices;
	vector<normal> normals;
	vector<face> faces;
};


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();



void ReadFileCar(model*);
void ReadFileLight(model*);


void DisplayCar(model);
void DisplayLight(model);

void Keyboard(unsigned char, int, int);
void Arrows(int, int, int);
void Up();
void Down();
//void Left();
//void Right();
void rightCycle();
void leftCycle();
void crash(const char*, float);