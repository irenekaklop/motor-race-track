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

bool startingState = true;
bool pausedState = false;

bool fullscreen = false;

bool crashFlag = false;

bool redFlag = false;
bool orangeFlag = false;
bool greenFlag = true;

float R1 = 13;
float R2 = 8;
float C1x = 15;
float C2x = -15;
//float Cz = -34;
float Cz = -40;
float height = -7.5;
float offset = 2.5;

float dt = 1.0f;
float acc = 0.1f;
float v_max = 1.25f;
float v_start = 0.25f;
float paused_vcomp, paused_vuser;

float move_x = 0.0f, move_y = 0.0f;
float angle = 0;

time_t current, crashTime, redlight_t, greenlight_t = -1, orangelight_t= -1, pausedlight_t;
clock_t redlight, current_cl = -1, pausedlight;

// Values that control the material properties.

GLfloat SphShininess = 10;   // Specular exponent for the spheres.
GLfloat SphAmbDiff[6][4] = {      // The ambient/diffuse colors of the six spheres 
   {1.0, 0.0, 0.0, 1.0},         // Red
   {0.5, 0.5, 0.0, 1.0},         // Yellow
   {0.0, 0.5, 0.0, 1.0},         // Green
   {0.0, 0.5, 0.5, 1.0},         // Cyan
   {0.0, 0.0, 0.5, 1.0},         // Blue
   {0.5, 0.0, 0.5, 1.0}         // Magenta
};
GLfloat SphSpecular[4] = { 1, 1, 1, 1.0 };

