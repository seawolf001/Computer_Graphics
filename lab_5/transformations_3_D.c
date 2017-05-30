#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#define PI 3.14159265

int flag=0, count=0; int i = 0 ; int j = 0 ; int k = 0 ;

double input_pts[8][3] = {{0,0,0},{50,0,0},{50,50,0},{0,50,0},{0,0,10},{50,0,50},{50,50,50},{0,10,10}};
double final_pts[8][3];
double trans_matrix[4][4];

double x = 0;
void displayPolygon()
{

        glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(3);
        glBegin(GL_LINES);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex3f(0.0f,400.0f,0.0f);
                glVertex3f(0.0f,-400.0f,0.0f);
                glVertex3f(400.0f,0.0f,0.0f);
                glVertex3f(-400.0f,0.0f,0.0f);
                glVertex3f(0.0f,0.0f,400.0f);
                glVertex3f(0.0f,0.0f,-400.0f);
        glEnd();

        glBegin(GL_QUADS);

        glColor3f(1.0f,0.0f,0.0f);

        for(i = 0 ; i < 8 ; i++)
        {
        	 glVertex3f(input_pts[i][0]/100.0, input_pts[i][1]/100.0, input_pts[i][2]/100.0);
        }
        glEnd();

        glBegin(GL_QUADS);

        glColor3f(0.0f,1.0f,0.0f);
        
        for(i = 0 ; i < 8 ; i++)
        {
        	 glVertex3f(final_pts[i][0]/100.0, final_pts[i][1]/100.0, final_pts[i][2]/100.0);
        }

        glEnd();

	glFlush();
	glutSwapBuffers();
}

void matrix_multiplication()
{
        int i = 0 , j = 0 , k = 0 ;
        double a = 0 ; double b = 0 ; double c = 0;

        for(i = 0 ; i < 8 ; i++)
        {
                a = trans_matrix[0][0]*input_pts[i][0] + trans_matrix[0][1]*input_pts[i][1] 
                		+ trans_matrix[0][2]*input_pts[i][2] + trans_matrix[0][3];

                b = trans_matrix[1][0]*input_pts[i][0] + trans_matrix[1][1]*input_pts[i][1] 
                		+ trans_matrix[1][2]*input_pts[i][2] + trans_matrix[1][3];

                c = trans_matrix[2][0]*input_pts[i][0] + trans_matrix[2][1]*input_pts[i][1] 
                		+ trans_matrix[2][2]*input_pts[i][2] + trans_matrix[2][3];

                final_pts[i][0]=a;
                final_pts[i][1]=b;
                final_pts[i][2]=c;
        }
}
void translate(double x , double y, double z)
{
	trans_matrix[0][0] = 1;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = 0;
    	trans_matrix[0][3] = x;

    	trans_matrix[1][0] = 0;
    	trans_matrix[1][1] = 1;
    	trans_matrix[1][2] = 0;
    	trans_matrix[1][3] = y;

    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = 1;
    	trans_matrix[2][3] = z;

    	trans_matrix[3][0] = 0;
    	trans_matrix[3][1] = 0;
    	trans_matrix[3][2] = 0;
    	trans_matrix[3][3] = 1;
}

void scale_x_y_z(double sx, double sy, double sz) 
{
    	trans_matrix[0][0] = sx;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = 0;
    	trans_matrix[0][3] = 0;

    	trans_matrix[1][0] = 0;
    	trans_matrix[1][1] = sy;
    	trans_matrix[1][2] = 0;
    	trans_matrix[1][3] = 0;

    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = sz;
    	trans_matrix[2][3] = 0;

    	trans_matrix[3][0] = 0;
    	trans_matrix[3][1] = 0;
    	trans_matrix[3][2] = 0;
    	trans_matrix[3][3] = 1;
}
void reflectAroundXY(void) 
{
    	trans_matrix[0][0] = 1;
    	trans_matrix[0][1] = 0;
    	trans_matrix[0][2] = 0;
    	trans_matrix[0][3] = 0;

    	trans_matrix[1][0] = 0;
    	trans_matrix[1][1] = 1;
    	trans_matrix[1][2] = 0;
    	trans_matrix[1][3] = 0;

    	trans_matrix[2][0] = 0;
    	trans_matrix[2][1] = 0;
    	trans_matrix[2][2] = -1;
    	trans_matrix[2][3] = 0;

    	trans_matrix[3][0] = 0;
    	trans_matrix[3][1] = 0;
    	trans_matrix[3][2] = 0;
    	trans_matrix[3][3] = 1;
}

