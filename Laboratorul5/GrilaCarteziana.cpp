#include "GrilaCarteziana.h"
ifstream infile("poligon.txt");


GrilaCarteziana::GrilaCarteziana()
{
	this->numar_ = def;
}

GrilaCarteziana::GrilaCarteziana(const int numar)
{
	this->numar_ = numar;
	this->number_cells_ = numar / 2;
	int x, y;
	auto index = 0;

	infile >> this->numar_varfuri;

	while (infile >> x >> y && numar_varfuri > 0)
	{
		poligon_coord_.add_element(index++, element_type(x, y));
		numar_varfuri--;
	}

	infile.close();
	poligon_coord_.display_elements();
}

auto GrilaCarteziana::draw_grid() const -> void
{
	glLineWidth(1.0);
	float i = -number_cells_;
	float distMargin = 1 - (number_cells_ / (number_cells_ + DIST));
	const float startXPoint = -1 + distMargin;
	const float endXPoint = 1 - distMargin;
	
	glColor3f(0.1,0.1,0.1);

	// draw rows
	while(true)
	{
		if(i > number_cells_) break;

		const auto commonYPoint = static_cast<float>(i / (number_cells_ + DIST));

        glBegin(GL_LINES); 
			glVertex2f(startXPoint, commonYPoint);
			glVertex2f(endXPoint, commonYPoint);
		glEnd();  

		i++;
	}

	i = -number_cells_;

	// draw coloumns
	while(true)
	{
		if(i > number_cells_) break;
 
		const auto commonXPoint = static_cast<float>(i / (number_cells_ + DIST));
 
        glBegin(GL_LINES); 
			glVertex2f(commonXPoint, endXPoint);
			glVertex2f(commonXPoint, startXPoint);
		glEnd();  
 
		i++;
	}
}

auto GrilaCarteziana::draw_round_point(int point_x, int point_y) const -> void
{
	glColor3f(0.1, 0.1, 0.1);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	const auto point_x_position = -number_cells_ + point_x;
	const auto point_y_position = -number_cells_ + point_y;

	glBegin(GL_POLYGON);
		for (auto k = 0; k <= 360; k += 5)
		{
			glVertex2f( (point_x_position * (2 - 2*DIST) + sin(k) * (DIST/2)) / (number_cells_ + DIST), 
						(point_y_position * (2 - 2*DIST) + cos(k) * (DIST/2)) / (number_cells_ + DIST));
		}
	glEnd();
}

auto GrilaCarteziana::draw_square_point(int point_x, int point_y) const -> void
{
	glPointSize(14);
	glColor3f(0.1, 0.1, 0.1);

	const auto point_x_position = -number_cells_ + point_x;
	const auto point_y_position = -number_cells_ + point_y;

	auto output_x = static_cast<float>(point_x_position / (number_cells_ + DIST));
	auto output_y = static_cast<float>(point_y_position / (number_cells_ + DIST));
	
	glBegin(GL_POINTS);
		glVertex2f(output_x, output_y);
	glEnd();
}

auto GrilaCarteziana::draw_poligon() -> void
{
	auto points_list = poligon_coord_.get_element_type_list();

	glLineWidth(3.0);
	glColor3f(1, 0.1, 0.1);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glBegin(GL_POLYGON);
	    for (auto& it : points_list)
	    {
			const auto point_x_position = -number_cells_ + it.first;
			const auto point_y_position = -number_cells_ + it.second;

			const auto output_x = static_cast<float>(point_x_position / (number_cells_ + DIST));
			const auto output_y = static_cast<float>(point_y_position / (number_cells_ + DIST));
			    
			glVertex2f(output_x, output_y);
	    }
	glEnd();
}

auto GrilaCarteziana::draw_pixels() -> void
{
	auto x_points = poligon_coord_.get_x_points();
	auto y_points = poligon_coord_.get_y_points();
	
	for(auto i=0; i<= numar_; i++)
		for(auto j=0; j<= numar_; j++)
		{
			const auto in_pol = inside_the_polygon(poligon_coord_.get_pairs(), x_points, y_points, i, j);
			if(!in_pol) continue;
			draw_round_point(i, j);
		}
}


// WIP
// nvert: Number of vertices in the polygon. Whether to repeat the first vertex at the end has been discussed in the article referred above.
// vertx, verty: Arrays containing the x- and y-coordinates of the polygon's vertices.
// testx, testy: X- and y-coordinate of the test point.
// c: 0 means even and 1 means odd
// https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html


auto GrilaCarteziana::inside_the_polygon(const int pol_lines, vector<float>& pol_X_lines, vector<float>& pol_Y_lines, float point_x, float point_y) -> int
{
  int i, j, c = 0;
  for (i = 0, j = pol_lines-1; i < pol_lines; j = i++) {
    if ( ((pol_Y_lines[i] > point_y) != (pol_Y_lines[j] > point_y)) &&
	 (point_x < (pol_X_lines[j] - pol_X_lines[i]) * (point_y - pol_Y_lines[i]) / (pol_Y_lines[j] - pol_Y_lines[i]) + pol_X_lines[i]) )
       c = !c;
  }
  return c;
}

GrilaCarteziana::~GrilaCarteziana()
= default;
