/*
 *  Sample.h
 *  3DTest
 *
 *  Created by Shi Yan on 12/8/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#ifndef __Sample__
#define __Sample__

#include "Point3.h"
#include "transformation.h"
class Sample
{
private:
	GGL::Point3f pos;
	double jacobian[3][3];
	GGL::Point3f eigenVector;
	GGL::Point3f z;
	GGL::Point3f x;
	GGL::Point3f y;
	
	double signature[3][3];
	
        double descriptor;
public:
	Sample();
	~Sample();
	
	void generate(int i);
	void generateJacobian();
	void computeSignature();
	void draw();

        void initializeWithPos(GGL::Point3f &p);

        void computeDescriptor();
	
	Sample(const Sample & in);
	void operator=(const Sample & in);
	
	friend double distance(Sample n1,Sample n2);
        friend Transformation computeTransformation(const Sample &n1,const Sample &n2);
	
	GGL::Point3f & getPos()
	{
		return pos;
	};
        /*
        void setPos(const )
        {

        };*/

        GGL::Point3f & getZ()
        {
            return z;
        };

        GGL::Point3f & getX()
        {
            return x;
        };

        GGL::Point3f & getY()
        {
            return y;
        };

        GGL::Point3f & getEigen()
        {
            return eigenVector;
        }
	
};

Transformation computeTransformation(const Sample &n1,const Sample &n2);

#endif
