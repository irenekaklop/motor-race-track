#include "visuals.h"
#include <cmath>


model car;
model light;

bool fullscreen = false;

bool leftFlag = false;
bool rightFlag = true;
bool firstTime = false;

bool crashFlag = false;

float R = 25;
float C1x = 100;
float C2x = -100;
float Cz = -110;
float origRot = 180;
float origTx;
float origTz;
float omega;
float theta;
float time = 0;

float tx = 0.0;
float tz = Cz+R;
float acc = 2.5;
float rotx = 270.0;
float roty = 180;



// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;


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
	
	
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);



	glPushMatrix();
	//glTranslatef(0, 0, -250);
	glTranslatef(tx, 0, tz);
	glRotatef(roty, 0, 90, 0);
	glRotatef(rotx, 180, 0, 0); 
	glScalef(0.05f, 0.05f, 0.05f);
	glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	DisplayCar(car);
<<<<<<< HEAD
	
	
	if (tx >= C1x) {
		/*
		if (firstTime < 0) {
			firstTime = 1;
			origTx = C1x;
			origTz = Cz-R;
			origRot = 180;
		}
		else {
			firstTime += 1;
		}
		float omega = acc / R;
		float theta = omega * firstTime;
		
		tx = origTx + (R * sin(theta*PI / 180));

		if (rightFlag) {
			tz = origTz - R * cos((270+theta)*PI / 180);
			cout << "hi\n";
			//tx = origTx + (R * sin(theta*PI / 180));
			//tz = origTz - acc * sin(theta*PI / 180);
		}
		if (leftFlag) {
			cout << "hi2\n";
		//	tx = origTx + (R * sin(theta*PI / 180));
			tz = origTz - (R - R * cos((270 + theta)*PI / 180));
		}

		roty = origRot + theta;

		if (!leftFlag && tz <= Cz) {
			cout << "hi3\n";
			leftFlag = true;
			rightFlag = false;
			origTz -= R;
		}
		cout << "R\t" << tz << "\t" << theta << "\t" << tz << "\t" << tx << " " << (R * sin(theta*PI / 180)) << endl;
		*/
		rightCycle();
	}
	else if (tx <= C2x) {
		/*
		if (firstTime < 0) {
			firstTime = 1;
			origTx = -200;
			origTz = -270;
			origRot = 0;
		}
		else {
			firstTime += 1;
		}
		float omega = acc / R;
		float theta = omega * firstTime;

		tx = origTx - (R * sin(theta*PI / 180));

		if (leftFlag) {
			tz = origTz + R * cos((270 + theta)*PI / 180);
		}
		if (rightFlag) {
			tz = origTz + (R - R * cos(theta*PI / 180));
		}
		
		if (!rightFlag && tz >= -260) {
			rightFlag = true;
			leftFlag = false;
			origTz += R;
		}

		roty = origRot + theta;
		cout << "L\t" << tz << "\t" << theta << endl;
		*/
		leftCycle();
	}
	else{
		if (firstTime) {
			firstTime = false;
		}
		if (rightFlag) {
			tx += acc;//*time;
			cout << "A" << endl;
			if (tx > C1x) {
				rightCycle();
			}
			cout << tx << endl;
		}
		if (leftFlag) {
			tx -= acc;//*time;
			cout << "B" << endl;
			if (tx < C2x) {
				leftCycle();
			}
			cout << tx << endl;

		}
	}
	glPopMatrix();

	//time += 1;

	/*
	glPushMatrix();
=======
	glPopMatrix();
	*/



	torus(50, 20, 30);

	
	//Track
	/*Track(40, -25, 35);
	Track(30, 20, 30);*/


	/*Light*/
	/*glPushMatrix();
>>>>>>> origin/master
	glTranslatef(0, 0, -100);
	//glRotatef(45, 0, 1, 0);
	//glRotatef(rotx, 180, 0, 0);
	//glScalef(0.25f, 0.25f, 0.25f);
	glColor3f(0.749020, 0.749020, 0.749020);                            // Set drawing colour
	DisplayLight(light);
	glPopMatrix();
<<<<<<< HEAD
	*/
	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(C1x, 0, Cz);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(C2x, 0, Cz);
	glEnd();
	glPopMatrix();
	