// Lighting values
//GLfloat ambientLight[4] = {0, 100.0, 100.0, 1.0};
GLfloat Lt0amb[4] = {0.3, 0.3, 0.3, 1.0};
GLfloat Lt0diff[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat Lt0spec[4] = {0, 0, Cz, 1.0};


int minTime = 1, maxTime = 15;

using namespace std;


void Render()
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(0.0, 0.0, 3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	current = time(NULL);
	current_cl = clock();

	/*Light*/
	//glLoadIdentity();

	glPushMatrix();
	glTranslatef(-3, height, Cz - R1 - offset - 2);
	glScalef(0.25f, 0.25f, 0.25f);
	glColor3f(0.749020, 0.749020, 0.749020);                            // Set drawing colour
	glCallList(lightId);
	glPopMatrix();

	if (!startingState && !pausedState) {
		light_controller();
	}
	else {
		BlackLight();
	}
	
	// Draw a light sphere
	/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, SphAmbDiff[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SphSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SphShininess);*/
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SphShininess);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SphSpecular);
	
	//Set position

	//cout << compCarM.tx << endl;

	/* UPPER STRAIGHT TRACK	*/

	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);											//make the colour blue (lower)
	glBegin(GL_QUADS);									
	glVertex3f(C1x, height,	 Cz-R2+offset);										
	glVertex3f(C1x, height,  Cz-R1-offset);
	glVertex3f(-5.0, height, Cz-R1-offset);
	glVertex3f(-5.0, height, Cz-R2+offset);
	glEnd();
	
	
	
	/* DOWN STRAIGHT TRACK
	(-200, -75)(A)	 (D)(200, -75)
	(-200, -125)(B)	 (C)(200, -125)
	*/
	
	glColor3f(0.0, 0.0, 1.0);											//make the colour blue (lower)
	glBegin(GL_QUADS);
	glVertex3f(C1x, height, Cz + R2 - offset);
	glVertex3f(C1x, height, Cz + R1 + offset);
	glVertex3f(C2x, height, Cz + R1 + offset);
	glVertex3f(C2x, height, Cz + R2 - offset);
	glEnd();
	
	/*WHITE BOXES at down straight track*/

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0, height, Cz+R1+offset-1);
	glVertex3f(-5.0, height, Cz + R1 + offset - 2);
	glVertex3f(-6.0, height, Cz + R1 + offset - 2);
	glVertex3f(-6.0, height, Cz + R1 + offset - 1);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0, height, Cz + R1 + offset - 3);
	glVertex3f(-5.0, height, Cz + R1 + offset - 4);
	glVertex3f(-6.0, height, Cz + R1 + offset - 4);
	glVertex3f(-6.0, height, Cz + R1 + offset - 3);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0, height, Cz + R1 + offset - 5);
	glVertex3f(-5.0, height, Cz + R1 + offset - 6);
	glVertex3f(-6.0, height, Cz + R1 + offset - 6);
	glVertex3f(-6.0, height, Cz + R1 + offset - 5);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0, height, Cz + R1 + offset - 7);
	glVertex3f(-5.0, height, Cz + R1 + offset - 8);
	glVertex3f(-6.0, height, Cz + R1 + offset - 8);
	glVertex3f(-6.0, height, Cz + R1 + offset - 7);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0, height, Cz + R1 + offset - 9);
	glVertex3f(-5.0, height, Cz + R1 + offset - 10);
	glVertex3f(-6.0, height, Cz + R1 + offset - 10);
	glVertex3f(-6.0, height, Cz + R1 + offset - 9);
	glEnd();

	glPopMatrix();

	//Semi circle right
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	//glLoadIdentity();

	glTranslatef(C1x, height, Cz);
	glRotatef(90, 90, 0, 0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluPartialDisk(quad, R2 - offset, R1 + offset, 100.0, 3, 0.0, 180.0);
	glPopMatrix();

	//Semi circle left
	//glLoadIdentity();
	glPushMatrix();

	glTranslatef(C2x, height, Cz);
	glRotatef(-180.0, 0, 0, 1);
	glRotatef(90, 90, 0, 0);

	glColor3f(0.0, 0.0, 1.0);
	gluPartialDisk(quad, R2 - offset, R1 + offset, 100.0, 3, 0.0, 180.0);

	glPopMatrix();

	/*BRIDGE- PINK Closed
	*/
	//glLoadIdentity();
	glColor3f(1.0, 0.24, 0.75);
	glBegin(GL_POLYGON);
	glVertex3f(-5.0, height, Cz - R2 + offset);
	glVertex3f(-5.0, height, Cz - R1 - offset);
	glVertex3f(C2x + move_x, height + move_y, Cz - R1 - offset);
	glVertex3f(C2x + move_x, height + move_y, Cz - R2 + offset);
	glEnd();

	if (redFlag && !pausedState) {
		Gatemove(redlight);
	}


	//glLoadIdentity();

	glPushMatrix();
	glTranslatef(userCarM.tx, height, userCarM.tz);
	//glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	glRotatef(userCarM.roty, 0, 90, 0);
	glRotatef(userCarM.rotx, 180, 0, 0);
	glScalef(0.01f, 0.01f, 0.01f);
	glColor3f(1.0, 1.0, 1.0);                            // Set drawing colour
	//DisplayCar(userCar);

	glCallList(userCarId);
	
	if (!pausedState) {
		RenderUserCar();
	}

	glPopMatrix();


	glPushMatrix();
	glTranslatef(compCarM.tx, height, compCarM.tz);
	glRotatef(compCarM.roty, 0, 90, 0);
	glRotatef(compCarM.rotx, 180, 0, 0);
	glScalef(0.01f, 0.01f, 0.01f);
	glColor3f(1.0, 0.6, 0.2);                            // Set drawing colour
	//DisplayCar(compCar);
	glCallList(compCarId);

	if (!pausedState) {
		RenderCompCar();
	}

	glPopMatrix();
	

	//glLoadIdentity();
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
		//cout << "CRASH!!!" << endl;
		if (crashTime < 0) {
			crashTime = current;

			compCarM.acc = 0;
			userCarM.acc = 0;

			compCarM.leftFlag = false;
			compCarM.rightFlag = true;
			compCarM.firstTime = false;
			compCarM.tx = -10.0;
			compCarM.tz = Cz + R2;
			compCarM.rotx = 270.0;
			compCarM.roty = 180;
			compCarM.origRot = 180;

			userCarM.leftFlag = false;
			userCarM.rightFlag = true;
			userCarM.firstTime = false;
			userCarM.tx = -10.0;
			userCarM.tz = Cz + R1;
			userCarM.rotx = 270.0;
			userCarM.roty = 180;
			userCarM.origRot = 180;

			//cout << difftime(crashTime, current) << endl;
		}
		//cout << difftime(current, crashTime) << endl;
		if (crashFlag && difftime(current, crashTime) >= 3) {
			//cout << "HERE\n";
			crashFlag = false;
			crashTime = -1;
			startingState = true;
			//compCarM.acc = v_start;
			//userCarM.acc = v_start;
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
	gluPerspective(45.0, aspect, 1.0, 500.0);
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
	srand(time(NULL));

	//Parameter handling
	glShadeModel(GL_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set global ambient light
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);   
	GLfloat light_position[] = { -50, 50.0, 50.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat diffuseLight[] = { 0.9, 0.9, 0.9, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	// Light 1 light values.  Its position is set in Render().
	//glLightfv(GL_LIGHT1, GL_POSITION, Lt0spec);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, Lt0amb);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, Lt0diff);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, SphAmbDiff[2]);

	
	//Set up light source
	glEnable(GL_LIGHTING);      // Enable lighting calculations
	glEnable(GL_LIGHT0);      // Turn on light #0.
	//glEnable(GL_LIGHT1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	compCarM.leftFlag = false;
	compCarM.rightFlag = true;
	compCarM.firstTime = false;
	compCarM.tx = -10.0;
	compCarM.tz = Cz + R2;
	compCarM.acc = 0.0f;
	compCarM.rotx = 270.0;
	compCarM.roty = 180;
	compCarM.origRot = 180;

	userCarM.leftFlag = false;
	userCarM.rightFlag = true;
	userCarM.firstTime = false;
	userCarM.tx = -10.0;
	userCarM.tz = Cz + R1;
	userCarM.acc = 0.0f;
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
		float i, j, k;

		/*
		i = ((md.vertices.at(it->vtx[0] - 1).y - md.vertices.at(it->vtx[1] - 1).y)*(md.vertices.at(it->vtx[1] - 1).z - md.vertices.at(it->vtx[2] - 1).z)
			- (md.vertices.at(it->vtx[1] - 1).y - md.vertices.at(it->vtx[2] - 1).y)*(md.vertices.at(it->vtx[0] - 1).z - md.vertices.at(it->vtx[1] - 1).z));
		j = -((md.vertices.at(it->vtx[0] - 1).x - md.vertices.at(it->vtx[1] - 1).x)*(md.vertices.at(it->vtx[1] - 1).z - md.vertices.at(it->vtx[2] - 1).z)
			- (md.vertices.at(it->vtx[1] - 1).x - md.vertices.at(it->vtx[2] - 1).x)*(md.vertices.at(it->vtx[0] - 1).z - md.vertices.at(it->vtx[1] - 1).z));
		k = ((md.vertices.at(it->vtx[0] - 1).x - md.vertices.at(it->vtx[1] - 1).x)*(md.vertices.at(it->vtx[1] - 1).y - md.vertices.at(it->vtx[2] - 1).y)
			- (md.vertices.at(it->vtx[1] - 1).x - md.vertices.at(it->vtx[2] - 1).x)*(md.vertices.at(it->vtx[0] - 1).y - md.vertices.at(it->vtx[1] - 1).y));
		*/

		/*
		i = ((md.vertices.at(it->vtx[1] - 1).y - md.vertices.at(it->vtx[0] - 1).y)*(md.vertices.at(it->vtx[2] - 1).z - md.vertices.at(it->vtx[1] - 1).z)
			- (md.vertices.at(it->vtx[2] - 1).y - md.vertices.at(it->vtx[1] - 1).y)*(md.vertices.at(it->vtx[1] - 1).z - md.vertices.at(it->vtx[0] - 1).z));
		j = -((md.vertices.at(it->vtx[1] - 1).x - md.vertices.at(it->vtx[0] - 1).x)*(md.vertices.at(it->vtx[2] - 1).z - md.vertices.at(it->vtx[1] - 1).z)
			- (md.vertices.at(it->vtx[2] - 1).x - md.vertices.at(it->vtx[1] - 1).x)*( md.vertices.at(it->vtx[1] - 1).z - md.vertices.at(it->vtx[0] - 1).z));
		k = ((md.vertices.at(it->vtx[1] - 1).x - md.vertices.at(it->vtx[0] - 1).x)*(md.vertices.at(it->vtx[2] - 1).y - md.vertices.at(it->vtx[1] - 1).y)
			- ( md.vertices.at(it->vtx[2] - 1).x - md.vertices.at(it->vtx[1] - 1).x)*(md.vertices.at(it->vtx[1] - 1).y) - md.vertices.at(it->vtx[0] - 1).y);
		*/

		/*
		i = ((md.vertices.at(it->vtx[1] - 1).y - md.vertices.at(it->vtx[0] - 1).y)*(md.vertices.at(it->vtx[2] - 1).z - md.vertices.at(it->vtx[0] - 1).z)
			- (md.vertices.at(it->vtx[2] - 1).y - md.vertices.at(it->vtx[0] - 1).y)*(md.vertices.at(it->vtx[1] - 1).z - md.vertices.at(it->vtx[0] - 1).z));
		j = -((md.vertices.at(it->vtx[1] - 1).x - md.vertices.at(it->vtx[0] - 1).x)*(md.vertices.at(it->vtx[2] - 1).z - md.vertices.at(it->vtx[0] - 1).z)
			- (md.vertices.at(it->vtx[2] - 1).x - md.vertices.at(it->vtx[0] - 1).x)*(md.vertices.at(it->vtx[1] - 1).z - md.vertices.at(it->vtx[0] - 1).z));
		k = ((md.vertices.at(it->vtx[1] - 1).x - md.vertices.at(it->vtx[0] - 1).x)*(md.vertices.at(it->vtx[2] - 1).y - md.vertices.at(it->vtx[0] - 1).y)
			- (md.vertices.at(it->vtx[2] - 1).x - md.vertices.at(it->vtx[0] - 1).x)*(md.vertices.at(it->vtx[1] - 1).y) - md.vertices.at(it->vtx[0] - 1).y);
		*/

		/*
		i = ((md.vertices.at(it->vtx[0] - 1).y - md.vertices.at(it->vtx[1] - 1).y)*(md.vertices.at(it->vtx[0] - 1).z - md.vertices.at(it->vtx[2] - 1).z)
			- (md.vertices.at(it->vtx[0] - 1).y - md.vertices.at(it->vtx[2] - 1).y)*(md.vertices.at(it->vtx[0] - 1).z - md.vertices.at(it->vtx[1] - 1).z));
		j = -((md.vertices.at(it->vtx[0] - 1).x - md.vertices.at(it->vtx[1] - 1).x)*(md.vertices.at(it->vtx[0] - 1).z - md.vertices.at(it->vtx[2] - 1).z)
			- (md.vertices.at(it->vtx[0] - 1).x - md.vertices.at(it->vtx[2] - 1).x)*(md.vertices.at(it->vtx[0] - 1).z - md.vertices.at(it->vtx[1] - 1).z));
		k = ((md.vertices.at(it->vtx[0] - 1).x - md.vertices.at(it->vtx[1] - 1).x)*(md.vertices.at(it->vtx[0] - 1).y - md.vertices.at(it->vtx[2] - 1).y)
			- (md.vertices.at(it->vtx[0] - 1).x - md.vertices.at(it->vtx[2] - 1).x)*(md.vertices.at(it->vtx[0] - 1).y - md.vertices.at(it->vtx[1] - 1).y));
		*/

		//float magnitude = sqrtf(powf(i,2)+ powf(j, 2)+ powf(k, 2));
		
		//glNormal3f(i/magnitude, j / magnitude, k / magnitude);

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
		if(!startingState && !pausedState) Up();
		break;
	case 's': 
	case 'S':
		if (!startingState && !pausedState) Down();
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
	case 'r':
	case 'R':
		startingState = true;

		redFlag = false;
		orangeFlag = false;
		greenFlag = true;

		move_x = 0.0f;
		move_y = 0.0f;

		greenlight_t = -1;
		orangelight_t = -1;
		redlight_t = -1;

		compCarM.leftFlag = false;
		compCarM.rightFlag = true;
		compCarM.firstTime = false;
		compCarM.tx = -10.0;
		compCarM.tz = Cz + R2;
		compCarM.acc = 0;
		compCarM.rotx = 270.0;
		compCarM.roty = 180;
		compCarM.origRot = 180;

		userCarM.leftFlag = false;
		userCarM.rightFlag = true;
		userCarM.firstTime = false;
		userCarM.tx = -10.0;
		userCarM.tz = Cz + R1;
		userCarM.acc = 0;
		userCarM.rotx = 270.0;
		userCarM.roty = 180;
		userCarM.origRot = 180;
		break;
	case 'p':
	case 'P':
		pausedState = !pausedState;
		if (pausedState) {
			pausedlight_t = current;
			pausedlight = current_cl;
		}
		if (!pausedState) {
			if (greenFlag) {
				greenlight_t += current - pausedlight_t;
			}
			else if (orangeFlag) {
				orangelight_t += current - pausedlight_t;
			}
			else if (redFlag) {
				redlight_t += current - pausedlight_t;
				redlight += current_cl - pausedlight;
			}
		}
		break;
	case SPACEBAR:
		if (startingState) {
			compCarM.acc = v_start;
			userCarM.acc = v_start;
			startingState = false;
		}
		break;
	default: break;
	}

	glutPostRedisplay();

}


void Arrows(int key, int x, int y) {
	//cout << "KEY\n";
	switch (key) {
	case GLUT_KEY_PAGE_UP:
		dt += 0.1f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		if(dt > 0.1f) dt -= 0.1f;
		break;
	case GLUT_KEY_UP:
		if (!startingState && !pausedState) Up();
		break;
	case GLUT_KEY_DOWN:
		if (!startingState && !pausedState) Down();
		break;
	default:
		break;
	}	
}


void Up() {
	if(!crashFlag) userCarM.acc += acc;
}

bool isSet = false;
void Down() {
	if (!crashFlag)	userCarM.acc -= acc;
	if (userCarM.acc < 0) userCarM.acc = 0;
	if (redFlag) isSet = true;
}


void rightCycle(carMovement* car, float R) {
	if (car->acc >= v_max) {
		crashFlag = true;
		return;
	}

	if (!car->firstTime) {
		car->firstTime = true;
		car->origTx = C1x;
		car->origTz = Cz;
		car->origRot = 180;
		if (car->tx > car->origTx) {
			car->theta = (car->tx - car->origTx) / R;
		}
		else{
			car->omega = car->acc / R;
			car->theta = car->omega*dt;
		}
	}
	else {
		car->omega = car->acc / R;
		car->theta += car->omega*dt;
	}

	car->tx = car->origTx + (R * sin(car->theta));

	if (!car->leftFlag && car->theta>PI/2) {
		car->leftFlag = true;
		car->rightFlag = false;
		car->origTz = Cz;
	}

	//float temp = sqrtf(pow(R, 2) - pow((car->tx - C1x), 2));

	if (car->theta <= PI/2) {
		car->tz = car->origTz + R * cos(car->theta);
		//if (temp + Cz > -temp + Cz) car->tz = temp + Cz;
		//else  car->tz = -temp + Cz;
	}
	else{
		car->tz = car->origTz + R* cos(car->theta);
		//if (temp + Cz > -temp + Cz) car->tz = -temp + Cz;
		//else  car->tz = temp + Cz;
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
		car->origTz = Cz;
		car->origRot = 0;
		if (car->tx < car->origTx) {
			car->theta = (car->origTx - car->tx)/R;
		}
		else {
			car->omega = car->acc / R;
			car->theta = car->omega*dt;
		}
	}
	else{
		car->omega = car->acc / R;
		car->theta += car->omega*dt;
	}

	if (!car->rightFlag && car->theta > PI/2) {
		car->rightFlag = true;
		car->leftFlag = false;
		car->origTz = Cz;
	}

	car->tx = car->origTx - (R * sin(car->theta));

	if (car->theta <= PI/2) {
		car->tz = car->origTz - R * cos(car->theta);
	}
	else {
		car->tz = car->origTz - R * cos(car->theta);
	}
	
	car->roty = car->origRot + car->theta*180/PI;

	if (car->roty > 180) {
		car->tx = C2x + ((2 * PI*R*(car->roty - 180)) / 360);
		car->tz = Cz + R;
		car->roty = 180;
	}
}


bool isStopped = false;
void RenderUserCar() {
	if (redFlag) {
		float temp = userCarM.tx;
		if (temp - userCarM.acc*dt <= -1 && temp + userCarM.acc*dt > C2x && userCarM.tz < Cz && isSet) {
			if (userCarM.tx != -1) {
				//cout << "STOPPED\n";
				isStopped = true;
				userCarM.acc = 0;
				userCarM.tx = -1;
				return;
			}
			//cout << "HERE!!!!!!!!!!!!!!!!!~~~~~~~~~~~~~\n";
		}
		if ( temp - userCarM.acc*dt < -1 && temp + userCarM.acc*dt > C2x && userCarM.tz < Cz && !isSet) {
			crashFlag = true;
			userCarM.acc = 0;
			//cout << "CRASH FLAG\n"<<endl;
		}
		
	}

	if (isSet) {
		if (!(userCarM.tx >= -1 && userCarM.tx < 2.5 && userCarM.tz < Cz)) {
			isSet = false;
			//cout << "not valid\n"<<endl;
		}
		if (isStopped && greenFlag) {
			isSet = false;
			isStopped = false;
			userCarM.acc = v_start;
			cout << "start again!" << isSet << "\t" << isStopped << "\t" << greenFlag << endl;
		}
	}

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
			userCarM.tx += userCarM.acc*dt;
			if (userCarM.tx > C1x) {
				rightCycle(&userCarM, R1);
			}
		}
		if (userCarM.leftFlag) {
			userCarM.tx -= userCarM.acc*dt;
			if (userCarM.tx < C2x) {
				leftCycle(&userCarM, R1);
			}

		}
	}
}

