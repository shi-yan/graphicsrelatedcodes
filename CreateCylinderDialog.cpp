#include "CreateCylinderDialog.h"

CreateCylinderDialog::CreateCylinderDialog(QString &title,QWidget *parent):DockWidget(title,parent)
{
	    setObjectName(QString::fromUtf8("CreateCylinderDialog"));
  
        scrollArea = new QScrollArea(this);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 502));

        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        axisTypeLabel = new QLabel(scrollAreaWidgetContents);
        axisTypeLabel->setObjectName(QString::fromUtf8("axisTypeLabel"));
        axisTypeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(axisTypeLabel, 0, 0, 1, 1);

        axisTypeComboBox = new QComboBox(scrollAreaWidgetContents);
        axisTypeComboBox->setObjectName(QString::fromUtf8("axisTypeComboBox"));

        gridLayout->addWidget(axisTypeComboBox, 0, 1, 1, 1);

        xLabel = new QLabel(scrollAreaWidgetContents);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));
        xLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(xLabel, 1, 0, 1, 1);

        xDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        xDoubleSpinBox->setObjectName(QString::fromUtf8("xDoubleSpinBox"));

        gridLayout->addWidget(xDoubleSpinBox, 1, 1, 1, 1);

        yLabel = new QLabel(scrollAreaWidgetContents);
        yLabel->setObjectName(QString::fromUtf8("yLabel"));
        yLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(yLabel, 2, 0, 1, 1);

        yDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        yDoubleSpinBox->setObjectName(QString::fromUtf8("yDoubleSpinBox"));

        gridLayout->addWidget(yDoubleSpinBox, 2, 1, 1, 1);

        zLabel = new QLabel(scrollAreaWidgetContents);
        zLabel->setObjectName(QString::fromUtf8("zLabel"));
        zLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(zLabel, 3, 0, 1, 1);

        zDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        zDoubleSpinBox->setObjectName(QString::fromUtf8("zDoubleSpinBox"));

        gridLayout->addWidget(zDoubleSpinBox, 3, 1, 1, 1);

        radiusLabel = new QLabel(scrollAreaWidgetContents);
        radiusLabel->setObjectName(QString::fromUtf8("radiusLabel"));
        radiusLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(radiusLabel, 4, 0, 1, 1);

        heightLabel = new QLabel(scrollAreaWidgetContents);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));
        heightLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(heightLabel, 5, 0, 1, 1);

        radiusDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        radiusDoubleSpinBox->setObjectName(QString::fromUtf8("radiusDoubleSpinBox"));

        gridLayout->addWidget(radiusDoubleSpinBox, 4, 1, 1, 1);

        heightDoubleSpinBox = new QDoubleSpinBox(scrollAreaWidgetContents);
        heightDoubleSpinBox->setObjectName(QString::fromUtf8("heightDoubleSpinBox"));

        gridLayout->addWidget(heightDoubleSpinBox, 5, 1, 1, 1);

        longitudeSegmentLabel = new QLabel(scrollAreaWidgetContents);
        longitudeSegmentLabel->setObjectName(QString::fromUtf8("longitudeSegmentLabel"));
        longitudeSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(longitudeSegmentLabel, 6, 0, 1, 1);

        radiusSegmentLabel = new QLabel(scrollAreaWidgetContents);
        radiusSegmentLabel->setObjectName(QString::fromUtf8("radiusSegmentLabel"));
        radiusSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(radiusSegmentLabel, 7, 0, 1, 1);

        heightSegmentLabel = new QLabel(scrollAreaWidgetContents);
        heightSegmentLabel->setObjectName(QString::fromUtf8("heightSegmentLabel"));
        heightSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(heightSegmentLabel, 8, 0, 1, 1);

        longitudeSpinBox = new QSpinBox(scrollAreaWidgetContents);
        longitudeSpinBox->setObjectName(QString::fromUtf8("longitudeSpinBox"));
        longitudeSpinBox->setMinimum(3);
        longitudeSpinBox->setMaximum(2342424);
        longitudeSpinBox->setValue(10);

        gridLayout->addWidget(longitudeSpinBox, 6, 1, 1, 1);

        radiusSpinBox = new QSpinBox(scrollAreaWidgetContents);
        radiusSpinBox->setObjectName(QString::fromUtf8("radiusSpinBox"));
        radiusSpinBox->setMinimum(1);
        radiusSpinBox->setMaximum(123443);

        gridLayout->addWidget(radiusSpinBox, 7, 1, 1, 1);

        heightSpinBox = new QSpinBox(scrollAreaWidgetContents);
        heightSpinBox->setObjectName(QString::fromUtf8("heightSpinBox"));
        heightSpinBox->setMinimum(1);
        heightSpinBox->setMaximum(3414314);

        gridLayout->addWidget(heightSpinBox, 8, 1, 1, 1);

        applyPushButton = new QPushButton(scrollAreaWidgetContents);
        applyPushButton->setObjectName(QString::fromUtf8("applyPushButton"));

        gridLayout->addWidget(applyPushButton, 9, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 0, 1, 2);

        scrollArea->setWidget(scrollAreaWidgetContents);


        setWidget(scrollArea);
       

        axisTypeComboBox->setCurrentIndex(2);


        axisTypeLabel->setText(QApplication::translate("MainWindow", "Axis Type:", 0, QApplication::UnicodeUTF8));
        axisTypeComboBox->clear();
        axisTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "X Axis", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Y Axis", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Z Axis", 0, QApplication::UnicodeUTF8)
        );
        xLabel->setText(QApplication::translate("MainWindow", "X:", 0, QApplication::UnicodeUTF8));
        yLabel->setText(QApplication::translate("MainWindow", "Y:", 0, QApplication::UnicodeUTF8));
        zLabel->setText(QApplication::translate("MainWindow", "Z:", 0, QApplication::UnicodeUTF8));
        radiusLabel->setText(QApplication::translate("MainWindow", "Radius:", 0, QApplication::UnicodeUTF8));
        heightLabel->setText(QApplication::translate("MainWindow", "Height:", 0, QApplication::UnicodeUTF8));
        longitudeSegmentLabel->setText(QApplication::translate("MainWindow", "Longitude Segment:", 0, QApplication::UnicodeUTF8));
        radiusSegmentLabel->setText(QApplication::translate("MainWindow", "Radius Segment:", 0, QApplication::UnicodeUTF8));
        heightSegmentLabel->setText(QApplication::translate("MainWindow", "Height Segment:", 0, QApplication::UnicodeUTF8));
        applyPushButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
}

CreateCylinderDialog::~CreateCylinderDialog(void)
{
}
