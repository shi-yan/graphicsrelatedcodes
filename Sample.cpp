/*
 *  Sample.cpp
 *  3DTest
 *
 *  Created by Shi Yan on 12/8/10.
 *  Copyright 2010 UCDavis. All rights reserved.
 *
 */

#include "alglib/linalg.h"
#include <QGLWidget>
#include "Sample.h"
#include "VectorField.h"
//#include <sys/time.h>
#include <cstdlib>
#include "Point3.h"
#include "eig3.h"

#include "matrix44.h"


Sample::Sample(): pos(), eigenVector(),z(),x(),y(),descriptor(0.0)
{
    jacobian[0][0]=0;
    jacobian[0][1]=0;
    jacobian[0][2]=0;

    jacobian[1][0]=0;
    jacobian[1][1]=0;
    jacobian[1][2]=0;

    jacobian[2][0]=0;
    jacobian[2][1]=0;
    jacobian[2][2]=0;

    signature[0][0]=0;
    signature[0][1]=0;
    signature[0][2]=0;

    signature[1][0]=0;
    signature[1][1]=0;
    signature[1][2]=0;

    signature[2][0]=0;
    signature[2][1]=0;
    signature[2][2]=0;
}

Sample::~Sample()
{

}
void Sample::initializeWithPos(GGL::Point3f &p)
{
    pos=p;

}

void Sample::generate(int i)
{

	float x=(float)(rand()%6400)/6399.0f*(VectorField::getSingleton().xSize-1);

	float y=(float)(rand()%6400)/6399.0f*(VectorField::getSingleton().ySize-1);

	float z=(float)(rand()%6400)/6399.0f*(VectorField::getSingleton().zSize-1);
	
        GGL::Point3f start( x,  y ,z);
	
	pos=start;
}

void Sample::generateJacobian()
{
	const float epsilon=0.0001f;
	
        GGL::Point3f original=VectorField::getSingleton().getVector(pos.X(),pos.Y(),pos.Z());
	
        GGL::Point3f xx=VectorField::getSingleton().getVector(pos.X()+epsilon,pos.Y(),pos.Z());
        GGL::Point3f yy=VectorField::getSingleton().getVector(pos.X(),pos.Y()+epsilon,pos.Z());
        GGL::Point3f zz=VectorField::getSingleton().getVector(pos.X(),pos.Y(),pos.Z()+epsilon);
	
        alglib::real_2d_array a;
        a = "[[5,2,4],[-3,6,2],[3,-3,1]]";

    /*    jacobian[0][0]=(xx.X()-original.X())/epsilon;
        jacobian[1][0]=(yy.X()-original.X())/epsilon;
        jacobian[2][0]=(zz.X()-original.X())/epsilon;
	
	
        jacobian[0][1]=(xx.Y()-original.Y())/epsilon;
        jacobian[1][1]=(yy.Y()-original.Y())/epsilon;
        jacobian[2][1]=(zz.Y()-original.Y())/epsilon;
	
        jacobian[0][2]=(xx.Z()-original.Z())/epsilon;
        jacobian[1][2]=(yy.Z()-original.Z())/epsilon;
        jacobian[2][2]=(zz.Z()-original.Z())/epsilon;
*/

        a[0][0]=(xx.X()-original.X())/epsilon;
            a[1][0]=(yy.X()-original.X())/epsilon;
            a[2][0]=(zz.X()-original.X())/epsilon;


            a[0][1]=(xx.Y()-original.Y())/epsilon;
            a[1][1]=(yy.Y()-original.Y())/epsilon;
            a[2][1]=(zz.Y()-original.Y())/epsilon;

            a[0][2]=(xx.Z()-original.Z())/epsilon;
            a[1][2]=(yy.Z()-original.Z())/epsilon;
            a[2][2]=(zz.Z()-original.Z())/epsilon;

qDebug("{{%f,%f,%f},{%f,%f,%f},{%f,%f,%f}}",a[0][0],a[0][1],a[0][2],a[1][0],a[1][1],a[1][2],a[2][0],a[2][1],a[2][2]);

        alglib::real_1d_array wr;
        alglib::real_1d_array wi;
        alglib::real_2d_array vl;
        alglib::real_2d_array vr;

        bool alglibresult=alglib::rmatrixevd(
             a,
             3,
            3,
          wr,
           wi,
            vl,
            vr);

        qDebug("%f",wr[0]);
        qDebug("%f,%f,%f",vl[0][0],vl[1][0],vl[2][0]);


       /* jacobian[0][0]=5.0;
        jacobian[0][1]=2.0;
        jacobian[0][2]=4.0;


        jacobian[1][0]=-3.0;
        jacobian[1][1]=6.0;
        jacobian[1][2]=2.0;

        jacobian[2][0]=3.0;
        jacobian[2][1]=-3.0;
        jacobian[2][2]=1.0;*/


        /*double V[3][3];
	double d[3];
	
        eigen_decomposition(jacobian, V, d);*/
	
        GGL::Point3f e(vl[0][0],vl[1][0],vl[2][0]);

      /*  qDebug("eigen vector of jacobian %f (%f,%f,%f)",d[0],V[0][0],V[1][0],V[2][0]);

        qDebug("eigen vector of jacobian %f (%f,%f,%f)",d[1],V[0][1],V[1][1],V[2][1]);

        qDebug("eigen vector of jacobian %f (%f,%f,%f)",d[2],V[0][2],V[1][2],V[2][2]);
*/
	eigenVector=e;
	
        GGL::Point3f dir(original.X(),original.Y(),original.Z());
	z=dir;
	
        x=z^eigenVector;

    /*    if(x.length()<0.00001)
        {
            eigenVector.vec(V[0][2],V[1][2],V[2][2]);
            x=z^eigenVector;
        }*/
	
	y=z^x;
	
        z.Normalize();
	x.Normalize();
	y.Normalize();



}

