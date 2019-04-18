#include "GrilaCarteziana.h"

GrilaCarteziana::GrilaCarteziana(const string& file_name)
{
	int x, y;
	auto index = 0;

	ifstream infile(file_name);
	infile >> this->number_peaks_;

	while (infile >> x >> y && number_peaks_ > 0)
	{
		poligon_coord_.add_element(index++, element_type(x, y));
		number_peaks_--;
	}

	infile.close();
	poligon_coord_.display_elements();
}

auto GrilaCarteziana::draw_grid(const float numar, const float dist) -> void
{
	this->number_ = numar;
	this->dist_ = dist;
	this->number_cells_ = numar / 2;
	this->dist_margin_ = 1 - (number_cells_ / (number_cells_ + dist_));
	const auto start_x_point = -1 + dist_margin_;
	const auto end_x_point = 1 - dist_margin_;
	
	glLineWidth(1.0);
	glColor3f(0.1,0.1,0.1);

	auto i = -number_cells_;
	auto set_row_size_counter = 0;
		float common_y_point = 0;
	float prev_y_value = 0;

	// draw rows
	while(true)
	{
		if(i > number_cells_) break;

		prev_y_value = common_y_point;
		common_y_point = static_cast<float>(i / (number_cells_ + dist_));

        glBegin(GL_LINES); 
			glVertex2f(start_x_point, common_y_point);
			glVertex2f(end_x_point, common_y_point);
		glEnd();

		if(set_row_size_counter == 2)
		{
			this->size_row_ = fabsf(prev_y_value - common_y_point);
		}

		i++;
		set_row_size_counter++;
	}
 
	i = -number_cells_;
 
	// draw coloumns
	while(true)
	{
		if(i > number_cells_) break;
 
		const auto common_x_point = static_cast<float>(i / (number_cells_ + dist_));
 
        glBegin(GL_LINES); 
			glVertex2f(common_x_point, end_x_point);
			glVertex2f(common_x_point, start_x_point);
		glEnd();  
 
		i++;
	}
}

auto GrilaCarteziana::draw_round_point(const int point_x, const int point_y, const string& color) const -> void
{
	glColor3f(0.1, 0.1, 0.1);
	if(color == "red") glColor3f(1, 0.1, 0.1);
	if(color == "gray") glColor3f(0.2,0.2,0.2);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	const auto margin_distant_err = 2 - dist_margin_ * 2;
	const auto point_x_position = -number_cells_ + point_x;
	const auto point_y_position = -number_cells_ + point_y;

	glBegin(GL_POLYGON);
		float angle = 0;
		const float radius = 0.35;
		while(true)
		{
			if(angle >= 2*PI) break;

			const auto output_x = (point_x_position + radius * sin(angle)) / (number_cells_ + dist_);
			const auto output_y = (point_y_position + radius * cos(angle)) / (number_cells_ + dist_);
			glVertex2f(output_x, output_y);

			angle += 0.01;
		}
	glEnd();
}

auto GrilaCarteziana::draw_square_point(const int point_x, const int point_y, const int point_size, const string& color) const -> void
{
	glPointSize(point_size);
	glColor3f(0.1, 0.1, 0.1);

	if(color == "red")
	{
		glColor3f(1, 0.1, 0.1);
	}

	const auto point_x_position = point_x + -number_cells_;
	const auto point_y_position = point_y + -number_cells_;

	const auto output_x = static_cast<float>(point_x_position / (number_cells_ + dist_));
	const auto output_y = static_cast<float>(point_y_position / (number_cells_ + dist_));
	
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

			const auto output_x = static_cast<float>(point_x_position / (number_cells_ + dist_));
			const auto output_y = static_cast<float>(point_y_position / (number_cells_ + dist_));
			    
			glVertex2f(output_x, output_y);
	    }
	glEnd();
}

