#include "GrilaCarteziana.h"
#include <GL/glut.h>
#include <cstdlib>
#include <list>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace std;
unsigned char prevKey;

auto grila3 = new GrilaCarteziana(14);

void Init(void) 
{
	glClearColor(1.0,1.0,1.0,1.0);
	glLineWidth(1);
	glPolygonMode(GL_FRONT, GL_LINE);
	glMatrixMode(GL_PROJECTION);
}

void Display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);

	if(prevKey == '3')
	{
		grila3->draw_grid();
		grila3->draw_poligon();
		grila3->draw_pixels();
	}

	glFlush();
}

void Reshape(const int width, const int height) 
{
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	prevKey = key;
	if (key == 27)
		exit(0);
	glutPostRedisplay();
}

int main(int argc, char** argv) 
{
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