void Sample::draw()
{
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3f(pos.X(), pos.Y(), pos.Z());
	glVertex3f(pos.X()+z.X(), pos.Y()+z.Y(), pos.Z()+z.Z());
	glEnd();
	
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3f(pos.X(), pos.Y(), pos.Z());
	glVertex3f(pos.X()+x.X(), pos.Y()+x.Y(), pos.Z()+x.Z());
	glEnd();
	
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(pos.X(), pos.Y(), pos.Z());
	glVertex3f(pos.X()+y.X(), pos.Y()+y.Y(), pos.Z()+y.Z());
	glEnd();
}


Sample::Sample(const Sample & in)
{
	pos=in.pos;
	 eigenVector=in.eigenVector;
	z=in.z;
	 x=in.x;
	 y=in.y;
	
	jacobian[0][0]=in.jacobian[0][0];
	jacobian[0][1]=in.jacobian[0][1];
	jacobian[0][2]=in.jacobian[0][2];
	
	jacobian[1][0]=in.jacobian[1][0];
	jacobian[1][1]=in.jacobian[1][1];
	jacobian[1][2]=in.jacobian[1][2];
	
	jacobian[2][0]=in.jacobian[2][0];
	jacobian[2][1]=in.jacobian[2][1];
	jacobian[2][2]=in.jacobian[2][2];
	
	
	signature[0][0]=in.signature[0][0];
	signature[0][1]=in.signature[0][1];
	signature[0][2]=in.signature[0][2];
	
	signature[1][0]=in.signature[1][0];
	signature[1][1]=in.signature[1][1];
	signature[1][2]=in.signature[1][2];
	
	signature[2][0]=in.signature[2][0];
	signature[2][1]=in.signature[2][1];
	signature[2][2]=in.signature[2][2];

        descriptor=in.descriptor;
}

void Sample::computeDescriptor()
{
   descriptor=signature[0][0]*signature[1][1]*signature[2][2]
               +signature[0][1]*signature[1][2]*signature[2][0]
               +signature[0][2]*signature[ 1][0]*signature[ 2][1]-

               signature[0][2]*signature[ 1][1]*signature[ 2][0]
               -signature[0][1]*signature[1][0]*signature[2][2]
               -signature[0][0]*signature[1][2]*signature[2][1];
    if(descriptor>0)
        descriptor=1.0;
    else if(descriptor<0)
        descriptor=-1.0;
    else
        descriptor=0.0;
}

