#include "featuredetectiondata.h"
//#include <sys/time.h>
#include <cstdio>
#include <QImage>
#include <QPainter>
#include <QApplication>

const double PI=4.0*atan(1.0);

FeatureDetectionData::FeatureDetectionData()
{

}

FeatureDetectionData::~FeatureDetectionData()
{
}

void FeatureDetectionData::draw()
{
    for(std::vector<Signature>::iterator iter=sampleList.begin();iter!=sampleList.end();++iter)
    {
        iter->draw();
    }

    for(std::vector<SamplePair>::iterator iter=samplePairList.begin();iter!=samplePairList.end();++iter)
        iter->draw();
}

void FeatureDetectionData::computeTransformation()
{
    int k=0;
    for(std::vector<SamplePair>::iterator iter=samplePairList.begin();iter!=samplePairList.end();++iter)
    {
        Transformation t=iter->getTransformation();
        t.setPairID(k++);
        transformationList.push_back(t);
    }
}


GGL::Point2f FeatureDetectionData::translateCoordinate(const GGL::Point2f &in)
{
    float x=              (in.X()+0.1f)/(2.0*PI+0.2f)*1000.0f;
    float y=1000.0f*(1.0f-(in.Y()+0.1f)/(2.0*PI+0.2f));

    return GGL::Point2f(x,y);
}

GGL::Point2f FeatureDetectionData::translateCoordinate2(const GGL::Point2f &in)
{
    float x=500.0f+in.X()*480.0f;
    float y=500.0f+in.Y()*480.0f;

    return GGL::Point2f(x,y);
}

void FeatureDetectionData::outputRotationAxisCloud()
{

    QImage outputimage(1000,1000,QImage::Format_RGB32);
    QPainter p(&outputimage);
    p.setBackgroundMode(Qt::TransparentMode);
    p.setBackground(QBrush(Qt::white));
    p.fillRect (0,0,1000,1000,Qt::white);
    p.setRenderHint(QPainter::HighQualityAntialiasing);

    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::black);

    /*GGL::Point2f xl(-0.05f,0.0f);
    GGL::Point2f xr(2.0*PI+0.05f,0.0f);

    xl=translateCoordinate(xl);
    xr=translateCoordinate(xr);

    p.drawLine ( xl.X(),xl.Y(),xr.X(),xr.Y() );


    GGL::Point2f yt(0,0.5*PI+0.05);
    GGL::Point2f yb(0,-0.05);

    yt=translateCoordinate(yt);
    yb=translateCoordinate(yb);

    p.drawLine(yt.X(),yt.Y(),yb.X(),yb.Y());

    p.setPen(QPen(QBrush(Qt::blue),1.0,Qt::DashLine));

    for(float x=0;x<2.0*PI;x+=0.1*PI)
    {
        GGL::Point2f a(x,0);
        GGL::Point2f b(x,2.0*PI);

        a=translateCoordinate(a);
        b=translateCoordinate(b);

        p.drawLine(a.X(),a.Y(),b.X(),b.Y());
    }

    for(float y=0.0;y<0.5*PI;y+=0.1*PI)
    {
        GGL::Point2f a(0,y);
        GGL::Point2f b(2.0*PI,y);

        a=translateCoordinate(a);
        b=translateCoordinate(b);

        p.drawLine(a.X(),a.Y(),b.X(),b.Y());
    }*/


    for(int i=48;i<480;i+=48)
    {
        p.drawEllipse(QPoint(500,500),i,i);
    }



    p.setBrush(QColor::fromRgb(100,0,0,20));
    p.setPen(Qt::NoPen);


    FILE *fp=fopen("./rotationAxisCloud.txt","w");

    for(std::vector<Transformation>::iterator iter=transformationList.begin();iter!=transformationList.end();++iter)
    {

        GGL::Point3f rotationAxis=iter->getRotationAxis();

        qDebug("%f,%f,%f",rotationAxis.X(),rotationAxis.Y(),rotationAxis.Z());

        if(rotationAxis.length()<0.1f)
            continue;

      //  if(rotationAxis*GGL::Point3f(0.0f,0.0f,1.0f)<0.0f)
        //    rotationAxis=rotationAxis*-1.0f;

        double xylength=sqrt(rotationAxis.X()*rotationAxis.X()+rotationAxis.Y()*rotationAxis.Y());

        double siny=rotationAxis.Z();

        double yangle=asin(siny);

        if(yangle!=yangle)
            continue;

        double cosx=rotationAxis.X()/xylength;
        double sinx=rotationAxis.Y()/xylength;

        double xangle=acos(cosx);

        if(xangle!=xangle)
            continue;

        if(sinx<0.0)
            xangle=8.0*atan(1.0)-xangle;

        GGL::Point2f position(xangle,yangle);

        position=translateCoordinate(position);

        GGL::Point2f position2(rotationAxis.X(),rotationAxis.Y());
 qDebug("%f,%f",position2.X(),position2.Y());
        position2=translateCoordinate2(position2);

      //  p.drawEllipse(QPoint(position.X(),position.Y()),2,2);
       // if((xylength-0.7)*(xylength-0.7)<0.00001 && (cosx*cosx<0.00001 || sinx*sinx<0.00001))
        {

            qDebug("%f,%f",position2.X(),position2.Y());

            p.drawEllipse(QPoint(position2.X(),position2.Y()),2,2);
            samplePairList[iter->getPairID()].setTestInfo(10);
        }

        fprintf(fp,"%f,%f\n",xangle,yangle);
    }

    outputimage.save("result.png");

    fclose(fp);
}

