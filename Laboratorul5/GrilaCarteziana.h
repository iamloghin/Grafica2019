#pragma once
#include "MyListPairs.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <complex>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include<cmath>
#include<cstdlib>

using namespace std; 

#define DIM 400
#define def 10
#define PI 4*atan(1.0)
#define DEG2RAD PI/180.0

class GrilaCarteziana
{
	private:
	    int number_peaks_{};
		float dist_{};
		float number_{};
		float number_cells_{};
		float size_row_{};
		float dist_margin_{};
		MyListPairs poligon_coord_;
		static int inside_the_polygon(const int nvert, vector<float>& vertx, vector<float>& verty, float testx, float testy);
    public:
		GrilaCarteziana();
	    ~GrilaCarteziana();
	    GrilaCarteziana(const string& file_name);
	    auto draw_grid(float numar, float dist) -> void;
		auto draw_round_point(int point_x, int point_y, const string& color) const -> void;
		auto draw_square_point(int point_x, int point_y, int point_size, const string& color) const -> void;
		void draw_poligon();
	    auto draw_ellipse(int origin_x, int origin_y, int radius_x, int radius_y) const -> void;
	    auto draw_ellipse_origin(int radius) const -> void;
		void draw_pixels();
		void intensificare_pixel(int x, int y, double length);
		void umplereElipsa(int x0, int y0, int a, int b);
		void afisareCerc4(int R);
		void pixels(int x, int y, int length);
};