void Sample::operator=(const Sample & in)
{
	pos=in.pos;
	eigenVector=in.eigenVector;
	z=in.z;
	x=in.x;
	y=in.y;
	
	jacobian[0][0]=in.jacobian[0][0];
	jacobian[0][1]=in.jacobian[0][1];
	jacobian[0][2]=in.jacobian[0][2];
	
	jacobian[1][0]=in.jacobian[1][0];
	jacobian[1][1]=in.jacobian[1][1];
	jacobian[1][2]=in.jacobian[1][2];
	
	jacobian[2][0]=in.jacobian[2][0];
	jacobian[2][1]=in.jacobian[2][1];
	jacobian[2][2]=in.jacobian[2][2];
	
	signature[0][0]=in.signature[0][0];
	signature[0][1]=in.signature[0][1];
	signature[0][2]=in.signature[0][2];
	
	signature[1][0]=in.signature[1][0];
	signature[1][1]=in.signature[1][1];
	signature[1][2]=in.signature[1][2];
	
	signature[2][0]=in.signature[2][0];
	signature[2][1]=in.signature[2][1];
	signature[2][2]=in.signature[2][2];

        descriptor=in.descriptor;
}


void Sample::computeSignature()
{
	const float epsilon=0.0001f;
	
        GGL::Point3f original=VectorField::getSingleton().getVector(pos.X(),pos.Y(),pos.Z());
	
        GGL::Point3f xx=VectorField::getSingleton().getVector(pos.X()+epsilon*x.X(),pos.Y()+epsilon*x.Y(),pos.Z()+epsilon*x.Z());
        GGL::Point3f yy=VectorField::getSingleton().getVector(pos.X()+epsilon*y.X(),pos.Y()+epsilon*y.Y(),pos.Z()+epsilon*y.Z());
        GGL::Point3f zz=VectorField::getSingleton().getVector(pos.X()+epsilon*z.X(),pos.Y()+epsilon*z.Y(),pos.Z()+epsilon*z.Z());
	
        signature[0][0]=(xx.X()-original.X())/epsilon;
        signature[0][1]=(yy.X()-original.X())/epsilon;
        signature[0][2]=(zz.X()-original.X())/epsilon;
	
        signature[1][0]=(xx.Y()-original.Y())/epsilon;
        signature[1][1]=(yy.Y()-original.Y())/epsilon;
        signature[1][2]=(zz.Y()-original.Y())/epsilon;
	
        signature[2][0]=(xx.Z()-original.Z())/epsilon;
        signature[2][1]=(yy.Z()-original.Z())/epsilon;
        signature[2][2]=(zz.Z()-original.Z())/epsilon;
	
        float length=original.length();
	
	signature[0][0]/=length;
	signature[0][1]/=length;
	signature[0][2]/=length;
	
	signature[1][0]/=length;
	signature[1][1]/=length;
	signature[1][2]/=length;
	
	signature[2][0]/=length;
	signature[2][1]/=length;
	signature[2][2]/=length;
	
}

double distance(Sample s1,Sample s2)
{
	double dissqr=(s1.signature[0][0]-s2.signature[0][0])*(s1.signature[0][0]-s2.signature[0][0])+
				  (s1.signature[0][1]-s2.signature[0][1])*(s1.signature[0][1]-s2.signature[0][1]) +
				 (s1.signature[0][2]-s2.signature[0][2])*(s1.signature[0][2]-s2.signature[0][2])+
	
				 (s1.signature[1][0]-s2.signature[1][0])*(s1.signature[1][0]-s2.signature[1][0])+
				 (s1.signature[1][1]-s2.signature[1][1])*(s1.signature[1][1]-s2.signature[1][1])+
				 (s1.signature[1][2]-s2.signature[1][2])*(s1.signature[1][2]-s2.signature[1][2])+
	
				 (s1.signature[2][0]-s2.signature[2][0])*(s1.signature[2][0]-s2.signature[2][0])+
				 (s1.signature[2][1]-s2.signature[2][1])*(s1.signature[2][1]-s2.signature[2][1])+
				 (s1.signature[2][2]-s2.signature[2][2])*(s1.signature[2][2]-s2.signature[2][2]);
	
	return sqrt(dissqr);
}

