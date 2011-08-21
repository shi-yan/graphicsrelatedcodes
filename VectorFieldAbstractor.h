/*
 *  VectorFieldAbstractor.h
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/15/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#ifndef __VectorFieldAbstractor__
#define __VectorFieldAbstractor__

#include "DockWidget.h"

class VectorFieldAbstractor:public DockWidget
{


public:
    VectorFieldAbstractor(QString name,QWidget *parent):DockWidget(name,parent){};
    ~VectorFieldAbstractor(){};
};

#endif