=======
	glPushMatrix();
>>>>>>> origin/master

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
		
		/*
		glPushMatrix();
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

		glEnd();*/
		crash("CRASH!", 0.05f);
		//glPopMatrix();
	}
<<<<<<< HEAD

=======
	glPopMatrix();*/
>>>>>>> origin/master
	

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
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}


void Idle()
{
	glutPostRedisplay();
}


void Setup()  // TOUCH IT !! 
{
	ReadFileCar(&car);
	ReadFileLight(&light);

	//Parameter handling
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_POINT_SMOOTH);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
}

static void torus(float inner, float outer, unsigned int pts)
{
	glPushMatrix();
	glTranslatef(-30, -40, -200);

	glColor3f(1.0, 0, 0);
	glRotatef(90, 1.0, 0, 0);
	glRotatef(90, 0, 0, 1.0);

	glBegin(GL_QUAD_STRIP);
	
	for (unsigned int i = 0; i <= pts/2; ++i)
	{
		float angle = (i / (float)pts) * 3.14159f * 2.0f;
		glVertex2f(inner * cos(angle), inner * sin(angle));
		glVertex2f(outer * cos(angle), outer * sin(angle));
	}
	glEnd();

	glPopMatrix();

}

void Track(int x, int y, int z) {
	/*Track*/

	glPushMatrix();
	glTranslatef(0, 0, -75);
	glColor3f(0, 0, 1.0);
	glPointSize(5);
	glBegin(GL_POLYGON);

	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z-10);
	glVertex3f(-x, y, z-10);

	glEnd();

	glPopMatrix();
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
		/*
		glVertex3f(md.vertices.at(it->vtx[0] - 1).x + md.normals.at(it->vn[0] - 1).x*5.0,
				   md.vertices.at(it->vtx[0] - 1).y + md.normals.at(it->vn[0] - 1).y*5.0,
				   md.vertices.at(it->vtx[0] - 1).z + md.normals.at(it->vn[0] - 1).z*5.0);
		glVertex3f(md.vertices.at(it->vtx[1] - 1).x + md.normals.at(it->vn[1] - 1).x*5.0,
				   md.vertices.at(it->vtx[1] - 1).y + md.normals.at(it->vn[1] - 1).y*5.0,
				   md.vertices.at(it->vtx[1] - 1).z + md.normals.at(it->vn[1] - 1).z*5.0);
		glVertex3f(md.vertices.at(it->vtx[2] - 1).x + md.normals.at(it->vn[2] - 1).x*5.0,
				   md.vertices.at(it->vtx[2] - 1).y + md.normals.at(it->vn[2] - 1).y*5.0,
				   md.vertices.at(it->vtx[2] - 1).z + md.normals.at(it->vn[2] - 1).z*5.0);
		*/
		
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
		//Left();
		break;
	case 'd':
	case 'D':
		//Right();
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
	/*
	switch (key) {
	case GLUT_KEY_UP:
		Up();
		break;
	case GLUT_KEY_DOWN:
		Down();
		break;
	case GLUT_KEY_LEFT:
		//Left();
		break;
	case GLUT_KEY_RIGHT:
		//Right();
		break;
	}
	*/

	float fraction = 1.0f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}


void Up() {

	acc += 0.1;
	//tx -= acc;
	//acc += 0.1f;
	//float alpha = 0.0f;
	//float start = tx;
	//float end = tx - acc;
	//do {
	//	alpha += 0.025f;
	//	tx = (1 - alpha)*start + alpha * end;
	//} while (alpha < 1.0);
}


void Down() {
	acc -= 0.1f;
}


//void Left() {
//	roty += 5;
//}

//void Right() {
//	roty -= 5;
//}


