/*
 *  FeatureDetector.cpp
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/15/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#include "FeatureDetector.h"
#include "featuredetectiondata.h"
#include "Sample.h"
#include <cstdio>

FeatureDetector::FeatureDetector(QString name,QWidget *parent):DockWidget(name,parent)
{
    setObjectName(QString::fromUtf8("FeatureDetector"));
   dockWidgetContents = new QWidget();
   dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
   horizontalLayout = new QHBoxLayout(dockWidgetContents);
   horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
   newSampleGroupBox = new QGroupBox(dockWidgetContents);
   newSampleGroupBox->setObjectName(QString::fromUtf8("newSampleGroupBox"));
   newSamplersVerticalLayout = new QVBoxLayout(newSampleGroupBox);
   newSamplersVerticalLayout->setObjectName(QString::fromUtf8("newSamplersVerticalLayout"));
   newSampleSpinBox = new QSpinBox(newSampleGroupBox);
   newSampleSpinBox->setObjectName(QString::fromUtf8("newSampleSpinBox"));
   newSampleSpinBox->setMinimum(1);
   newSampleSpinBox->setMaximum(10000);
   newSampleSpinBox->setValue(1000);

   newSamplersVerticalLayout->addWidget(newSampleSpinBox);

   addNewSamplesPushButton = new QPushButton(newSampleGroupBox);
   addNewSamplesPushButton->setObjectName(QString::fromUtf8("addNewSamplesPushButton"));

   newSamplersVerticalLayout->addWidget(addNewSamplesPushButton);

   newSampleVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

   newSamplersVerticalLayout->addItem(newSampleVerticalSpacer);


   horizontalLayout->addWidget(newSampleGroupBox);

   pairGroupBox = new QGroupBox(dockWidgetContents);
   pairGroupBox->setObjectName(QString::fromUtf8("pairGroupBox"));
   pairSampleVerticalLayout = new QVBoxLayout(pairGroupBox);
   pairSampleVerticalLayout->setObjectName(QString::fromUtf8("pairSampleVerticalLayout"));
   pairInfoPlainTextEdit = new QPlainTextEdit(pairGroupBox);
   pairInfoPlainTextEdit->setObjectName(QString::fromUtf8("pairInfoPlainTextEdit"));
   QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(0);
   sizePolicy.setHeightForWidth(pairInfoPlainTextEdit->sizePolicy().hasHeightForWidth());
   pairInfoPlainTextEdit->setSizePolicy(sizePolicy);

   pairSampleVerticalLayout->addWidget(pairInfoPlainTextEdit);

   findPairPushButton = new QPushButton(pairGroupBox);
   findPairPushButton->setObjectName(QString::fromUtf8("findPairPushButton"));

   testPushButton=new QPushButton(pairGroupBox);
   testPushButton->setObjectName(QString::fromUtf8("testPushButton"));

   pairSampleVerticalLayout->addWidget(findPairPushButton);
   pairSampleVerticalLayout->addWidget(testPushButton);

   pairSampleVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

   pairSampleVerticalLayout->addItem(pairSampleVerticalSpacer);


   horizontalLayout->addWidget(pairGroupBox);

   setWidget(dockWidgetContents);

   QMetaObject::connectSlotsByName(this);
   newSampleGroupBox->setTitle(QApplication::translate("FeatureDetector", "New Samples", 0, QApplication::UnicodeUTF8));
   addNewSamplesPushButton->setText(QApplication::translate("FeatureDetector", "Add New Samples", 0, QApplication::UnicodeUTF8));
   pairGroupBox->setTitle(QApplication::translate("FeatureDetector", "Pair Samples", 0, QApplication::UnicodeUTF8));
   findPairPushButton->setText(QApplication::translate("FeatureDetector", "Find Pair", 0, QApplication::UnicodeUTF8));
   testPushButton->setText(QApplication::translate("FeatureDetector","Test",0,QApplication::UnicodeUTF8));

   connect(addNewSamplesPushButton,SIGNAL(clicked()),this,SLOT(onGenerateNewSamples()));
   connect(findPairPushButton,SIGNAL(clicked()),this,SLOT(onPairSamples()));
   connect(&FeatureDetectionData::getSingleton(),SIGNAL(pairsCollected()),this,SLOT(onPairsCollected()));
   connect(testPushButton,SIGNAL(clicked()),this,SLOT(onTest()));
}

void FeatureDetector::onTest()
{
    Sample n1;
    Sample n2;

    n1.generate(1);
    n2.generate(2);

    n1.generateJacobian();
    n2.generateJacobian();

    Transformation t=computeTransformation(n1,n2);

    qDebug("n1 z (%f,%f,%f)",n1.getZ().X(),n1.getZ().Y(),n1.getZ().Z());
    qDebug("n2 z (%f,%f,%f)",n2.getZ().X(),n2.getZ().Y(),n2.getZ().Z());

    GGL::Point3f n1AfterRotation=t.getRotationMatrix()*n1.getZ();
   // n1AfterRotation.Normalize();

    qDebug("n1 z after rotation: %f,%f,%f\n",n1AfterRotation.X(),n1AfterRotation.Y(),n1AfterRotation.Z());


    qDebug("n1 x (%f,%f,%f)",n1.getX().X(),n1.getX().Y(),n1.getX().Z());
    qDebug("n2 x (%f,%f,%f)",n2.getX().X(),n2.getX().Y(),n2.getX().Z());

    GGL::Point3f n1xAfterRotation=t.getRotationMatrix()*n1.getX();

    qDebug("n1 x after rotation: %f,%f,%f\n",n1xAfterRotation.X(),n1xAfterRotation.Y(),n1xAfterRotation.Z());

    qDebug("n1 y (%f,%f,%f)",n1.getY().X(),n1.getY().Y(),n1.getY().Z());
    qDebug("n2 y (%f,%f,%f)",n2.getY().X(),n2.getY().Y(),n2.getY().Z());

    GGL::Point3f n1yAfterRotation=t.getRotationMatrix()*n1.getY();

    qDebug("n1 y after rotation: %f,%f,%f\n",n1yAfterRotation.X(),n1yAfterRotation.Y(),n1yAfterRotation.Z());


    qDebug("rotation axis: %f,%f,%f\n",t.getRotationAxis().X(),t.getRotationAxis().Y(),t.getRotationAxis().Z());

}

void FeatureDetector::onGenerateNewSamples()
{
    FeatureDetectionData::getSingleton().generateSamples(newSampleSpinBox->value());
}

void FeatureDetector::onPairSamples()
{
    FeatureDetectionData::getSingleton().collectPairs();
    FeatureDetectionData::getSingleton().computeTransformation();
    FeatureDetectionData::getSingleton().outputRotationAxisCloud();
}

void FeatureDetector::onPairsCollected()
{
    pairInfoPlainTextEdit->setPlainText(QString("%1 signature pairs are collected!\n").arg(FeatureDetectionData::getSingleton().getPairSize()));
}

FeatureDetector::~FeatureDetector()
{

}
