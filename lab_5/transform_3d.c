#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

typedef float Matrix4x4 [4][4];

Matrix4x4 theMatrix;
float Initial_Points[8][3]={{0,0,-100},{100,0,-100},{100,100,-100},{0,100,-100},{30,30,0},{130,30,0},{130,130,0},{30,130,0}};
float Final_Points[8][3];
float TransDistX,TransDistY,TransDistZ;
float ScaleX,ScaleY,ScaleZ;
float RotationAngle;
int choice,RotationAxis,ReflectionPlane;

void matrixSetIdentity(Matrix4x4 m){
        int i, j;
        for (i=0; i<4; i++){
                for (j=0; j<4; j++){
                        m[i][j] = (i == j);
                }
        }
}      

// Multiplies matrix a times b, putting result in theMatrix
void matrixPreMultiply(Matrix4x4 a , Matrix4x4 b){
        int i,j;
        Matrix4x4 tmp;
        //b can be theMatrix so first create a new matrix and then copy it in b
        for (i = 0; i < 4; i++){
                for (j = 0; j < 4; j++){
                        tmp[i][j]=a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j];
                }
        }
        for (i = 0; i < 4; i++){
                for (j = 0; j < 4; j++){
                        theMatrix[i][j] = tmp[i][j];
                }
        }
}

void Translate(int tx, int ty, int tz){
        Matrix4x4 m;
        matrixSetIdentity(m);
        m[0][3] = tx;
        m[1][3] = ty;
        m[2][3] = tz;
        matrixPreMultiply(m, theMatrix);
}

void Shear()
{
	Matrix4x4 m;
	matrixSetIdentity(m);
	m[0][1] = 1;
	m[0][2] = 0;
	matrixPreMultiply(m , theMatrix);
}

void Scale(float sx , float sy ,float sz){
        Matrix4x4 m;
        matrixSetIdentity(m);
        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = sz;
        matrixPreMultiply(m , theMatrix);
}

void RotateX(float angle){
        Matrix4x4 m;
        matrixSetIdentity(m);
        angle = angle*22/1260;
        m[1][1] = cos(angle);
        m[1][2] = -sin(angle);
        m[2][1] = sin(angle);
        m[2][2] = cos(angle);
        matrixPreMultiply(m , theMatrix);
}

void RotateY(float angle){
        Matrix4x4 m;
        matrixSetIdentity(m);
        angle = angle*22/1260;
        m[0][0] = cos(angle);
        m[0][2] = sin(angle);
        m[2][0] = -sin(angle);
        m[2][2] = cos(angle);
        matrixPreMultiply(m , theMatrix);
}

void RotateZ(float angle){
        Matrix4x4 m;
        matrixSetIdentity(m);
        angle = angle*22/1260;
        m[0][0] = cos(angle);
        m[0][1] = -sin(angle);
        m[1][0] = sin(angle);
        m[1][1] = cos(angle);
        matrixPreMultiply(m , theMatrix);
}

void Reflect(void){
        Matrix4x4 m;
        matrixSetIdentity(m);
        switch(ReflectionPlane){
                case 1:
                        m[2][2] = -1;
                        break;
                case 2:
                        m[0][0] = -1;
                        break;
                case 3:
                        m[1][1] = -1;
                        break;
        }
        matrixPreMultiply(m , theMatrix);
}

void TransformPoints(void){
        int i,k;
        float tmp ;
        for(k=0 ; k<8 ; k++){
        	for (i=0 ; i<3 ; i++){
                        Final_Points[k][i] = theMatrix[i][0]*Initial_Points[k][0] + theMatrix[i][1]*Initial_Points[k][1]+ theMatrix[i][2]*Initial_Points[k][2] + theMatrix[i][3];
                }
        }
}

void Axes(void){
        glColor3f (0.0, 0.0, 0.0);               // Set the color to BLACK
        glBegin(GL_LINES);                       // Plotting X-Axis
        glVertex2s(-1000 ,0);
        glVertex2s( 1000 ,0);
        glEnd();
        glBegin(GL_LINES);                       // Plotting Y-Axis
        glVertex2s(0 ,-500);
        glVertex2s(0 , 500);
        glEnd();
}

