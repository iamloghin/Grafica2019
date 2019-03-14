#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <cstdlib>
#include <cmath>
#include <GL/glut.h>

#define DIM 300
const auto pi = 4 * atan(1);

unsigned char prev_key;

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void display1() {
	const auto max_x = 8 * pi;
	const auto max_y = exp(1.1);
	const auto ratio = 0.05;
	double x = 0;

	glBegin(GL_LINE_STRIP); 
		while(true) {
			if(x >= max_x) break;

			const auto output_x = x / max_x;
			const auto output_y = (fabs(sin(x)) * exp(-sin(x))) / max_y;

			x += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();
}

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display2() {
	double min_y;
	double a = 1, b = 2;
	const auto ratio = 0.05;

	auto max_x = a - b - 1;
	auto min_x = a + b + 1;
	auto max_y = min_y = 0;

	for (auto t = - pi/2 + ratio; t < pi / 2; t += ratio) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		max_x = (max_x < x1) ? x1 : max_x;
		min_x = (min_x > x1) ? x1 : min_x;

		x2 = a - b * cos(t);
		max_x = (max_x < x2) ? x2 : max_x;
		min_x = (min_x > x2) ? x2 : min_x;

		y1 = a * tan(t) + b * sin(t);
		max_y = (max_y < y1) ? y1 : max_y;
		min_y = (min_y > y1) ? y1 : min_y;

		y2 = a * tan(t) - b * sin(t);
		max_y = (max_y < y2) ? y2 : max_y;
		min_y = (min_y > y2) ? y2 : min_y;
	}

	max_x = (fabs(max_x) > fabs(min_x)) ? fabs(max_x) : fabs(min_x);
	max_y = (fabs(max_y) > fabs(min_y)) ? fabs(max_y) : fabs(min_y);

	glBegin(GL_LINE_STRIP);
		for (auto t = - pi/2 + ratio; t < pi / 2; t += ratio) {
			double x1, y1;
			x1 = (a + b * cos(t)) / max_x;
			y1 = (a * tan(t) + b * sin(t)) / max_y;

			glVertex2f(x1,y1);
		}
	glEnd();

	glBegin(GL_LINE_STRIP); 
		for (auto t = - pi/2 + ratio; t < pi / 2; t += ratio) {
			double x2, y2;
			x2 = (a - b * cos(t)) / max_x;
			y2 = (a * tan(t) - b * sin(t)) / max_y;

			glVertex2f(x2,y2);
		}
	glEnd();
}

