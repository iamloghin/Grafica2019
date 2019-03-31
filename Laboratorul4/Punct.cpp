#include "Punct.h"

Punct::Punct(int x, int y)
{
	this->X = x;
	this->Y = y;
}

int Punct::getX() const { return this->X;}
int Punct::getY() const { return this->Y;}

void Punct::setX(int x) { this->X = x;}
void Punct::setY(int y) { this->Y = y;}


Punct::~Punct()
= default;