auto GrilaCarteziana::draw_ellipse(const int origin_x, const int origin_y, const int radius_x, const int radius_y) const -> void
{
	const auto margin_distant_err = dist_margin_ * 2;

	const auto cells_left_x = size_row_ * (number_ - radius_x);
	const auto cells_left_y = size_row_ * (number_ - radius_y);

	const auto calculated_x_radius = 2 - margin_distant_err - cells_left_x;
	const auto calculated_y_radius = 2 - margin_distant_err - cells_left_y;


	const auto origin_x_position = -number_cells_ + origin_x;
	const auto origin_y_position = -number_cells_ + origin_y;

	const auto output_origin_x = static_cast<float>(origin_x_position / (number_cells_ + dist_));
	const auto output_origin_y = static_cast<float>(origin_y_position / (number_cells_ + dist_));

	glLineWidth(3.0);
	glColor3f(1, 0.1, 0.1);

	glBegin(GL_LINE_LOOP);
		for(auto index = 0; index < 360; index++)
		{
			const float rad = index * DEG2RAD;

			const auto output_x = cos(rad)*calculated_x_radius + output_origin_x;
			const auto output_y = sin(rad)*calculated_y_radius + output_origin_y;
			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void GrilaCarteziana::draw_ellipse_origin(const int radius) const
{
	const auto cells_left = size_row_ * (number_ - radius);
	const auto margin_distant_err = dist_margin_ * 2;
	const auto calculated_radius = 2 - margin_distant_err - cells_left;

	glLineWidth(3.0);
	glColor3f(1, 0.1, 0.1);

	glBegin(GL_LINE_LOOP);
		for(auto index = 0; index < 360; index++)
		{
			const float rad = index * DEG2RAD;

			const auto output_x = cos(rad)*calculated_radius - (1 - dist_margin_);
			const auto output_y = sin(rad)*calculated_radius - (1 - dist_margin_);
			
			glVertex2f(output_x, output_y);
		}
	glEnd();
	draw_square_point(0, 0, 4, "red");

	
}

auto GrilaCarteziana::draw_pixels() -> void
{
	auto x_points = poligon_coord_.get_x_points();
	auto y_points = poligon_coord_.get_y_points();
	
	for(auto i = 0; i <= number_; i++)
		for(auto j = 0; j <= number_; j++)
		{
			const auto in_polygon = inside_the_polygon(poligon_coord_.get_pairs(), x_points, y_points, i, j);
			if(!in_polygon) continue;
			draw_round_point(i, j, "");
		}
}


auto GrilaCarteziana::inside_the_polygon(const int pol_lines, vector<float>& pol_X_lines, vector<float>& pol_Y_lines, float point_x, float point_y) -> int
{
  int i, j, paritate = 0;
  for (i = 0, j = pol_lines-1; i < pol_lines; j = i++) {
    if ( ((pol_Y_lines[i] > point_y) != (pol_Y_lines[j] > point_y)) &&
	 (point_x < (pol_X_lines[j] - pol_X_lines[i]) * (point_y - pol_Y_lines[i]) / (pol_Y_lines[j] - pol_Y_lines[i]) + pol_X_lines[i]) )
       paritate = !paritate;
  }
  return paritate;
}


auto GrilaCarteziana::intensificare_pixel(int x, int y, double length) -> void 
{
	draw_square_point(x, y, (round(fabs (length))) * 2, "red");
}


void GrilaCarteziana::umplereElipsa(int x0, int y0, int a, int b)
{
	int xi = 0, x = 0, y = -b;
	double fxpyp = 0.0;
	double deltaV, deltaNV, deltaN;
	draw_round_point(x + x0, y + y0, "gray");
	// regiunea 1
	while (a*a*(y - 0.5) < b*b*(x + 1))
	{
		deltaV = b * b * (-2 * x + 1);
		deltaNV = b * b * (-2 * x + 1) + a * a * (2 * y + 1);
		if (fxpyp + deltaV <= 0.0)
		{
			// V este in interior
			fxpyp += deltaV;
			x--;
		}
		else if (fxpyp + deltaNV <= 0.0)
		{
			// NV este in interior
			fxpyp += deltaNV;
			x--;y++;
		}
		for(auto i = x + x0; i <= x0; i++)
		{
			draw_round_point(i, y + y0, "gray");
		}

	}
	// regiunea 2
	while (y < 0)
	{
		deltaNV = b * b * (-2 * x + 1) + a * a * (2 * y + 1);
		deltaN = a * a*(2 * y + 1);
		if (fxpyp + deltaNV <= 0.0)
		{
			// NV este in interior
			fxpyp += deltaNV;
			x--;y++;
		}
		else
		{
			// N este in interior
			fxpyp += deltaN;
			y++;
		}
		for (auto i = x + x0; i <= x0; i++)
		{
			draw_round_point(i, y + y0, "gray");
		}
	}
}

void GrilaCarteziana::afisareCerc4(int R)
{
	int x = R, y = 0;
	int d = 1 - R;
	int dN = 3, dNV = -2 * R + 5;
	pixels(x, y, 2);
	while (y < x)
	{
		if (d < 0)
		{
			d += dN;
			dN += 2;
			dNV += 2;
		}
		else
		{
			d += dNV;
			dN += 2;
			dNV += 4;
			x--;
		}
		y++;
		pixels(x, y, 2);
	}
}

void GrilaCarteziana::pixels(int x, int y, int length)
{
	length = length / 2;
	for(auto i = -length; i <= length; i++)
	{
		draw_round_point(x + i, y, "gray");
	}
}


GrilaCarteziana::GrilaCarteziana()
{
}

GrilaCarteziana::~GrilaCarteziana()
= default;