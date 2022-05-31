
//Incluimos los ficheros de cabecera necesarios
#include "commonstuff.h"
#include "Shape.h"

//Definimos include guards
#ifndef __ANIMALITOS_H__
#define __ANIMALITOS_H__

class Animalito : public Shape {
private:
	int status;
public:
	Animalito(float , float, float, float);
	void draw();
	float getSize();
};

#endif