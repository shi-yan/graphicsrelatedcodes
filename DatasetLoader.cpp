/*
 *  DatasetLoader.cpp
 *  VectorFieldProject
 *
 *  Created by Shi Yan on 1/14/11.
 *  Copyright 2011 UCDavis. All rights reserved.
 *
 */

#include "DatasetLoader.h"
#include "VectorField.h"
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

DatasetLoader::DatasetLoader(QString name,QWidget *parent):DockWidget(name,parent)
{

	setObjectName(QString::fromUtf8("DatasetLoader"));
        resize(433, 479);
	datasetLoaderScrollArea = new QScrollArea(this);
	datasetLoaderScrollArea->setObjectName(QString::fromUtf8("datasetLoaderScrollArea"));
	datasetLoaderScrollArea->setWidgetResizable(true);
	datasetScrollAreaWidgetContents = new QWidget(datasetLoaderScrollArea);
	datasetScrollAreaWidgetContents->setObjectName(QString::fromUtf8("datasetScrollAreaWidgetContents"));
	datasetScrollAreaWidgetContents->setGeometry(QRect(0, 0, 407, 453));
	scrollAreaVerticalLayout = new QVBoxLayout(datasetScrollAreaWidgetContents);
	scrollAreaVerticalLayout->setObjectName(QString::fromUtf8("scrollAreaVerticalLayout"));
	dataInfoGroupBox = new QGroupBox(datasetScrollAreaWidgetContents);
	dataInfoGroupBox->setObjectName(QString::fromUtf8("dataInfoGroupBox"));
	dataInfoVerticalLayout = new QVBoxLayout(dataInfoGroupBox);
	dataInfoVerticalLayout->setObjectName(QString::fromUtf8("dataInfoVerticalLayout"));
	dataInfoPlainTextEdit = new QPlainTextEdit(dataInfoGroupBox);
	dataInfoPlainTextEdit->setObjectName(QString::fromUtf8("dataInfoPlainTextEdit"));
	
	dataInfoVerticalLayout->addWidget(dataInfoPlainTextEdit);
	
	
	scrollAreaVerticalLayout->addWidget(dataInfoGroupBox);
	
	dataGroupBox = new QGroupBox(datasetScrollAreaWidgetContents);
	dataGroupBox->setObjectName(QString::fromUtf8("dataGroupBox"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(dataGroupBox->sizePolicy().hasHeightForWidth());
	dataGroupBox->setSizePolicy(sizePolicy);
	dataPresetHorizontalLayout = new QHBoxLayout(dataGroupBox);
	dataPresetHorizontalLayout->setObjectName(QString::fromUtf8("dataPresetHorizontalLayout"));
	presetComboBox = new QComboBox(dataGroupBox);
	presetComboBox->setObjectName(QString::fromUtf8("presetComboBox"));
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(presetComboBox->sizePolicy().hasHeightForWidth());
	presetComboBox->setSizePolicy(sizePolicy1);
	
	dataPresetHorizontalLayout->addWidget(presetComboBox);
	
	loadPresetPushButton = new QPushButton(dataGroupBox);
	loadPresetPushButton->setObjectName(QString::fromUtf8("loadPresetPushButton"));
	
	dataPresetHorizontalLayout->addWidget(loadPresetPushButton);
	
	
	
	scrollAreaVerticalLayout->addWidget(dataGroupBox);
	
	openDataGroupBox = new QGroupBox(datasetScrollAreaWidgetContents);
	openDataGroupBox->setObjectName(QString::fromUtf8("openDataGroupBox"));
	openDataGridLayout = new QGridLayout(openDataGroupBox);
	openDataGridLayout->setObjectName(QString::fromUtf8("openDataGridLayout"));
	dataDimensionXLabel = new QLabel(openDataGroupBox);
	dataDimensionXLabel->setObjectName(QString::fromUtf8("dataDimensionXLabel"));
	QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
	sizePolicy2.setHorizontalStretch(0);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(dataDimensionXLabel->sizePolicy().hasHeightForWidth());
	dataDimensionXLabel->setSizePolicy(sizePolicy2);
	
	openDataGridLayout->addWidget(dataDimensionXLabel, 1, 0, 1, 1);
	
	dataDimensionXSpinBox = new QSpinBox(openDataGroupBox);
	dataDimensionXSpinBox->setObjectName(QString::fromUtf8("dataDimensionXSpinBox"));
	sizePolicy1.setHeightForWidth(dataDimensionXSpinBox->sizePolicy().hasHeightForWidth());
	dataDimensionXSpinBox->setSizePolicy(sizePolicy1);
	dataDimensionXSpinBox->setMinimum(1);
	dataDimensionXSpinBox->setMaximum(1024);
	dataDimensionXSpinBox->setValue(64);
	
	openDataGridLayout->addWidget(dataDimensionXSpinBox, 1, 1, 1, 1);
	
	dataDimensionYLabel = new QLabel(openDataGroupBox);
	dataDimensionYLabel->setObjectName(QString::fromUtf8("dataDimensionYLabel"));
	sizePolicy2.setHeightForWidth(dataDimensionYLabel->sizePolicy().hasHeightForWidth());
	dataDimensionYLabel->setSizePolicy(sizePolicy2);
	
	openDataGridLayout->addWidget(dataDimensionYLabel, 2, 0, 1, 1);
	
	dataDimensionZLabel = new QLabel(openDataGroupBox);
	dataDimensionZLabel->setObjectName(QString::fromUtf8("dataDimensionZLabel"));
	sizePolicy2.setHeightForWidth(dataDimensionZLabel->sizePolicy().hasHeightForWidth());
	dataDimensionZLabel->setSizePolicy(sizePolicy2);
	
	openDataGridLayout->addWidget(dataDimensionZLabel, 3, 0, 1, 1);
	
	dataDimensionYSpinBox = new QSpinBox(openDataGroupBox);
	dataDimensionYSpinBox->setObjectName(QString::fromUtf8("dataDimensionYSpinBox"));
	dataDimensionYSpinBox->setMinimum(1);
	dataDimensionYSpinBox->setMaximum(1024);
	dataDimensionYSpinBox->setValue(64);
	
	openDataGridLayout->addWidget(dataDimensionYSpinBox, 2, 1, 1, 1);
	
	dataDimensionZSpinBox = new QSpinBox(openDataGroupBox);
	dataDimensionZSpinBox->setObjectName(QString::fromUtf8("dataDimensionZSpinBox"));
	dataDimensionZSpinBox->setMinimum(1);
	dataDimensionZSpinBox->setMaximum(1024);
	dataDimensionZSpinBox->setValue(64);
	
	openDataGridLayout->addWidget(dataDimensionZSpinBox, 3, 1, 1, 1);
	
	openDatasetPushButton = new QPushButton(openDataGroupBox);
	openDatasetPushButton->setObjectName(QString::fromUtf8("openDatasetPushButton"));
	QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(openDatasetPushButton->sizePolicy().hasHeightForWidth());
	openDatasetPushButton->setSizePolicy(sizePolicy3);
	
	openDataGridLayout->addWidget(openDatasetPushButton, 0, 2, 4, 1);
	
	dimensionLabel = new QLabel(openDataGroupBox);
	dimensionLabel->setObjectName(QString::fromUtf8("dimensionLabel"));
	
	openDataGridLayout->addWidget(dimensionLabel, 0, 0, 1, 2);
	
	
	scrollAreaVerticalLayout->addWidget(openDataGroupBox);
	
	dataLoaderVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	
	scrollAreaVerticalLayout->addItem(dataLoaderVerticalSpacer);
	
	datasetLoaderScrollArea->setWidget(datasetScrollAreaWidgetContents);
	
	setWidget(datasetLoaderScrollArea);
	setWindowTitle(QApplication::translate("DatasetLoader", "Dataset Loader", 0, QApplication::UnicodeUTF8));
	dataInfoGroupBox->setTitle(QApplication::translate("DatasetLoader", "Dataset Info:", 0, QApplication::UnicodeUTF8));
	dataGroupBox->setTitle(QApplication::translate("DatasetLoader", "Data Presets:", 0, QApplication::UnicodeUTF8));
	presetComboBox->clear();

	loadPresetPushButton->setText(QApplication::translate("DatasetLoader", " Load ", 0, QApplication::UnicodeUTF8));
	openDataGroupBox->setTitle(QApplication::translate("DatasetLoader", "Open a Dataset:", 0, QApplication::UnicodeUTF8));
	dataDimensionXLabel->setText(QApplication::translate("DatasetLoader", "X:", 0, QApplication::UnicodeUTF8));
	dataDimensionYLabel->setText(QApplication::translate("DatasetLoader", "Y:", 0, QApplication::UnicodeUTF8));
	dataDimensionZLabel->setText(QApplication::translate("DatasetLoader", "Z:", 0, QApplication::UnicodeUTF8));
	openDatasetPushButton->setText(QApplication::translate("DatasetLoader", " Open \n Dataset ", 0, QApplication::UnicodeUTF8));
	dimensionLabel->setText(QApplication::translate("DatasetLoader", "Dimension:", 0, QApplication::UnicodeUTF8));
	

        connect(openDatasetPushButton,SIGNAL(clicked()),this,SLOT(onDataOpen()));
        connect(loadPresetPushButton,SIGNAL(clicked()),this,SLOT(onLoadPreset()));
        connect(&VectorField::getSingleton(),SIGNAL(dataUpdated()),this,SLOT(onDataLoaded()));

        preparePresets();
}

DatasetLoader::~DatasetLoader()
{

}

void DatasetLoader::onDataLoaded()
{


    dataInfoPlainTextEdit->setPlainText( QString("Dataset: %1\nData Dimension: %2x%3x%4\nMinimum Magnitude: %5\nMaximum Magnitude:%6").arg( VectorField::getSingleton().getDataName() ).arg(VectorField::getSingleton().xSize).arg(VectorField::getSingleton().ySize).arg(VectorField::getSingleton().zSize).arg(VectorField::getSingleton().minMag).arg(VectorField::getSingleton().maxMag));

}

bool DatasetLoader::parseVolumeAttribute(VolumeData * vd, QByteArray attr, QByteArray value) {
        if (attr == "filename") {
                value += '\0';
                vd->filename = new char[value.size() + 1];
                qstrcpy(vd->filename, value.constData());
                return true;
        }
        else if (attr == "tfefile") {
                value += '\0';
                vd->tfefile = new char[value.size() + 1];
                qstrcpy(vd->tfefile, value.constData());
                return true;
        }
        else if (attr == "totalstep") {
                vd->totalstep = value.toInt();
                return true;
        }
        else if (attr == "startstep") {
                vd->startstep = value.toInt();
                return true;
        }
        else if (attr == "dim") {
                QList<QByteArray> dim = value.split('x');
                if (dim.size() != 3) return false;
                vd->dim = GGL::Point3f(dim[0].toInt(), dim[1].toInt(), dim[2].toInt());
                return true;
        }
        else if (attr == "clampminval"){
                vd->clampminval = value.toFloat();
                vd->ifclampminval = true;
                return true;
        }
        else if (attr == "clampmaxval"){
                vd->clampmaxval = value.toFloat();
                vd->ifclampmaxval = true;
                return true;
        }
        else if (attr == "format") {
                if (value == "UNSIGNED_8BIT") { vd->format = UNSIGNED_8BIT; return true; }
                else if (value == "SIGNED_8BIT") { vd->format = SIGNED_8BIT; return true; }
                else if (value == "UNSIGNED_16BIT") { vd->format = UNSIGNED_16BIT; return true; }
                else if (value == "SIGNED_16BIT") { vd->format = SIGNED_16BIT; return true; }
                else if (value == "UNSIGNED_32BIT") { vd->format = UNSIGNED_32BIT; return true; }
                else if (value == "SIGNED_32BIT") { vd->format = SIGNED_32BIT; return true; }
                else if (value == "FLOATT") { vd->format = FLOATT; return true; }
                else if (value == "DOUBLEE") { vd->format = DOUBLEE; return true; }
                else return false;
        }
        else if (attr == "byteorder") {
                if (value == "BIGENDIAN") { vd->byteorder = BIGENDIAN; return true; }
                else if (value == "LITTEENDIAN") { vd->byteorder = LITTEENDIAN; return true; }
                else return false;
        }
        return false;
}

void DatasetLoader::preparePresets()
{
    parsePresets("volumedata.txt");
    QStringList datasetNameList;

    for(QHash<QString,VolumeData*>::iterator iter=m_volumeData.begin();iter!=m_volumeData.end();++iter)
    {
        datasetNameList<<iter.key();
    }
    presetComboBox->insertItems(0, datasetNameList          );
}

void DatasetLoader::   onLoadPreset()
{
    QString dataname=presetComboBox->currentText();

    if (!m_volumeData.contains(dataname))
    {
        QMessageBox msgBox;
        msgBox.setText(QString("The data %1 doesn't exist!").arg(dataname));
        msgBox.exec();
           exit(1);
    }

    VolumeData * vd = m_volumeData[dataname];
    QString fileName(vd->filename);

    qDebug("Vector field dimension: %f x %f x %f\n",vd->dim.X(),vd->dim.Y(),vd->dim.Z());

    if (fileName.length()>0)
    {
            setWindowTitle(QString("3DTest - opened file:%1").arg(fileName));
            VectorField::getSingleton().init(fileName.toStdString().c_str(), vd->dim.X(), vd->dim.Y(), vd->dim.Z(),dataname);
    }
}

void DatasetLoader::parsePresets(const char * datafile)
{


            QFile inpfile(datafile);
            inpfile.open(QIODevice::ReadOnly);
            QByteArray buffer = inpfile.readAll();
            QByteArray name, attr, value;

            enum State{ Out, Item, Value};
            State state = Out;

            VolumeData * temp;

            for (int i = 0; i < buffer.size(); ++i) {
                    switch(state) {
                    case Out:
                            if (buffer[i] == '{') {
                                    name = name.trimmed();
                                    name += '\0';
                                    temp = new VolumeData;
                                    temp->name = new char[name.size()+1];
                                    qstrcpy(temp->name, name.constData());
                                    state = Item;
                            }
                            else name += buffer[i];
                            break;
                    case Item:
                            if (buffer[i] == '=') {
                                    attr = attr.trimmed();
                                    state = Value;
                            }
                            else if (buffer[i] == '}') {
                                    m_volumeData[QString(tr(temp->name))] = temp;
                                    name.clear(); attr.clear(); value.clear(); state = Out;
                            }
                            else attr += buffer[i];
                            break;
                    case Value:
                            if (buffer[i] == ',') {
                                    value = value.trimmed();
                                    if (!parseVolumeAttribute(temp, attr, value)) qDebug("Volume Data Format Error!");
                                    attr.clear(); value.clear(); state = Item;
                            }
                            else if (buffer[i] == '}') {
                                    value = value.trimmed();
                                    if (!parseVolumeAttribute(temp, attr, value)) qDebug("Volume Data Format Error!");
                                    m_volumeData[QString(tr(temp->name))] = temp;
                                    name.clear(); attr.clear(); value.clear(); state = Out;
                            }
                            else value += buffer[i];
                            break;
                    }
            }
    }

void DatasetLoader::onDataOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Vector Field"), "./", tr("Vector Field File (*.vec)"));

    if (fileName.length()>0)
    {
            setWindowTitle(QString("3DTest - opened file:%1").arg(fileName));
            VectorField::getSingleton().init(fileName.toStdString().c_str(), dataDimensionXSpinBox->value(), dataDimensionYSpinBox->value(), dataDimensionZSpinBox->value(),fileName);
    }
}
