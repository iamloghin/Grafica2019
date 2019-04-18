#include "GrilaCarteziana.h"

GrilaCarteziana::GrilaCarteziana()
{
	this->numar = def;
}

GrilaCarteziana::GrilaCarteziana(const int numar)
{
	this->numar = numar;
}

void GrilaCarteziana::drawLine()
{	
	const auto negXPoint = -1 + marginDistance;
	const auto pozXPoint = 1 - marginDistance;

    glLineWidth(4.0);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES); 
		glVertex2f(negXPoint,pozXPoint);
		glVertex2f(pozXPoint, 2.5 / (cellsNumber + DIST));
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(negXPoint,negXPoint);
		glVertex2f(pozXPoint,(-0.5 / (cellsNumber + DIST)));
	glEnd();

	SegmentDreapta3(0,numar, numar, 10,2);
	SegmentDreapta3(0, 0, numar, 7, 0);
}

void GrilaCarteziana::drawGrid()
{  
	cellsNumber = static_cast<float>(numar) / 2;
	marginDistance = 1 - (cellsNumber / (cellsNumber + DIST));
	const auto startXPoint = -1 + marginDistance;
	const auto endXPoint = 1 - marginDistance;

	glLineWidth(1.0);
	glColor3f(0.1,0.1,0.1);

	for(float i = -cellsNumber; i <= cellsNumber; i++)
	{
		const auto commonYPoint = static_cast<float>(i / (cellsNumber + DIST));

        glBegin(GL_LINES); 
			glVertex2f(startXPoint, commonYPoint);
			glVertex2f(endXPoint, commonYPoint);
		glEnd();  
	}

	for(auto i= -cellsNumber; i <= numar; i++)
	{
		const auto commonXPoint = static_cast<float>(i / (cellsNumber + DIST));
	
		glBegin(GL_LINES); 
			glVertex2f(commonXPoint,endXPoint);
			glVertex2f(commonXPoint,startXPoint);
		glEnd();
	}
}

void GrilaCarteziana::writePixel(int i, int j)
{
	glColor3f(0.3,0.3,0.3);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	const auto point_x_position = i + -cellsNumber;
	const auto point_y_position = j + -cellsNumber;

	glBegin(GL_POLYGON);
		for (float k = 0; k <= 360; k += 0.5)
		{
			const float radius = 0.35;
			const auto output_x = static_cast<float>(point_x_position + radius * sin(k)) / (cellsNumber + DIST);
			const auto output_y = static_cast<float>(point_y_position + radius * cos(k)) / (cellsNumber + DIST);
			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void GrilaCarteziana::pixels(int x, int y, int length)
{
	length = length / 2;
	for(auto i = -length; i <= length; i++)
	{
		writePixel(x,	y + i);
	}
}

void GrilaCarteziana::SegmentDreapta3(const int from_x, const int from_y, const int to_x, const int to_y, const unsigned int bold = 0)
{
	int dx = to_x - from_x;
	int x = from_x, y = from_y;
	float m = ((to_y - from_y) / static_cast<float>(to_x - from_x));
	int i = m > 0 ? 1: -1;
	int dy = i * (to_y - from_y);

	auto d = 2*dy - dx, 
		 dE = 2*dy,
		 dNE = 2*(dy-dx);

	pixels(x, y,bold);
	while(x < to_x) {
		if(d <= 0)
		{
			d += dE;
			x++;
		}
		else
		{
			d +=dNE;
			x++;
			y += i;
		}
		pixels(x, y,bold);
	}
}

GrilaCarteziana::~GrilaCarteziana()
= default;
