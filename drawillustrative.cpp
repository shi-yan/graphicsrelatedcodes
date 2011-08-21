#include "drawillustrative.h"
#include "VectorField.h"
#include "drawillustrativedata.h"
//#include <sys/time.h>
#include <QString>

int resultCount=30;


QString resultfiles[]={

    "cluster-syn-cluster18.dat","syn0001_100x100x100.vec","100","100","100",
    "cluster-syn-cluster20.dat","syn0001_100x100x100.vec","100","100","100",
    "cluster-syn-15cluster.dat","syn0001_100x100x100.vec","100","100","100",
    "cluster-syn-25cluster.dat","syn0001_100x100x100.vec","100","100","100",
    "cluster-syn-10cluster.dat","syn0001_100x100x100.vec","100","100","100",
    "cluster-supernova-16cluster.dat","supernova.vec","64","64","64",
   "cluster-random-16cluster.dat","random-51x51x51.vec","51","51","51",
    "cluster-hurricanedownsample-16cluster.dat","hurricane36-100x100x20.vec","100","100","20",

 "cluster-syn-16cluster.dat","syn0001_100x100x100.vec","100","100","100",
   "cluster-twoswirls-16cluster.dat","TwoSwirls.vec","64","64","64",
    "cluster-hurricaneDownsample100x100x20-10cluster.dat","hurricane36-100x100x20.vec","100","100","20",
    "cluster-HurricaneDownsample-100x100x20.dat","hurricane36-100x100x20.vec","100","100","20",
    "cluster-hurricane-20.dat","hurricane36-100x100x20.vec","100","100","20",

    "cluster-velo2-10cluster.dat","velo2.vec","64","64","64",
    "cluster-velo2-20cluster.dat","velo2.vec","64","64","64",

    "cluster-hurrucanesmall-20cluster.dat","hurricane64.vec","64","64","64",

    "cluster-supernova-10cluster.dat","supernova.vec","64","64","64",

    "cluster-tornado-10cluster.dat","PC_tornado.vec","64","64","64",

    "cluster-tornado-8.dat","PC_tornado.vec","64","64","64",


    "cluster-twoswirl-10cluster.dat","TwoSwirls.vec","64","64","64",

    "cluster-random-10cluster.dat","random-51x51x51.vec","51","51","51",

    "cluster-random-20cluster.dat","random-51x51x51.vec","51","51","51",

    "cluster-plume-12.dat","15plume3d421.vec","126","126","512",
    "cluster-plume-24.dat","15plume3d421.vec","126","126","512",
    "cluster-plume.dat","15plume3d421.vec","126","126","512",
    "cluster-supernova100x100x100.dat","supernova-100x100x100.vec","100","100","100",
    "cluster-supernova-10cluster2.dat","supernova-100x100x100.vec","100","100","100",
    "cluster-supernova-15cluster.dat","supernova-100x100x100.vec","100","100","100",
    "cluster-supernova-20cluster2.dat","supernova-100x100x100.vec","100","100","100",
    "cluster-supernova-30cluster.dat","supernova-100x100x100.vec","100","100","100",
    "cluster-computerroom-40.dat","RSCC36.vec","417","345","60"

};

int currentSelected=0;

