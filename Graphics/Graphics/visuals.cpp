#include "visuals.h"
#include <cmath>


model car;
model light;
bool fullscreen = false;
static float tx = 0.0;
float acc = 0.5;
float dec = -0.5;
float speeds = 1;
static float rotx = 270.0;
static float rotz = 180;
static bool animate = false;
bool crashFlag = false;


using namespace std;

void axes()
{
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(0, 0, -1.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 100.0);
	glEnd();
	glPopMatrix();
}

void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														 // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Set position
	glTranslatef(0.0, 0.0, -250.0);
	glRotatef(-50, 1, 0, 0);

	//Track

	/* UPPER STRAIGHT TRACK
	(200, 25)(Á)			(D)(-50, 25)
	(200,-25)(Â)			(C)(-50,-25)

	second part
	(-200, 25)	(-150, 25)
	(-200, -25)	(-150, -25)
	*/
	glColor3f(0.0, 0.0, 1.0);											//make the colour blue (lower)
	glBegin(GL_QUADS);									
	glVertex2f(200.0, 25.0);										
	glVertex2f(200.0, -25.0);	
	glVertex2f(-50.0, -25.0);
	glVertex2f(-50.0, 25.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);											//make the colour blue (lower)
	glBegin(GL_QUADS);
	glVertex2f(-200.0, 25.0);
	glVertex2f(-200.0, -25.0);
	glVertex2f(-150.0, -25.0);
	glVertex2f(-150.0, 25.0);
	glEnd();

	/* DOWN STRAIGHT TRACK
	(-200, -75)(A)	 (D)(200, -75)
	(-200, -125)(B)	 (C)(200, -125)
	*/
	glColor3f(0.0, 0.0, 1.0);											//make the colour blue (lower)
	glBegin(GL_QUADS);
	glVertex2f(-200.0, -75.0);
	glVertex2f(-200.0, -125.0);
	glVertex2f(200.0, -125.0);
	glVertex2f(200.0, -75.0);
	glEnd();

	/*WHITE BOXES at down straight track
	(-150, -87.5)	(-140, -87.5) 
	(-150, -93.75)	(-140, -93.75)

	(-150, -100)	(-140, -100)
	(-150, -106.25)	(-140, -106.25)

	(-150, -112.5)	(-140, -112.5)
	(-150, -118.75)	(-140, -118.75)

	*/

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-150.0, -87.5);
	glVertex2f(-150.0, -93.75);
	glVertex2f(-140.0, -93.75);
	glVertex2f(-140.0, -87.5);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-150.0, -100);
	glVertex2f(-150.0, -106.25);
	glVertex2f(-140.0, -106.25);
	glVertex2f(-140.0, -100);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-150.0, -112.5);
	glVertex2f(-150.0, -118.75);
	glVertex2f(-140.0, -118.75);
	glVertex2f(-140.0, -112.5);
	glEnd();

	/*BRIDGE- PINK Closed
	(-150, 25)	(-50, 25)
	(-150,-25)	(-50,-25)
	*/

	/*glColor3f(1.0, 0.20, 0.80);
	glBegin(GL_POLYGON);
	glVertex2f(-150.0, 25);
	glVertex2f(-150.0, -25);
	glVertex2f(-50.0, -25);
	glVertex2f(-50.0, 25);
	glEnd();*/

	int i = 0;
	for (i = 0; i < 30; i++) {
		Gatemove(10);
	}


	//Semi circle right
	glColor3f(0.0, 0.0, 1.0);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -250.0);
	glRotatef(-50, 1, 0, 0);

	glTranslatef(200.0, -50.0, 0.0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluPartialDisk(quad, 25.0, 75.0, 100.0, 3, 0.0, 180.0);

	//Semi circle left
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -250.0);
	glRotatef(-50, 1, 0, 0);

	glRotatef(-180.0, 0, 0, 1);
	glTranslatef(200.0, 50.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	gluPartialDisk(quad, 25.0, 75.0, 100.0, 3, 0.0, 180.0);


	/*
	glPushMatrix();
	glTranslatef(0, 0, -250);
	glTranslatef(tx, -80, 0.0);
	glRotatef(rotz, 0, 90, 0);
	glRotatef(rotx, 180, 0, 0);
	glScalef(0.25f, 0.25f, 0.25f);
	glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	DisplayCar(car);
	glPopMatrix();
	*/

	/*Light*/
	/*glPushMatrix();
	glTranslatef(0, 0, -100);
	glTranslatef(tx, 0, 0.0);
	//glRotatef(45, 0, 1, 0);
	//glRotatef(rotx, 180, 0, 0);
	//glScalef(0.25f, 0.25f, 0.25f);
	glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	DisplayLight(light);
	glPopMatrix();
	glPushMatrix();

	if (crashFlag) {
		//CRASH
		//-7.04769, -2.56515			Es
		//-15.0, 0						0b
		//-7.04769, 2.56515				Ds
		//-11265462, 10.26056			Ab
		//-3.75, 6.49519				Cs
		//-2.604722, 14.772116			Bb
		//1.30236, 7.38606				Bs
		//7.5, 12.990381				Cb
		//5.74533, 4.82091				As
		//14.095389, 5.459553			Db
		//7.5, 0						0s
		//14.095389, -5.459553			Eb
		//5.74533, -4.82091				Hs
		//7.5, -12.990381				Fb
		//1.30236, -7.38606				Gs
		//-2.604722, -14.772116			Gb
		//-3.75, -6.49519				Fs
		//-11265462, -10.26056			Hb

		//glPushMatrix();
		glTranslatef(0, 25, -75);
		glPointSize(5);
		glBegin(GL_POLYGON);



		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-7.04769, -2.56515);
		glVertex2f(-15.0, 0);
		glVertex2f(-7.04769, 2.56515);
		glVertex2f(-11.265462, 10.26056);
		glVertex2f(-3.75, 6.49519);
		glVertex2f(-2.604722, 14.772116);
		glVertex2f(1.30236, 7.38606);
		glVertex2f(7.5, 12.990381);
		glVertex2f(5.74533, 4.82091);
		glVertex2f(14.095389, 5.459553);
		glVertex2f(7.5, 0);
		glVertex2f(14.095389, -5.459553);
		glVertex2f(5.74533, -4.82091);
		glVertex2f(7.5, -12.990381);
		glVertex2f(1.30236, -7.38606);
		glVertex2f(-2.604722, -14.772116);
		glVertex2f(-3.75, -6.49519);
		glVertex2f(-11.265462, -10.26056);

		glEnd();
		crash("CRASH!", 0.05f);
	}
	glPopMatrix();*/
	

	glutSwapBuffers();             // All drawing commands applied to the 
								   // hidden buffer, so now, bring forward
								   // the hidden buffer and hide the visible one

}