void RenderCompCar() {
	if (redFlag) {
		//cout << "in " << redFlag << endl;
		float temp = compCarM.tx;
		if (temp - compCarM.acc*dt < -1 && temp + compCarM.acc*dt > C2x && compCarM.tz < Cz) {
			if (compCarM.tx != -1) {
				compCarM.tx = -1;
			}
			//cout << "HERE!!!!!!!!!!!!!!!!!~~~~~~~~~~~~~\n";

		}
	}
	//cout << "out " << redFlag << endl;

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
			compCarM.tx += compCarM.acc*dt;
			if (compCarM.tx > C1x) {
				rightCycle(&compCarM, R2);
			}
		}
		if (compCarM.leftFlag) {
			compCarM.tx -= compCarM.acc*dt;
			if (compCarM.tx < C2x) {
				leftCycle(&compCarM, R2);
			}

		}
	}
	//cout << compCarM.tx << "\t" << compCarM.tz << "\t" << compCarM.theta*180/PI << endl;

}


void crash(const char *str, float size)
{
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -75);
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

void Gatemove(time_t time) {

	double diffticks = current_cl - redlight;
	double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);

	//cout << diffms << endl;

	if (redFlag && diffms*dt <= 2000 ) { //bridge opens
		float perc = diffms*dt / 2000;
		angle = perc * (PI / 6);
		move_x = 7.5 - 7.5 * cos(angle);
		move_y = 7.5 * sin(angle);
	}
	
	if (redFlag && diffms*dt >= 4000) {
		redFlag = false;
		greenFlag = true;
		move_x = 0;
		move_y = 0;
		diffms = 0;
		redlight = -1;
		greenlight_t = -1;
		redlight_t = -1;
	}

	if (redFlag && diffms*dt > 2000 && diffms*dt < 4000) { //bridge closes
		float perc = (2000+(2000-diffms*dt)) / 2000;
		angle = perc * (PI / 6);
		move_x = 7.5 - 7.5 * cos(angle);
		move_y = 7.5 * sin(angle);
	}

}

