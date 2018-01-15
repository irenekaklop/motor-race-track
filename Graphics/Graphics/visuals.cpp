#include "visuals.h"
#include "time.h"

model compCar;
model userCar;
model light;

int compCarId;
int userCarId;
int lightId;

carMovement compCarM;
carMovement userCarM;

bool fullscreen = false;

bool crashFlag = false;

float R1 = 12.5;
float R2 = 7.5;
float C1x = 15;
float C2x = -15;
float Cz = -30;
float height = -7.5;

float acc = 0.1f;
float v_max = 1.25f;

time_t current, crashTime = -1;

using namespace std;


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
	(200, 25)(�)			(D)(-50, 25)
	(200,-25)(�)			(C)(-50,-25)

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
	
	current = time(NULL);

	glPushMatrix();
	glTranslatef(userCarM.tx, height, userCarM.tz);
	glRotatef(userCarM.roty, 0, 90, 0);
	glRotatef(userCarM.rotx, 180, 0, 0);
	glScalef(0.01f, 0.01, 0.01);
	glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	//DisplayCar(userCar);
	glCallList(userCarId);
	
	RenderUserCar();

	glPopMatrix();


	glPushMatrix();
	glTranslatef(compCarM.tx, height, compCarM.tz);
	glRotatef(compCarM.roty, 0, 90, 0);
	glRotatef(compCarM.rotx, 180, 0, 0);
	glScalef(0.01f, 0.01f, 0.01f);
	glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	//DisplayCar(compCar);
	glCallList(compCarId);

	RenderCompCar();

	glPopMatrix();
	


	/*Light*/
	glPushMatrix();

	glTranslatef(0, 0, -100);
	//glRotatef(45, 0, 1, 0);
	//glRotatef(rotx, 180, 0, 0);
	//glScalef(0.25f, 0.25f, 0.25f);
	glColor3f(0.749020, 0.749020, 0.749020);                            // Set drawing colour
	//DisplayLight(light);
	glCallList(lightId);
	glPopMatrix();

	
	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(C1x, height, Cz);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(C2x, height, Cz);
	glEnd();
	glPopMatrix();
	

	if (crashFlag) {
		crash("CRASH!", 0.05f);
		if (crashTime < 0) {
			crashTime = current;
			
			compCarM.acc = 0;
			userCarM.acc = 0;

			compCarM.leftFlag = false;
			compCarM.rightFlag = true;
			compCarM.firstTime = false;
			compCarM.tx = 0.0;
			compCarM.tz = Cz + R2;
			compCarM.rotx = 270.0;
			compCarM.roty = 180;
			compCarM.origRot = 180;

			userCarM.leftFlag = false;
			userCarM.rightFlag = true;
			userCarM.firstTime = false;
			userCarM.tx = 0.0;
			userCarM.tz = Cz + R1;
			userCarM.rotx = 270.0;
			userCarM.roty = 180;
			userCarM.origRot = 180;

			cout << difftime(crashTime, current) << endl;
		}
		cout << difftime(current, crashTime) << endl;
		if (crashFlag && difftime(current, crashTime) >= 3) {
			cout << "HERE\n";
			crashFlag = false;
			crashTime = -1;
			compCarM.acc = 0.25;
			userCarM.acc = 0.25;
		}
	}
	

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
	glutPostRedisplay();
}


void Setup()  // TOUCH IT !! 
{
	ReadFileCar(&userCar);
	ReadFileCar(&compCar);
	ReadFileLight(&light);
	userCarId = DisplayCar(userCar);
	compCarId = DisplayCar(compCar);
	lightId = DisplayLight(light);

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


	compCarM.leftFlag = false;
	compCarM.rightFlag = true;
	compCarM.firstTime = false;
	compCarM.tx = 0.0;
	compCarM.tz = Cz + R2;
	compCarM.acc = 0.25;
	compCarM.rotx = 270.0;
	compCarM.roty = 180;
	compCarM.origRot = 180;

	userCarM.leftFlag = false;
	userCarM.rightFlag = true;
	userCarM.firstTime = false;
	userCarM.tx = 0.0;
	userCarM.tz = Cz + R1;
	userCarM.acc = 0.25;
	userCarM.rotx = 270.0;
	userCarM.roty = 180;
	userCarM.origRot = 180;
	
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


int DisplayCar(model md)
{
	int id;
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);

	glBegin(GL_TRIANGLES);
	
	for (vector<face>::iterator it = md.faces.begin(); it != md.faces.end(); it++) {

		glVertex3f(md.vertices.at(it->vtx[0] - 1).x, md.vertices.at(it->vtx[0] - 1).y, md.vertices.at(it->vtx[0] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[1] - 1).x, md.vertices.at(it->vtx[1] - 1).y, md.vertices.at(it->vtx[1] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[2] - 1).x, md.vertices.at(it->vtx[2] - 1).y, md.vertices.at(it->vtx[2] - 1).z);
	}

	glEnd();

	glEndList();

	return id;
}


