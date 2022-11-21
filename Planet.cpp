
#include "Planet.h"

inline  bool Planet::wiremode = false;

	 Planet::Planet() {
		x = 0;
		y = 0;
		z = 0;
		angle = 0;
		//draw(0, 0, 0, 0);
	}
	 Planet::Planet(float X, float Y, float Z, float SIZE, float OFFSET) {
		x = X;
		y = Y;
		z = Z;
		offset = OFFSET;
		size = SIZE;
		angle = rand() % 360 + 1;
		//draw(size, r, g, b);
	}
	 void Planet::draw(float SIZE, float r, float g, float b ) {

		glPushMatrix();
		glRotatef((angle+10) *(1/size) *50, 0,1,0);
		//glColor3f (r, g, b);
		//color
		float color[] = { r, g, b, 0.25f };
		//float specularColor[] = {1.0, 0.0f, 0.0f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, color);
		glMateriali(GL_FRONT, GL_SHININESS, 120);
		//endcolor

		//glutSolidSphere(size, 360, 100);
		if (wiremode) {
			glColor3f(r, g, b);
			glutWireSphere(size, 50, 10);
		}
		else {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			glMaterialfv(GL_FRONT, GL_SPECULAR, color);
			glMateriali(GL_FRONT, GL_SHININESS, 120);
			glutSolidSphere(size, 360, 100);

		}
		glPopMatrix();

	}
	 void Planet::rotate(Planet& orbital, axis My_Axis) {
		x = orbital.size * 3.5+offset;
		z = orbital.size * 3.5 + offset;
		glRotatef(angle, My_Axis.x, My_Axis.y, My_Axis.z);
		glTranslatef(x, 0, z);
		//glTranslatef(-orbital.x, 0, -orbital.z);
	}


