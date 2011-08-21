/*
 *  StreamLine.cpp
 *  3DTest
 *
 *  Created by Shi Yan on 12/8/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "StreamLine.h"
#include "VectorField.h"
#include <QGLWidget>
//#include <sys/time.h>

std::vector<Streamline> Streamline::streamlinePool;

Streamline::Streamline()
{

}

Streamline::~Streamline()
{

}


GGL::Point3f Streamline::movePoint(float x,float y,float z)
{
	
	
	
	//const float deltaT=0.025f;
	
	GGL::Point3f pos(x,y,z);
	
        GGL::Point3f dir=VectorField::getSingleton().getVector(x,y,z);
	
        float deltaT=1.5f/(dir.length());
	
	if (deltaT>2.0f) {
		deltaT=1.5f;
	}
	
        GGL::Point3f dd(dir);
	
	GGL::Point3f k1(dd*deltaT);
	
	GGL::Point3f tempP=pos+(k1*0.5f);
	
	dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());
	
        dd=(dir);
	
	GGL::Point3f  k2=dd*deltaT;
	
	tempP=pos+k2*0.5f;
	
	dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());
	
	
        dd=(dir);
	
	GGL::Point3f  k3=dd*deltaT;
	
	tempP=pos+(k3*0.5f);
	
	dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());
	
        dd=(dir);
	
	GGL::Point3f  k4=dd*deltaT;
	
	pos+=(k1+k2*2.0f+k3*3.0f+k4)*(1.0f/6.0f);
	
	return pos;
}



void Streamline::draw()
{
	glColor4ub(100, 0, 0,80);
	glBegin(GL_LINE_STRIP);
	for (std::vector<GGL::Point3f>::iterator iter=pointlist.begin(); iter!=pointlist.end(); ++iter) {
		glVertex3f((*iter).X(),(*iter).Y(),(*iter).Z());
	}
	glEnd();
}

Streamline::Streamline(const Streamline & in)
{
	pointlist.clear();
	pointlist.resize(in.pointlist.size());
	std::copy(in.pointlist.begin(),in.pointlist.end(),pointlist.begin());
}

void Streamline::operator=(const Streamline & in)
{
	pointlist.clear();
	pointlist.resize(in.pointlist.size());
	std::copy(in.pointlist.begin(),in.pointlist.end(),pointlist.begin());
}

void Streamline::generate(GGL::Point3f &start)
{
	GGL::Point3f current(start.X(),start.Y(),start.Z());
	
	pointlist.push_back(current);
	
	for (int i=0; i<500; ++i) 
	{
		GGL::Point3f newpos=movePoint(current.X(),current.Y(),current.Z());
		float length=(newpos-current).length();
		
		if (length<0.00001f) {
			break;
		}
		
		current=newpos;
		pointlist.push_back(current);
	}
}

void Streamline::generateRandomly()
{
	GGL::Point3f start( (float)(rand()%6400)/6400.0f*(VectorField::getSingleton().xSize-1) , 
	                    (float)(rand()%6400)/6400.0f*(VectorField::getSingleton().ySize-1) ,
	                    (float)(rand()%6400)/6400.0f*(VectorField::getSingleton().zSize-1) );
	generate(start);
}