//Display the Figure
void Draw(float a[8][3])                 //Display the Figure
{
	int i;
	glColor3f (1.0, 0, 0);
	glBegin(GL_POLYGON);       
	glVertex3f(a[0][0],a[0][1],a[0][2]);
	glVertex3f(a[1][0],a[1][1],a[1][2]);
	glVertex3f(a[2][0],a[2][1],a[2][2]);
	glVertex3f(a[3][0],a[3][1],a[3][2]);
	glEnd();
	i=0;
	glColor3f (0, 1.0, 0);
	glBegin(GL_POLYGON);       
	glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
	glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
	glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
	glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
	glEnd();
	glColor3f (0, 0, 1.0);
	glBegin(GL_POLYGON);       
	glVertex3f(a[0][0],a[0][1],a[0][2]);
	glVertex3f(a[3][0],a[3][1],a[3][2]);
	glVertex3f(a[7][0],a[7][1],a[7][2]);
	glVertex3f(a[4][0],a[4][1],a[4][2]);
	glEnd();
	i=1;
	glColor3f (1.0, 1.0, 0);
	glBegin(GL_POLYGON);       
	glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
	glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
	glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
	glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
	glEnd();
	i=2;
	glColor3f (1.0, 0, 1.0);
	glBegin(GL_POLYGON);       
	glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
	glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
	glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
	glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
	glEnd();
	i=4;
	glColor3f (0, 1.0, 1.0);
	glBegin(GL_POLYGON);       
	glVertex3f(a[0+i][0],a[0+i][1],a[0+i][2]);
	glVertex3f(a[1+i][0],a[1+i][1],a[1+i][2]);
	glVertex3f(a[2+i][0],a[2+i][1],a[2+i][2]);
	glVertex3f(a[3+i][0],a[3+i][1],a[3+i][2]);
	glEnd();
}

void display(void){
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Axes();
        // Set the color to RED
        glColor3f (1.0, 0.0, 0.0);
        Draw(Initial_Points);
        matrixSetIdentity(theMatrix);
        switch(choice){
                case 1:
                        Translate(TransDistX , TransDistY ,TransDistZ);
                        break;
                case 2:
                        Scale(ScaleX, ScaleY, ScaleZ);
                        break;
                case 3:
                        switch(RotationAxis){
                                case 1:
                                        RotateX(RotationAngle);
                                        break;
                                case 2:
                                        RotateY(RotationAngle);
                                        break;
                                case 3:
                                        RotateZ(RotationAngle);
                                        break;
                        }
                        break;
                case 4:
                        Reflect();
                        break;
                case 5: Shear();
 			break;
        }  
        TransformPoints();   
        Draw(Final_Points);
        glFlush();
}

void input_choice(){
        printf("Enter your choice number:\n1> Translation\n2> Scaling\n3> Rotation\n4> Reflection\n5> Shear\n");
        scanf("%d",&choice);
        switch(choice){
                case 1:
                	TransDistX = 50;
                	TransDistY = 50;
                	TransDistZ = 0;
                        break;
                case 2:
                        ScaleX = 2 ;
                        ScaleY = 2 ;
                        ScaleZ = 2 ;
                        break;
                case 3:
                        //Rotation Axis . 1> X 2> Y 3> Z
                        RotationAxis = 3;
                        RotationAngle = 45;
                        break;
                case 4:
                        //Reflection Plane 1>XY 2>YZ 3>XZ
                        ReflectionPlane = 3;
                        break;
                case 5: 
                	//shearx
                	break;
                default:
                        printf("Invalid Choice\n");
                        break;
        }
}

void init(void){
        glClearColor (1.0, 1.0, 1.0, 1.0);
        glOrtho(-500.0, 500.0, -300.0, 300.0, -300.0, 300.0); 
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main (int argc, char *argv){
        glutInit(&argc, &argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1000, 600);
	glutInitWindowPosition (0, 0);
	glutCreateWindow (" Basic 3d Transformations ");
	init ();
	input_choice();
	glutDisplayFunc(display);
	glutMainLoop();
        return 0;
}