#include "CreateBoxDialog.h"
#include <QApplication>

CreateBoxDialog::CreateBoxDialog(QString &title,QWidget *parent):DockWidget(title,parent)
{
	setObjectName(QString::fromUtf8("CreateBoxDialog"));
        scrollArea = new QScrollArea(this);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 180, 502));
      
		gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        xLabel = new QLabel(scrollAreaWidgetContents);
        xLabel->setObjectName(QString::fromUtf8("xLable"));
        xLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(xLabel, 0, 0, 1, 1);

        xDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        xDoubleSpinBox->setObjectName(QString::fromUtf8("xDoubleSpinBox"));
        xDoubleSpinBox->setMinimum(-1.11111e+09);
        xDoubleSpinBox->setMaximum(1.11111e+09);

        gridLayout->addWidget(xDoubleSpinBox, 0, 1, 1, 1);

        yLabel = new QLabel(scrollAreaWidgetContents);
        yLabel->setObjectName(QString::fromUtf8("yLabel"));
        yLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(yLabel, 1, 0, 1, 1);

        yDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        yDoubleSpinBox->setObjectName(QString::fromUtf8("yDoubleSpinBox"));
        yDoubleSpinBox->setMinimum(-1.11111e+09);
        yDoubleSpinBox->setMaximum(1.11111e+09);

        gridLayout->addWidget(yDoubleSpinBox, 1, 1, 1, 1);

        zLabel = new QLabel(scrollAreaWidgetContents);
        zLabel->setObjectName(QString::fromUtf8("zLabel"));
        zLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(zLabel, 2, 0, 1, 1);

        zDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        zDoubleSpinBox->setObjectName(QString::fromUtf8("zDoubleSpinBox"));
        zDoubleSpinBox->setMinimum(-1.11111e+09);
        zDoubleSpinBox->setMaximum(1.11111e+09);

        gridLayout->addWidget(zDoubleSpinBox, 2, 1, 1, 1);

        lengthLabel = new QLabel(scrollAreaWidgetContents);
        lengthLabel->setObjectName(QString::fromUtf8("lengthLabel"));
        lengthLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lengthLabel, 3, 0, 1, 1);

        widthLabel = new QLabel(scrollAreaWidgetContents);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
        widthLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(widthLabel, 4, 0, 1, 1);

        heightLabel = new QLabel(scrollAreaWidgetContents);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));
        heightLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(heightLabel, 5, 0, 1, 1);

        lengthDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        lengthDoubleSpinBox->setObjectName(QString::fromUtf8("lengthDoubleSpinBox"));

        gridLayout->addWidget(lengthDoubleSpinBox, 3, 1, 1, 1);

        widthDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        widthDoubleSpinBox->setObjectName(QString::fromUtf8("widthDoubleSpinBox"));

        gridLayout->addWidget(widthDoubleSpinBox, 4, 1, 1, 1);

        heightDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        heightDoubleSpinBox->setObjectName(QString::fromUtf8("heightDoubleSpinBox"));

        gridLayout->addWidget(heightDoubleSpinBox, 5, 1, 1, 1);

        lengthSegmentLabel = new QLabel(scrollAreaWidgetContents);
        lengthSegmentLabel->setObjectName(QString::fromUtf8("lengthSegmentLabel"));
		lengthSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(lengthSegmentLabel, 6, 0, 1, 1);

        widthSegmentLabel = new QLabel(scrollAreaWidgetContents);
        widthSegmentLabel->setObjectName(QString::fromUtf8("widthSegmentLabel"));
		widthSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(widthSegmentLabel, 7, 0, 1, 1);

        heightSegmentLabel = new QLabel(scrollAreaWidgetContents);
        heightSegmentLabel->setObjectName(QString::fromUtf8("heightSegmentLabel"));
		heightSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(heightSegmentLabel, 8, 0, 1, 1);

        applyPushButton = new QPushButton(scrollAreaWidgetContents);
        applyPushButton->setObjectName(QString::fromUtf8("applyPushButton"));

        gridLayout->addWidget(applyPushButton, 9, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 2);

        xSegmentSpinBox = new QSpinBox(scrollAreaWidgetContents);
        xSegmentSpinBox->setObjectName(QString::fromUtf8("xSegmentSpinBox"));
        xSegmentSpinBox->setMinimum(1);
        xSegmentSpinBox->setValue(2);

        gridLayout->addWidget(xSegmentSpinBox, 6, 1, 1, 1);

        ySegmentSpinBox = new QSpinBox(scrollAreaWidgetContents);
        ySegmentSpinBox->setObjectName(QString::fromUtf8("ySegmentSpinBox"));
        ySegmentSpinBox->setMinimum(1);
        ySegmentSpinBox->setValue(2);

        gridLayout->addWidget(ySegmentSpinBox, 7, 1, 1, 1);

        zSegmentSpinBox = new QSpinBox(scrollAreaWidgetContents);
        zSegmentSpinBox->setObjectName(QString::fromUtf8("zSegmentSpinBox"));
        zSegmentSpinBox->setMinimum(1);
        zSegmentSpinBox->setValue(2);

        gridLayout->addWidget(zSegmentSpinBox, 8, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        setWidget(scrollArea);

        xLabel->setText(QApplication::translate("MainWindow", "X:", 0, QApplication::UnicodeUTF8));
        yLabel->setText(QApplication::translate("MainWindow", "Y:", 0, QApplication::UnicodeUTF8));
        zLabel->setText(QApplication::translate("MainWindow", "Z:", 0, QApplication::UnicodeUTF8));
        lengthLabel->setText(QApplication::translate("MainWindow", "Length:", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("MainWindow", "Width:", 0, QApplication::UnicodeUTF8));
        heightLabel->setText(QApplication::translate("MainWindow", "Height:", 0, QApplication::UnicodeUTF8));
        lengthSegmentLabel->setText(QApplication::translate("MainWindow", "X Segment:", 0, QApplication::UnicodeUTF8));
        widthSegmentLabel->setText(QApplication::translate("MainWindow", "Y Segment:", 0, QApplication::UnicodeUTF8));
        heightSegmentLabel->setText(QApplication::translate("MainWindow", "Z Segment:", 0, QApplication::UnicodeUTF8));
        applyPushButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
     
}

CreateBoxDialog::~CreateBoxDialog(void)
{
}
