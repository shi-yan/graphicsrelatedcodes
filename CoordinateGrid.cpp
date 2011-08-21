#include "CoordinateGrid.h"

CoordinateGrid::CoordinateGrid(void):
	CoordinateGridCallIDXY(0),CoordinateGridCallIDYZ(0),CoordinateGridCallIDXZ(0)
{
}

void CoordinateGrid::prepare()
{
	CoordinateGridCallIDXY=glGenLists(3);
	CoordinateGridCallIDYZ=CoordinateGridCallIDXY+1;
	CoordinateGridCallIDXZ=CoordinateGridCallIDXY+2;

	glNewList(CoordinateGridCallIDXY,GL_COMPILE);
	glColor3ub(155,174,155);
	glBegin(GL_LINES);
	for(int i=0;i<9;++i)
	{
		if(i==4)
			continue;

		glVertex3f(-80.0f+i*20.0f,-80.0f,0.0f);
		glVertex3f(-80.0f+i*20.0f,80.0f,0.0f);

	}

	for(int i=0;i<9;++i)
	{
		if(i==4)
			continue;

		glVertex3f(-80,-80.0f+i*20.0f,0.0f);
		glVertex3f(80,-80.0f+i*20.0f,0.0f);
	}
	glEnd();


	glBegin(GL_LINES);

	glColor3ub(125,125,125);
	glVertex3f(-80,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,-80,0);
	glVertex3f(0,0,0);

	glColor3ub(176,98,62);
	glVertex3f(80,0,0);
	glVertex3f(0,0,0);

	glColor3ub(62,143,183);
	glVertex3f(0,80,0);
	glVertex3f(0,0,0);

	glEnd();


	glEndList();

	glNewList(CoordinateGridCallIDYZ,GL_COMPILE);

	

	glEndList();

		
	glNewList(CoordinateGridCallIDXZ,GL_COMPILE);

	

	glEndList();


}

void CoordinateGrid::draw(enum GridMode mode)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	
	switch(mode)
	{
	case XY:
		glCallList(CoordinateGridCallIDXY);
		break;
	case XZ:
		glCallList(CoordinateGridCallIDXZ);
		break;
	case YZ:
		glCallList(CoordinateGridCallIDYZ);
		break;
	}
}

CoordinateGrid::~CoordinateGrid(void)
{
	glDeleteLists(CoordinateGridCallIDXY,3);
}