int DisplayLight(model md) {
	int id;
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);

	glBegin(GL_TRIANGLES);

	for (vector<face>::iterator it = md.faces.begin(); it != md.faces.end(); it++) {	
		glNormal3f(md.normals.at(it->vn[0] - 1).x, md.normals.at(it->vn[0] - 1).y, md.normals.at(it->vn[0] - 1).z);
		glNormal3f(md.normals.at(it->vn[1] - 1).x, md.normals.at(it->vn[1] - 1).y, md.normals.at(it->vn[1] - 1).z);
		glNormal3f(md.normals.at(it->vn[2] - 1).x, md.normals.at(it->vn[2] - 1).y, md.normals.at(it->vn[2] - 1).z);

		glVertex3f(md.vertices.at(it->vtx[0] - 1).x, md.vertices.at(it->vtx[0] - 1).y, md.vertices.at(it->vtx[0] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[1] - 1).x, md.vertices.at(it->vtx[1] - 1).y, md.vertices.at(it->vtx[1] - 1).z);
		glVertex3f(md.vertices.at(it->vtx[2] - 1).x, md.vertices.at(it->vtx[2] - 1).y, md.vertices.at(it->vtx[2] - 1).z);
	}

	glEnd();

	glEndList();

	return id;
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
	cout << "KEY\n";
	switch (key) {
	case GLUT_KEY_UP:
		Up();
		break;
	case GLUT_KEY_DOWN:
		Down();
		break;
	default:
		break;
	}	
}


void Up() {
	if(!crashFlag) userCarM.acc += acc;
}


void Down() {
	if (!crashFlag)	userCarM.acc -= acc;
	if (userCarM.acc < 0) userCarM.acc = 0;
}


void rightCycle(carMovement* car, float R) {
	if (car->acc >= v_max) {
		crashFlag = true;
		return;
	}

	if (!car->firstTime) {
		car->firstTime = true;
		car->origTx = C1x;
		car->origTz = Cz+R;
		car->origRot = 180;
		if (car->tx > car->origTx) {
			car->theta = (car->tx - car->origTx) / R;
		}
		else{
			car->omega = car->acc / R;
			car->theta = car->omega;
		}
	}
	else {
		car->omega = car->acc / R;
		car->theta += car->omega;
	}

	car->tx = car->origTx + (R * sin(car->theta));

	if (!car->leftFlag && car->theta>PI/2) {
		car->leftFlag = true;
		car->rightFlag = false;
		car->origTz = Cz;
	}

	if (car->theta <= PI/2) {
		car->tz = car->origTz - R * cos(3*PI/2 + car->theta);
	}
	else{
		car->tz = car->origTz - (R - R * cos(3*PI/2 + car->theta));
	}

	car->roty = car->origRot + car->theta*180/PI;

	if (car->roty > 360) {
		car->tx = C1x - ((2 * PI*R*(car->roty - 360)) / 360);
		car->tz = Cz - R;
		car->roty = 0;
	}

}


void leftCycle(carMovement *car, float R) {
	if (car->acc >= v_max) {
		crashFlag = true;
		return;
	}


	if (!car->firstTime) {
		car->firstTime = true;
		car->origTx = C2x;
		car->origTz = Cz-R;
		car->origRot = 0;
		if (car->tx < car->origTx) {
			car->theta = (car->origTx - car->tx)/R;
		}
		else {
			car->omega = car->acc / R;
			car->theta = car->omega;
		}
	}
	else{
		car->omega = car->acc / R;
		car->theta += car->omega;
	}

	if (!car->rightFlag && car->theta > PI/2) {
		car->rightFlag = true;
		car->leftFlag = false;
		car->origTz = Cz;
	}

	car->tx = car->origTx - (R * sin(car->theta));

	if (car->theta <= PI/2) {
		car->tz = car->origTz + R * cos(3*PI/2 + car->theta);
	}
	else {
		car->tz = car->origTz + (R - R * cos(3*PI/2 + car->theta));
	}
	
	car->roty = car->origRot + car->theta*180/PI;

	if (car->roty > 180) {
		car->tx = C2x + ((2 * PI*R*(car->roty - 180)) / 360);
		car->tz = Cz + R;
		car->roty = 180;
	}
}


void RenderUserCar() {
	if (userCarM.tx >= C1x) {
		rightCycle(&userCarM, R1);
	}
	else if (userCarM.tx <= C2x) {
		leftCycle(&userCarM, R1);
	}
	else {
		if (userCarM.firstTime) {
			userCarM.firstTime = false;
		}
		if (userCarM.rightFlag) {
			userCarM.tx += userCarM.acc;
			if (userCarM.tx > C1x) {
				rightCycle(&userCarM, R1);
			}
		}
		if (userCarM.leftFlag) {
			userCarM.tx -= userCarM.acc;
			if (userCarM.tx < C2x) {
				leftCycle(&userCarM, R1);
			}

		}
	}
}


void RenderCompCar() {
	//to stop with traffic light

	//
	
	if (compCarM.tx >= C1x) {
		rightCycle(&compCarM, R2);
	}
	else if (compCarM.tx <= C2x) {
		leftCycle(&compCarM, R2);
	}
	else {
		if (compCarM.firstTime) {
			compCarM.firstTime = false;
		}
		if (compCarM.rightFlag) {
			compCarM.tx += compCarM.acc;
			if (compCarM.tx > C1x) {
				rightCycle(&compCarM, R2);
			}
		}
		if (compCarM.leftFlag) {
			compCarM.tx -= compCarM.acc;
			if (compCarM.tx < C2x) {
				leftCycle(&compCarM, R2);
			}

		}
	}
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

}

void Gatemove(float Ypos) {

		/*BRIDGE- PINK �pen
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