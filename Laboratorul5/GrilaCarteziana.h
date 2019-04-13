#pragma once
#include "MyListPairs.h"
#include <GL/glut.h>
#include <complex>
#include <string>
#include <iostream>
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
		static int inside_the_polygon(const int nvert, vector<float>& vertx, vector<float>& verty, float testx, float testy);
	public:
		GrilaCarteziana();
		~GrilaCarteziana();
		void draw_grid(const int numar);
		void draw_poligon();
		static void draw_circle();
		void draw_pixels();
		void draw_round_point(int point_x, int point_y) const;
		void draw_square_point(int point_x, int point_y) const;
};

