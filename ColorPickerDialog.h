#pragma once
#include "DockWidget.h"

#include <QtCore/QVariant>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

#include "colorpickerwidget.h"

class ColorPickerDialog:public DockWidget
{
	Q_OBJECT

private:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QPushButton *applyPushButton;
    QLabel *rLabel;
    QLabel *gLabel;
    QLabel *bLabel;
    QSpacerItem *verticalSpacer;
    QSpinBox *rSpinBox;
    QSpinBox *gSpinBox;
    QSpinBox *bSpinBox;
	ColorPickerWidget *colorPicker;
public:
	ColorPickerDialog(QString &title,QWidget *parent=0);
	~ColorPickerDialog(void);
};
