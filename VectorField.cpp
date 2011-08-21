#include "VectorField.h"
#include <fstream>
#include <math.h>
#include <vector>
#include <QGLWidget>
#include "Point3.h"




void VectorField::init(const char *filename,int _sizex,int _sizey,int _sizez,const QString & _dataName)
{
    dataName=_dataName;

	xSize=_sizex;
	ySize=_sizey;
	zSize=_sizez;
	
	
	if (vectorField) {
		delete [] vectorField;
	}
	
	vectorField=new FVector[xSize*ySize*zSize];
	
	FILE *fp=fopen(filename,"rb");
	fread(vectorField ,sizeof(struct FVector),xSize*ySize*zSize,fp);
	fclose(fp);

	for(int x=0;x<xSize;++x)
		for(int y=0;y<ySize;++y)
			for(int z=0;z<zSize;++z)
			{
				FVector v=vectorField[(int)x + (int)y*xSize + (int)z*xSize*ySize];

				float mag=sqrt(v.x*v.x+v.y*v.y+v.z*v.z);

				if(mag>maxMag)
					maxMag=mag;
				
				if(mag<minMag)
					minMag=mag;
			}

        emit dataUpdated();
}



GGL::Point3f VectorField::getVector(float x,float y,float z)
{

	if(x>(float)(xSize-1) || x<0.0f || y>(float)(ySize-1) || y<0.0f || z<0.0f ||z>(float)(zSize-1))
	{
		FVector i1;
		i1.x=0.0f;
		i1.y=0.0f;
		i1.z=0.0f;
                return GGL::Point3f(0,0,0);
	}

	float xd=x-(int)x;
	float yd=y-(int)y;
	float zd=z-(int)z;

	float azd=1.0f-zd;

	FVector l=vectorField[(int)x + (int)y*xSize + (int)z*xSize*ySize];
	FVector r=vectorField[(int)x + (int)y*xSize + ((int)z+1)*xSize*ySize];

	FVector i1;
	i1.x=l.x*azd+r.x*zd;
	i1.y=l.y*azd+r.y*zd;
	i1.z=l.z*azd+r.z*zd;

	l=vectorField[(int)x + ((int)y+1)*xSize + (int)z*xSize*ySize];
	r=vectorField[(int)x + ((int)y+1)*xSize + ((int)z+1)*xSize*ySize];

	FVector i2;
	i2.x=l.x*azd+r.x*zd;
	i2.y=l.y*azd+r.y*zd;
	i2.z=l.z*azd+r.z*zd;


	l=vectorField[(int)x+1 + (int)y*xSize + (int)z*xSize*ySize];
	r=vectorField[(int)x+1 + (int)y*xSize + ((int)z+1)*xSize*ySize];

	FVector j1;
	j1.x=l.x*azd+r.x*zd;
	j1.y=l.y*azd+r.y*zd;
	j1.z=l.z*azd+r.z*zd;

	l=vectorField[(int)x+1 + ((int)y+1)*xSize + (int)z*xSize*ySize];
	r=vectorField[(int)x+1 + ((int)y+1)*xSize + ((int)z+1)*xSize*ySize];

	FVector j2;
	j2.x=l.x*azd+r.x*zd;
	j2.y=l.y*azd+r.y*zd;
	j2.z=l.z*azd+r.z*zd;


	FVector w1;
	w1.x=i1.x*(1.0f-yd)+i2.x*yd;
	w1.y=i1.y*(1.0f-yd)+i2.y*yd;
	w1.z=i1.z*(1.0f-yd)+i2.z*yd;

	FVector w2;
	w2.x=j1.x*(1.0f-yd)+j2.x*yd;
	w2.y=j1.y*(1.0f-yd)+j2.y*yd;
	w2.z=j1.z*(1.0f-yd)+j2.z*yd;

	FVector result;	
	result.x=w1.x*(1.0f-xd)+w2.x*xd;
	result.y=w1.y*(1.0f-xd)+w2.y*xd;
	result.z=w1.z*(1.0f-xd)+w2.z*xd;

        return GGL::Point3f(result.x,result.y,result.z);
}


GGL::Point3f VectorField::getCenter()
{
	FVector result;
	result.x=0.5f*(float)(xSize-1);
	result.y=0.5f*(float)(ySize-1);
	result.z=0.5f*(float)(zSize-1);
        return GGL::Point3f(result.x,result.y,result.z);
}


float VectorField::getRadius()
{
        return sqrt((double)((xSize-1)*(xSize-1)+(ySize-1)*(ySize-1)+(zSize-1)*(zSize-1)));
}

void VectorField::draw()
{

	glDisable(GL_LIGHTING);
	
	glColor3ub(0, 0, 0);
	
	glBegin(GL_LINE_STRIP);
	
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f, 0.0f, zSize);
	
	glVertex3f(0.0f,ySize,zSize);
	glVertex3f(0.0f, ySize, 0.0f);
	
	glVertex3f(0.0f, 0.0f, 0.0f);

	glVertex3f(xSize, 0.0f, 0.0f);
	
	glVertex3f(xSize, 0.0f, zSize);
	
	glVertex3f(xSize, ySize, zSize);
	
	glVertex3f(xSize, ySize, 0.0f);
	
	glVertex3f(xSize, 0.0f, 0.0f);
	
	glEnd();
	
	glBegin(GL_LINES);
	glVertex3f(0.0f, ySize, 0.0f);
	glVertex3f(xSize, ySize, 0.0f);
	
	glVertex3f(0.0f, 0.0f, zSize);
	glVertex3f(xSize, 0.0f, zSize);
	
	glVertex3f(0.0f, ySize, zSize);
	glVertex3f(xSize, ySize, zSize);
	glEnd();

	
}
