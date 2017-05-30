#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define windowSize 600
int x_1 , x_2 , y_1 , y_2 , flag , y_increment , d , d1 , d2 ;

void displayLine(void)
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(3);
	glBegin(GL_LINES);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(0.0f,1.0f);
                glVertex2f(0.0f,-1.0f);
                glVertex2f(1.0f,0.0f);
                glVertex2f(-1.0f,0.0f);
        glEnd();
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glColor3f(1,0,0);
	double x = x_1, y = y_1;
	printf("\nPoints in between the End points :\n");
	printf("\nX\t\tY\n\n");
	while(x <= x_2)
	{
		glVertex3f(x/100.0,y/100.0,1.0f);
		printf("%f\t%f\n",x/100.0,y/100.0);
		if(d<=0)
			d += d1;
		else
		{
			d += d2;
			if(flag)
				y += y_increment;
			else
				x++;
		}
		if(flag)
			x++;
		else
			y += y_increment;
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	printf("Enter  the  coordinates  of first point  : ");
	scanf("%d %d",&x_1,&y_1);
	printf("Enter  the  coordinates  of Second point : ");
	scanf("%d %d",&x_2,&y_2);
	glutInit(&argc,argv);
    	glutInitDisplayMode(GLUT_RGB);
    	glutInitWindowSize(windowSize, windowSize);
    	gluOrtho2D(-1*windowSize/2, windowSize/2, -1*windowSize/2, windowSize/2);
	/*********************************************************************************/
	float slope = (float)(y_2-y_1)/(float)(x_2-x_1);
	if(slope >= 0 && slope <=1 && x_1 >=0 && x_2 >= 0 && y_1 >=0 && y_2 >= 0)
	{
		printf("\nSlope of the line : %f <= 1, So The points lie in first octant\n",slope);
		int dx = x_2-x_1;
		int dy = abs(y_2-y_1);
		if(y_2 < y_1)
			y_increment = -1;
		else
			y_increment = 1;
		if(dy>dx)
		{
			flag = 0;
			d = 2*dx - dy;
			d1 = 2*dx;
			d2 = 2*(dx-dy);
		}
		else
		{
			flag = 1;
			d = 2*dy - dx;
			d1 = 2*dy;
			d2 = 2*(dy-dx);
		}
	}
	else
	{
		printf("Please enter the point  in first octant only\n");
		exit(1);
	}
	/*********************************************************************************/
	glutCreateWindow("Bresenham Line Drawing");
	glutDisplayFunc(displayLine);
	glutMainLoop();
	return 0;
}