void FeatureDetectionData::clusterRotationAxis()
{

    int nclusters=5;
    int nrows=transformationList.size();
    int ncolumns=3;

    double **data;

    data=new double*[nrows];

    for(int i=0;i<transformationList.size();++i)
    {
        data[i]=new double[3];
        GGL::Point3f ra=transformationList[i].getRotationAxis();
        data[i][0]=ra.X();
        data[i][1]=ra.Y();
        data[i][2]=ra.Z();
    }

    int **mask=new int*[nrows];
    for(int i=0;i<nrows;++i)
    {
        mask[i]=new int[3];

        mask[i][0]=1;
        mask[i][1]=1;
        mask[i][2]=1;
    }

    double *weight=new double[nrows];
    for(int i=0;i<nrows;++i)
        weight[i]=1.0;

    int *clusterid=new int[nrows];
    double error;
    int ifound;


    kcluster (nclusters, nrows, ncolumns, data,    mask,  weight, 0, 1, 'a', 'e',  clusterid, &error, &ifound);
}


void FeatureDetectionData::generateSamples(int count)
{
    //struct timeval tim;
         //   gettimeofday(&tim, NULL);

            srand(/*tim.tv_sec+tim.tv_usec*/23);

            for (int i=0; i<count; ++i)
            {
                    Sample s;
                    s.generate(i+52);
                    s.generateJacobian();
                    s.computeSignature();

                    Signature sig;
                    sig.add(s);

                    sampleList.push_back(sig);
            }
}

void FeatureDetectionData::collectPairs()
{
    double smalldis=100.0;
            double largedis=-0.5;
            for (int i=0; i<sampleList.size()-1; ++i)
            {
                    for (int e=i+1; e<sampleList.size(); ++e)
                    {
                            double dis=distance(sampleList[i], sampleList[e]);

                            //printf("dis %f\n",dis);

                            if (dis>largedis) {
                                    largedis=dis;
                            }

                            if (dis<smalldis) {
                                    smalldis=dis;
                            }

                            if (dis<0.05f)
                            {
                                    SamplePair samplep(sampleList[i],sampleList[e],dis);

                                    samplePairList.push_back(samplep);
                            }
                    }
            }

            emit pairsCollected();

}