time_t randDuration;
void light_controller() {
	glPushMatrix();
	if (greenFlag) {
		glColor3f(0, 1, 0);
		if (greenlight_t == -1) {
			greenlight_t = current;
			randDuration = rand() % (maxTime - minTime + 1) + minTime;
		}
		if (difftime(current, greenlight_t)*dt >= randDuration) {
			greenFlag = false;
			orangeFlag = true;
			greenlight_t = -1;
			orangelight_t = -1;
			glColor3f(0, 0, 0);
		}
		// << "green" << endl;
	}
	else {
		glColor3f(0, 0, 0);
	}
	//Green sphere
	glTranslatef(-3, 0, Cz-R1-offset);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPushMatrix();
	if (orangeFlag) {
		glColor3f(1, 0.68, 0);
		if (orangelight_t == -1) {
			orangelight_t = current;
		}
		if (difftime(current, orangelight_t)*dt >= 2) {
			orangeFlag = false;
			redFlag = true;
			redlight_t = -1;
			orangelight_t = -1;
			glColor3f(0, 0, 0);
		}
		//cout << "orange" << endl;
	}
	else {
		glColor3f(0, 0, 0);
	}
	//Orange sphere
	glTranslatef(-3, 1, Cz - R1 - offset);
	glutSolidSphere(0.3, 25, 25);
	glPopMatrix();

	glPushMatrix();
	if (redFlag) {
		glColor3f(1, 0, 0);
		if (redlight_t == -1) {
			redlight = current_cl;
			redlight_t = current;
		}
		
		cout << "Red" << endl;
	}
	else {
		glColor3f(0, 0, 0);
	}
	glTranslatef(-3, 2, Cz - R1 - offset);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();
}

void BlackLight() {
	if (redFlag) {
		glColor3f(1, 0, 0);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glPushMatrix();
	glTranslatef(-3, 2, Cz - R1 - offset);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();
	//Orange
	if (orangeFlag) {
		glColor3f(1, 0.68, 0);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glPushMatrix();
	glTranslatef(-3, 1, Cz - R1 - offset);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();
	//Green
	if (greenFlag) {
		glColor3f(0, 1, 0);
	}
	else {
		glColor3f(0, 0, 0);
	}
	glPushMatrix();
	glTranslatef(-3, 0, Cz - R1 - offset);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();
}