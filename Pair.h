/*
 *  Pair.h
 *  3DTest
 *
 *  Created by Shi Yan on 1/4/11.
 *  Copyright 2011 Univerisity of California, Davis. All rights reserved.
 *
 */

#ifndef __Pair__
#define __Pair__

#include "Signature.h"
#include "transformation.h"

class SamplePair
{
private:
	Signature sample1;
	Signature sample2;
	double distance;
        Transformation t;

        int testinfo;

public:
	void grow();
	double computeDistance();
	SamplePair():sample1(),sample2()
	{
		
	};

        void setTestInfo(int _info)
        {
            testinfo=_info;
        };
	
        SamplePair(const Signature & s1,const Signature &s2,const double dis):sample1(s1),sample2(s2),distance(dis),testinfo(0)
	{};
	~SamplePair(){};
	
	void updateDistance();
	
	void setDistance(double _dis)
	{
		distance=_dis;
	};
	
	double getDistance()
	{
		return distance;
	};

        Transformation getTransformation();

        void draw();
	
};

#endif
