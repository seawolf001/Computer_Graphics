#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int point;
int points[99999];

int cmpfunc (const void * a, const void * b)
{
        return ( (*(float*)a > *(float*)b ) ? 1 : 0);
}

int update (int a,int b)
{
	if(a-b>0)
        {        // going up
		return 1;
	}
	if(a-b<0)
        {        // going down
		return -1;
	}
	if(a-b==0)
        {       // horizontal
		return 0;
	}
}

float find_inter(int x,int y,int a,int b,int line)
{
	printf("Finding intersection : %d %d %d %d %d ",x,y,a,b,line);
	float result;
	int ymin;
	int ymax;
	int xmin;
	int xmax;
	if(y<b)
        {
		ymin=y;
		ymax=b;
	}
	else
        {
		ymin=b;
		ymax=y;
	}
	if(x<a)
        {
		xmin=x;
		xmax=a;
	}
	else
        {
		xmin=a;
		xmax=x;
	}
	if(a-x==0)
        {
		if(line<ymin || line>ymax)
                {
			result=-999999;
		}
		else
                {
			result=x;
		}
	}
	else if(b-y==0)
        {
		result= -999999;
		printf("parallel ");
	}
	else
        {
		if(line<ymin || line >ymax)
                {
			result=-999999;
		}
		else
                {
			result = x+((line-y)/((b-y)/(float)(a-x)));
		}
	}
	printf("%f \n",result);
	return result;
}
void display(void)
{
	int i=0;
	int j=0;
	int k=0;
	int ymax=-999999999,ymin=999999999;
	for(i=0;i<2*point;i+=2)
        {
		if(points[i+1]>ymax)
                {
			ymax=points[i+1];
		}
		if(points[i+1]<ymin)
                {
			ymin=points[i+1];
		}
	}
	float final_points[99999];
	int tot=0;
	for(i=ymin;i<ymax+1;i++)
        {
		float inter_points[99999];
		int count=0;
		int flag=0;
		float prev_inter_point=-999999;
		for(j=0;j<2*(point-1);j+=2)
                {
			float inter_point = find_inter(points[j],points[j+1],points[j+2],points[j+3],i);
			if(inter_point==-999999)
                        { // no intersection point
				flag = update(points[j+3],points[j+1]);
				prev_inter_point=inter_point;
				continue;
			}
			if(points[j+3]-points[j+1]>0)
                        { // going up
				if(flag==1 && prev_inter_point==inter_point)
                                {
					flag = update(points[j+3],points[j+1]);
					prev_inter_point=inter_point;
					continue;
				}
			}
			else if(points[j+3]-points[j+1]<0)
                        { // going down
				if(flag==-1 && prev_inter_point==inter_point)
                                {
					flag = update(points[j+3],points[j+1]);
					prev_inter_point=inter_point;
					continue;
				}
			}
			inter_points[count]= inter_point;
			flag = update(points[j+3],points[j+1]);
			prev_inter_point=inter_point;
			count++;
		}
		float inter_point = find_inter(points[2*point-2],points[2*point-1],points[0],points[1],i);
		if(inter_point!=-999999)
                {
			if(points[1]-points[2*point-1]>0)
                        { // going up
				if(flag!=1 || prev_inter_point!=inter_point)
                                {
					inter_points[count]=inter_point;
					count++;
				}
			}
			else if(points[1]-points[2*point-1]<0)
                        { // going down
				if(flag!=-1 || prev_inter_point!=inter_point)
                                {
					inter_points[count]=inter_point;
					count++;
				}
			}
			else
                        { // horizontal
				inter_points[count]=inter_point;
				count++;
			}
		}
		qsort(inter_points, count, sizeof(float), cmpfunc);
		printf("Intersection co-ordinates\n");
		for(k=0;k<count;k=k+1)
                {
			printf("%f %d\n",inter_points[k],i);
		}
		printf("All points\n");
		for(k=0;k<count;k=k+2)
                {
			float l=0;
			if(k>=count-1)
                        {
				break;
			}
			for(l=inter_points[k];l<=inter_points[k+1];l=l+1)
                        {
				final_points[tot]=l;
				tot++;
				final_points[tot]=i;
				tot++;
				printf("%f %d\n",l,i);
			}
		}
	}

	printf("Plotting filled points\n");
	       glClear(GL_COLOR_BUFFER_BIT);
	                glPointSize(1.0);
                        glBegin(GL_LINES);
                                glColor3f(0.0,0.0,0.0);
                                glVertex2d(-300,0);
                        	glVertex2d(300,0);
                        	glVertex2d(0,300);
                        	glVertex2d(0,-300);
                                glColor3f(0.0,1.0,0.0);
	                glEnd();

        glBegin(GL_POINTS);
	       for(i=0;i<tot;i+=2)
                {
		        printf("%f %f\n",final_points[i],final_points[i+1]);
		        glVertex2f(final_points[i],final_points[i+1]);
	        }
	glEnd();
	glFlush();
}
void Init()
{
	/* Set clear color to white */
	glClearColor(1.0,1.0,1.0,1);
	/* Set fill color to black */
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(-300 , 300 , -300 , 300);
}
int main (int argc, char **argv){
	int i;
	printf("Enter the no. of points in the polygon : ");
	scanf("%i",&point);
	for(i=0;i<2*point;i+=2)
        {
		printf("Enter the co-ordinate of %dth point     : ",(i/2)+1);
		scanf("%i%i",&points[i],&points[i+1]);
	}
	/* Initialise GLUT library */
	glutInit(&argc,argv);
	/* Set the initial display mode */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/* Set the initial window position and size */
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	/* Create the window with title "DDA_Line" */
	glutCreateWindow("Polygon filling algorithm");
	/* Initialize drawing colors */
	Init();
	/* Call the displaying function */
	glutDisplayFunc(display);
	/* Keep displaying untill the program is closed */
	glutMainLoop();
	return 0;
}
