// Daca se doreste utilizarea bibliotecii GLUT trebuie
// inclus fisierul header GL/glut.h (acesta va include
// la GL/gl.h si GL/glu.h, fisierele header pentru
// utilizarea bibliotecii OpenGL). Functiile din biblioteca
// OpenGL sunt prefixate cu gl, cele din GLU cu glu si
// cele din GLUT cu glut.

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <cstdlib>
#include <cmath>
#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
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

	// afisarea punctelor propriu-zise precedata de scalare
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

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
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

	// afisarea punctelor propriu-zise precedata de scalare
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

			const auto output_y = y - (ratio / 2);
			const auto output_x = x / max_x;

			x += ratio;

			glVertex2f(output_x, output_y);
		}
	glEnd();
}

void Display4() {
	const auto ratio = 0.005;
	const auto a = 0.3, b = 0.2;
	auto t = -pi + ratio;

	glBegin(GL_LINE_STRIP);
		while(true)
		{
			if(t >= pi) break;

			const auto x = 2 * (a * cos(t) + b) * cos(t);
			const auto y = 2 * (a * cos(t) + b) * sin(t);

			t += ratio;

			glVertex2f(x ,y);
		}
	glEnd();
}

void Display5() {
	const auto ratio = 0.05;

	double piPe2 = pi/2;
	double piPe6 = pi/6;
	double t, x1, y1, a = 0.2;

	glBegin(GL_LINE_STRIP);
		for(t = -piPe2+ratio; t < piPe2; t+=ratio){
			if(t!=piPe6 || t!=(-piPe6)){
				x1 = a / (4 * pow(cos(t), 2) -3);
				y1 = (a*tan(t))/(4*pow(cos(t),2)-3);
			}
			if(x1<0 && y1>0)
			{
				glVertex2f(x1,y1);
			}
		}
	glEnd();
}

void Display55() {
	const auto ratio = 0.05;
	double a = 0.2;
	double ys[1000], xs[1000];
	int n = 0;

	glBegin(GL_LINE_STRIP);
		for (double t = -pi / 2 + ratio; t < -pi / 6; t += ratio) { //de ce e -pi/6
			if (t == pi / 6 || t == -pi / 6) { continue; }
			double x1, y1;
			x1 = a / (4 * cos(t) * cos(t) - 3);
			y1 = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);
			xs[n] = x1;
			ys[n] = y1;
			n++;
			glVertex2f(x1, y1);
		}
	glEnd();

	for (int i = 0; i < n; i += 2) {
		if (i > n / 4 && i < 3 * n / 4) { continue; }
		glColor3f(1, 0.1, 0.1);
		glBegin(GL_TRIANGLES);
		glVertex2f(-1.0, 1.0);
		glVertex2f(xs[i], ys[i]);
		glVertex2f(xs[i + 1], ys[i + 1]);
		glEnd();
	}

	glColor3f(0.0, 0.0, 0.0);  //pt linie
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i < n; i++)
			glVertex2f(xs[i + 1], ys[i + 1]);
	glEnd();

	glColor3f(1,0.1,0.1); // rosu
}

void Display6() {
	double ratio = 0.05;
	double t,x1,y1, a=0.1, b=0.2;

	glBegin(GL_LINE_STRIP);
		for(t = -(4*pi); t <= (4*pi); t+=ratio)
		{
			x1 = a*t-b*sin(t);
			y1 = a-b*cos(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display7() {
	double ratio = 0.05;
	double t,x1,y1, R=0.1, r=0.3;

	glBegin(GL_LINE_STRIP);
		for(t = 0; t <= (2*pi); t+=ratio)
{
			x1 = (R+r)*cos((r/R)*t)-r*cos(t+(r/R)*t);
			y1 = (R+r)*sin((r/R)*t)-r*sin(t+(r/R)*t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display8() {
	double ratio = 0.05;
	double t,x1,y1, R=0.1, r=0.3;

	glBegin(GL_LINE_STRIP);
		for(t = 0; t <= (2*pi); t+=ratio){
			x1 = (R-r)*cos((r/R)*t)-r*cos(t-(r/R)*t);
			y1 = (R-r)*sin((r/R)*t)-r*sin(t-(r/R)*t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display9() {
	double ratio = 0.005;
	double piPe4 = pi/4;
	double t,x1,y1, a=0.4,r;

	glBegin(GL_LINE_STRIP);
		for(t = piPe4-ratio; t > -piPe4; t-=ratio){
			r=a*sqrt(2*cos(2*t));
			x1 =r*cos(t);
			y1 =r*sin(t);
			glVertex2f(x1,y1);
		}
		for(t = -piPe4+ratio; t < piPe4; t+=ratio){
			r=-a*sqrt(2*cos(2*t));
			x1 =r*cos(t);
			y1 =r*sin(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display10() {
	double ratio = 0.05;
	double piPe4 = pi/4;
	double t,x1,y1, a=0.02,r;

	glBegin(GL_LINE_STRIP);
		for(t = 0+ratio; t < (9999*pi); t+=ratio){
			r=a*exp(1+t);
			x1 =r*cos(t);
			y1 =r*sin(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}


void init(void) {
	glClearColor(1.0,1.0,1.0,1.0);

	glColor3f(1,0.1,0.1);

	glLineWidth(1);

// 	glPointSize(4);

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
