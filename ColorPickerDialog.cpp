#include "ColorPickerDialog.h"
#include <QtGui/QApplication>

ColorPickerDialog::ColorPickerDialog(QString &title,QWidget *parent):DockWidget(title,parent)
{
    setObjectName(QString::fromUtf8("ColorPickerDialog"));
        dockWidgetContents = new QWidget(this);
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
       
		colorPicker=new ColorPickerWidget(this); 

		colorPicker->setMinimumSize(QSize(200,200));
		
	    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(colorPicker->sizePolicy().hasHeightForWidth());
        colorPicker->setSizePolicy(sizePolicy);
  

        gridLayout->addWidget(colorPicker, 0, 0, 1, 2);

        applyPushButton = new QPushButton(dockWidgetContents);
        applyPushButton->setObjectName(QString::fromUtf8("applyPushButton"));

        gridLayout->addWidget(applyPushButton, 4, 0, 1, 2);

        rLabel = new QLabel(dockWidgetContents);
        rLabel->setObjectName(QString::fromUtf8("rLabel"));
        rLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(rLabel, 1, 0, 1, 1);

        gLabel = new QLabel(dockWidgetContents);
        gLabel->setObjectName(QString::fromUtf8("gLabel"));
        gLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(gLabel, 2, 0, 1, 1);

        bLabel = new QLabel(dockWidgetContents);
        bLabel->setObjectName(QString::fromUtf8("bLabel"));
        bLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(bLabel, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 2);

        rSpinBox = new QSpinBox(dockWidgetContents);
        rSpinBox->setObjectName(QString::fromUtf8("rSpinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rSpinBox->sizePolicy().hasHeightForWidth());
        rSpinBox->setSizePolicy(sizePolicy1);
        rSpinBox->setMaximum(255);

        gridLayout->addWidget(rSpinBox, 1, 1, 1, 1);

        gSpinBox = new QSpinBox(dockWidgetContents);
        gSpinBox->setObjectName(QString::fromUtf8("gSpinBox"));
        sizePolicy1.setHeightForWidth(gSpinBox->sizePolicy().hasHeightForWidth());
        gSpinBox->setSizePolicy(sizePolicy1);
        gSpinBox->setMaximum(255);

        gridLayout->addWidget(gSpinBox, 2, 1, 1, 1);

        bSpinBox = new QSpinBox(dockWidgetContents);
        bSpinBox->setObjectName(QString::fromUtf8("bSpinBox"));
        sizePolicy1.setHeightForWidth(bSpinBox->sizePolicy().hasHeightForWidth());
        bSpinBox->setSizePolicy(sizePolicy1);
        bSpinBox->setMaximum(255);

        gridLayout->addWidget(bSpinBox, 3, 1, 1, 1);

        setWidget(dockWidgetContents);
  
      
        applyPushButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        rLabel->setText(QApplication::translate("MainWindow", "R:", 0, QApplication::UnicodeUTF8));
        gLabel->setText(QApplication::translate("MainWindow", "G:", 0, QApplication::UnicodeUTF8));
        bLabel->setText(QApplication::translate("MainWindow", "B:", 0, QApplication::UnicodeUTF8));

}

ColorPickerDialog::~ColorPickerDialog(void)
{
}
