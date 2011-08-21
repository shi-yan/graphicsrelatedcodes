#include "clustercolorscheme.h"
#include <iostream>
#include <cstdio>
#include <QFile>
#include <QTextStream>
ClusterColorScheme::ClusterColorScheme()
{
}

void ClusterColorScheme::resize(int _size)
{
    colorList.clear();
    colorList.resize(_size);
    initializeWithColorSchemeE();

    emit clusterColorChanged();
}

void ClusterColorScheme::save(const QString &filename)
{
    FILE *fp=fopen(filename.toStdString().c_str(),"w");
    fprintf(fp,"%d\n",colorList.size());

    for(int i=0;i<colorList.size();++i)
    {
        fprintf(fp,"%d %d %d\n",colorList[i].r,colorList[i].g,colorList[i].b);
    }

    fclose(fp);
}

void ClusterColorScheme::load(const QString &filename)
{
    QFile data(filename);
    if (data.open(QFile::ReadOnly))
    {
        QTextStream in(&data);

        int clusterCount=0;
        in>>clusterCount;

        if(colorList.size()<clusterCount){
            colorList.clear();
            colorList.resize(clusterCount);
        }

        for(int i=0;i<clusterCount;++i)
        {
            int r=0;
            int g=0;
            int b=0;

            in>>r;
            in>>g;
            in>>b;

            colorList[i].r=r;
            colorList[i].g=g;
            colorList[i].b=b;
        }
    }
}

void ClusterColorScheme::initializeWithColorSchemeA()
{
    unsigned char colorSet[]=
    {
        252,192,166,
        195,32,95,
        205,165,191,
        164,101,109,
        251,246,242,
        252,211,165,};

    int colorSetN=6;


    for(int i=0;i<colorList.size();++i)
    {
        colorList[i].r=colorSet[(i%colorSetN)*3];

        colorList[i].g=colorSet[(i%colorSetN)*3+1];

        colorList[i].b=colorSet[(i%colorSetN)*3+2];
    }
}

void ClusterColorScheme::initializeWithColorSchemeB()
{
    unsigned char colorSet[]=
    {
      0xbb,0x44,0x44,
              0xdd,0x99,0x44,
              0xee,0xee,0xff,
              0xcc,0xaa,0xbb,
              0x66,0x33,0x77,

  };
    int colorSetN=5;
    for(int i=0;i<colorList.size();++i)
    {
        colorList[i].r=colorSet[(i%colorSetN)*3];

        colorList[i].g=colorSet[(i%colorSetN)*3+1];

        colorList[i].b=colorSet[(i%colorSetN)*3+2];
    }
}

void ClusterColorScheme::initializeWithColorSchemeC()
{

        unsigned char colorSet[]=
        {
     0x44,0x33,0x33,
             0x88,0x77,0x99,
             0xdd,0xcc,0xcc,
             0xcc,0xaa,0xaa,
             0x99,0x77,0x77};
        int colorSetN=5;
        for(int i=0;i<colorList.size();++i)
        {
            colorList[i].r=colorSet[(i%colorSetN)*3];

            colorList[i].g=colorSet[(i%colorSetN)*3+1];

            colorList[i].b=colorSet[(i%colorSetN)*3+2];
        }


}

void ClusterColorScheme::initializeWithColorSchemeD()
{

            unsigned char colorSet[]=
            {
     0xbb,0x44,0x55
             ,0xdd,0xaa,0x66
             ,0xee,0xdd,0x99
             ,0xdd,0xaa,0x88
             ,0xbb,0x55,0x77
 };
            int colorSetN=5;
            for(int i=0;i<colorList.size();++i)
            {
                colorList[i].r=colorSet[(i%colorSetN)*3];

                colorList[i].g=colorSet[(i%colorSetN)*3+1];

                colorList[i].b=colorSet[(i%colorSetN)*3+2];
            }
}

void ClusterColorScheme::initializeWithColorSchemeE()
{

                unsigned char colorSet[]=
                {
    0x88,0x66,0x66
            ,0xaa,0xbb,0xbb
            ,0xbb,0xcc,0xcc
            ,0xff,0xff,0xff
            ,0xbb,0x88,0xaa};

                int colorSetN=5;

                for(int i=0;i<colorList.size();++i)
                {
                    colorList[i].r=colorSet[(i%colorSetN)*3];

                    colorList[i].g=colorSet[(i%colorSetN)*3+1];

                    colorList[i].b=colorSet[(i%colorSetN)*3+2];
                }

}

void ClusterColorScheme::initializeWithColorSchemeF()
{

                    unsigned char colorSet[]=
                    {
     0xdd,0x99,0x77
     ,0xee,0xaa,0x99
     ,0xff,0xff,0xee
     ,0xdd,0xcc,0x99
     ,0xbb,0x77,0x55};

                    int colorSetN=5;

                    for(int i=0;i<colorList.size();++i)
                    {
                        colorList[i].r=colorSet[(i%colorSetN)*3];

                        colorList[i].g=colorSet[(i%colorSetN)*3+1];

                        colorList[i].b=colorSet[(i%colorSetN)*3+2];
                    }
}

void ClusterColorScheme::initializeWithColorSchemeG()
{

                        unsigned char colorSet[]=
                        {
        0xcc,0x99,0x66
                ,0xcc,0xbb,0x99
                ,0x11,0x11,0x11
                ,0x22,0x22,0x22
                ,0x99,0x66,0x55
        };

                        int colorSetN=5;
                        for(int i=0;i<colorList.size();++i)
                        {
                            colorList[i].r=colorSet[(i%colorSetN)*3];

                            colorList[i].g=colorSet[(i%colorSetN)*3+1];

                            colorList[i].b=colorSet[(i%colorSetN)*3+2];
                        }
}
