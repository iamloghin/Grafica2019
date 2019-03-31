#include "Dreapta.h"
#include <complex>

Dreapta::Dreapta(int fromX, int fromY, int toX, int toY)
{
	this->fromX = fromX;
	this->fromY = fromY;
	this->toX = toX;
	this->toY = toY;
	dX = abs(toX - fromX);
	dY = abs(toY - fromY);
	a = dY;
	b = -dX;
	c = dX*fromY - dY*fromX;
	m = dY/(dX+0.0f);
	n = fromY - (dY*fromX)/(dX+0.0f);
}

float Dreapta::getM() const { return m; }
float Dreapta::getN() const { return n; }
int Dreapta::getDX() const { return dX; }
int Dreapta::getDY() const { return dY; }
int Dreapta::getA() const { return a; }
int Dreapta::getB() const { return b; }
int Dreapta::getC() const { return c; }

void Dreapta::setM(const float val) { m = val; }
void Dreapta::setN(const float val) { n = val; }
void Dreapta::setDX(const int val) { dX = val; }
void Dreapta::setDY(const int val) { dY = val; }
void Dreapta::setA(const int val) { a = val; }
void Dreapta::setB(const int val) { b = val; }
void Dreapta::setC(const int val) { c = val; }


Dreapta::~Dreapta()
= default;
