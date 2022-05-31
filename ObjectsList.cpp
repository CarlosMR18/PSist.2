/*******************************************************/
/*              Cabecera de equipo                     */
/*******************************************************/


//Archivos de cabecera
#include "ObjectsList.h"

//Implementación de los metodos de la  clase.

ObjectsList::ObjectsList() {
	//Constructor
}

ObjectsList::~ObjectsList() {
	//Destructor
}

void ObjectsList::move() {
	//Implementar mover
}

void ObjectsList::draw() {
	//Implementar codigo
}

void ObjectsList::add(Shape* s) {
	//Pendiente de Implementar
}

void ObjectsList::remove(Shape* s) {
	//Pendiente de Implementar
}

void ObjectsList::reposition(Man* theMan) {
	//Pendiente de Implementar
}

Man* ObjectsList::getMan() {
	//Pendiente de Implementar
	Man theMan;

	return &theMan;
}

float ObjectsList::collisions(Bullet* theBullet, Man* theMan) {
	//Pendiente de Implementar
	return 0.0;
}

