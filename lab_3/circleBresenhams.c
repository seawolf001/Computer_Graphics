#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int centre_x = 0 ; int centre_y=0 ; int radius =0 ;
int n = 0 ;
int x_coordinate[1000];
int y_coordinate[1000];

void displayCircle(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
       
        int d = 3-2*radius;
	int x = 0, y = radius; 
	putPixels(centre_x, centre_y, x, y);
	
	while (x < y)
	{
		if (d < 0)
		{
		   d += 4*x + 6;
		}
		else 
		{
		   d += 4*(x-y) + 10;
		   y--;
		}
		x++;
		putPixels(centre_x, centre_y, x, y);
	}
    	int i;
    	for (i = 0; i < n; i++ )
    	{
		glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);
		//printf("x : %d y : %d\n", x_coordinate[i], y_coordinate[i]);
		glVertex2f(x_coordinate[i]/100.0, y_coordinate[i]/100.0);
		glEnd();
	}
    	glFlush();
}

void putPixels(int X, int Y, int P, int Q )
{
	x_coordinate[n] = X + P;
	y_coordinate[n++] = Y + Q;

	x_coordinate[n] = X - P;
	y_coordinate[n++] = Y + Q;

	x_coordinate[n] = X + P;
	y_coordinate[n++] = Y - Q;

	x_coordinate[n] = X - P; 
	y_coordinate[n++] = Y - Q;

	x_coordinate[n] = X + Q;
	y_coordinate[n++] = Y + P;

	x_coordinate[n] = X - Q; 
	y_coordinate[n++] = Y + P;

	x_coordinate[n] = X + Q; 
	y_coordinate[n++] = Y - P;

	x_coordinate[n] = X - Q;
	y_coordinate[n++] = Y - P;
}
int main(int argc, char const *argv[])
{
	printf("centre coordinates : ");
	scanf("%d  %d", &centre_x , &centre_y);
	printf("radius of circle   : ");
	scanf("%d",&radius);

	glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowSize(640,480);
        glutCreateWindow("Bresenham Circle Drawing Algorithm");
        glutInitWindowPosition(100,100);
        glutDisplayFunc(displayCircle);
        glutMainLoop();
	return 0;
}