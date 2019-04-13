#include "GrilaCarteziana.h"
ifstream infile("poligon.txt");


GrilaCarteziana::GrilaCarteziana()
{
	this->numar_ = def;
}

GrilaCarteziana::GrilaCarteziana(const int numar)
{
	this->numar_ = numar;
	int numar_varfuri, x , y;
	auto index = 0;

	infile >> numar_varfuri;

	while (infile >> x >> y && numar_varfuri > 0)
	{
		poligon_coord_.add_element(index++,element_type(x, y));
		numar_varfuri--;
	}

	infile.close();
	poligon_coord_.display_elements();
}

auto GrilaCarteziana::draw_grid() const -> void
{  
	float i;
	const float endXPoint = -numar_ / (numar_ + DIST);
	const float startXPoint = numar_ / (numar_ + DIST);
	
	glColor3f(0.1,0.1,0.1);

	for(auto i = -numar_; i <= numar_; i++)
	{
		const auto commonYPoint = static_cast<float>(i / (numar_ + DIST));

        glBegin(GL_LINES); 
			glVertex2f(startXPoint, commonYPoint);
			glVertex2f(endXPoint, commonYPoint);
		glEnd();  
	}

	for(auto i= -numar_; i <= numar_; i++)
	{
		const auto commonXPoint = static_cast<float>(i / (numar_ + DIST));

		glBegin(GL_LINES); 
			glVertex2f(commonXPoint,endXPoint);
			glVertex2f(commonXPoint,startXPoint);
		glEnd();
	}
}

auto GrilaCarteziana::draw_poligon() -> void
{
	auto numar_varfuri = poligon_coord_.count();
	auto index = 0;

	glColor3f(0.1,0.1,0.1); 
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_POLYGON);
		while(numar_varfuri--)
		{
			const auto pair = poligon_coord_.get_element(index++);
			const auto point_x = static_cast<float>(pair->second.first);
			const auto point_y = static_cast<float>(pair->second.second);
			glVertex2f(point_x,point_y);
		}
	glEnd();
}

GrilaCarteziana::~GrilaCarteziana()
= default;
