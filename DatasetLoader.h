/*
 *  DatasetLoader.h
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/14/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#ifndef __DatasetLoader__
#define __DatasetLoader__


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "Point3.h"
#include "DockWidget.h"


class DatasetLoader :public DockWidget
{
	Q_OBJECT
private:


         enum BYTEORDER	{LITTEENDIAN, BIGENDIAN/*LITTLE_ENDIAN, BIG_ENDIAN*/};
         enum MESHATT	{UNSIGNED_8BIT, SIGNED_8BIT,  // 0
                                          UNSIGNED_16BIT, SIGNED_16BIT,
                                          UNSIGNED_32BIT, SIGNED_32BIT,
                                          FLOATT, DOUBLEE};

         struct VolumeData {
                 VolumeData() {
                         name = NULL;
                         filename = NULL;
                         tfefile = NULL;
                         totalstep = 1;
                         startstep = 1;
                         dim = GGL::Point3f(0.0,0.0,0.0);
                         format = UNSIGNED_8BIT;
                         byteorder = BIGENDIAN;
                         clampmaxval = 1e+20;
                         clampminval = -1e+20;
                         ifclampmaxval = false;
                         ifclampminval = false;
                 }
                 ~VolumeData() {
                         if (name) delete [] name;
                         if (filename) delete [] filename;
                         if (tfefile) delete [] tfefile;
                 }
                 char * name;
                 char * filename;
                 char * tfefile;
                 int totalstep;
                 int startstep;
                 double clampmaxval, clampminval;
                 bool   ifclampmaxval, ifclampminval;
                 GGL::Point3f dim;
                 MESHATT format;
                 BYTEORDER byteorder;
         };

          QHash<QString, VolumeData*> m_volumeData;

    QScrollArea *datasetLoaderScrollArea;
    QWidget *datasetScrollAreaWidgetContents;
    QVBoxLayout *scrollAreaVerticalLayout;
    QGroupBox *dataInfoGroupBox;
    QVBoxLayout *dataInfoVerticalLayout;
    QPlainTextEdit *dataInfoPlainTextEdit;
    QGroupBox *dataGroupBox;
    QHBoxLayout *dataPresetHorizontalLayout;
    QComboBox *presetComboBox;
    QPushButton *loadPresetPushButton;
    QGroupBox *openDataGroupBox;
    QGridLayout *openDataGridLayout;
    QLabel *dataDimensionXLabel;
    QSpinBox *dataDimensionXSpinBox;
    QLabel *dataDimensionYLabel;
    QLabel *dataDimensionZLabel;
    QSpinBox *dataDimensionYSpinBox;
    QSpinBox *dataDimensionZSpinBox;
    QPushButton *openDatasetPushButton;
    QLabel *dimensionLabel;
    QSpacerItem *dataLoaderVerticalSpacer;
	
public:
	DatasetLoader(QString name,QWidget *parent);
	~DatasetLoader();

    private slots:
       void  onDataOpen();
       void onLoadPreset();
       void onDataLoaded();
	
private:
    void parsePresets(const char * datafile);
    void preparePresets();
    bool parseVolumeAttribute(VolumeData * vd, QByteArray attr, QByteArray value) ;
}; 

#endif
