/*******************************************************/
/*              Cabecera de equipo                     */
/*******************************************************/

//Incluimos ficheros de cabecera
#include "commonstuff.h"
#include "Animalitos.h"

//Implementamos metodos
Animalito::Animalito(float px, float py, float vx, float vy) {
	
	status = 0;

	pos[X] = px;
	pos[Y] = py;
	pos[Z] = 0;

	rot[Z] = 0;
	rot[X] = -90;
	rot[Y] = 0;

	rspeed[X] = 0;
	rspeed[Y] = 0;
	rspeed[Z] = 0;

	tspeed[X] = vx;
	tspeed[Y] = vy;
	tspeed[Z] = 0;

	color[R] = 0.9;
	color[G] = 0.9;
	color[B] = 0.0;

	acc_ratio = 0.0;

}

void Animalito::draw() {
	predraw();

	//Draw body
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0, 0, 0);
	glutSolidSphere(0.3, 10, 10);
	//Draw Eye
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.5f);
	glTranslatef(0.1f, 0.46f, -0.15f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.2f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();
	//Draw lip
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(0.15f, 0.5f, 10, 2);

	postdraw();
}

float Animalito::getSize() {
	return (0.1);
}
