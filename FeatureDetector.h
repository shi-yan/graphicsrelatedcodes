/*
 *  FeatureDetector.h
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/15/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#ifndef __FeatureDetector__
#define __FeatureDetector__
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "DockWidget.h"

class FeatureDetector : public DockWidget
{
	Q_OBJECT
	
private:
	
    QWidget *dockWidgetContents;
        QHBoxLayout *horizontalLayout;
        QGroupBox *newSampleGroupBox;
        QVBoxLayout *newSamplersVerticalLayout;
        QSpinBox *newSampleSpinBox;
        QPushButton *addNewSamplesPushButton;
        QSpacerItem *newSampleVerticalSpacer;
        QGroupBox *pairGroupBox;
        QVBoxLayout *pairSampleVerticalLayout;
        QPlainTextEdit *pairInfoPlainTextEdit;
        QPushButton *findPairPushButton;
        QSpacerItem *pairSampleVerticalSpacer;

        QPushButton *testPushButton;

public:
        FeatureDetector(QString name,QWidget *parent);
	~FeatureDetector();

private slots:

        void onGenerateNewSamples();
        void onPairSamples();
        void onPairsCollected();
        void onTest();

signals:


};

#endif