DrawIllustrative::DrawIllustrative(QString name,QWidget *parent):DockWidget(name,parent)
{
   setObjectName(QString::fromUtf8("DrawIllustrative"));

        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        manualInsertGroupBox = new QGroupBox(dockWidgetContents);
        manualInsertGroupBox->setObjectName(QString::fromUtf8("manualInsertGroupBox"));
        gridLayout = new QGridLayout(manualInsertGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    //    line1XDoubleSpinBox = new QDoubleSpinBox(manualInsertGroupBox);
      //  line1XDoubleSpinBox->setObjectName(QString::fromUtf8("line1XDoubleSpinBox"));
      /*  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line1XDoubleSpinBox->sizePolicy().hasHeightForWidth());
        line1XDoubleSpinBox->setSizePolicy(sizePolicy);
*/
        resultList=new QListWidget(this);
        gridLayout->addWidget(resultList,0,0,1,4);

        for(int i=0;i<resultCount;++i)
        {
            QListWidgetItem *k=new QListWidgetItem(resultList);

            k->setText(resultfiles[i*5]);
        }

           connect(resultList,SIGNAL(currentRowChanged(int)),this,SLOT(onRowChanged(int)));



     //   gridLayout->addWidget(line1XDoubleSpinBox, 1, 1, 1, 1);

     //   line1XLabel = new QLabel(manualInsertGroupBox);
       // line1XLabel->setObjectName(QString::fromUtf8("line1XLabel"));

       // gridLayout->addWidget(line1XLabel, 1, 0, 1, 1);

       // line1YLabel = new QLabel(manualInsertGroupBox);
       // line1YLabel->setObjectName(QString::fromUtf8("line1YLabel"));

   //     gridLayout->addWidget(line1YLabel, 1, 2, 1, 1);

     //   defineALineLabel = new QLabel(manualInsertGroupBox);
     //   defineALineLabel->setObjectName(QString::fromUtf8("defineALineLabel"));

    //    gridLayout->addWidget(defineALineLabel, 0, 0, 1, 6);

     //   line1ZLabel = new QLabel(manualInsertGroupBox);
     //   line1ZLabel->setObjectName(QString::fromUtf8("line1ZLabel"));

   //     gridLayout->addWidget(line1ZLabel, 1, 4, 1, 1);

     //   line1ZDoubleSpinBox = new QDoubleSpinBox(manualInsertGroupBox);
   //     line1ZDoubleSpinBox->setObjectName(QString::fromUtf8("line1ZDoubleSpinBox"));
  //      sizePolicy.setHeightForWidth(line1ZDoubleSpinBox->sizePolicy().hasHeightForWidth());
  //      line1ZDoubleSpinBox->setSizePolicy(sizePolicy);

   //     gridLayout->addWidget(line1ZDoubleSpinBox, 1, 5, 1, 1);

   //     line1YDoubleSpinBox = new QDoubleSpinBox(manualInsertGroupBox);
  //      line1YDoubleSpinBox->setObjectName(QString::fromUtf8("line1YDoubleSpinBox"));
   //     sizePolicy.setHeightForWidth(line1YDoubleSpinBox->sizePolicy().hasHeightForWidth());
   //     line1YDoubleSpinBox->setSizePolicy(sizePolicy);

   //     gridLayout->addWidget(line1YDoubleSpinBox, 1, 3, 1, 1);

    //    line2XLabel = new QLabel(manualInsertGroupBox);
    //    line2XLabel->setObjectName(QString::fromUtf8("line2XLabel"));

     //   gridLayout->addWidget(line2XLabel, 2, 0, 1, 1);

   //     line2XDoubleSpinBox = new QDoubleSpinBox(manualInsertGroupBox);
    //    line2XDoubleSpinBox->setObjectName(QString::fromUtf8("line2XDoubleSpinBox"));

    //    gridLayout->addWidget(line2XDoubleSpinBox, 2, 1, 1, 1);

    //    line2YLabel = new QLabel(manualInsertGroupBox);
    //    line2YLabel->setObjectName(QString::fromUtf8("line2YLabel"));

    //    gridLayout->addWidget(line2YLabel, 2, 2, 1, 1);

   //     line2YDoubleSpinBox = new QDoubleSpinBox(manualInsertGroupBox);
   //     line2YDoubleSpinBox->setObjectName(QString::fromUtf8("line2YDoubleSpinBox"));

   //     gridLayout->addWidget(line2YDoubleSpinBox, 2, 3, 1, 1);

    //    line2ZLabel = new QLabel(manualInsertGroupBox);
    //    line2ZLabel->setObjectName(QString::fromUtf8("line2ZLabel"));

     //   gridLayout->addWidget(line2ZLabel, 2, 4, 1, 1);

    //    line2ZDoubleSpinBox = new QDoubleSpinBox(manualInsertGroupBox);
  //      line2ZDoubleSpinBox->setObjectName(QString::fromUtf8("line2ZDoubleSpinBox"));

     //   gridLayout->addWidget(line2ZDoubleSpinBox, 2, 5, 1, 1);

    //    addALinePushButton = new QPushButton(manualInsertGroupBox);
   //     addALinePushButton->setObjectName(QString::fromUtf8("addALinePushButton"));

   //     thresholdDoubleSpinBox=new QDoubleSpinBox(manualInsertGroupBox);
   //     thresholdDoubleSpinBox->setMinimum(0);
   //     thresholdDoubleSpinBox->setMaximum(1.0);

   //     gridLayout->addWidget(thresholdDoubleSpinBox,3,0,1,5);

  //      gridLayout->addWidget(addALinePushButton, 3, 5, 1, 1);

        isDrawCenterCheckBox=new QCheckBox(this);
        isDrawLargestEntropy=new QCheckBox(this);
        isDrawSmallestEntropy=new QCheckBox(this);



        gridLayout->addWidget(isDrawCenterCheckBox,4,0,1,2);
        isDrawCenterCheckBox->setText("Draw Center");

        gridLayout->addWidget(isDrawLargestEntropy,4,2,1,2);
        isDrawLargestEntropy->setText("Draw Largest Entropy");
        isDrawLargestEntropy->setChecked(true);

        gridLayout->addWidget(isDrawSmallestEntropy,4,4,1,2);
        isDrawSmallestEntropy->setText("Draw Smallest Entropy");
      //  gridLayout->addWidget();

        tapeWidthBase=new QDoubleSpinBox(this);
        tapeWidthBase->setMinimum(0);
        tapeWidthBase->setMaximum(5);


        tapeWidthFlex=new QDoubleSpinBox(this);
        tapeWidthFlex->setMinimum(0);
        tapeWidthFlex->setMaximum(5);



        tapeWidthBaseLabel=new QLabel(this);
        tapeWidthFlexLabel=new QLabel(this);

        tapeWidthBaseLabel->setText("Base Width");
        tapeWidthFlexLabel->setText("Flex Width");


        smoothLabel=new QLabel("Smoothness");
        smoothness=new QSpinBox(this);

        smoothLabel->setText("Smoothness");

        smoothness->setMinimum(0);
        smoothness->setMaximum(20);
        smoothness->setValue(8);

        gridLayout->addWidget(tapeWidthBaseLabel,5,0,1,1);
        gridLayout->addWidget(tapeWidthBase,5,1,1,1);
        gridLayout->addWidget(tapeWidthFlexLabel,5,2,1,1);
        gridLayout->addWidget(tapeWidthFlex,5,3,1,1);
        gridLayout->addWidget(smoothLabel,5,4,1,1);
        gridLayout->addWidget(smoothness,5,5,1,1);

        verticalLayout->addWidget(manualInsertGroupBox);
        tapeWidthBase->setValue(0.6);
tapeWidthFlex->setValue(1.9);

        automaticGroupBox = new QGroupBox(dockWidgetContents);
        automaticGroupBox->setObjectName(QString::fromUtf8("automaticGroupBox"));
        horizontalLayout = new QHBoxLayout(automaticGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        loadPushButton = new QPushButton(automaticGroupBox);
        loadPushButton->setObjectName(QString::fromUtf8("loadPushButton"));

        horizontalLayout->addWidget(loadPushButton);

        generatePushButton = new QPushButton(automaticGroupBox);
        generatePushButton->setObjectName(QString::fromUtf8("generatePushButton"));

        horizontalLayout->addWidget(generatePushButton);

        testPushButton = new QPushButton(automaticGroupBox);
        testPushButton->setObjectName(QString::fromUtf8("testPushButton"));

        horizontalLayout->addWidget(testPushButton);


        verticalLayout->addWidget(automaticGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        setWidget(dockWidgetContents);



         manualInsertGroupBox->setTitle(QApplication::translate("DrawIllustrative", "Manually Insert a Line:", 0, QApplication::UnicodeUTF8));
  //      line1XLabel->setText(QApplication::translate("DrawIllustrative", "X:", 0, QApplication::UnicodeUTF8));
 //       line1YLabel->setText(QApplication::translate("DrawIllustrative", "Y:", 0, QApplication::UnicodeUTF8));
//        defineALineLabel->setText(QApplication::translate("DrawIllustrative", "Define a Line to Add:", 0, QApplication::UnicodeUTF8));
 //       line1ZLabel->setText(QApplication::translate("DrawIllustrative", "Z:", 0, QApplication::UnicodeUTF8));
 //       line2XLabel->setText(QApplication::translate("DrawIllustrative", "X:", 0, QApplication::UnicodeUTF8));
 //       line2YLabel->setText(QApplication::translate("DrawIllustrative", "Y:", 0, QApplication::UnicodeUTF8));
 //       line2ZLabel->setText(QApplication::translate("DrawIllustrative", "Z:", 0, QApplication::UnicodeUTF8));
 //       addALinePushButton->setText(QApplication::translate("DrawIllustrative", "Add", 0, QApplication::UnicodeUTF8));
        automaticGroupBox->setTitle(QApplication::translate("DrawIllustrative", "Auto:", 0, QApplication::UnicodeUTF8));
        loadPushButton->setText(QApplication::translate("DrawIllustrative", "Load", 0, QApplication::UnicodeUTF8));
        generatePushButton->setText(QApplication::translate("DrawIllustrative", "PushButton", 0, QApplication::UnicodeUTF8));
        testPushButton->setText(QApplication::translate("DrawIllustrative","Test",0,QApplication::UnicodeUTF8));

        connect(&VectorField::getSingleton(),SIGNAL(dataUpdated()),this,SLOT(onDataUpdated()));
      //  connect(addALinePushButton,SIGNAL(clicked()),this,SLOT(onAddATape()));
      //  connect(thresholdDoubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(thresholdValueChanged(double)));
        connect(loadPushButton,SIGNAL(clicked()),this,SLOT(onLoadData()));
        connect(testPushButton,SIGNAL(clicked()),this,SLOT(onTest()));
};

void DrawIllustrative::onTest()
{
 //   DrawIllustrativeData::getSingleton().testRepresentativeLine();

    DrawIllustrativeData::getSingleton().clear();
    DrawIllustrativeData::getSingleton().setLineWidthBaseAndFlex(tapeWidthBase->value(),tapeWidthFlex->value());
DrawIllustrativeData::getSingleton().setSmoothness(smoothness->value());
        DrawIllustrativeData::getSingleton().setDrawCenter(isDrawCenterCheckBox->isChecked());
        DrawIllustrativeData::getSingleton().setDrawLargestEntropy(isDrawLargestEntropy->isChecked());
        DrawIllustrativeData::getSingleton().setDrawSmallestEntropy(isDrawSmallestEntropy->isChecked());

      //  DrawIllustrativeData::getSingleton().loadResultFromFile(resultfiles[currentSelected*5]);


        DrawIllustrativeData::getSingleton().generateATapeFromAStartPoint(GGL::Point3f(48,20,30),GGL::Point3f(1,0,0));
    //    DrawIllustrativeData::getSingleton().generateATapeFromAStartPoint(GGL::Point3f(48,20,30));


}

void DrawIllustrative::onRowChanged(int id)
{
    currentSelected=id;
}

void DrawIllustrative::onLoadData()
{
    /*QString(
                                                                 "cluster-syn-cluster18.dat"
                                                               // "cluster-syn-cluster20.dat"
                                                            //    "cluster-syn-15cluster.dat"
                                                              //  "cluster-syn-25cluster.dat"
                                                               // "cluster-hurricaneDownsample100x100x20-10cluster.dat"
                                                              //  "cluster-velo2-10cluster.dat"
                                                       //         "cluster-hurrucanesmall-20cluster.dat"
                                                             //   "cluster-supernova-10cluster.dat"
                                                             //   "cluster-tornado-10cluster.dat"
                                                                //   "cluster-plumemed-30cluster.dat"
                                                       //    "cluster-twoswirl-10cluster.dat"
                                                         //       "cluster-syn-10cluster.dat"
                                                        //        "cluster-random-10cluster.dat"
                                                    )*/

    DrawIllustrativeData::getSingleton().clear();
    DrawIllustrativeData::getSingleton().setLineWidthBaseAndFlex(tapeWidthBase->value(),tapeWidthFlex->value());
DrawIllustrativeData::getSingleton().setSmoothness(smoothness->value());
        DrawIllustrativeData::getSingleton().setDrawCenter(isDrawCenterCheckBox->isChecked());
        DrawIllustrativeData::getSingleton().setDrawLargestEntropy(isDrawLargestEntropy->isChecked());
        DrawIllustrativeData::getSingleton().setDrawSmallestEntropy(isDrawSmallestEntropy->isChecked());

        VectorField::getSingleton().init(resultfiles[currentSelected*5+1].toStdString().c_str(),resultfiles[currentSelected*5+2].toInt(),resultfiles[currentSelected*5+3].toInt(),resultfiles[currentSelected*5+4].toInt(),resultfiles[currentSelected*5]);
        DrawIllustrativeData::getSingleton().loadResultFromFile(resultfiles[currentSelected*5]);
}


void DrawIllustrative::thresholdValueChanged(double newvalue)
{
    DrawIllustrativeData::getSingleton().setThreshold(newvalue);
}

void DrawIllustrative::onDataUpdated()
{
  /*  line1XDoubleSpinBox->setMaximum(VectorField::getSingleton().xSize-1);
    line2XDoubleSpinBox->setMaximum(VectorField::getSingleton().xSize-1);
    line1YDoubleSpinBox->setMaximum(VectorField::getSingleton().ySize-1);
    line2YDoubleSpinBox->setMaximum(VectorField::getSingleton().ySize-1);
    line1ZDoubleSpinBox->setMaximum(VectorField::getSingleton().zSize-1);
    line2ZDoubleSpinBox->setMaximum(VectorField::getSingleton().zSize-1);*/
}

void DrawIllustrative::onAddATape()
{
   // struct timeval tim;
         //   gettimeofday(&tim, NULL);

            srand(/*tim.tv_sec+tim.tv_usec*/23);
    for(int i=0;i<20;++i)
    {
        GGL::Point3f p1( (float)(rand()%6400)/6400.0f*20+20 ,
                            (float)(rand()%6400)/6400.0f*20+20 ,
                            (float)(rand()%6400)/6400.0f*63 );

        GGL::Point3f p2(    (float)(rand()%6400)/6400.0f*4 ,
                            (float)(rand()%6400)/6400.0f*4,
                            (float)(rand()%6400)/6400.0f*4 );

        GGL::Point3f p3=p1;
        p3.Z()=p1.Z()+5;

        if(p3.X()<VectorField::getSingleton().xSize-1 && p3.Y()<VectorField::getSingleton().ySize-1 && p3.Z()<VectorField::getSingleton().zSize-1 )

           DrawIllustrativeData::getSingleton().generateATape(p1,p3);
       // DrawIllustrativeData::getSingleton().generateATape(GGL::Point3f(line1XDoubleSpinBox->value(),line1YDoubleSpinBox->value(),line1ZDoubleSpinBox->value()),GGL::Point3f(line2XDoubleSpinBox->value(),line2YDoubleSpinBox->value(),line2ZDoubleSpinBox->value()));
    }
}


DrawIllustrative::~DrawIllustrative()
{

};
