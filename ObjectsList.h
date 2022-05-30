

//MARCO DEL GRUPO -falta co pletar-

//Inclusión de ficheros

#ifndef __SHIP_H__
	#include "Man.h"
#endif

#ifndef __BULLET_H__
	#include "Bullet.h"
#endif

#ifndef __SHAPE_H__
	#include "Shape.h"
#endif

//Declaramos constantes adcionales

//Declaramos clases y estructuras
	// Obtamos por una estructura ya que la seguridad no es una prioridad y es más facil de implementar y relacionar. 
	// Aun que podriamos trabajar con una clase amiga.
struct nodo {	
	Shape* anterior;
	Shape* nodo;
	Shape* siguiente;
};

class ObjectsList {
private:
	int n;
	nodo* head;
	Man* theMan;
public:
	ObjectsList();
	~ObjectsList();
	void move();
	void draw();
	Man* getMan();
	void add(Shape*);
	void remove(Shape*);
	void reposition(Man*);
	float collisions(Bullet*, Man*);
};
