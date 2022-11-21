//Include necessary header files
#include "freeglut.h"
#include <cstdlib>
#include <cmath>
#include "Planet.h"
//Link with necessary libraries.
//This need to be written in at least one .cpp file in the project
//#pragma comment (lib, "freeglut.lib")


int x, y, z;
 //float Planet::angle=0;

//Callback function prototypes
void render(void);
void onKeyboard(unsigned char, int, int);
void update(void);

#define ESC_ASCII 27

int g_Win;	//Stores window identifier (handle) returned by glutCreateWindow
			//We need this handle to terminate the window

float g_X = 0.0f, g_Theta = 0.0f, g_Z = 50.0f, g_Y = 0.0f;
float b_X = 0.0f, b_Z = 0.0f,Distance_Unit=5.f;
bool birdseye = false,backward=false,pause=false;
float factor = 25,subFactor=25;
Planet list_of_plantes[] = { {3, 0, 3, 7, 0},
							{ 1, 0, 1, 0.5, 0},
							{-5, 0, -5, 2, 2},
							{0, 0, 0, 5, 15},
							{0, 0, 0, 4, 30} };
//Planet sun = Planet(3, 0, 3, 7, 0, 1, 1, 0);
//Planet moon = Planet(1, 0, 1, 0.5, 0, 1, 1, 1);
//Planet earth = Planet(-5, 0, -5, 2, 2, 0, 0.4, 0.3);
//Planet jupiter = Planet(0, 0, 0, 5, 15, 0.6, 0, 0.1);
//Planet uranus = Planet(0, 0, 0, 4, 30, 0, 0.8, 0.2);

int main(int argc, char** argv)
{


	//earth.angle = 10;
	//==========================================
	//Step 1: Initialize GLUT
	//==========================================
	glutInit(&argc, argv);

	//GLUT_RGBA: Red, Green, Blue, Alpha color representation.
	//GLUT_DOUBLE: Double buffering 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glClearDepth(0.0f);
	glDepthFunc(GL_LEQUAL);

	//Create Window
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(700, 300);
	//glutInitWindowPosition(100, 100);
	g_Win = glutCreateWindow("Solar System");
	glEnable(GL_DEPTH_TEST);
	//Set the color to be used to clear display buffer.
	//Try different values.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Set projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);

	//==========================================
	//Step 2: Register callback functions
	//==========================================
	glutDisplayFunc(render);
	glutKeyboardFunc(onKeyboard);
	glutIdleFunc(update);

	glEnable(GL_LIGHTING);	//Enable lighting
	glEnable(GL_SPECULAR);
	glEnable(GL_NORMALIZE);	//Enable auto-normalization of normal vectors
	float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);	//Zero global ambient component
	glShadeModel(GL_SMOOTH);



	//Setup material


	//==========================================
	//Step 3: Enter main loop
	//==========================================
	glutMainLoop();
	return 0;
}

//Callback function definitions
void render(void)
{
	//Clear display buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Draw something
	glLoadIdentity();
	if (!birdseye)
	{
		gluLookAt(g_X, 0, g_Z, g_X + (1 * sinf(g_Theta)), 0.0, g_Z + (1 * -cosf(g_Theta)), 0, 1.0f, 0);
	}
	else
	{
		gluLookAt(b_X, 200, b_Z, b_X, 0, b_Z, 0, 0.0f, 1.0f);
	}

	//Sunlight0
	float light0position[] = { 0.0f,0.0f,0.0f,1.0f };
	float light0Ambient[] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float light0Diffuse[] = { 1.0f, 1.0f, 1.0f };
	//float light0Specular[] = {1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glEnable(GL_LIGHT0);	//Enable light source 0

	//glRotatef(sun.angle + 30, 1, 0, 0);
	glPushMatrix();
	list_of_plantes[0].draw(list_of_plantes[0].size, 1, 1, 0);
	glPushMatrix();
	list_of_plantes[1].rotate(list_of_plantes[0]);
	list_of_plantes[1].draw(list_of_plantes[1].size, 0, 0.4, 0.3);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	list_of_plantes[2].rotate(list_of_plantes[1]);
	list_of_plantes[2].draw(list_of_plantes[2].size, 1, 1, 1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	list_of_plantes[3].rotate(list_of_plantes[0]);
	list_of_plantes[3].draw(list_of_plantes[3].size, 0.7, 0, 0.1);
	glPopMatrix();

	glPushMatrix();
	list_of_plantes[4].rotate(list_of_plantes[0]);
	list_of_plantes[4].draw(list_of_plantes[4].size, 0, 0.8, 0.2);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	list_of_plantes[3].rotate(list_of_plantes[0]);
	list_of_plantes[3].draw(list_of_plantes[3].size, 0.7, 0, 0.1);
	glPopMatrix();



	//Output color buffer to screen
	glutSwapBuffers();
}


void update(void) {

	
	if (!pause)
	{
	
		if (!backward)
		{
			for (int i=0; i< int(sizeof(list_of_plantes)/sizeof(Planet));i++)
			if (list_of_plantes[i].angle < 360)
			{
				list_of_plantes[i].angle += factor * 0.005f;
			}
			else
			{
				list_of_plantes[i].angle = 0;
			}
		}
		else {
			for (int i=0; i< int(sizeof(list_of_plantes) / sizeof(Planet));i++)
			if (list_of_plantes[i].angle > 0)
			{
				list_of_plantes[i].angle -= factor * 0.005f;
			}
			else
			{
				list_of_plantes[i].angle = 360;
			}
	
		}

	}

	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int)
{
	switch (key)
	{
	case 'a':
		if (!birdseye)
		{
			g_X += Distance_Unit;
		}
		else
		{
			b_X += Distance_Unit;
		}
		break;

	case 'e':
		g_Theta += 0.1f;
		break;

	case 'd':
		if (!birdseye)
		{
			g_X -= Distance_Unit;
		}
		else
		{
			b_X -= Distance_Unit;
		}
		break;

	case 'q':
		g_Theta -= 0.1f;
		break;

	case 'w':
		if (!birdseye)
		{
			g_Z -= Distance_Unit * cosf(g_Theta);
			g_X += Distance_Unit * sinf(g_Theta);
		}
		else
		{
			b_Z += Distance_Unit;
		}
		break;

	case 's':
		if (!birdseye)
		{
			g_Z += Distance_Unit * cosf(g_Theta);
			g_X -= Distance_Unit * sinf(g_Theta);
		}
		else
		{
			b_Z -= Distance_Unit;
		}
		break;
	case 'z':
		g_Y += 0.1f;
		break;

	case 'x':
		g_Y -= 0.1f;
		break;

	case 'b':
		if (birdseye)
		{
			birdseye = false;
		}
		else
		{
			birdseye = true;
		}
		break;

	case 'f':
		if (birdseye)
			b_X = 0.0f, b_Z = 0.0f;


		else
			g_X = 0.0f, g_Theta = 0.0f, g_Z = -50.0f, g_Y = 0.0f;
		break;



	case ' ':
		factor += 100;
		break;

	case 'v':
		if (factor-100> 0)
			factor -= 100;
		else
			factor = 25;
		break;
	case 'n':
		backward = (!backward);
		break;
	case 'm': 
		pause = (!pause);
		if (pause) {
			subFactor = factor;
			factor = 0;
		}
		else
			factor = subFactor;
		break;
	case 'i':
		list_of_plantes[0].wiremode = !list_of_plantes[0].wiremode;
		break;
	}
	glutPostRedisplay();
}