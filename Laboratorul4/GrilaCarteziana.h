#pragma once
#include <GL/glut.h>
#include <complex>

#define DIM 400
#define def 10
#define DIST 0.5

class GrilaCarteziana
{
	private:
		int numar;
	public:
		GrilaCarteziana();
		GrilaCarteziana(const int numar);
		void drawGrid();
		void drawLine();
		void pixels(int x, int y, int t, int dis);
		void writePixel(int x, int y);
		void SegmentDreapta3(int fromX, int fromY, int toX, int toY, unsigned int bold);
		~GrilaCarteziana();
};

