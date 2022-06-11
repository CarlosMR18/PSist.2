/*******************************************************/
/*              Cabecera de equipo                     */
/*******************************************************/


//Archivos de cabecera
#include "ObjectsList.h"

//Implementación de los metodos de la  clase.

ObjectsList::ObjectsList() {

	//Variables locales de trabajo
	Shape* Bola = NULL;

	//Inicializamos los atributos
	n = 0;
	head = NULL;
	theMan = NULL;

	//Añadimos los objetos iniciales
		//Añadimos el avatar
	theMan = new Man; //El hombre se coloca en el punto (0, 9 , 0)
	add(theMan);
		//Añadimos los proyectiles
	for (int i = 0; i < NUMBALLS; i++)
	{
		Bola = new Ball(255); //EL parametro t es el color
		add(Bola);
	}
	
}

ObjectsList::~ObjectsList() {

	//Variables locales
	pnodo tmp, p;

	//Inicializamos
	p = head;
	tmp = p->next;

	//Recorremos y eliminamos 
	while ( (tmp=p->next) != NULL) {
		free(p->figura);
		free(p);
		p = tmp;
	}
	free(tmp);
}

void ObjectsList::move() {

	//Variables locales de trabajo
	pnodo tmp = NULL;
	tmp = head;

	//Enviamos menasajes a todos los objetos de la lista
	while(tmp)
	{
		tmp->figura->move(); //Enviamos mensajes a los objetos
		tmp = tmp->next; //Saltamos al siguiente nodo
	}

}

void ObjectsList::draw() {

	//Variables locales de trabajo
	pnodo tmp = NULL;
	tmp = head;

	//Enviamos mensajes a todos los objetos de la lista
	while (tmp)
	{
		tmp->figura->draw(); //Enviamos mensajes a los objetos 
		tmp = tmp->next; //Saltamos al siguiente nodo
	}
	
}

void ObjectsList::add(Shape* s) {
	pnodo tmp, p;
	p = head;
	tmp = new nodo;
	tmp->obj = s;
	tmp->next = NULL;
	if (head == NULL) {
		head = tmp;
	}
	else {
		//Si contiene elementos
		while (p->next != NULL) p = p->next;
		p->next = tmp;
	}
}

/*void ObjectsList::add(Shape* s) {

	//Variables auxiliares
	pnodo tmp = NULL; //Puntero a nodo que recorre la lista
	pnodo p = (nodo*)malloc(sizeof(nodo)); //Nodo que adjunto a la lista

	//Inicilizamos las variable
	if (n) {
		tmp = head;
		//Incializo el nodo que adjuntamos
		p->figura = s;
		p->next = NULL;

		//Buscamos el final de la lista
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = p; //Enlazamos
		n++; //Sumamos uno al contador de objetos
	}
	else {
		head = p;
		//Inicializo el nod que adjuntamos
		p->figura = s;
		p->next = NULL;
	}

}*/

void ObjectsList::remove(Shape* s) {
	//La lista es recorrida en busca de un nodo cuyo obj = s
	// Encontrado: eliminarlo y reenlaza la lista
	// No encontrado: sale bucle
	pnodo p = head;
	pnodo nextNode = p->next;
	if (p && nextNode) {
		while ((nextNode->obj != s) && nextNode->next) {
			p = nextNode;
			nextNode = nextNode->next;
		}

		if (nextNode->obj == s) {
			p->next = nextNode->next;
			delete nextNode;
			n--;
		}

		else if (p->obj == s) {
			delete p;
			head = NULL;
		}
	}
}

/*
void ObjectsList::remove(Shape* s) {

	//Variables auxiliares
	pnodo tmp, p;

	//Inicializamos
	p = head;
	tmp = p->next;

	//Primer elemento
	if (p->figura == s)
	{
		head = tmp; //Posiciono nueva cabeza.
		free(p); //Libero anterior cabeza
	}

	//Caso general
	while ((tmp=p->next) != NULL)
	{
		if (tmp->figura == s)
		{
			p->next = tmp->next; //Saltamos nodo con figura a borrar
			//Liberamos el nodo
			free(tmp->figura);
			free(tmp);
		}
		else
		{
			p = p->next;
		}
	}

	n--; //Restamos uno al contador de objetos de la lista

}*/

void ObjectsList::reposition(Man* theMan) {

	//Variables auxiliares
	pnodo tmp = head;

	//Comprobamos y desplazamos los objetos cercanos al origen que no son hombre
	while (tmp->next != NULL)
	{
		//theMan->getSize() <= theMan + (*(tmp->figura));
	}
	
}

Man* ObjectsList::getMan() {

	//Devolvemnos atributo solicitado
	return theMan;

}

float ObjectsList::collisions(Bullet* theBullet, Man* theMan) {

	//Pendiente de Implementar
	return 0.0;
}

