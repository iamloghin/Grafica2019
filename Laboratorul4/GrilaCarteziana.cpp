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
	const float negXPoint = -numar / (numar + DIST);
	const float pozXPoint = numar / (numar + DIST);

    glLineWidth(3.0);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES); 
		glVertex2f(negXPoint,pozXPoint);
		glVertex2f(pozXPoint, 3 / (numar + DIST));
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(negXPoint,negXPoint);
		glVertex2f(pozXPoint,(-1/(numar + DIST)));
	glEnd();

	SegmentDreapta3 (-numar,numar, numar,(3),2);
	SegmentDreapta3 (-numar, -numar, numar, -1, 0);
}

void GrilaCarteziana::drawGrid()
{  
	float i;
	const float endXPoint = -numar / (numar + DIST);
	const float startXPoint = numar / (numar + DIST);
	
	glColor3f(0.1,0.1,0.1);

	for(auto i = -numar; i <= numar; i++)
	{
		const auto commonYPoint = static_cast<float>(i / (numar + DIST));

        glBegin(GL_LINES); 
			glVertex2f(startXPoint, commonYPoint);
			glVertex2f(endXPoint, commonYPoint);
		glEnd();  
	}

	for(auto i= -numar; i <= numar; i++)
	{
		const auto commonXPoint = static_cast<float>(i / (numar + DIST));

		glBegin(GL_LINES); 
			glVertex2f(commonXPoint,endXPoint);
			glVertex2f(commonXPoint,startXPoint);
		glEnd();
	}
}

void GrilaCarteziana::writePixel(int i, int j)
{
	glColor3f(0.1,0.1,0.1); 
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_POLYGON);
		for (auto k = 0; k <= 360; k += 5)
		{
			glVertex2f( (i * (2 - 2*DIST) + sin(k) * (DIST/2)) / (numar+DIST), 
						(j * (2 - 2*DIST) + cos(k) * (DIST/2)) / (numar+DIST));
		}
	glEnd();
}

void GrilaCarteziana::pixels(int x, int y, int t, int dis)
{
	t /= 2;
	if(dis == 0)
	{
		for(auto i = -t; i <= t; i++)
		{
			writePixel(x + i, y);
		}
	}
	for(auto i = -t; i <= t; i++)
	{
		writePixel(x, y + i);
	}
}

void GrilaCarteziana::SegmentDreapta3(int fromX, int fromY, int toX, int toY, unsigned int bold=0)
{
	auto dx = toX - fromX, dy = toY - fromY;
	auto x = fromX, y = fromY;
	
	if(fromY < toY) {
		auto d = 2*dy - dx, 
			 dE = 2*dy,
			 dNE = 2*(dy-dx);

		pixels(x, y,bold,1);

		while(x < toX) {
			if(d <= 0)
			{
				d += dE;
				x++;
			}
			else
			{
				d +=dNE;
				x++;
				y++;
			}
			pixels(x, y,bold, 1);
		}
	}	
	else {		
		if(toY < fromY) {
			auto dy = fromY - toY, 
				 d = 2*dy - dx, 
				 dE = 2*dy, 
				 dNE = 2*(dy-dx);

			pixels(x, y,bold,1);
			while(x < toX) {
				if(d <= 0)
				{
					d += dE;
					x++;
				}
				else
				{
					d +=dNE;
					x++;
					y--;
				}
				pixels(x, y,bold,1);
			}
		}
	}
}

GrilaCarteziana::~GrilaCarteziana()
= default;
