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

unsigned char prev_key;

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display1() {
	double pi = 4 * atan(1);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP); 
		for (double x = 0; x < xmax; x += ratia) {
		double x1 = x / xmax;
		double y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1,y1);
		}
	glEnd();
}

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display2() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1);
	double ratia = 0.05;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;

	for (auto t = - pi/2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for (auto t = - pi/2 + ratia; t < pi / 2; t += ratia) {
			double x1, y1, x2, y2;
			x1 = (a + b * cos(t)) / xmax;
			x2 = (a - b * cos(t)) / xmax;
			y1 = (a * tan(t) + b * sin(t)) / ymax;
			y2 = (a * tan(t) - b * sin(t)) / ymax;

			glVertex2f(x1,y1);
		}
	glEnd();

	glBegin(GL_LINE_STRIP); 
		for (auto t = - pi/2 + ratia; t < pi / 2; t += ratia) {
			double x1, y1, x2, y2;
			x1 = (a + b * cos(t)) / xmax;
			x2 = (a - b * cos(t)) / xmax;
			y1 = (a * tan(t) + b * sin(t)) / ymax;
			y2 = (a * tan(t) - b * sin(t)) / ymax;

			glVertex2f(x2,y2);
		}
	glEnd();
}

void Display3() {
	double ratia = 0.05;
	double xmax = 100;
	double ceilValue, floorValue;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for (double x = 0; x <=xmax; x += ratia) {
			double x1=x/xmax, y1;
			if(x==0)
			{
				y1 = 1;
			}
			else {
				ceilValue = ceil(x)-x;
				floorValue = x-floor(x);
				if(floorValue<ceilValue){
					y1 = floorValue/x;
				} else {
					y1 = ceilValue/x;
				}
			}
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display4() {
	double xmax = 100;
	double ratia = 0.05;
	double pi = 4 * atan(1.0);
	double t,x1,y1, a= 0.3, b= 0.2;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(t = -pi+ratia; t < pi; t+=ratia){
			x1 = 2*(a*cos(t)+b)*cos(t);
			y1 = 2*(a*cos(t)+b)*sin(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display5() {
	double xmax = 100;
	double ratia = 0.05;
	double pi = 4 * atan(1.0);
	double piPe2 = pi/2;
	double piPe6 = pi/6;
	double t, x1, y1, a = 0.2;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(t = -piPe2+ratia; t < piPe2; t+=ratia){
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
	double a = 0.2;
	double pi = 4 * atan(1.0), ratia = 0.01, xs[1000];
	double ys[1000];
	int n = 0;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
		for (double t = -pi / 2 + ratia; t < -pi / 6; t += ratia) { //de ce e -pi/6
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
}

void Display6() {
	double xmax = 100;
	double ratia = 0.05;
	double pi = 4 * atan(1.0);
	double t,x1,y1, a=0.1, b=0.2;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(t = -(4*pi); t <= (4*pi); t+=ratia)
		{
			x1 = a*t-b*sin(t);
			y1 = a-b*cos(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display7() {
	double xmax = 100;
	double ratia = 0.05;
	double pi = 4 * atan(1.0);
	double t,x1,y1, R=0.1, r=0.3;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(t = 0; t <= (2*pi); t+=ratia)
{
			x1 = (R+r)*cos((r/R)*t)-r*cos(t+(r/R)*t);
			y1 = (R+r)*sin((r/R)*t)-r*sin(t+(r/R)*t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display8() {
	double xmax = 100;
	double ratia = 0.05;
	double pi = 4 * atan(1.0);
	double t,x1,y1, R=0.1, r=0.3;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(t = 0; t <= (2*pi); t+=ratia){
			x1 = (R-r)*cos((r/R)*t)-r*cos(t-(r/R)*t);
			y1 = (R-r)*sin((r/R)*t)-r*sin(t-(r/R)*t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display9() {
	double xmax = 100;
	double ratia = 0.005;
	double pi = 4 * atan(1.0);
	double piPe4 = pi/4;
	double t,x1,y1, a=0.4,r;

	glColor3f(1,0.1,0.1); // rosu
	glBegin(GL_LINE_STRIP);
		for(t = piPe4-ratia; t > -piPe4; t-=ratia){
			r=a*sqrt(2*cos(2*t));
			x1 =r*cos(t);
			y1 =r*sin(t);
			glVertex2f(x1,y1);
		}
		for(t = -piPe4+ratia; t < piPe4; t+=ratia){
			r=-a*sqrt(2*cos(2*t));
			x1 =r*cos(t);
			y1 =r*sin(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}

void Display10() {
	double xmax = 100;
	double ratia = 0.05;
	double pi = 4 * atan(1.0);
	double piPe4 = pi/4;
	double t,x1,y1, a=0.02,r;
	glColor3f(1,0.1,0.1);

	glBegin(GL_LINE_STRIP);
		for(t = 0+ratia; t < (9999*pi); t+=ratia){
			r=a*exp(1+t);
			x1 =r*cos(t);
			y1 =r*sin(t);
			glVertex2f(x1,y1);
		}
	glEnd();
}


void Init(void) {
	glClearColor(1.0,1.0,1.0,1.0);

	glLineWidth(1);

	glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch(prev_key) {
		case '1':
		  Display1();
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

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
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

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
