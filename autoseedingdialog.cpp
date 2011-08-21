#include "autoseedingdialog.h"
#include "seedingideadata.h"

AutoSeedingDialog::AutoSeedingDialog(const QString &title,QWidget *parent):DockWidget(title,parent)
{

setObjectName(QString::fromUtf8("AutoSeeding Dialog"));
content=new QWidget(this);
verticalLayout = new QVBoxLayout(content);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    generateBoundaryPushButton = new QPushButton(content);
    generateBoundaryPushButton->setObjectName(QString::fromUtf8("generateBoundaryPushButton"));

    verticalLayout->addWidget(generateBoundaryPushButton);

    shouldDrawCheckBox = new QCheckBox(content);
    shouldDrawCheckBox->setObjectName(QString::fromUtf8("shouldDrawCheckBox"));

    verticalLayout->addWidget(shouldDrawCheckBox);

    preprocessPushButton = new QPushButton(content);
    preprocessPushButton->setObjectName(QString::fromUtf8("preprocessPushButton"));

    verticalLayout->addWidget(preprocessPushButton);

    generateStreamlinePushButton = new QPushButton(content);
    generateStreamlinePushButton->setObjectName(QString::fromUtf8("generateStreamlinePushButton"));

    verticalLayout->addWidget(generateStreamlinePushButton);

    generateStreamSurfacePushButton = new QPushButton(content);
    generateStreamSurfacePushButton->setObjectName(QString::fromUtf8("generateStreamSurfacePushButton"));

    verticalLayout->addWidget(generateStreamSurfacePushButton);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);
           generateBoundaryPushButton->setText(QApplication::translate("AutoSeeding Dialog", "Generate Boundry", 0, QApplication::UnicodeUTF8));
           shouldDrawCheckBox->setText(QApplication::translate("AutoSeeding Dialog", "Should Draw?", 0, QApplication::UnicodeUTF8));
           preprocessPushButton->setText(QApplication::translate("AutoSeeding Dialog", "Preprocess", 0, QApplication::UnicodeUTF8));
           generateStreamlinePushButton->setText(QApplication::translate("AutoSeeding Dialog", "Generate Streamlines", 0, QApplication::UnicodeUTF8));
           generateStreamSurfacePushButton->setText(QApplication::translate("AutoSeeding Dialog", "Generate Streamsurfaces", 0, QApplication::UnicodeUTF8));
setWidget(content);
    QMetaObject::connectSlotsByName(this);

    connect(generateBoundaryPushButton,SIGNAL(clicked()),this,SLOT(onCreateBoundary()));
}

void AutoSeedingDialog::onCreateBoundary()
{
    SeedingIdeaData::getSingleton().onVectorFieldLoaded();
}
