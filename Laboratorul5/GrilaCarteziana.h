#pragma once
#include <GL/glut.h>
#include <complex>
#include <string>
#include <iostream>
#include "MyListPairs.h"
#include <fstream>
#include <map>
using namespace std; 

#define DIM 400
#define def 10
#define DIST 0.5

class GrilaCarteziana
{
	private:
		int numar_;
		MyListPairs poligon_coord_;
	public:
		GrilaCarteziana();
		~GrilaCarteziana();
		explicit GrilaCarteziana(const int numar);
		void draw_grid() const;
		void draw_poligon();
};

