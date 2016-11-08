#include "Meteorito.h"

Meteorito::Meteorito(int x, int y, int level)
{
    this->x = x;
	this->y = y;

	this->vy = 4*level;
	this->vida = (unsigned)level;
}

Meteorito::~Meteorito()
{
    //dtor
}

void Meteorito::avanzar(){
	y = y + vy;
}