Transformation computeTransformation(const Sample &n1,const Sample &n2)
{
    //transform

    GGL::Point3f transform=n2.pos-n1.pos;

    GGL::Point3f v1=VectorField::getSingleton().getVector(n1.pos.X(),n1.pos.Y(),n1.pos.Z());
    GGL::Point3f v2=VectorField::getSingleton().getVector(n2.pos.X(),n2.pos.Y(),n2.pos.Z());

    float scaling=v2.length()/v1.length();

    //rotation
    //fist compute the rotation axis of z

 /*   GGL::Point3f zRotationAxis=n1.z^n2.z;

    double zangle=acos(n1.z*n2.z);

    GGL::Matrix44<float> zRotationMatrix;

    zRotationMatrix.SetRotate(zangle,zRotationAxis);

    GGL::Matrix44<float> xRotationMatrix;

    GGL::Point3f newx=zRotationMatrix*n1.x;

    newx.Normalize();

    GGL::Point3f newxn2xcross=newx^n2.x;

    double xangle=acos(newx*n2.x);

    if(newxn2xcross*n2.z<0.0)
    {
        xangle=atan(1)*8.0-xangle;
    }

    xRotationMatrix.SetRotate(xangle,n2.z);


    GGL::Matrix44<float> rotationMatrix=xRotationMatrix*zRotationMatrix;*/

/*

    qDebug("length of z1 %f and z2 %f",n1.z.length(),n2.z.length());
    qDebug("length of x1 %f and x2 %f",n1.x.length(),n2.x.length());
    qDebug("length of y1 %f and y2 %f",n1.y.length(),n2.y.length());
*/


    GGL::Matrix33f m1;
    GGL::Matrix33f m2;


    m1.SetRow(0,n1.x);
    m1.SetRow(1,n1.y);
    m1.SetRow(2,n1.z);

    m2.SetColumn(0,n2.x);
    m2.SetColumn(1,n2.y);
    m2.SetColumn(2,n2.z);

    GGL::Matrix33f rotationMatrix=m2*m1;


  //  double rm[3][3];

      alglib::real_2d_array rm;
            rm  = "[[5,2,4],[-3,6,2],[3,-3,1]]";
    rm[0][0]=rotationMatrix[0][0];
    rm[0][1]=rotationMatrix[0][1];
    rm[0][2]=rotationMatrix[0][2];

    rm[1][0]=rotationMatrix[1][0];
    rm[1][1]=rotationMatrix[1][1];
    rm[1][2]=rotationMatrix[1][2];

    rm[2][0]=rotationMatrix[2][0];
    rm[2][1]=rotationMatrix[2][1];
    rm[2][2]=rotationMatrix[2][2];

  //  double V[3][3];
//    double d[3];

 //   eigen_decomposition(rm, V, d);

   // qDebug("{{%f,%f,%f},{%f,%f,%f},{%f,%f,%f}}",rm[0][0],rm[0][1],rm[0][2],rm[1][0],rm[1][1],rm[1][2],rm[2][0],rm[2][1],rm[2][2]);

            alglib::real_1d_array wr;
            alglib::real_1d_array wi;
            alglib::real_2d_array vl;
            alglib::real_2d_array vr;

            bool alglibresult=alglib::rmatrixevd(
                 rm,
                 3,
                3,
              wr,
               wi,
                vl,
                vr);

       //     qDebug("%f",wr[0]);
       //     qDebug("%f,%f,%f",vl[0][0],vl[1][0],vl[2][0]);

    double mini=10.0f;
    int minindex=-1;
    for(int i=0;i<3;++i)
    {
       // qDebug("eigen vector %d: %f (%f,%f,%f)",i,d[i],V[0][i],V[1][i],V[2][i]);
        double current=wr[i]-1.0;
        current=current*current;
       // qDebug("current: %f",current);
        if(current<mini)
        {
            mini=current;
            minindex=i;
        }
    }

  GGL::Point3f rotationAxis(0,0,0);

    if(mini<0.001f)
  {

       rotationAxis.vec(vl[0][minindex],vl[1][minindex],vl[2][minindex]);
    }

    Transformation t;
    t.setRotationAxis(rotationAxis.Normalize());

    //GGL::Matrix33f rotationMatrix33(rotationMatrix,3);
    t.setRotationMatrix(rotationMatrix);

    return t;
}
