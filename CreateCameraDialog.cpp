#include "CreateCameraDialog.h"
#include <QtGui/QApplication>
#include "PerspectiveCamera.h"
#include "OrthogonalCamera.h"
#include "UserCameraManager.h"

CreateCameraDialog::CreateCameraDialog(QString &title,QWidget *parent):DockWidget(title,parent)
{

        setObjectName(QString::fromUtf8("CreateCameraDialog"));
        dockWidgetContents = new QWidget(this);
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));

        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        nameLabel = new QLabel(dockWidgetContents);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(nameLabel, 0, 0, 1, 1);

        cameraNameLineEdit = new QLineEdit(dockWidgetContents);
        cameraNameLineEdit->setObjectName(QString::fromUtf8("cameraNameLineEdit"));

        gridLayout->addWidget(cameraNameLineEdit, 0, 1, 1, 1);

        nearPlaneLabel = new QLabel(dockWidgetContents);
        nearPlaneLabel->setObjectName(QString::fromUtf8("nearPlaneLabel"));
        nearPlaneLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(nearPlaneLabel, 1, 0, 1, 1);

        nearPlaneDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        nearPlaneDoubleSpinBox->setObjectName(QString::fromUtf8("nearPlaneDoubleSpinBox"));
		nearPlaneDoubleSpinBox->setRange(-2147483647,2147483647);
		nearPlaneDoubleSpinBox->setValue(0.1);

        gridLayout->addWidget(nearPlaneDoubleSpinBox, 1, 1, 1, 1);

        fromLabel = new QLabel(dockWidgetContents);
        fromLabel->setObjectName(QString::fromUtf8("fromLabel"));

        gridLayout->addWidget(fromLabel, 3, 0, 1, 2);

        farPlaneDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        farPlaneDoubleSpinBox->setObjectName(QString::fromUtf8("farPlaneDoubleSpinBox"));
		farPlaneDoubleSpinBox->setRange(-2147483647,2147483647);
		farPlaneDoubleSpinBox->setValue(1000.0);

        gridLayout->addWidget(farPlaneDoubleSpinBox, 2, 1, 1, 1);

        farPlaneLabel = new QLabel(dockWidgetContents);
        farPlaneLabel->setObjectName(QString::fromUtf8("farPlaneLabel"));
        farPlaneLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(farPlaneLabel, 2, 0, 1, 1);

        fromXLabel = new QLabel(dockWidgetContents);
        fromXLabel->setObjectName(QString::fromUtf8("fromXLabel"));
        fromXLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(fromXLabel, 4, 0, 1, 1);

        fromYLabel = new QLabel(dockWidgetContents);
        fromYLabel->setObjectName(QString::fromUtf8("fromYLabel"));
        fromYLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(fromYLabel, 5, 0, 1, 1);

        fromZLabel = new QLabel(dockWidgetContents);
        fromZLabel->setObjectName(QString::fromUtf8("fromZLabel"));
        fromZLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(fromZLabel, 6, 0, 1, 1);

        toLabel = new QLabel(dockWidgetContents);
        toLabel->setObjectName(QString::fromUtf8("toLabel"));

        gridLayout->addWidget(toLabel, 7, 0, 1, 2);

        toXLabel = new QLabel(dockWidgetContents);
        toXLabel->setObjectName(QString::fromUtf8("toXLabel"));
        toXLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(toXLabel, 8, 0, 1, 1);

        toYLabel = new QLabel(dockWidgetContents);
        toYLabel->setObjectName(QString::fromUtf8("toYLabel"));
        toYLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(toYLabel, 9, 0, 1, 1);

        toZLabel = new QLabel(dockWidgetContents);
        toZLabel->setObjectName(QString::fromUtf8("toZLabel"));
        toZLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(toZLabel, 10, 0, 1, 1);

        createPushButton = new QPushButton(dockWidgetContents);
        createPushButton->setObjectName(QString::fromUtf8("createPushButton"));

        gridLayout->addWidget(createPushButton, 11, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 12, 0, 1, 2);

		fovDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        fovDoubleSpinBox->setObjectName(QString::fromUtf8("fovDoubleSpinBox"));
		fovDoubleSpinBox->setRange(-2147483647,2147483647);
		fovDoubleSpinBox->setValue(60.0);
        gridLayout->addWidget(fovDoubleSpinBox, 1, 1, 1, 1);

        fovLabel = new QLabel(dockWidgetContents);
        fovLabel->setObjectName(QString::fromUtf8("fovLabel"));
        fovLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(fovLabel, 1, 0, 1, 1);

        fromXDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        fromXDoubleSpinBox->setObjectName(QString::fromUtf8("fromXDoubleSpinBox"));
		fromXDoubleSpinBox->setRange(-2147483647,2147483647);
		fromXDoubleSpinBox->setValue(100);

        gridLayout->addWidget(fromXDoubleSpinBox, 4, 1, 1, 1);

        fromYDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        fromYDoubleSpinBox->setObjectName(QString::fromUtf8("fromYDoubleSpinBox"));
		fromYDoubleSpinBox->setRange(-2147483647,2147483647);
		fromYDoubleSpinBox->setValue(100);

        gridLayout->addWidget(fromYDoubleSpinBox, 5, 1, 1, 1);

        fromZDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        fromZDoubleSpinBox->setObjectName(QString::fromUtf8("fromZDoubleSpinBox"));
		fromZDoubleSpinBox->setRange(-2147483647,2147483647);
		fromZDoubleSpinBox->setValue(100);

        gridLayout->addWidget(fromZDoubleSpinBox, 6, 1, 1, 1);

        toXDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        toXDoubleSpinBox->setObjectName(QString::fromUtf8("toXDoubleSpinBox"));
		toXDoubleSpinBox->setRange(-2147483647,2147483647);
		toXDoubleSpinBox->setValue(0);

        gridLayout->addWidget(toXDoubleSpinBox, 8, 1, 1, 1);

        toYDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        toYDoubleSpinBox->setObjectName(QString::fromUtf8("toYDoubleSpinBox"));
		toYDoubleSpinBox->setRange(-2147483647,2147483647);
		toYDoubleSpinBox->setValue(0);

        gridLayout->addWidget(toYDoubleSpinBox, 9, 1, 1, 1);

        toZDoubleSpinBox = new QDoubleSpinBox(dockWidgetContents);
        toZDoubleSpinBox->setObjectName(QString::fromUtf8("toZDoubleSpinBox"));
		toZDoubleSpinBox->setRange(-2147483647,2147483647);
		toZDoubleSpinBox->setValue(0);

        gridLayout->addWidget(toZDoubleSpinBox, 10, 1, 1, 1);

		cameraTypeLabel = new QLabel(dockWidgetContents);
        cameraTypeLabel->setObjectName(QString::fromUtf8("cameraTypeLabel"));
		

        gridLayout->addWidget(cameraTypeLabel, 0, 0, 1, 1);

        cameraTypeComboBox = new QComboBox(dockWidgetContents);
        cameraTypeComboBox->setObjectName(QString::fromUtf8("cameraTypeComboBox"));
		cameraTypeComboBox->addItem(QString("Perspective"));
		cameraTypeComboBox->addItem(QString("Orthogonal"));
        gridLayout->addWidget(cameraTypeComboBox, 0, 1, 1, 1);

        setWidget(dockWidgetContents);
    
    
        nameLabel->setText(QApplication::translate("MainWindow", "Camera Name:", 0, QApplication::UnicodeUTF8));
        cameraNameLineEdit->setText(QApplication::translate("MainWindow", "Unnamed Camera", 0, QApplication::UnicodeUTF8));
        nearPlaneLabel->setText(QApplication::translate("MainWindow", "Near Plane:", 0, QApplication::UnicodeUTF8));
        fromLabel->setText(QApplication::translate("MainWindow", "From:", 0, QApplication::UnicodeUTF8));
        farPlaneLabel->setText(QApplication::translate("MainWindow", "Far Plane:", 0, QApplication::UnicodeUTF8));
        fromXLabel->setText(QApplication::translate("MainWindow", "X:", 0, QApplication::UnicodeUTF8));
        fromYLabel->setText(QApplication::translate("MainWindow", "Y:", 0, QApplication::UnicodeUTF8));
        fromZLabel->setText(QApplication::translate("MainWindow", "Z:", 0, QApplication::UnicodeUTF8));
        toLabel->setText(QApplication::translate("MainWindow", "To:", 0, QApplication::UnicodeUTF8));
        toXLabel->setText(QApplication::translate("MainWindow", "X:", 0, QApplication::UnicodeUTF8));
        toYLabel->setText(QApplication::translate("MainWindow", "Y:", 0, QApplication::UnicodeUTF8));
        toZLabel->setText(QApplication::translate("MainWindow", "Z:", 0, QApplication::UnicodeUTF8));
		fovLabel->setText(QApplication::translate("MainWindow", "Fov:", 0, QApplication::UnicodeUTF8));
        createPushButton->setText(QApplication::translate("MainWindow", "Create", 0, QApplication::UnicodeUTF8));
		createPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        cameraTypeLabel->setText(QApplication::translate("MainWindow", "Camera Type:", 0, QApplication::UnicodeUTF8));
   
		connect(createPushButton,SIGNAL(clicked()),this,SLOT(onCreateCamera()));


}

CreateCameraDialog::~CreateCameraDialog(void)
{
}

void CreateCameraDialog::onCreateCamera()
{
	if(cameraTypeComboBox->currentIndex()==0)
	{
		QString cameraName=cameraNameLineEdit->text();
		PerspectiveCamera *camera=new PerspectiveCamera(cameraName);
		UserCameraManager::getSingleton().addCamera(camera);
	}
	else
	{
		QString cameraName=cameraNameLineEdit->text();
		OrthogonalCamera *camera=new OrthogonalCamera(cameraName);
		UserCameraManager::getSingleton().addCamera(camera);
	}
}