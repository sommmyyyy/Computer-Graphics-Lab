#include<iostream>
#include<math.h>
using namespace std;
#include<gl/glut.h>
float f, g, r, x[4], y[4];
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	gluOrtho2D(0.0, 800, 0.0, 800);
}
void draw_pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
void drawcircle(float xc,float yc)
{
draw_pixel(xc,yc);
draw_pixel(yc,xc);
draw_pixel(-yc,xc);
draw_pixel(-xc,yc);
draw_pixel(xc,-yc);
draw_pixel(yc,-xc);
draw_pixel(-xc,-yc);
draw_pixel(-yc,-xc);
}
void draw_circle(float x1,float x2,float rad)
{
glClear(GL_COLOR_BUFFER_BIT);
float x=rad,y=0,theta,k;
for(theta=0.0;theta<=45;theta=theta+0.25)
{
x=rad*cos(theta);
y=rad*sin(theta);
drawcircle(x+x1,y+x2);
}
for(k=1;k<rad;k++)
draw_circle(x1,x2,k);
glFlush();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	double t;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (t = 0.0; t < 1.0; t += 0.0005)
	{
		double xt = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t,
			3) * x[3];
		double yt = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] + 3 * pow(t, 2) * (1 -
			t) * y[2] + pow(t, 3) * y[3];
		glVertex2f(xt, yt);
	}
	glColor3f(1.0, 1.0, 0.0);
	for (i = 0; i < 4; i++)
		glVertex2f(x[i], y[i]);
	glEnd();
	glFlush();
}
int main(int argc, char** argv)
{
	cout << "Enter x coordinates\n";
	cin >> x[0] >> x[1] >> x[2] >> x[3];
	cout << "Enter y coordinates\n";
	cin >> y[0] >> y[1] >> y[2] >> y[3];
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("new window");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
