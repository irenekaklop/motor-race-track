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
#define M_PI 3.1415926535897932384626433832795
#define SPACEBAR 32


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

struct carMovement {
	//movement variables for the model
	float tx;
	float tz;
	float acc;
	float rotx;
	float roty;

	//flag variables for the type of movement
	bool leftFlag;
	bool rightFlag;
	bool firstTime;

	//saved values for easier circular motion
	float origRot;
	float origTx;
	float origTz;
	float omega;
	float theta;
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

int DisplayCar(model);
int DisplayLight(model);

void RenderUserCar();
void RenderCompCar();

void Keyboard(unsigned char, int, int);
void Arrows(int, int, int);

void Up();
void Down();
void rightCycle(carMovement*, float);
void leftCycle(carMovement*, float);
void crash(const char*, float);


void Track(int x, int y, int z);
static void torus(float inner, float outer, unsigned int pts);
void Gatemove(time_t time);
void light_controller(void);