//-----------------------------------------------------------

void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho (-50.0f, 50.0f, -50.0f, 50.0f,-1000.0f,1000.0f);
	float aspect = (float)w / (float)h;
	gluPerspective(100.0, aspect, 1.0, 500.0);
}


void Idle()
{
	if (animate)
		rotx += 0.4;

	glutPostRedisplay();
}


void Setup()  // TOUCH IT !! 
{
	ReadFileCar(&car);
	ReadFileLight(&light);

	//Parameter handling
	glShadeModel(GL_SMOOTH);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

static void torus(float inner, float outer, unsigned int pts)
{
	glTranslatef(0.0, 0.0, -200.0);
	glRotatef(-60, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(150.0, -75.0, 0.0);


	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0, 0, 0);
	
	for (unsigned int i = 0; i <= pts/2; ++i)
	{
		float angle = (i / (float)pts) * 3.14159f * 2.0f;
		glVertex2f(inner * cos(angle), inner * sin(angle));
		glVertex2f(outer * cos(angle), outer * sin(angle));
	}
	glEnd();


}

void ReadFileCar(model *car) {
	string input;
	
	ifstream car_file("Models/clk.obj", ios::in);                   // Open the file for reading OBJINFO.TXT

	if (car_file.fail())
		exit(1);

	while (getline(car_file, input)) {

		if (input.substr(0, 2) == "v ") {
			vertex temp_vtx;

			istringstream s(input.substr(2));
			s >> temp_vtx.x;
			s >> temp_vtx.y;
			s >> temp_vtx.z;

			car->vertices.push_back(temp_vtx);
		}
		else if (input.substr(0, 2) == "f ") {
			face temp_face;

			istringstream s(input.substr(2));
			s >> temp_face.vtx[0];
			s >> temp_face.vtx[1];
			s >> temp_face.vtx[2];

			car->faces.push_back(temp_face);
		}
		else if (input[0] == '#') {
			//nothing
		}
		else {
			//nothing
		}
	}
}


void ReadFileLight(model *traffic_light) {
	string input;

	ifstream light_file("Models/trafficlight.obj", ios::in);                   // Open the file for reading OBJINFO.TXT

	if (light_file.fail())
		exit(1);

	while (getline(light_file, input)) {

		if (input.substr(0, 3) == "vn ") {
			normal temp_normal;

			istringstream s(input.substr(3));
			s >> temp_normal.x;
			s >> temp_normal.y;
			s >> temp_normal.z;

			traffic_light->normals.push_back(temp_normal);
		}
		else if (input.substr(0, 2) == "v ") {
			vertex temp_vtx;

			istringstream s(input.substr(2));
			s >> temp_vtx.x;
			s >> temp_vtx.y;
			s >> temp_vtx.z;
			s >> temp_vtx.i;
			s >> temp_vtx.j;
			s >> temp_vtx.k;

			traffic_light->vertices.push_back(temp_vtx);
		}
		else if (input.substr(0, 2) == "f ") {
			face temp_face;
			int i = 0;
			string token;
			string item;
			istringstream s(input.substr(2));
			
			/*
			s >> temp_face.vtx[0];
			s >> temp_face.vn[0];
			cout << temp_face.vtx[0] << '\t' << temp_face.vn[0];
			s >> temp_face.vtx[1];
			s >> temp_face.vn[1];
			cout << temp_face.vtx[1] << '\t' << temp_face.vn[1];
			s >> temp_face.vtx[2];
			s >> temp_face.vn[2];
			cout << temp_face.vtx[2] << '\t' << temp_face.vn[2] << endl;
			*/
			
			while (getline(s, token, ' ')) {
				int pos = token.find('/');
				istringstream (token.substr(0, pos)) >> temp_face.vtx[i];
				pos += 2;
				istringstream(token.substr(pos)) >> temp_face.vn[i];
				i++;
			}

			traffic_light->faces.push_back(temp_face);
		}
		else if (input[0] == '#') {
			//nothing
		}
		else {
			//nothing
		}
	}
}


void DisplayCar(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);


	/*
	for (face f : md.faces) {
		glVertex3f(md.vertices.at(f.vtx[0] - 1).x, md.vertices.at(f.vtx[0] - 1).y, md.vertices.at(f.vtx[0] - 1).z);
		glVertex3f(md.vertices.at(f.vtx[1] - 1).x, md.vertices.at(f.vtx[1] - 1).y, md.vertices.at(f.vtx[1] - 1).z);
		glVertex3f(md.vertices.at(f.vtx[2] - 1).x, md.vertices.at(f.vtx[2] - 1).y, md.vertices.at(f.vtx[2] - 1).z);
	}
	*/
	
	
	for (vector<face>::iterator it = md.faces.begin(); it != md.faces.end(); it++) {
		glVertex3f(md.vertices.at(it->vtx[0] - 1).x, md.vertices.at(it->vtx[0] - 1).y, md.vertices.at(it->vtx[0] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[1] - 1).x, md.vertices.at(it->vtx[1] - 1).y, md.vertices.at(it->vtx[1] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[2] - 1).x, md.vertices.at(it->vtx[2] - 1).y, md.vertices.at(it->vtx[2] - 1).z);
	}
	
	/*
	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);
	}
	*/

	glEnd();
	glPopMatrix();

}


