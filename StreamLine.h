/*
 *  StreamLine.h
 *  3DTest
 *
 *  Created by Shi Yan on 12/8/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __Streamline__
#define __Streamline__

#include <vector>
#include "Point3.h"

class Streamline
{
public:
    static std::vector<Streamline> streamlinePool;

private:
	std::vector<GGL::Point3f> pointlist;
	GGL::Point3f movePoint(float x,float y,float z);
	
public:
	Streamline();
	~Streamline();
	void draw();
	void generate(GGL::Point3f &start);
	void generateRandomly();
	
	Streamline(const Streamline& in);
	void operator=(const Streamline& in);
};

#endif
