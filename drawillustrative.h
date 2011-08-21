#ifndef DRAWILLUSTRATIVE_H
#define DRAWILLUSTRATIVE_H

#include "DockWidget.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>

class DrawIllustrative:public DockWidget
{
    Q_OBJECT

private:

     QWidget *dockWidgetContents;
     QVBoxLayout *verticalLayout;
     QGroupBox *manualInsertGroupBox;
     QGridLayout *gridLayout;
     QDoubleSpinBox *line1XDoubleSpinBox;
     QLabel *line1XLabel;
     QLabel *line1YLabel;
     QLabel *defineALineLabel;
     QLabel *line1ZLabel;
     QDoubleSpinBox *line1ZDoubleSpinBox;
     QDoubleSpinBox *line1YDoubleSpinBox;
     QLabel *line2XLabel;
     QDoubleSpinBox *line2XDoubleSpinBox;
     QLabel *line2YLabel;
     QDoubleSpinBox *line2YDoubleSpinBox;
     QLabel *line2ZLabel;
     QDoubleSpinBox *line2ZDoubleSpinBox;
     QPushButton *addALinePushButton;
     QGroupBox *automaticGroupBox;
     QHBoxLayout *horizontalLayout;
     QPushButton *loadPushButton;
     QPushButton *generatePushButton;
     QSpacerItem *verticalSpacer;
     QPushButton *testPushButton;
     QCheckBox *isDrawCenterCheckBox;
     QCheckBox *isDrawLargestEntropy;
     QCheckBox *isDrawSmallestEntropy;

    QDoubleSpinBox *thresholdDoubleSpinBox;
    QListWidget *resultList;

    QDoubleSpinBox *tapeWidthBase;
    QDoubleSpinBox *tapeWidthFlex;

    QLabel *tapeWidthBaseLabel;
    QLabel *tapeWidthFlexLabel;

    QLabel *smoothLabel;
    QSpinBox *smoothness;

public:
    DrawIllustrative(QString name,QWidget *parent);
    ~DrawIllustrative();

protected slots:
    void onDataUpdated();
    void onAddATape();
    void thresholdValueChanged(double);
    void onLoadData();
    void onTest();
    void onRowChanged(int);
};

#endif // DRAWILLUSTRATIVE_H