void rightCycle() {
	if (!firstTime) {
		firstTime = true;
		origTx = C1x;
		origTz = Cz+R;
		origRot = 180;
		if (tx > origTx) {
			//theta = ((tx - origTx) * 360) / (2 * PI*R);
			theta = (tx - origTx) / R;
		}
		else{
			omega = acc / R;
			theta = omega;
		}
	}
	else {
		omega = acc / R;
		theta += omega;
	}

	//tx = origTx + (R * sin(theta*PI / 180));
	tx = origTx + (R * sin(theta));

	
	/*
	if (rightFlag) {
		tz = origTz - R * cos((270 + theta)*PI / 180);
		cout << "hi\n";
		//tx = origTx + (R * sin(theta*PI / 180));
		//tz = origTz - acc * sin(theta*PI / 180);
	}
	if (leftFlag) {
		cout << "hi2\n";
		//	tx = origTx + (R * sin(theta*PI / 180));
		tz = origTz - (R - R * cos((270 + theta)*PI / 180));
	}
	*/
	//if (!leftFlag && theta>90) {
	if (!leftFlag && theta>PI/2) {
		cout << "hi3\n";
		leftFlag = true;
		rightFlag = false;
		origTz = Cz;
	}

	//if (theta <= 90) {
	if (theta <= PI/2) {
		tz = origTz - R * cos(3*PI/2 + theta);
		cout << "hi\n";
		//tx = origTx + (R * sin(theta*PI / 180));
		//tz = origTz - acc * sin(theta*PI / 180);
	}
	else{
		cout << "hi2\n";
		//	tx = origTx + (R * sin(theta*PI / 180));
		//tz = origTz - (R - R * cos((270 + theta)*PI / 180));
		tz = origTz - (R - R * cos(3*PI/2 + theta));
	}

	//roty = origRot + theta;
	roty = origRot + theta*180/PI;

	if (roty > 360) {
		tx = C1x - ((2 * PI*R*(roty - 360)) / 360);
		tz = Cz - R;
		roty = 0;
	}

	cout << "R\t" << theta << "\t" << roty << "\t" << tz << "\t" << tx << endl;
}


void leftCycle() {
	if (!firstTime) {
		firstTime = true;
		origTx = C2x;
		origTz = Cz-R;
		origRot = 0;
		if (tx < origTx) {
			//theta = ((origTx - tx) * 360) / (2 * PI*R);
			theta = (origTx - tx)/R;
		}
		else {
			omega = acc / R;
			theta = omega;
		}
	}
	else{
		omega = acc / R;
		theta += omega;
	}

	//if (!rightFlag && theta > 90) {
	if (!rightFlag && theta > PI/2) {
		rightFlag = true;
		leftFlag = false;
		cout << "DID IT !!!\n";
		origTz = Cz;
	}

	//tx = origTx - (R * sin(theta*PI / 180));
	tx = origTx - (R * sin(theta));

	/*
	if (theta <= 90) {
		tz = origTz + R * cos((270 + theta)*PI / 180);
	}
	else {
		tz = origTz + (R - R * cos((270 + theta)*PI / 180));
	}
	*/

	if (theta <= PI/2) {
		tz = origTz + R * cos(3*PI/2 + theta);
	}
	else {
		tz = origTz + (R - R * cos(3*PI/2 + theta));
	}

	

	//roty = origRot + theta;
	
	roty = origRot + theta*180/PI;

	if (roty > 180) {
		tx = C2x + ((2 * PI*R*(roty - 180)) / 360);
		tz = Cz + R;
		roty = 180;
	}
	cout << "L\t" << theta << "\t" << Cz << "\t" << tz << "\t" << tx << endl;
}


void crash(const char *str, float size)
{
	glPushMatrix();
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

	glPushMatrix();
	glTranslatef(-10.5, -2.0, 0.0);
	glScalef(size, size, size);
	glColor3f(1.0, 1.0, 0.0);

	for (int i = 0; i<strlen(str); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();

	glPopMatrix();

}