void DisplayLight(model md) {
	glPushMatrix();
	glBegin(GL_TRIANGLES);


	/*
	for (face f : md.faces) {
	glVertex3f(md.vertices.at(f.vtx[0] - 1).x, md.vertices.at(f.vtx[0] - 1).y, md.vertices.at(f.vtx[0] - 1).z);
	glVertex3f(md.vertices.at(f.vtx[1] - 1).x, md.vertices.at(f.vtx[1] - 1).y, md.vertices.at(f.vtx[1] - 1).z);
	glVertex3f(md.vertices.at(f.vtx[2] - 1).x, md.vertices.at(f.vtx[2] - 1).y, md.vertices.at(f.vtx[2] - 1).z);
	}
	*/


	for (vector<face>::iterator it = md.faces.begin(); it != md.faces.end(); it++) {
		glVertex3f(md.vertices.at(it->vtx[0] - 1).x, md.vertices.at(it->vtx[0] - 1).y, md.vertices.at(it->vtx[0] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[1] - 1).x, md.vertices.at(it->vtx[1] - 1).y, md.vertices.at(it->vtx[1] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[2] - 1).x, md.vertices.at(it->vtx[2] - 1).y, md.vertices.at(it->vtx[2] - 1).z);
	}

	/*
	for (int i = 0; i < md.faces; i++)
	{
	glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
	glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
	glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);
	}
	*/

	glEnd();
	glPopMatrix();
}


