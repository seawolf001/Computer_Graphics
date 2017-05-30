#include "GL/glut.h"
#include "GL/gl.h"
#include <math.h>
#include <stdio.h>
#define window_size 500
int n = 0 ; int POLYGON[10][2];
double x_min=10 , x_max=50, y_min=10, y_max=50;
int k; float m; int POINTS[20][2];
void display_Before_clipping()
{
	int POLYGON[10][2]; int n = 6; int p = 0;
	POLYGON[0][0] = 5; 	POLYGON[0][1] = 30;
	POLYGON[1][0] = 30;	POLYGON[1][1] = 5;
	POLYGON[2][0] = 55;	POLYGON[2][1] = 5;
	POLYGON[3][0] = 55;	POLYGON[3][1] = 30;
	POLYGON[4][0] = 30;	POLYGON[4][1] = 55;
	POLYGON[5][0] = 5;	POLYGON[5][1] = 30;

	printf("\n\nVertices before clipping : \n");
	printf("\nX\tY\n\n");
	for(p = 0 ; p < n-1 ; p++)
	{
		printf("%d\t%d\n",POLYGON[p][0],POLYGON[p][1]);
	}
	printf("\n\n");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3);
	glBegin(GL_LINES);
        	glColor3f(0.0f, 0.0f, 0.0f);
        	glVertex2f(0.0f,400.0f);
        	glVertex2f(0.0f,-400.0f);
        	glVertex2f(400.0f,0.0f);
        	glVertex2f(-400.0f,0.0f);
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
        	glColor3f(1.0f, 0.0f, 0.0f);
        	glVertex2f(x_min/100.0f,y_min/100.0f);
        	glVertex2f(x_max/100.0f,y_min/100.0f);
        	glVertex2f(x_max/100.0f,y_max/100.0f);
        	glVertex2f(x_min/100.0f,y_max/100.0f);
	glEnd();
	int i = 0;
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	for(i = 0 ; i < n ; i++)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(POLYGON[i][0]/100.0f,POLYGON[i][1]/100.0f);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void display_After_clipping()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(3);
	glBegin(GL_LINES);
        	glColor3f(0.0f, 0.0f, 0.0f);
        	glVertex2f(0.0f,400.0f);
        	glVertex2f(0.0f,-400.0f);
        	glVertex2f(400.0f,0.0f);
        	glVertex2f(-400.0f,0.0f);
	glEnd();
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
        	glColor3f(1.0f, 0.0f, 0.0f);
        	glVertex2f(x_min/100.0f,y_min/100.0f);
        	glVertex2f(x_max/100.0f,y_min/100.0f);
        	glVertex2f(x_max/100.0f,y_max/100.0f);
        	glVertex2f(x_min/100.0f,y_max/100.0f);
	glEnd();
	int i = 0;
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	for(i = 0 ; i < n ; i++)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(POLYGON[i][0]/100.0f,POLYGON[i][1]/100.0f);
	}
	glEnd();
	int p=0;
	printf("\n\nVertices After clipping : \n");
	printf("\nX\tY\n\n");
	for(p = 0 ; p < n ; p++)
	{
		printf("%d\t%d\n",POLYGON[p][0],POLYGON[p][1]);
	}
	glFlush();
	glutSwapBuffers();
}
void left(int x1,int y1,int x2,int y2)
{
	if(x2-x1) m = (y2-y1)/(float)(x2-x1);
	else m = 100000;
	if(x1 >= x_min && x2 >= x_min)
	{
		POINTS[k][0] = x2;
		POINTS[k][1] = y2;
		k++;
	}
	if(x1 < x_min && x2 >= x_min)
	{
		POINTS[k][0]=x_min;
        	POINTS[k][1]=y1+m*(x_min-x1);
        	POINTS[k+1][0]=x2;
        	POINTS[k+1][1]=y2;
        	k += 2;
	}
	if(x1 >= x_min && x2 < x_min)
	{
		POINTS[k][0] = x_min;
		POINTS[k][1] = y1+m*(x_min-x1);
		k++;
	}
}
void clip_left()
{
	int i = 0; k = 0 ;
	for(i = 0 ; i < n ; i++) left(POLYGON[i][0],POLYGON[i][1],POLYGON[i+1][0],POLYGON[i+1][1]);
	for(i=0;i<k;i++)
	{
		POLYGON[i][0] = POINTS[i][0];
		POLYGON[i][1] = POINTS[i][1];
	}
	POLYGON[i][0] = POLYGON[0][0];
	POLYGON[i][1] = POLYGON[0][1];
	n = k;
}
void top(int x1,int y1,int x2,int y2)
{
	if(y2-y1)
        	m=(x2-x1)/(float)(y2-y1);
    	else
        	m=100000;
	if(y1 <= y_max && y2 <= y_max)
        {
               	POINTS[k][0]=x2;
               	POINTS[k][1]=y2;
               	k+=1;
        }
	if(y1 > y_max && y2 <= y_max)
	{
		POINTS[k][0]=x1+m*(y_max-y1);
        	POINTS[k][1]=y_max;
        	POINTS[k+1][0]=x2;
        	POINTS[k+1][1]=y2;
        	k+=2;
	}
	if(y1 <= y_max && y2 > y_max)
	{
		POINTS[k][0]=x1+m*(y_max-y1);
        	POINTS[k][1]=y_max;
        	k+=1;
	}
}
void clip_top()
{
	int i = 0 ; k = 0;
	for(i = 0 ; i < n ; i++) top(POLYGON[i][0],POLYGON[i][1],POLYGON[i+1][0],POLYGON[i+1][1]);
	for(i=0;i<k;i++)
	{
		POLYGON[i][0] = POINTS[i][0];
		POLYGON[i][1] = POINTS[i][1];
	}
	POLYGON[i][0] = POLYGON[0][0];
	POLYGON[i][1] = POLYGON[0][1];
	n = k;
}
void right(int x1,int y1,int x2,int y2)
{
	if(x2-x1)
        	m=(y2-y1)/(float)(x2-x1);
    	else
        	m=100000;
    	if(x1 <= x_max && x2 <= x_max)
    	{
        	POINTS[k][0]=x2;
        	POINTS[k][1]=y2;
        	k+=1;
    	}
    	if(x1 > x_max && x2 <= x_max)
    	{
        	POINTS[k][0]=x_max;
        	POINTS[k][1]=y1+m*(x_max-x1);
        	POINTS[k+1][0]=x2;
        	POINTS[k+1][1]=y2;
        	k+=2;
    	}
    	if(x1 <= x_max  && x2 > x_max)
    	{
        	POINTS[k][0]=x_max;
        	POINTS[k][1]=y1+m*(x_max-x1);
        	k+=1;
    	}
}
void clip_right()
{
	int i = 0 ; k = 0;
	for(i = 0 ; i < n ; i++) right(POLYGON[i][0],POLYGON[i][1],POLYGON[i+1][0],POLYGON[i+1][1]);
	for(i=0;i<k;i++)
	{
		POLYGON[i][0] = POINTS[i][0];
		POLYGON[i][1] = POINTS[i][1];
	}
	POLYGON[i][0] = POLYGON[0][0];
	POLYGON[i][1] = POLYGON[0][1];
	n = k;
}
void bottom(int x1,int y1,int x2,int y2)
{
	if(y2-y1)
        	m=(x2-x1)/(float)(y2-y1);
    	else
        	m=100000;
    	if(y1 >= y_min && y2 >= y_min)
    	{
        	POINTS[k][0]=x2;
        	POINTS[k][1]=y2;
        	k+=1;
    	}
    	if(y1 < y_min && y2 >= y_min)
    	{
        	POINTS[k][0]=x1+m*(y_min-y1);
        	POINTS[k][1]=y_min;
        	POINTS[k+1][0]=x2;
        	POINTS[k+1][1]=y2;
        	k+=2;
    	}
    	if(y1 >= y_min  && y2 < y_min)
    	{
        	POINTS[k][0]=x1+m*(y_min-y1);
        	POINTS[k][1]=y_min;
        	k+=1;
    	}
}
void clip_bottom()
{
	int i = 0 ; k = 0;
	for(i = 0 ; i < n ; i++) bottom(POLYGON[i][0],POLYGON[i][1],POLYGON[i+1][0],POLYGON[i+1][1]);
	for(i=0;i<k;i++)
	{
		POLYGON[i][0] = POINTS[i][0];
		POLYGON[i][1] = POINTS[i][1];
	}
	POLYGON[i][0] = POLYGON[0][0];
	POLYGON[i][1] = POLYGON[0][1];
	n = k;
}
void clip_the_polygon()
{
	clip_left();
	clip_top();
	clip_right();
	clip_bottom();
}
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
    	glutInitDisplayMode(GLUT_RGB);
    	glutInitWindowSize(window_size, window_size);
    	gluOrtho2D(-1*window_size/2, window_size/2, -1*window_size/2, window_size/2);
	/**********************************************************************/
	n = 6;
	POLYGON[0][0] = 5; 	POLYGON[0][1] = 30;
	POLYGON[1][0] = 30;	POLYGON[1][1] = 5;
	POLYGON[2][0] = 50;	POLYGON[2][1] = 5;
	POLYGON[3][0] = 55;	POLYGON[3][1] = 30;
	POLYGON[4][0] = 30;	POLYGON[4][1] = 55;
	POLYGON[5][0] = 5;	POLYGON[5][1] = 30;

	glutCreateWindow("POLYGON BEFORE CLIPPING");
	glutDisplayFunc(display_Before_clipping);
	clip_the_polygon();
	glutCreateWindow("POLYGON AFTER CLIPPING");
	glutDisplayFunc(display_After_clipping);
	/**********************************************************************/
	glutMainLoop();
	return 0;
}
