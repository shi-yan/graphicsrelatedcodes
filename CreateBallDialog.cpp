#include "CreateBallDialog.h"

CreateBallDialog::CreateBallDialog(QString &title,QWidget *parent):DockWidget(title,parent)
{
	      setObjectName(QString::fromUtf8("CreateBallDialog"));
     
 
      
        scrollArea = new QScrollArea(this);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);

        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 195, 502));

        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout_2"));

        axisTypeLabel = new QLabel(this);
        axisTypeLabel->setObjectName(QString::fromUtf8("axisTypeLabel"));
        axisTypeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(axisTypeLabel, 0, 0, 1, 1);

        axisTypeComboBox = new QComboBox(this);
        axisTypeComboBox->setObjectName(QString::fromUtf8("axisTypeComboBox"));

        gridLayout->addWidget(axisTypeComboBox, 0, 1, 1, 1);

        xLabel = new QLabel(this);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));
        xLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(xLabel, 1, 0, 1, 1);

        xDoubleSpinBox = new QDoubleSpinBox(this);
        xDoubleSpinBox->setObjectName(QString::fromUtf8("xDoubleSpinBox"));

        gridLayout->addWidget(xDoubleSpinBox, 1, 1, 1, 1);

        yLabel = new QLabel(this);
        yLabel->setObjectName(QString::fromUtf8("yLabel"));
        yLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(yLabel, 3, 0, 1, 1);

        yDoubleSpinBox = new QDoubleSpinBox(this);
        yDoubleSpinBox->setObjectName(QString::fromUtf8("yDoubleSpinBox"));

        gridLayout->addWidget(yDoubleSpinBox, 3, 1, 1, 1);

        zLabel = new QLabel(this);
        zLabel->setObjectName(QString::fromUtf8("zLabel"));
        zLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(zLabel, 4, 0, 1, 1);

        zDoubleSpinBox = new QDoubleSpinBox(this);
        zDoubleSpinBox->setObjectName(QString::fromUtf8("zDoubleSpinBox"));

        gridLayout->addWidget(zDoubleSpinBox, 4, 1, 1, 1);

        radiusLabel = new QLabel(this);
        radiusLabel->setObjectName(QString::fromUtf8("radiusLabel"));
        radiusLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(radiusLabel, 6, 0, 1, 1);

        radiusDoubleSpinBox = new QDoubleSpinBox(this);
        radiusDoubleSpinBox->setObjectName(QString::fromUtf8("radiusDoubleSpinBox"));

        gridLayout->addWidget(radiusDoubleSpinBox, 6, 1, 1, 1);

        longitudeSegmentSpinBox = new QSpinBox(this);
        longitudeSegmentSpinBox->setObjectName(QString::fromUtf8("longitudeSegmentSpinBox"));
        longitudeSegmentSpinBox->setMinimum(3);
        longitudeSegmentSpinBox->setMaximum(312412341);

        gridLayout->addWidget(longitudeSegmentSpinBox, 7, 1, 1, 1);

        longitudeSegmentLabel = new QLabel(this);
        longitudeSegmentLabel->setObjectName(QString::fromUtf8("longitudeSegmentLabel"));
        longitudeSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(longitudeSegmentLabel, 7, 0, 1, 1);

        latitudeSegmentLabel = new QLabel(this);
        latitudeSegmentLabel->setObjectName(QString::fromUtf8("latitudeSegmentLabel"));
        latitudeSegmentLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(latitudeSegmentLabel, 8, 0, 1, 1);

        latitudeSegmentSpinBox = new QSpinBox(this);
        latitudeSegmentSpinBox->setObjectName(QString::fromUtf8("latitudeSegmentSpinBox"));
        latitudeSegmentSpinBox->setMinimum(1);
        latitudeSegmentSpinBox->setMaximum(31241234);

        gridLayout->addWidget(latitudeSegmentSpinBox, 8, 1, 1, 1);

        applyPushButton = new QPushButton(this);
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
        longitudeSegmentLabel->setText(QApplication::translate("MainWindow", "Longitude Segment:", 0, QApplication::UnicodeUTF8));
        latitudeSegmentLabel->setText(QApplication::translate("MainWindow", "Latitude Segment:", 0, QApplication::UnicodeUTF8));
        applyPushButton->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
}

CreateBallDialog::~CreateBallDialog(void)
{
}
