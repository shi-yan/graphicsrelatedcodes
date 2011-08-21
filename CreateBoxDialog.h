#pragma once
#include "DockWidget.h"
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>

class CreateBoxDialog:public DockWidget
{
	Q_OBJECT

private:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *xLabel;
    QDoubleSpinBox *xDoubleSpinBox;
    QLabel *yLabel;
    QDoubleSpinBox *yDoubleSpinBox;
    QLabel *zLabel;
    QDoubleSpinBox *zDoubleSpinBox;
    QLabel *lengthLabel;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QDoubleSpinBox *lengthDoubleSpinBox;
    QDoubleSpinBox *widthDoubleSpinBox;
    QDoubleSpinBox *heightDoubleSpinBox;
    QLabel *lengthSegmentLabel;
    QLabel *widthSegmentLabel;
    QLabel *heightSegmentLabel;
    QPushButton *applyPushButton;
    QSpacerItem *verticalSpacer;
    QSpinBox *xSegmentSpinBox;
    QSpinBox *ySegmentSpinBox;
    QSpinBox *zSegmentSpinBox;
public:
	CreateBoxDialog(QString &title,QWidget *parent=0);
	~CreateBoxDialog(void);
};
