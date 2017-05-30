#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#define PI 3.14159265
int flag, count; int i = 0 ; int j = 0 ; int k = 0 ;
double input_pts[10][2];
double final_pts[10][2];
double trans_matrix[3][3];

double x = 0 ;

void displayPolygon()
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

        glBegin(GL_LINE_LOOP);

        glColor3f(1.0f,0.0f,0.0f);

        glVertex3f(input_pts[0][0]/100.0, input_pts[0][1]/100.0, 1.0f);
        glVertex3f(input_pts[1][0]/100.0, input_pts[1][1]/100.0, 1.0f);
        glVertex3f(input_pts[2][0]/100.0, input_pts[2][1]/100.0, 1.0f);
        glVertex3f(input_pts[3][0]/100.0, input_pts[3][1]/100.0, 1.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);

        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(final_pts[0][0]/100.0, final_pts[0][1]/100.0, 1.0f);
        glVertex3f(final_pts[1][0]/100.0, final_pts[1][1]/100.0, 1.0f);
        glVertex3f(final_pts[2][0]/100.0, final_pts[2][1]/100.0, 1.0f);
        glVertex3f(final_pts[3][0]/100.0, final_pts[3][1]/100.0, 1.0f);
        glEnd();

	glFlush();
	glutSwapBuffers();
}

void matrix_multiplication()
{
        int i = 0 , j = 0 , k = 0 ;
        double a = 0 ; double b = 0 ;

        for(i = 0 ; i < 4 ; i++)
        {
                a = trans_matrix[0][0]*input_pts[i][0] + trans_matrix[0][1]*input_pts[i][1] + trans_matrix[0][2];
                b = trans_matrix[1][0]*input_pts[i][0] + trans_matrix[1][1]*input_pts[i][1] + trans_matrix[1][2];

                final_pts[i][0]=a;
                final_pts[i][1]=b;
        }
}


void translate(double x , double y)
{
	trans_matrix[0][0] = 1;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = x;
    	trans_matrix[1][0] = 0;
    	trans_matrix[1][1] = 1;
    	trans_matrix[1][2] = y;
    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = 1;
}

void scale_x_y(double sx, double sy)
{
    	trans_matrix[0][0] = sx;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = 0;
    	trans_matrix[1][0] = 0;
    	trans_matrix[1][1] = sy;
    	trans_matrix[1][2] = 0;
    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = 1;
}

void reflectAroundX(void)
{
    	trans_matrix[0][0] = 1;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = 0;
    	trans_matrix[1][0] = 0;
    	trans_matrix[1][1] = -1;
    	trans_matrix[1][2] = 0;
    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = 1;
}


void shearaboutY(double b)
{
    	trans_matrix[0][0] = 1;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = 0;
    	trans_matrix[1][0] = b;
    	trans_matrix[1][1] = 1;
    	trans_matrix[1][2] = 0;
    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = 1;
}

void rotate(double a)
{
	x = PI / 180 ;
	a = a*x;
    	trans_matrix[0][0] = cos(a);
    	trans_matrix[0][1] = -1 * sin(a);
    	trans_matrix[0][2] = 0;
    	trans_matrix[1][0] = sin(a);
    	trans_matrix[1][1] = cos(a);
    	trans_matrix[1][2] = 0;
    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = 1;
}

void transformPoints()
{
        int choice ;
        printf("\nEnter your choice:\n1. Translation\n2. Scaling\n3. Reflection\n4. Shear\n5. Rotate\n");
        printf("Your choice : ");
        scanf("%d",&choice);

        double x , y , scale_factor_x, scale_factor_y, shear_factor ,rotation_angle ;

        if(choice==1)
        {
                printf("Enter translate_x : ");
                scanf("%lf",&x);
                printf("Enter translate_y : ");
                scanf("%lf",&y);
                translate(x,y);
        }

        if(choice==2)
        {
                printf("Enter scale_factor_x : ");
                scanf("%lf",&scale_factor_x);
                printf("Enter scale_factor_y : ");
                scanf("%lf",&scale_factor_y);
                scale_x_y(scale_factor_x,scale_factor_y);
        }

        if(choice==3)
        {
                reflectAroundX();
        }

        if(choice==4)
        {
                printf("\nEnter  the shearing Factor :  ");
                scanf("%lf",&shear_factor);
                shearaboutY(shear_factor);
        }

        if(choice==5)
        {
                printf("\nEnter the rotation_angle :  ");
                scanf("%lf",&rotation_angle);
                rotate(rotation_angle);
        }
}


int main(int argc, char **argv)
{
	    glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB);
    	glutInitWindowSize(800, 800);
    	for(i = 0 ; i < 10 ; i++)
        {
                for(j = 0 ; j < 3 ; j++)
                {
                        input_pts[i][j]=0;
                }
        }
    	printf("**********\nWe'll be applying  transformations to a sqaure polygon\n**********\n");
    	printf("Enter the polygon coordinates : ");
    	count = 4 ;

    	for( i = 0 ; i < count ; i++)
    	{
    		scanf("%lf %lf",&input_pts[i][0],&input_pts[i][1]);
    	}


        for(i = 0 ; i < 10 ; i++)
        {
                for(j = 0 ; j < 2 ; j++)
                {
                        final_pts[i][j]=0;
                }
        }
        for(i = 0 ; i < 3 ; i++)
        {
                for(j = 0 ; j < 3 ; j++)
                {
                        trans_matrix[i][j]=0;
                }
        }

    	transformPoints();
    	matrix_multiplication();
    	gluOrtho2D(-400, 400, -400, 400);
        glutCreateWindow("\nPolygon transformations");
        glutDisplayFunc(displayPolygon);
        glutMainLoop();

	return 0;
}