void Keyboard(unsigned char key, int x, int y)
{
	//cout << key << endl;
	switch (key)
	{
	case 'q': 
	case 'Q':
		exit(0);
		break;
	case 'w': 
	case 'W':
		Up();
		break;
	case 's': 
	case 'S':
		Down();
		break;
	case 'a':
	case 'A':
		Left();
		break;
	case 'd':
	case 'D':
		Right();
		break;
	case 'f':
	case 'F':
		fullscreen = !fullscreen;
		if (fullscreen) {
			glutFullScreen();
		}
		else {
			glutReshapeWindow(960, 480);
			glutPositionWindow(50, 50);
		}
		break;
	case 'c':
	case 'C':
		crashFlag = !crashFlag;
		break;
	default: break;
	}

	glutPostRedisplay();

}


void Arrows(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		Up();
		break;
	case GLUT_KEY_DOWN:
		Down();
		break;
	case GLUT_KEY_LEFT:
		Left();
		break;
	case GLUT_KEY_RIGHT:
		Right();
		break;
	}
}


void Up() {
	tx -= acc;
	acc += 0.5f;
}


void Down() {
	tx += 5.5f;
}


void Left() {
	rotz += 5;
}

void Right() {
	rotz -= 5;
}


void crash(const char *str, float size)
{

	glPushMatrix();
	glTranslatef(-10.5, -2.0, 0.0);
	glScalef(size, size, size);
	glColor3f(1.0, 1.0, 0.0);

	for (int i = 0; i<strlen(str); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();

}

void Gatemove(float Ypos) {

		/*BRIDGE- PINK Ïpen
		(-150, 140)	(-50, 25)
		(-150, 90)	(-50,-25)
		*/
		glRotatef(1, 0, 1, 0);
		glTranslatef(0, sin(1), 0);
		glColor3f(1.0, 0.20, 0.80);
		glBegin(GL_POLYGON);
		glVertex2f(-150.0, 25);
		glVertex2f(-150.0, -25);
		glVertex2f(-50.0, -25);
		glVertex2f(-50.0, 25);
		glEnd();

}