void  shear(double shear_factor_x)
{
	trans_matrix[0][0] = 1;
	trans_matrix[0][1] = 0;
	trans_matrix[0][2] = shear_factor_x;
	trans_matrix[0][3] = 0;

	trans_matrix[1][0] = 0;
	trans_matrix[1][1] = 1;
	trans_matrix[1][2] = 0;
	trans_matrix[1][3] = 0;

	trans_matrix[2][0] = 0;
	trans_matrix[2][1] = 0;
	trans_matrix[2][2] = 1;
	trans_matrix[2][3] = 0;

	trans_matrix[3][0] = 0;
	trans_matrix[3][1] = 0;
	trans_matrix[3][2] = 0;
	trans_matrix[3][3] = 1;
}

void rotate(double a)
{
	x = PI / 180 ;
	a = a*x;
	trans_matrix[0][0] = 1;
	trans_matrix[0][1] = 0;
	trans_matrix[0][2] = 0;
	trans_matrix[0][3] = 0;

	trans_matrix[1][0] = 0;
	trans_matrix[1][1] = cos(a);
	trans_matrix[1][2] = -1*sin(a);
	trans_matrix[1][3] = 0;

	trans_matrix[2][0] = 0;
	trans_matrix[2][1] = sin(a);
	trans_matrix[2][2] = cos(a);
	trans_matrix[2][3] = 0;

	trans_matrix[3][0] = 0;
	trans_matrix[3][1] = 0;
	trans_matrix[3][2] = 0;
	trans_matrix[3][3] = 1;
}
void transformPoints()
{
        int choice ;
        printf("\nEnter your choice:\n1. Translation\n2. Scaling\n3. Reflection\n4. Shear\n5. Rotate\n");
        printf("Your choice : ");
        scanf("%d",&choice);

        double x , y , z, scale_factor_x, scale_factor_y, scale_factor_z, shear_factor_x , rotation_angle_x ;
        double shear_factor_y, shear_factor_z;

        if(choice==1) 
        {
                printf("Enter translate_x : ");
                scanf("%lf",&x);
                printf("Enter translate_y : ");
                scanf("%lf",&y);
                printf("Enter translate_z : ");
                scanf("%lf",&z);
                translate(x,y,z);
        }

        if(choice==2)
        {
                printf("Enter scale_factor_x : ");
                scanf("%lf",&scale_factor_x);
                printf("Enter scale_factor_y : ");
                scanf("%lf",&scale_factor_y);
                printf("Enter scale_factor_z : ");
                scanf("%lf",&scale_factor_z);
                scale_x_y_z(scale_factor_x,scale_factor_y,scale_factor_z);
        }

        if(choice==3)
        {
                reflectAroundXY();
        }

        if(choice==4)
        {
                printf("Enter  the shear_factor_x :  ");
                scanf("%lf",&shear_factor_x);
                
                shear(shear_factor_x);
        }

        if(choice==5)
        {
                printf("\nEnter the rotation_angle :  ");
                scanf("%lf",&rotation_angle_x);
                rotate(rotation_angle_x);
        }
}


int main(int argc, char const *argv[])
{
	glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB);
    	glutInitWindowSize(800, 800);
    	glutInitWindowSize(800, 800);
    	transformPoints();
    	matrix_multiplication();
    	glClearColor(1.0, 1.0, 1.0, 1.0);
    	gluOrtho2D(-400, 400, -400, 400);
        glutCreateWindow("\nPolygon transformations");
        glutDisplayFunc(displayPolygon);
        glutMainLoop();
	return 0;
}