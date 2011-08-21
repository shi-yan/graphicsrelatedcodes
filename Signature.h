/*
 *  Signature.h
 *  3DTest
 *
 *  Created by Shi Yan on 1/3/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#ifndef __Signature__
#define __Signature__

#include "Sample.h"
#include "Box3.h"
#include <vector>

class Signature
{
private:
	std::vector<Sample> sampleList;
	
        GGL::Box3<float> bbox;
	
public:
	int getSampleSize()
	{
		return sampleList.size();
	};
	
	void refreshBoundingBox();
	
	friend double distance(Signature &s1,Signature &s2);
	
	void add(Sample &in);

        Sample & getSample(int id)
        {
            return sampleList[id];
        }

	void operator=(const Signature &in)
	{
		sampleList.clear();
		sampleList.resize(in.sampleList.size());
		
		std::copy(in.sampleList.begin(),in.sampleList.end(),sampleList.begin());
		
		bbox=in.bbox;
	};
	
	Signature(const Signature &in)
	{
		sampleList.clear();
		sampleList.resize(in.sampleList.size());
		
		std::copy(in.sampleList.begin(),in.sampleList.end(),sampleList.begin());
		
		bbox=in.bbox;
	};
	
	Signature():bbox()
	{};
	
	void draw();
	
};

#endif
