#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double x_1 , x_2 , y_1 , y_2 , x_increment , y_increment ;
double length ;

displayLine(void)
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_LINES);
                glColor3f(0.0f, 0.0f, 0.0f);
                glVertex2f(0.0f,1.0f);
                glVertex2f(0.0f,-1.0f);
                glVertex2f(1.0f,0.0f);
                glVertex2f(-1.0f,0.0f);
        glEnd();
	glBegin(GL_LINE_STRIP);
	double x = round(x_1);
	double y = round(y_1);
	while(x <= x_2)
	{
		double xf = floor(x);
		double yf = floor(y);
		xf/=100;
		yf/=100;
		glVertex3f(xf,yf,1.0f);
		x += x_increment;
		y += y_increment;
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char const *argv[])
{
	int flag=0;
	printf("Enter  the  coordinates  of first point  : ");
	scanf("%lf %lf",&x_1,&y_1);
	printf("Enter  the  coordinates  of Second point : ");
	scanf("%lf %lf",&x_2,&y_2);
	printf("Enter choice\n\t1 : Draw Line using simple DDA\n\t2 : Draw Line using Symmetric DDA\n");
	printf("Your choice : ");
	scanf("%d\n",&flag);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	if(flag==1)
	{
		length = abs(x_2-x_1);
		if(length < abs(y_2-y_1))
			length = abs(y_2-y_1);
		x_increment = (x_2-x_1)/length;
		y_increment = (y_2-y_1)/length;
		glutCreateWindow("Demonstrating Simple DDA");
		
	}
	else if(flag==2)
	{
		x_increment = x_2-x_1 ;
		y_increment = y_2-y_1 ;
		while(abs(x_increment)>=1 || abs(y_increment)>=1)
		{
			x_increment /= 2;
			y_increment /= 2;
		}
		glutCreateWindow("Demonstrating Symmetric DDA");
	}
	else 
	{
		printf("Please try with correct input\n");
		exit(1);
	}
	glutDisplayFunc(displayLine);
	glutMainLoop();
	return 0;
}