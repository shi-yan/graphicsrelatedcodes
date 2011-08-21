/*
 *  Pair.cpp
 *  3DTest
 *
 *  Created by Shi Yan on 1/4/11.
 *  Copyright 2011 Univerisity of California, Davis. All rights reserved.
 *
 */
#include <QGLWidget>

#include "Pair.h"

Transformation SamplePair::getTransformation()
{
     t=computeTransformation(sample1.getSample(0),sample2.getSample(0));
     return t;
}


void SamplePair::draw()
{
    if(testinfo)
    {
        glBegin(GL_LINES);

        glVertex3f(sample1.getSample(0).getPos().X(),sample1.getSample(0).getPos().Y(),sample1.getSample(0).getPos().Z());
        glVertex3f(sample2.getSample(0).getPos().X(),sample2.getSample(0).getPos().Y(),sample2.getSample(0).getPos().Z());


        glEnd();
    }
}
