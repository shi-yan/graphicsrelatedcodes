#pragma once

#include "Point3.h"

class Vertex
{
public:
	GGL::Point3f position;
	GGL::Point3f normal;
	GGL::Point3f color;
	float r;
	int debugID;

	float tempDistance;

	int startIdx;
	int cuttingPlaneLength;

	int uid;
	int listID;

public:
	Vertex(void);
	Vertex(GGL::Point3f &_position,GGL::Point3f &_normal,float _r);
	Vertex(GGL::Point3f &_position,GGL::Point3f &_normal);
	~Vertex(void);
};
