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
		int number_cells_;
	    int numar_varfuri;
		MyListPairs poligon_coord_;
		static int pnpoly(const int nvert, vector<float>& vertx, vector<float>& verty, float testx, float testy);
	public:
		GrilaCarteziana();
		~GrilaCarteziana();
		explicit GrilaCarteziana(const int numar);
		void draw_grid() const;
		void draw_poligon();
		void draw_pixels();
		void draw_point(int point_x, int point_y) const;
};

