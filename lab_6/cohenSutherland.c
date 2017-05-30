#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <GL/glut.h>

double x_min=10 , x_max=50, y_min=20, y_max=50;
double xf1=0, yf1=0, xf2=60, yf2=50;

int get_code_for_this_point(float x,float y)
{
    	int c=0;
    	if(y>y_max) c=8;
    	if(y<y_min) c=4;
    	if(x>x_max) c=c|2;
    	if(x<x_min) c=c|1;
    	return c;
}

void clipping_Line(float x1,float y1,float x2,float y2)
{
	int c1=get_code_for_this_point(x1,y1);
	int c2=get_code_for_this_point(x2,y2);

	while((c1|c2) != 0)
	{
		if((c1&c2) > 0)
		{
			printf("\nLine outside the window\n");
			break;
		}

		float slope = (y2-y1)/(x2-x1);

		float xi = x1 ;
		float yi = y1 ;
		int code = c1 ;

		if(code==0)
		{
			code = c2 ;
			xi = x2 ;
			yi = y2 ;
		}

		float x = 0 ; float y = 0;

		if((code & 8)>0)
    		{
       			y = y_max;
       			x = xi+ 1.0/slope*(y_max-yi);
		}
		else if((code & 4)>0)
		{
			y = y_min;
			x = xi+1.0/slope*(y_min-yi);
		}
		else if((code & 2)>0)
		{
			x = x_max;
			y = yi+slope*(x_max-xi);
		}
		else if((code & 1)>0)
		{
			x = x_min;
			y = yi+slope*(x_min-xi);
		}

		if(code == c1)
		{
			xf1 = x ;
			yf1 = y ;
			c1 = get_code_for_this_point(xf1,yf1);
		}
		if(code == c2)
		{
			xf2 = x ;
			yf2 = y ;
			c2 = get_code_for_this_point(xf2,yf2);
		}
	}
}


void display_function_after()
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


        clipping_Line(xf1,yf1,xf2,yf2);

        glLineWidth(3);
        glBegin(GL_LINES);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(xf1/100.0f,yf1/100.0f);
                glVertex2f(xf2/100.0f,yf2/100.0f);
        glEnd();
        glFlush();
	glutSwapBuffers();
}
void display_function_before()
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


        glLineWidth(3);
        glBegin(GL_LINES);
                glColor3f(0.0f, 1.0f, 0.0f);
                glVertex2f(xf1/100.0f,yf1/100.0f);
                glVertex2f(xf2/100.0f,yf2/100.0f);
        glEnd();

        glFlush();
	glutSwapBuffers();
}

int main(int argc, char const *argv[])
{
	glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB);
    	glutInitWindowSize(500, 500);
    	gluOrtho2D(-400, 400, -400, 400);
         glutCreateWindow("Cohen-sutherland Line Clipping: Before");
	glutDisplayFunc(display_function_before);
         glutCreateWindow("Cohen-sutherland Line Clipping: After");
         glutDisplayFunc(display_function_after);
         glutMainLoop();
	return 0;
}