void Display3() {
	const auto ratio = 0.05;
	const auto max_x = 25;
	const auto err = ratio / 2;
	double x = 0;
	double y = 1;

	glBegin(GL_LINE_STRIP);
		while (true) {
			
			if(x > max_x) break;

			if(x > 0)
			{
				const auto ceil_value = ceil(x) - x;
				const auto floor_value = x - floor(x);

				y = (floor_value < ceil_value) ? (floor_value / x) : (ceil_value / x);
			}

			const auto output_y = y - err;
			const auto output_x = (x / max_x);

			x += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void Display4() {
	const auto ratio = 0.005;
	const auto a = 0.3, b = 0.2;
	const auto err = 0.05;
	auto t = -pi + ratio;

	glBegin(GL_LINE_STRIP);
		while(true)
		{
			if(t >= pi) break;

			const auto x = 2 * (a * cos(t) + b) * cos(t);
			const auto y = 2 * (a * cos(t) + b) * sin(t);

			t += ratio;

			const auto output_x = x - err;
			const auto output_y = y + err;

			glVertex2f(output_x , output_y);
		}
	glEnd();
}

void Display5() {
	const auto ratio = 0.005;
	const auto a = 0.2;
	double ys[250], xs[250];
	auto t = -pi / 2 + ratio;
	auto n = 0;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
		while (true) {
			
			if(t >= -pi / 6) break;

			const auto output_x = a / (4 * cos(t) * cos(t) - 3);
			const auto output_y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);
			
			xs[n] = output_x;
			ys[n] = output_y;
			n++;

			t += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_TRIANGLES);
		for (auto i = 1; i < n - 1; i += 3) {
			
			if (i > n / 4 && i < 3 * n / 4) continue;
			
			glVertex2f(-1.0, 1.0);
			glVertex2f(xs[i], ys[i]);
			glVertex2f(xs[i + 1], ys[i + 1]);
		}
	glEnd();
}

void Display6() {
	const auto ratio = 0.05;
	const auto a = 0.1, b = 0.2;
	auto t = -(4 * pi);

	glBegin(GL_LINE_STRIP);
		while(true)
		{
			if(t > (4 * pi)) break;

			const auto output_x = a * t - b * sin(t);
			const auto output_y = a - b * cos(t);
			
			t += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void Display7() {
	const auto ratio = 0.05;
	const auto R = 0.1;
	const auto r = 0.3;
	double t = 0;

	glBegin(GL_LINE_STRIP);
		while(true)
		{
			if(t > (2 * pi)) break;

			const auto output_x = (R + r) * cos((r / R) * t) - r * cos(t + (r / R) * t);
			const auto output_y = (R + r) * sin((r / R) * t) - r * sin(t + (r / R) * t);
			
			t += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void Display8() {
	const auto ratio = 0.05;
	const auto r = 0.3;
	const auto R = 0.1;
	double t = 0;

	glBegin(GL_LINE_STRIP);
		while(true){
			
			if(t > (2*pi)) break;

			const auto output_x = (R-r) * cos((r/R)*t) - r * cos(t-(r/R)*t);
			const auto output_y = (R-r) * sin((r/R)*t) - r * sin(t-(r/R)*t);
			
			t += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void Display9() {
	const auto ratio = 0.005;
	const auto a = 0.4;
	auto t = (pi / 4) - ratio;

	glBegin(GL_LINE_STRIP);
		while(true){
			
			if(t <= -(pi / 4))
			{
				t = - (pi / 4) + ratio;
				break;
			}
			
			const auto r = a * sqrt(2*cos(2*t));
			const auto output_x = r * cos(t);
			const auto output_y = r * sin(t);
			
			t -= ratio;

			glVertex2f(output_x, output_y);
		}

		while(true)
		{
			if(t >= (pi / 4) - ratio) break;

			const auto r = -a * sqrt(2*cos(2*t));
			const auto output_x = r * cos(t);
			const auto output_y = r * sin(t);
			
			t += ratio;

			glVertex2f(output_x, output_y);
		}

	glEnd();
}

void Display10() {
	const auto ratio = 0.05;
	const auto a = 0.02;
	auto t = ratio;
	// is not necessary because it does not appear in view
	const float infinity = pi * 1000;

	glBegin(GL_LINE_STRIP);
		while(true){

			if(t >= 3) break;

			const auto r = a * exp(1 + t);

			const auto output_x = r * cos(t);
			const auto output_y = r * sin(t);

			t += ratio;

			glVertex2f(output_x , output_y);
		}
	glEnd();
}


void init(void) {
	glClearColor(1.0,1.0,1.0,1.0);

	glColor3f(1,0.1,0.1);

	glLineWidth(1);

 	glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch(prev_key) {
		case '1':
			display1();
			break;
		case '2':
			Display2();
			break;
		case '3':
			Display3();
			break;
		case '4':
			Display4();
			break;
		case '5':
			Display5();
			break;
		case '6':
			Display6();
			break;
		case '7':
			Display7();
			break;
		case '8':
			Display8();
			break;
		case '9':
			Display9();
			break;
		case '0':
			Display10();
			break;
		default:
			break;
	}

	glFlush();
}

void reshape(const int w, const int h) {
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
}

void keyboard_func(const unsigned char key, int x, int y) {
	prev_key = key;

	if (key == 27) // escape
	{
		exit(0);
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(DIM, DIM);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow (argv[0]);

	init();

	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard_func);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
