/*
 *  DownSampler.cpp
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/14/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#include "DownSampler.h"

DownSampler::DownSampler(QString name,QWidget *parent):DockWidget(name,parent)
{
	setObjectName(QString::fromUtf8("DownSampler"));
	resize(400, 300);
	
	downSamplerScrollArea = new QScrollArea(this);
	downSamplerScrollArea->setObjectName(QString::fromUtf8("downSamplerScrollArea"));
	downSamplerScrollArea->setWidgetResizable(true);
	scrollAreaWidgetContents = new QWidget();
	scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
	scrollAreaWidgetContents->setGeometry(QRect(0, 0, 374, 274));
	downSamplerGridLayout = new QGridLayout(scrollAreaWidgetContents);
	downSamplerGridLayout->setObjectName(QString::fromUtf8("downSamplerGridLayout"));
	downSampleDimensionXLabel = new QLabel(scrollAreaWidgetContents);
	downSampleDimensionXLabel->setObjectName(QString::fromUtf8("downSampleDimensionXLabel"));
	
	downSamplerGridLayout->addWidget(downSampleDimensionXLabel, 1, 0, 1, 1);
	
	downSampleDimensionXSpinBox = new QSpinBox(scrollAreaWidgetContents);
	downSampleDimensionXSpinBox->setObjectName(QString::fromUtf8("downSampleDimensionXSpinBox"));
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(downSampleDimensionXSpinBox->sizePolicy().hasHeightForWidth());
	downSampleDimensionXSpinBox->setSizePolicy(sizePolicy);
	
	downSamplerGridLayout->addWidget(downSampleDimensionXSpinBox, 1, 1, 1, 1);
	
	downSampleDimensionYLabel = new QLabel(scrollAreaWidgetContents);
	downSampleDimensionYLabel->setObjectName(QString::fromUtf8("downSampleDimensionYLabel"));
	
	downSamplerGridLayout->addWidget(downSampleDimensionYLabel, 2, 0, 1, 1);
	
	downSampleDimensionYSpinBox = new QSpinBox(scrollAreaWidgetContents);
	downSampleDimensionYSpinBox->setObjectName(QString::fromUtf8("downSampleDimensionYSpinBox"));
	sizePolicy.setHeightForWidth(downSampleDimensionYSpinBox->sizePolicy().hasHeightForWidth());
	downSampleDimensionYSpinBox->setSizePolicy(sizePolicy);
	
	downSamplerGridLayout->addWidget(downSampleDimensionYSpinBox, 2, 1, 1, 1);
	
	downSampleDimensionZLabel = new QLabel(scrollAreaWidgetContents);
	downSampleDimensionZLabel->setObjectName(QString::fromUtf8("downSampleDimensionZLabel"));
	
	downSamplerGridLayout->addWidget(downSampleDimensionZLabel, 3, 0, 1, 1);
	
	savePushButton = new QPushButton(scrollAreaWidgetContents);
	savePushButton->setObjectName(QString::fromUtf8("savePushButton"));
	
	downSamplerGridLayout->addWidget(savePushButton, 4, 0, 1, 2);
	
	downSampleDimensionZSpinBox = new QSpinBox(scrollAreaWidgetContents);
	downSampleDimensionZSpinBox->setObjectName(QString::fromUtf8("downSampleDimensionZSpinBox"));
	sizePolicy.setHeightForWidth(downSampleDimensionZSpinBox->sizePolicy().hasHeightForWidth());
	downSampleDimensionZSpinBox->setSizePolicy(sizePolicy);
	
	downSamplerGridLayout->addWidget(downSampleDimensionZSpinBox, 3, 1, 1, 1);
	
	verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	
	downSamplerGridLayout->addItem(verticalSpacer, 5, 0, 1, 2);
	
	downSampleDimensionLabel = new QLabel(scrollAreaWidgetContents);
	downSampleDimensionLabel->setObjectName(QString::fromUtf8("downSampleDimensionLabel"));
	
	downSamplerGridLayout->addWidget(downSampleDimensionLabel, 0, 0, 1, 2);
	
	downSamplerScrollArea->setWidget(scrollAreaWidgetContents);
	
	setWidget(downSamplerScrollArea);
	
	downSampleDimensionXLabel->setText(QApplication::translate("DownSampler", "X:", 0, QApplication::UnicodeUTF8));
	downSampleDimensionYLabel->setText(QApplication::translate("DownSampler", "Y:", 0, QApplication::UnicodeUTF8));
	downSampleDimensionZLabel->setText(QApplication::translate("DownSampler", "Z:", 0, QApplication::UnicodeUTF8));
	savePushButton->setText(QApplication::translate("DownSampler", "Save Down-Sampled Data", 0, QApplication::UnicodeUTF8));
	downSampleDimensionLabel->setText(QApplication::translate("DownSampler", "Down Sample Dimension:", 0, QApplication::UnicodeUTF8));
	
	QMetaObject::connectSlotsByName(this);
}

DownSampler::~DownSampler()
{
	
}