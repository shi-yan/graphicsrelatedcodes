/*
 *  DownSampler.h
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/14/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#ifndef __DownSampler__
#define __DownSampler__

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "DockWidget.h"

class DownSampler:public DockWidget
{
	Q_OBJECT
private:
    QScrollArea *downSamplerScrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *downSamplerGridLayout;
    QLabel *downSampleDimensionXLabel;
    QSpinBox *downSampleDimensionXSpinBox;
    QLabel *downSampleDimensionYLabel;
    QSpinBox *downSampleDimensionYSpinBox;
    QLabel *downSampleDimensionZLabel;
    QPushButton *savePushButton;
    QSpinBox *downSampleDimensionZSpinBox;
    QSpacerItem *verticalSpacer;
    QLabel *downSampleDimensionLabel;

public:
	DownSampler(QString name,QWidget *parent);
	~DownSampler();
};

#endif