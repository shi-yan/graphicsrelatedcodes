/*
 *  Signature.cpp
 *  3DTest
 *
 *  Created by Shi Yan on 1/3/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#include "Signature.h"


void Signature::refreshBoundingBox()
{
	
}

double distance(Signature &s1,Signature &s2)
{
	if (s1.getSampleSize()!=s2.getSampleSize()) 
	{
		return -1.0;
	}
	else 
	{
		double r=0.0;
		
		for (int i=0; i<s1.getSampleSize(); ++i) 
		{
			r+=distance(s1.sampleList[i],s2.sampleList[i]);
		}
		
		return r/(double)s1.getSampleSize();
	}

}

void Signature::add(Sample &in)
{
	sampleList.push_back(in);
        bbox.Add(in.getPos());
}

void Signature::draw()
{
    for(std::vector<Sample>::iterator iter=sampleList.begin();iter!=sampleList.end();++iter)
    {
        iter->draw();
    }

}
