#include "Misil.h"

//constructor
Misil::Misil(int x, int y, int vy)
{
    this->x = x;
	this->y = y;
	this->vy = vy;
}

Misil::~Misil()
{
    //dtor
}

void Misil::avanzar(){
	y = y - vy;
}
