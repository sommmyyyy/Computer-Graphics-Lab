#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
struct screenPt
{
	int x;
	int y;
};
typedef enum { limacon = 1, cardioid = 2, threeLeaf = 3, spiral = 4 } curveName;
int w = 600, h = 500;
void myinit(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}
void lineSegment(screenPt p1, screenPt p2)
{
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
}
void drawCurve(int curveNum)
{
	const double twoPi = 6.283185;
	const int a = 175, b = 60;
	float r, theta, dtheta = 1.0 / float(a);
	int x0 = 200, y0 = 250;
	screenPt curvePt[2];
	glColor3f(0.0, 0.0, 0.0);
	curvePt[0].x = x0;
		curvePt[0].y = y0;
	switch (curveNum)
	{
	case limacon: curvePt[0].x += a + b; break;
	case cardioid: curvePt[0].x += a + a; break;
	case threeLeaf: curvePt[0].x += a; break;
	case spiral: break;
	default: break;
	}
	theta = dtheta;
	while (theta < twoPi)
	{
		switch (curveNum)
		{
		case limacon: r = a * cos(theta) + b; break;
		case cardioid: r = a * (1 + cos(theta)); break;
		case threeLeaf: r = a * cos(3 * theta); break;
		case spiral: r = (a / 4.0) * theta; break;
		default: break;
		}
		curvePt[1].x = x0 + r * cos(theta);
		curvePt[1].y = y0 + r * sin(theta);
		lineSegment(curvePt[0], curvePt[1]);
		curvePt[0].x = curvePt[1].x;
		curvePt[0].y = curvePt[1].y;
		theta += dtheta;
	}
}
void mydisplay()
{
	int curveNum;
	glClear(GL_COLOR_BUFFER_BIT);
	printf("\n Enter the integer value corresponding to \n");
	printf("one of the following curve names. \n");
	printf("Press any other key to exit. \n");
	printf("\n 1-limacon,2-cardioid,3-threeleaf,4-spiral:");
	scanf_s("%d", &curveNum);
	if (curveNum == 1 || curveNum == 2 || curveNum == 3 || curveNum == 4)
		drawCurve(curveNum);
		glFlush();
}
void myreshape(int nw, int nh)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)nw, 0.0, (double)nh);
	glClear(GL_COLOR_BUFFER_BIT);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Drawing curves");
	myinit();
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutMainLoop();
}