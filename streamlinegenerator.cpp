#include "streamlinegenerator.h"
#include "StreamLine.h"

StreamlineGenerator::StreamlineGenerator(QString name,QWidget *parent):DockWidget(name,parent)
{

      dockWidgetContents = new QWidget();
         dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
         verticalLayout = new QVBoxLayout(dockWidgetContents);
         verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
         generateStreamLineLabel = new QLabel(dockWidgetContents);
         generateStreamLineLabel->setObjectName(QString::fromUtf8("generateStreamLineLabel"));

         verticalLayout->addWidget(generateStreamLineLabel);

         randomStreamlineSpinBox = new QSpinBox(dockWidgetContents);
         randomStreamlineSpinBox->setObjectName(QString::fromUtf8("randomStreamlineSpinBox"));
         randomStreamlineSpinBox->setMinimum(1);
         randomStreamlineSpinBox->setMaximum(10000);
         randomStreamlineSpinBox->setValue(500);

         verticalLayout->addWidget(randomStreamlineSpinBox);

         generateStreamlinePushButton = new QPushButton(dockWidgetContents);
         generateStreamlinePushButton->setObjectName(QString::fromUtf8("generateStreamlinePushButton"));

         verticalLayout->addWidget(generateStreamlinePushButton);

         clearStreamlinePushButton = new QPushButton(dockWidgetContents);
         clearStreamlinePushButton->setObjectName(QString::fromUtf8("clearStreamlinePushButton"));

         verticalLayout->addWidget(clearStreamlinePushButton);

         verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

         verticalLayout->addItem(verticalSpacer);
        setWidget(dockWidgetContents);

         generateStreamLineLabel->setText(QApplication::translate("StreamlineGenerator", "New Streamline Number:", 0, QApplication::UnicodeUTF8));
         generateStreamlinePushButton->setText(QApplication::translate("StreamlineGenerator", "Generate", 0, QApplication::UnicodeUTF8));
         clearStreamlinePushButton->setText(QApplication::translate("StreamlineGenerator", "Clear", 0, QApplication::UnicodeUTF8));

         QMetaObject::connectSlotsByName(this);

         connect(generateStreamlinePushButton,SIGNAL(clicked()),this,SLOT(onGenerate()));
         connect(clearStreamlinePushButton,SIGNAL(clicked()),this,SLOT(onClear()));
}

void StreamlineGenerator::onGenerate()
{
    for(int i=0;i<randomStreamlineSpinBox->value();++i)
    {
        Streamline sl;
        sl.generateRandomly();

        Streamline::streamlinePool.push_back(sl);
    }
}

void StreamlineGenerator::onClear()
{
    Streamline::streamlinePool.clear();
}

StreamlineGenerator::~StreamlineGenerator()
{
}
