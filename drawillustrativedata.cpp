#include <GL/glew.h>
#include "drawillustrativedata.h"
#include "VectorField.h"
#include <QGLWidget>
#include "matrix44.h"
#include "Sample.h"
#include "Box3.h"
#include "clustercolorscheme.h"

extern void eigen_decomposition(double A[3][3], double V[3][3], double d[3]);

DrawIllustrativeData::DrawIllustrativeData():illustrativeShaderProgram(0),_threshold(0.24)//,fbo(0)
        ,illustrativeAntiAliasingShaderProgram(0),
        vshader(0),
        fshader(0),
        vashader(0),
        fashader(0),
         illustrativeShadowShaderProgram(0),
         vsshader(0),
         fsshader(0)
{
}


GGL::Point3f DrawIllustrativeData::movePointInBackward(float x,float y,float z)
{
    //const float deltaT=0.025f;

    GGL::Point3f pos(x,y,z);

    GGL::Point3f dir=VectorField::getSingleton().getVector(x,y,z);

    float deltaT=1.5f/(dir.length());

    if (deltaT>2.0f) {
            deltaT=1.5f;
    }

    deltaT=-deltaT;

    GGL::Point3f dd(dir);

    GGL::Point3f k1(dd*deltaT);

    GGL::Point3f tempP=pos+(k1*0.5f);

    dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

    dd=(dir);

    GGL::Point3f  k2=dd*deltaT;

    tempP=pos+k2*0.5f;

    dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());


    dd=(dir);

    GGL::Point3f  k3=dd*deltaT;

    tempP=pos+(k3*0.5f);

    dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

    dd=(dir);

    GGL::Point3f  k4=dd*deltaT;

    pos+=(k1+k2*2.0f+k3*3.0f+k4)*(1.0f/6.0f);

    return pos;
}

GGL::Point3f DrawIllustrativeData::movePoint(float x, float y, float z, float deltaT)
{
    //const float deltaT=0.025f;

    GGL::Point3f pos(x,y,z);

    GGL::Point3f dir=VectorField::getSingleton().getVector(x,y,z);



    GGL::Point3f dd(dir);

    GGL::Point3f k1(dd*deltaT);

    GGL::Point3f tempP=pos+(k1*0.5f);

    dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

    dd=(dir);

    GGL::Point3f  k2=dd*deltaT;

    tempP=pos+k2*0.5f;

    dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());


    dd=(dir);

    GGL::Point3f  k3=dd*deltaT;

    tempP=pos+(k3*0.5f);

    dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

    dd=(dir);

    GGL::Point3f  k4=dd*deltaT;

    pos+=(k1+k2*2.0f+k3*3.0f+k4)*(1.0f/6.0f);

    return pos;
}

GGL::Point3f DrawIllustrativeData::movePoint(float x,float y,float z)
{

        //const float deltaT=0.025f;

        GGL::Point3f pos(x,y,z);

        GGL::Point3f dir=VectorField::getSingleton().getVector(x,y,z);

        float deltaT=1.5f/(dir.length());

        if (deltaT>2.0f) {
                deltaT=1.5f;
        }

        GGL::Point3f dd(dir);

        GGL::Point3f k1(dd*deltaT);

        GGL::Point3f tempP=pos+(k1*0.5f);

        dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

        dd=(dir);

        GGL::Point3f  k2=dd*deltaT;

        tempP=pos+k2*0.5f;

        dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());


        dd=(dir);

        GGL::Point3f  k3=dd*deltaT;

        tempP=pos+(k3*0.5f);

        dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

        dd=(dir);

        GGL::Point3f  k4=dd*deltaT;

        pos+=(k1+k2*2.0f+k3*3.0f+k4)*(1.0f/6.0f);

        return pos;
}

void DrawIllustrativeData::drawSilhouette(const GGL::Point3f &eye)
{
    //fbo->bind();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ZERO);

    illustrativeShaderProgram->bind();
    illustrativeShaderProgram-> setUniformValue (eyePositionUniform, eye.X(),eye.Y(),eye.Z());
    glLineWidth(6.0);
    for(int e=0;e<tapes.size();++e)
    {
       glBegin(GL_TRIANGLE_STRIP);

     //  glBegin(GL_LINE_STRIP);
        for(int i=0;i<tapes[e].size();i+=1)
        {
            glNormal3f(tapeNormals[e][i].X(),tapeNormals[e][i].Y(),tapeNormals[e][i].Z());
            glVertex3f(tapes[e][i].X(),tapes[e][i].Y(),tapes[e][i].Z());
        }

        glEnd();

        glBegin(GL_TRIANGLES);
        if(tapes[e].size()>4)
        {
            GGL::Point3f last6=tapes[e][tapes[e].size()-2];
            GGL::Point3f last6norm=tapeNormals[e][tapes[e].size()-2];

            GGL::Point3f last5=tapes[e][tapes[e].size()-1];
            GGL::Point3f last5norm=tapeNormals[e][tapes[e].size()-1];

            GGL::Point3f up=(last6-last5).Normalize()*2.5+last6;
            GGL::Point3f upnorm=(last6norm+last5norm)*0.5;

            GGL::Point3f down=(last5-last6).Normalize()*2.5+last5;
            GGL::Point3f downnorm=upnorm;

            GGL::Point3f front=((last6-tapes[e][tapes[e].size()-4]).Normalize()+(last5-tapes[e][tapes[e].size()-3]).Normalize())*2.5f;
            front=(last6+last5)*0.5+front;

            GGL::Point3f frontnorm=upnorm;


            glNormal3f(upnorm.X(),upnorm.Y(),upnorm.Z());
            glVertex3f(up.X(),up.Y(),up.Z());
            glNormal3f(downnorm.X(),downnorm.Y(),downnorm.Z());
            glVertex3f(down.X(),down.Y(),down.Z());
            glNormal3f(frontnorm.X(),frontnorm.Y(),frontnorm.Z());
            glVertex3f(front.X(),front.Y(),front.Z());
        }
        glEnd();

    }


    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboAntiAliasing);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    illustrativeAntiAliasingShaderProgram->bind();

    illustrativeAntiAliasingShaderProgram->setUniformValue(mapUniform,0);
    illustrativeAntiAliasingShaderProgram->setUniformValue(thresholdUniform,(float)_threshold);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,img);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);

    glTexCoord2f(1, 0);
    glVertex2f(1, -1);

    glTexCoord2f(1, 1);
    glVertex2f(1, 1);

    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);


    glEnd();

    glUseProgram(0);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void DrawIllustrativeData::draw(const GGL::Point3f &eye)
{
    _eye=eye;
    bool drawAvg=false;

    if(tapes.size())
    {

      //  qDebug("tape size:%d",tapes.size());
      /*  glClampColor( GL_CLAMP_VERTEX_COLOR  , GL_FALSE );
        glClampColor( GL_CLAMP_FRAGMENT_COLOR, GL_FALSE );
        glClampColor( GL_CLAMP_READ_COLOR    , GL_FALSE );
        glViewport(0,0,1024,1024);
        generateShadowMap(GGL::Point3f(65.0f,65.0f,65.0f));
*/
        glViewport(0, 0, screenWidth*2, screenHeight*2);
      drawDotShadow(eye);

    drawSilhouette(eye);


        glViewport(0,0,screenWidth,screenHeight);
         drawColor();
        drawFinal();

    }
    else if(clusterlist.size() && drawAvg)
    {

        for(int e=0;e<clusterlist.size();++e)
        {
            glBegin(GL_LINE_STRIP);

            for(int i=0;i<49;++i)
            {
                GGL::Point3f avg(0,0,0);

                for(std::vector<StreamSampleLine>::iterator iter=clusterlist[e].begin();iter!=clusterlist[e].end();++iter)
                {

                    avg+=(*iter).samples[i];

                }

                avg/=49.0;

                glVertex3f(avg.X(),avg.Y(),avg.Z());
            }

            glEnd();
        }
    }
    else if(clusterlist.size() && !drawAvg)
    {
        glColor3ub(0,0,0);

        for(std::vector<StreamSampleLine>::iterator iter=clusterlist[1].begin();iter!=clusterlist[1].end();++iter)
        {
            glBegin(GL_LINE_STRIP);
            for(int i=0;i<(*iter).samples.size();++i)
            {
                glVertex3f((*iter).samples[i].X(),(*iter).samples[i].Y(),(*iter).samples[i].Z());
            }
            glEnd();
        }

        glColor3ub(255,0,0);
        glPointSize(5);

        for(std::vector<StreamSampleLine>::iterator iter=clusterlist[1].begin();iter!=clusterlist[1].end();++iter)
        {
            glBegin(GL_POINTS);
            for(int i=0;i<(*iter).samples.size();++i)
            {
                glVertex3f((*iter).samples[i].X(),(*iter).samples[i].Y(),(*iter).samples[i].Z());

                break;
            }
            glEnd();
        }
    }
}

void DrawIllustrativeData::drawColor()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // glDisable(GL_LIGHTING);
      glEnable ( GL_LIGHTING ) ;
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
      glEnable ( GL_COLOR_MATERIAL ) ;

      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

      GLfloat lightColor[]={1,1,1,1};
      GLfloat ambientLight[]={.7,.7,.7,1};
      glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
      glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

      glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
      glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHTING);
   //   glDisable(GL_LIGHTING);
    glUseProgram(0);


    glEnable(GL_BLEND);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
    glDisable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   // glBlendFunc (GL_ONE, GL_ONE);
   // glColor4ub(255,0,0,20);
    //glEnable(GL_POLYGON_STIPPLE);
    glColor3ub(255,255,255);

    //if(false)
    for(int e=0;e<tapes.size();++e)
    {


        GLfloat emi[4]={1,1,1,1};
      /*  emi[0]=colorSet[e%colorsetnum*3+0]/255.0f;
                emi[1]=colorSet[e%colorsetnum*3+1]/255.0f;
                        emi[2]=colorSet[e%colorsetnum*3+2]/255.0f;
                        emi[3]=1.0f;
        */

      //  if(e==3)
        glColor4ub(ClusterColorScheme::getSingleton()[e].r,ClusterColorScheme::getSingleton()[e].g,ClusterColorScheme::getSingleton()[e].b,60);
    //    glColor3ub(0,0,0);
//else
  //          glColor3ub(255,255,255);
        glLightfv(GL_LIGHT0, GL_EMISSION, emi);
        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<tapes[e].size();++i)
        {
        //    qDebug("tape xyz:%f,%f,%f",tapes[e][i].X(),tapes[e][i].Y(),tapes[e][i].Z());
            float curvature=1.0*(1.0-tapeCurvatures[e][i*0.5]);
            if(curvature>1.0)
                curvature=1.0;
/*
            if(curvature>0.4)
                curvature=1.0;
            else
            {
                curvature=curvature/0.4f;
            }
*/


  //          int colorid=((int)(ClusterColorScheme::getSingleton().getClusterColorSize()*curvature))%ClusterColorScheme::getSingleton().getClusterColorSize();
//  glColor4ub(ClusterColorScheme::getSingleton()[colorid].r,ClusterColorScheme::getSingleton()[colorid].g,ClusterColorScheme::getSingleton()[colorid].b,60);
//glColor3ub(255,255.0*curvature,255.0*curvature);

            glNormal3f(tapeNormals[e][i].X(),tapeNormals[e][i].Y(),tapeNormals[e][i].Z());
            glVertex3f(tapes[e][i].X(),tapes[e][i].Y(),tapes[e][i].Z());
        }

        glEnd();

        glBegin(GL_TRIANGLES);
        if(tapes[e].size()>4)
        {
            GGL::Point3f last6=tapes[e][tapes[e].size()-2];
            GGL::Point3f last6norm=tapeNormals[e][tapes[e].size()-2];

            GGL::Point3f last5=tapes[e][tapes[e].size()-1];
            GGL::Point3f last5norm=tapeNormals[e][tapes[e].size()-1];

            GGL::Point3f up=(last6-last5).Normalize()*2.5+last6;
            GGL::Point3f upnorm=(last6norm+last5norm)*0.5;

            upnorm.Normalize();

            GGL::Point3f down=(last5-last6).Normalize()*2.5+last5;
            GGL::Point3f downnorm=upnorm;

            GGL::Point3f front=((last6-tapes[e][tapes[e].size()-4]).Normalize()+(last5-tapes[e][tapes[e].size()-3]).Normalize())*2.5f;
            front=(last6+last5)*0.5+front;

            GGL::Point3f frontnorm=upnorm;


            glNormal3f(upnorm.X(),upnorm.Y(),upnorm.Z());
            glVertex3f(up.X(),up.Y(),up.Z());
            glNormal3f(downnorm.X(),downnorm.Y(),downnorm.Z());
            glVertex3f(down.X(),down.Y(),down.Z());
            glNormal3f(frontnorm.X(),frontnorm.Y(),frontnorm.Z());
            glVertex3f(front.X(),front.Y(),front.Z());
        }
        glEnd();

    }

    glDisable(GL_LIGHTING);
      glDisable ( GL_COLOR_MATERIAL ) ;

    glColor3ub(50,50,50);
    glDisable(GL_BLEND);

    glLineWidth(2.0);

    glBegin(GL_LINES);

    glVertex3f(0,0,0);
    glVertex3f(VectorField::getSingleton().xSize,0,0);


    glVertex3f(VectorField::getSingleton().xSize,0,0);
    glVertex3f(VectorField::getSingleton().xSize,VectorField::getSingleton().ySize,0);



    glVertex3f(VectorField::getSingleton().xSize,VectorField::getSingleton().ySize,0);
    glVertex3f(0,VectorField::getSingleton().ySize,0);


    glVertex3f(0,VectorField::getSingleton().ySize,0);
    glVertex3f(0,0,0);


    glVertex3f(0,0,VectorField::getSingleton().zSize);
    glVertex3f(VectorField::getSingleton().xSize,0,VectorField::getSingleton().zSize);

    //qDebug("xsize %d\n",VectorField::getSingleton().xSize);
    glVertex3f(VectorField::getSingleton().xSize,0,VectorField::getSingleton().zSize);
    glVertex3f(VectorField::getSingleton().xSize,VectorField::getSingleton().ySize,VectorField::getSingleton().zSize);



    glVertex3f(VectorField::getSingleton().xSize,VectorField::getSingleton().ySize,VectorField::getSingleton().zSize);
    glVertex3f(0,VectorField::getSingleton().ySize,VectorField::getSingleton().zSize);


    glVertex3f(0,VectorField::getSingleton().ySize,VectorField::getSingleton().zSize);
    glVertex3f(0,0,VectorField::getSingleton().zSize);

    glVertex3f(0,0,0);

    glVertex3f(0,0,VectorField::getSingleton().zSize);
    glVertex3f(VectorField::getSingleton().xSize,0,0);

    glVertex3f(VectorField::getSingleton().xSize,0,VectorField::getSingleton().zSize);
    glVertex3f(VectorField::getSingleton().xSize,VectorField::getSingleton().ySize,0);

    glVertex3f(VectorField::getSingleton().xSize,VectorField::getSingleton().ySize,VectorField::getSingleton().zSize);
    glVertex3f(0,VectorField::getSingleton().ySize,0);

    glVertex3f(0,VectorField::getSingleton().ySize,VectorField::getSingleton().zSize);
    glEnd();
}

void DrawIllustrativeData::drawFinal()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glClearColor(1,1,1,1);
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    finalShaderProgram->bind();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,/*antiAliasingMapID*/ /*shadowImg*/ /*shadowMapID*/ /*img*/ antiAliasingMapID);
    finalShaderProgram->setUniformValue(finalmapUniform,0);
    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);

    glTexCoord2f(1, 0);
    glVertex2f(1, -1);

    glTexCoord2f(1, 1);
    glVertex2f(1, 1);

    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);


    glEnd();

    glUseProgram(0);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

  //  drawColor();

}

void DrawIllustrativeData::generateShadowMap(const GGL::Point3f &light)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboshadowmap);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(light.X(),light.Y(),light.Z(),31.5,31.5,31.5,0,0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0, 1.0,0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX,tmodelview);
    qDebug("{%f,%f,%f,%f},\n{%f,%f,%f,%f},\n{%f,%f,%f,%f},\n{%f,%f,%f,%f}\n",tmodelview[0],tmodelview[4],tmodelview[8],tmodelview[12]
                                                                                                                                                ,tmodelview[1],tmodelview[5],tmodelview[9],tmodelview[13]
                                                                                                                                                ,tmodelview[2],tmodelview[6],tmodelview[10],tmodelview[14]
                                                                                                                                                ,tmodelview[3],tmodelview[7],tmodelview[11],tmodelview[15]);

    glMatrixMode(GL_PROJECTION);
    glGetFloatv(GL_PROJECTION_MATRIX,tprojection);
    qDebug("{%f,%f,%f,%f},\n{%f,%f,%f,%f},\n{%f,%f,%f,%f},\n{%f,%f,%f,%f}\n",tprojection[0],tprojection[4],tprojection[8],tprojection[12]
                                                                                                                                                ,tprojection[1],tprojection[5],tprojection[9],tprojection[13]
                                                                                                                                                ,tprojection[2],tprojection[6],tprojection[10],tprojection[14]
                                                                                                                                                ,tprojection[3],tprojection[7],tprojection[11],tprojection[15]);



        mt[0][0]=tmodelview[0];
        mt[1][0]=tmodelview[1];
        mt[2][0]=tmodelview[2];
        mt[3][0]=tmodelview[3];

        mt[0][1]=tmodelview[4];
        mt[1][1]=tmodelview[5];
        mt[2][1]=tmodelview[6];
        mt[3][1]=tmodelview[7];

        mt[0][2]=tmodelview[8];
        mt[1][2]=tmodelview[9];
        mt[2][2]=tmodelview[10];
        mt[3][2]=tmodelview[11];

        mt[0][3]=tmodelview[12];
        mt[1][3]=tmodelview[13];
        mt[2][3]=tmodelview[14];
        mt[3][3]=tmodelview[15];


        pt[0][0]=tprojection[0];
        pt[1][0]=tprojection[1];
        pt[2][0]=tprojection[2];
        pt[3][0]=tprojection[3];

        pt[0][1]=tprojection[4];
        pt[1][1]=tprojection[5];
        pt[2][1]=tprojection[6];
        pt[3][1]=tprojection[7];

        pt[0][2]=tprojection[8];
        pt[1][2]=tprojection[9];
        pt[2][2]=tprojection[10];
        pt[3][2]=tprojection[11];

        pt[0][3]=tprojection[12];
        pt[1][3]=tprojection[13];
        pt[2][3]=tprojection[14];
        pt[3][3]=tprojection[15];

        GGL::Point4f testpoint(31.5,31.5,31.5,0);

        GGL::Point4f resultingTestPoint=pt*(mt*testpoint);

        qDebug("result: %f,%f,%f",resultingTestPoint.X(),resultingTestPoint.Y(),resultingTestPoint.Z());



     shadowMapProgram->bind();

     shadowMapProgram->setUniformValue(lightUniform,light.X(),light.Y(),light.Z());



    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

     glClearColor(0,0,0,0);
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


     for(int e=0;e<tapes.size();++e)
     {
         glBegin(GL_TRIANGLE_STRIP);

         for(int i=0;i<tapes[e].size();++i)
         {

             glNormal3f(tapeNormals[e][i].X(),tapeNormals[e][i].Y(),tapeNormals[e][i].Z());
             glVertex3f(tapes[e][i].X(),tapes[e][i].Y(),tapes[e][i].Z());


         }

         glEnd();

       /*  glBegin(GL_TRIANGLES);
         if(tapes[e].size()>4)
         {
             GGL::Point3f last6=tapes[e][tapes[e].size()-2];

             GGL::Point3f last5=tapes[e][tapes[e].size()-1];

             GGL::Point3f up=(last6-last5).Normalize()*2.5+last6;

             GGL::Point3f down=(last5-last6).Normalize()*2.5+last5;

             GGL::Point3f front=((last6-tapes[e][tapes[e].size()-4]).Normalize()+(last5-tapes[e][tapes[e].size()-3]).Normalize())*2.5f;
             front=(last6+last5)*0.5+front;

             GGL::Point3f norm=(up-front)^(down-front);
             norm.Normalize();

             glNormal3f(norm.X(),norm.Y(),norm.Z());
             glVertex3f(up.X(),up.Y(),up.Z());
             glVertex3f(down.X(),down.Y(),down.Z());
             glVertex3f(front.X(),front.Y(),front.Z());
         }
         glEnd();*/

     }





     glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glUseProgram(0);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void DrawIllustrativeData::drawDotShadow(const GGL::Point3f &eye)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboshadow);

    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    illustrativeShadowShaderProgram->bind();

    illustrativeShadowShaderProgram-> setUniformValue (dotEyePositionUniform, eye.X(),eye.Y(),eye.Z());

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,shadowMapID);
    illustrativeShadowShaderProgram->setUniformValue(shadowmapUniform,0);

    illustrativeShadowShaderProgram->setUniformValue(lightpositionUniform,65.0f,65.0f,65.0f);
QMatrix4x4 mtq;
mtq(0,0)=mt[0][0];
mtq(0,1)=mt[0][1];
mtq(0,2)=mt[0][2];
mtq(0,3)= mt[0][3];

mtq(1,0)=mt[1][0];
mtq(1,1)=mt[1][1];
mtq(1,2)=mt[1][2];
mtq(1,3)=mt[1][3];

mtq(2,0)=mt[2][0];
mtq(2,1)=mt[2][1];
mtq(2,2)=mt[2][2];
mtq(2,3)=mt[2][3];

mtq(3,0)=mt[3][0];
mtq(3,1)=mt[3][1];
mtq(3,2)=mt[3][2];
mtq(3,3)=mt[3][3];

    illustrativeShadowShaderProgram->setUniformValue(modelviewUniform,mtq);


    QMatrix4x4 ptq;
    ptq(0,0)=pt[0][0];
    ptq(0,1)=pt[0][1];
    ptq(0,2)=pt[0][2];
    ptq(0,3)=pt[0][3];

    ptq(1,0)=pt[1][0];
    ptq(1,1)=pt[1][1];
    ptq(1,2)=pt[1][2];
    ptq(1,3)=pt[1][3];

    ptq(2,0)=pt[2][0];
    ptq(2,1)=pt[2][1];
    ptq(2,2)=pt[2][2];
    ptq(2,3)=pt[2][3];

    ptq(3,0)=pt[3][0];
    ptq(3,1)=pt[3][1];
    ptq(3,2)=pt[3][2];
    ptq(3,3)=pt[3][3];

    illustrativeShadowShaderProgram->setUniformValue(projectionUniform,ptq);



  //  if(false)
    for(int e=0;e<tapes.size();++e)
    {
        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<tapes[e].size();++i)
        {

            glNormal3f(tapeNormals[e][i].X(),tapeNormals[e][i].Y(),tapeNormals[e][i].Z());
            glVertex3f(tapes[e][i].X(),tapes[e][i].Y(),tapes[e][i].Z());


        }

        glEnd();

        glBegin(GL_TRIANGLES);
        if(tapes[e].size()>4)
        {
            GGL::Point3f last6=tapes[e][tapes[e].size()-2];
          //  GGL::Point3f last6norm=tapeNormals[e][tapes[e].size()-2];

            GGL::Point3f last5=tapes[e][tapes[e].size()-1];
            //GGL::Point3f last5norm=tapeNormals[e][tapes[e].size()-1];

            GGL::Point3f up=(last6-last5).Normalize()*2.5+last6;
            //GGL::Point3f upnorm=(last6norm+last5norm)*0.5;

            GGL::Point3f down=(last5-last6).Normalize()*2.5+last5;
            //GGL::Point3f downnorm=upnorm;

            GGL::Point3f front=((last6-tapes[e][tapes[e].size()-4]).Normalize()+(last5-tapes[e][tapes[e].size()-3]).Normalize())*2.5f;
            front=(last6+last5)*0.5+front;

            //GGL::Point3f frontnorm=upnorm;


            GGL::Point3f norm=(up-front)^(down-front);
            norm.Normalize();

            glNormal3f(norm.X(),norm.Y(),norm.Z());
            glVertex3f(up.X(),up.Y(),up.Z());
           // glNormal3f(downnorm.X(),downnorm.Y(),downnorm.Z());
            glVertex3f(down.X(),down.Y(),down.Z());
            //glNormal3f(frontnorm.X(),frontnorm.Y(),frontnorm.Z());
            glVertex3f(front.X(),front.Y(),front.Z());
        }
        glEnd();

    }


//fboAntiAliasing

     glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboAntiAliasing);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    dotShaderProgram->bind();

    dotShaderProgram->setUniformValue(dotOriginalUniform,0);

    dotShaderProgram->setUniformValue(dotmapUniform,1);

   // qDebug("threshold : %f",_threshold);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,shadowImg);

    glEnable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_3D,dotMapID);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glColor3ub(255, 255, 255);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);

    glTexCoord2f(1, 0);
    glVertex2f(1, -1);

    glTexCoord2f(1, 1);
    glVertex2f(1, 1);

    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);


    glEnd();





    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();







  glUseProgram(0);








}

void DrawIllustrativeData::resize(int width,int height)
{

    float scale=2.0f;

	illustrativeAntiAliasingShaderProgram->bind();
	
	illustrativeAntiAliasingShaderProgram->setUniformValue(mapUniform,0);
        illustrativeAntiAliasingShaderProgram->setUniformValue(widthUniform,(float)screenWidth*scale);
        illustrativeAntiAliasingShaderProgram->setUniformValue(heightUniform,(float)screenHeight*scale);

        dotShaderProgram->bind();
        dotShaderProgram->setUniformValue(dotWidthUniform,(float)screenWidth*scale);
        dotShaderProgram->setUniformValue(dotHeightUniform,(float)screenHeight*scale);

	glUseProgram(0);

        screenWidth=width;
        screenHeight=height;

        if(fbo)
            glDeleteFramebuffers(1,&fbo);
        if(depthbuffer)
            glDeleteRenderbuffers(1,&depthbuffer);

        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glGenRenderbuffers(1, &depthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth*scale,screenHeight*scale);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);

        if(img)
            glDeleteTextures(1,&img);

        glGenTextures(1, &img);
        glBindTexture(GL_TEXTURE_2D, img);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB,  screenWidth*scale,screenHeight*scale, 0, GL_RGBA, GL_FLOAT, NULL);


        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, img, 0);


        GLenum kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");


        if(fboshadow)
            glDeleteFramebuffers(1,&fboshadow);
        if(shadowDepthbuffer)
            glDeleteRenderbuffers(1,&shadowDepthbuffer);


        glGenFramebuffers(1, &fboshadow);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fboshadow);

        glGenRenderbuffers(1,&shadowDepthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER,shadowDepthbuffer);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth*scale,screenHeight*scale);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,shadowDepthbuffer);

        if(shadowImg)
            glDeleteTextures(1,&shadowImg);

        glGenTextures(1,&shadowImg);
               glBindTexture(GL_TEXTURE_2D,shadowImg);
        glTexImage2D(GL_TEXTURE_2D,0,GL_INTENSITY/* GL_RGBA*/,screenWidth*scale,screenHeight*scale,0,GL_LUMINANCE /*GL_RGBA*/,GL_FLOAT,NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowImg, 0);


        kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");



        if(fboAntiAliasing)
            glDeleteFramebuffers(1,&fboAntiAliasing);
        if(antiAliasingDepthbuffer)
            glDeleteRenderbuffers(1,&antiAliasingDepthbuffer);


        glGenFramebuffers(1, &fboAntiAliasing);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fboAntiAliasing);

        glGenRenderbuffers(1,&antiAliasingDepthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER,antiAliasingDepthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth*scale,screenHeight*scale);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,antiAliasingDepthbuffer);
        if(antiAliasingMapID)
            glDeleteTextures(1,&antiAliasingMapID);

        glGenTextures(1,&antiAliasingMapID);
        glBindTexture(GL_TEXTURE_2D,antiAliasingMapID);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,screenWidth*scale,screenHeight*scale,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, antiAliasingMapID, 0);

        kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");




        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

}

void DrawIllustrativeData::generateATape(const GGL::Point3f &p1,const GGL::Point3f &p2)
{
    GGL::Point3f pp1=p1;
    GGL::Point3f pp2=p2;

    std::vector<GGL::Point3f> atape;
    std::vector<GGL::Point3f> tnormals;


    for(int i=0;i<100;++i)
    {

        atape.push_back(pp1);
                pp2=pp1;
                pp2.Z()+=5;
        atape.push_back(pp2);

        tnormals.push_back(GGL::Point3f(0,0,0));
        tnormals.push_back(GGL::Point3f(0,0,0));

        pp1=movePoint(pp1.X(),pp1.Y(),pp1.Z());
        pp2=movePoint(pp2.X(),pp2.Y(),pp2.Z());
    }

    tapes.push_back(atape);


    for(int i=0;i+2<atape.size();++i)
    {
        int a=i;
        int b=i+1;
        int c=i+2;

        GGL::Point3f e1=atape[b]-atape[a];
        GGL::Point3f e2=atape[c]-atape[a];

        GGL::Point3f nor=e1^e2;

        nor.Normalize();

        tnormals[a]=tnormals[a]+nor;


        GGL::Point3f e3=atape[c]-atape[b];
        GGL::Point3f e4=atape[a]-atape[b];

        nor=e3^e4;
        nor.Normalize();

        tnormals[b]=tnormals[b]+nor;

        GGL::Point3f e5=atape[a]-atape[c];
        GGL::Point3f e6=atape[b]-atape[c];

        nor=e5^e6;
        nor.Normalize();


        tnormals[c]=tnormals[c]+nor;

    }

    for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
        iter->Normalize();

    tapeNormals.push_back(tnormals);
}

DrawIllustrativeData::~DrawIllustrativeData()
{
    if(illustrativeShaderProgram)
    {
        illustrativeShaderProgram->release();
        delete illustrativeShaderProgram;
        delete vshader;
        delete fshader;
//	delete fbo;
    }

    if(illustrativeAntiAliasingShaderProgram)
    {
        illustrativeAntiAliasingShaderProgram->release();
        delete illustrativeAntiAliasingShaderProgram;
        delete vashader;
        delete fashader;
    }

    if (illustrativeShadowShaderProgram)
    {
        illustrativeShadowShaderProgram->release();
        delete illustrativeShadowShaderProgram;
        delete vsshader;
        delete fsshader;
    }

}

void DrawIllustrativeData::init()
{
    screenWidth=1024;
    screenHeight=1024;
    vshader=new QGLShader(QGLShader::Vertex);
    vshader->compileSourceFile("IllustrativeShader.vsh");

    fshader=new QGLShader(QGLShader::Fragment);
    fshader->compileSourceFile("IllustrativeShader.fsh");

    illustrativeShaderProgram=new QGLShaderProgram();
    illustrativeShaderProgram->addShader(vshader);
    illustrativeShaderProgram->addShader(fshader);

    illustrativeShaderProgram->link();

    eyePositionUniform=illustrativeShaderProgram->uniformLocation("eyePos");

    qDebug("Output of Compiling IllustrativeShader");
    qDebug("%s",illustrativeShaderProgram->log().toStdString().c_str());
    qDebug("finsih illustrativeshader");

    vfinalshader=new QGLShader(QGLShader::Vertex);
    vfinalshader->compileSourceFile("FinalShader.vsh");

    ffinalshader=new QGLShader(QGLShader::Fragment);
    ffinalshader->compileSourceFile("FinalShader.fsh");


    finalShaderProgram=new QGLShaderProgram();
    finalShaderProgram->addShader(vfinalshader);
    finalShaderProgram->addShader(ffinalshader);

    finalShaderProgram->link();

    finalmapUniform=finalShaderProgram->uniformLocation("finalmap");

    qDebug("Output of Compiling FinalShader");
        qDebug("%s",finalShaderProgram->log().toStdString().c_str());
qDebug("Finish outputing FinalShader");


        vshadowmapshader=new QGLShader(QGLShader::Vertex);
        vshadowmapshader->compileSourceFile("ShadowMapShader.vsh");

        fshadowmapshader=new QGLShader(QGLShader::Fragment);
        fshadowmapshader->compileSourceFile("ShadowMapShader.fsh");

        shadowMapProgram=new QGLShaderProgram();
        shadowMapProgram->addShader(vshadowmapshader);
        shadowMapProgram->addShader(fshadowmapshader);


        shadowMapProgram->link();

        lightUniform=shadowMapProgram->uniformLocation("light");
        qDebug("Output of Compiling ShadowMapShader");
        qDebug("%s",shadowMapProgram->log().toStdString().c_str());
        qDebug("Finishing output ShadowMapShader");
	
	vashader=new QGLShader(QGLShader::Vertex);
	vashader->compileSourceFile("IllustrativeAntiAliasing.vsh");
	
	fashader=new QGLShader(QGLShader::Fragment);
	fashader->compileSourceFile("IllustrativeAntiAliasing.fsh");
	
	illustrativeAntiAliasingShaderProgram=new QGLShaderProgram();
	illustrativeAntiAliasingShaderProgram->addShader(vashader);
	illustrativeAntiAliasingShaderProgram->addShader(fashader);
	
	illustrativeAntiAliasingShaderProgram->link();
	
        mapUniform=illustrativeAntiAliasingShaderProgram->uniformLocation("map");
	widthUniform=illustrativeAntiAliasingShaderProgram->uniformLocation("width");
	heightUniform=illustrativeAntiAliasingShaderProgram->uniformLocation("height");
        thresholdUniform=illustrativeAntiAliasingShaderProgram->uniformLocation("threshold");
	
        qDebug("Output of Compiling IllustrativeAntiAliasing");
	qDebug("%s",illustrativeAntiAliasingShaderProgram->log().toStdString().c_str());
        qDebug("Finish outputing illustrativeAntiAliasing");
	
        vsshader=new QGLShader(QGLShader::Vertex);
        vsshader->compileSourceFile("IllustrativeShadow.vsh");

        fsshader=new QGLShader(QGLShader::Fragment);
        fsshader->compileSourceFile("IllustrativeShadow.fsh");

        illustrativeShadowShaderProgram=new QGLShaderProgram();
        illustrativeShadowShaderProgram->addShader(vsshader);
        illustrativeShadowShaderProgram->addShader(fsshader);

        illustrativeShadowShaderProgram->link();

        dotEyePositionUniform=illustrativeShadowShaderProgram->uniformLocation("eyePos");

        projectionUniform=illustrativeShadowShaderProgram->uniformLocation("modelview");
        modelviewUniform=illustrativeShadowShaderProgram->uniformLocation("projection");
        shadowmapUniform=illustrativeShadowShaderProgram->uniformLocation("shadowmap");
        lightpositionUniform=illustrativeShadowShaderProgram->uniformLocation("lightposition");

        qDebug("Output of Compiling IllustrativeShadow");
        qDebug("%s",illustrativeShadowShaderProgram->log().toStdString().c_str());
        qDebug("Finish outputing IllustrativeShadow");


       vdotshader=new QGLShader(QGLShader::Vertex);
       vdotshader->compileSourceFile("DotShader.vsh");
       fdotshader=new QGLShader(QGLShader::Fragment);
       fdotshader->compileSourceFile("DotShader.fsh");

       dotShaderProgram=new QGLShaderProgram();
       dotShaderProgram->addShader(vdotshader);
       dotShaderProgram->addShader(fdotshader);

       dotShaderProgram->link();
       dotOriginalUniform=dotShaderProgram->uniformLocation("map");
        dotWidthUniform=dotShaderProgram->uniformLocation("width");
        dotHeightUniform=dotShaderProgram->uniformLocation("height");
        dotmapUniform=dotShaderProgram->uniformLocation("dotmap");


        qDebug("Output of Compiling DotShader");
        qDebug("%s",dotShaderProgram->log().toStdString().c_str());
        qDebug("Finishing DotShader");
//	fbo=new QGLFramebufferObject(1024,1024,QGLFramebufferObject::Depth);

        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
        glGenRenderbuffers(1, &depthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth,screenHeight);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);

        glGenTextures(1, &img);
        glBindTexture(GL_TEXTURE_2D, img);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB,  screenWidth,screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);


        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, img, 0);


        GLenum kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");


        glGenFramebuffers(1, &fboshadow);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fboshadow);

        glGenRenderbuffers(1,&shadowDepthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER,shadowDepthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth,screenHeight);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,shadowDepthbuffer);

        glGenTextures(1,&shadowImg);
        glBindTexture(GL_TEXTURE_2D,shadowImg);
        glTexImage2D(GL_TEXTURE_2D,0,GL_INTENSITY,screenWidth,screenHeight,0,GL_LUMINANCE,GL_FLOAT,NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowImg, 0); 

        kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");




        glGenFramebuffers(1, &fboAntiAliasing);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fboAntiAliasing);

        glGenRenderbuffers(1,&antiAliasingDepthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER,antiAliasingDepthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenWidth,screenHeight);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,antiAliasingDepthbuffer);

        glGenTextures(1,&antiAliasingMapID);
        glBindTexture(GL_TEXTURE_2D,antiAliasingMapID);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,screenWidth,screenHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, antiAliasingMapID, 0);

        kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");

        glGenFramebuffers(1, &fboshadowmap);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fboshadowmap);

        glGenRenderbuffers(1,&shadowMapDepthbuffer);

        glBindRenderbuffer(GL_RENDERBUFFER,shadowMapDepthbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024,1024);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,shadowMapDepthbuffer);

        glGenTextures(1,&shadowMapID);
        glBindTexture(GL_TEXTURE_2D,shadowMapID);
        glTexImage2D(GL_TEXTURE_2D,0,GL_INTENSITY,1024,1024,0,GL_LUMINANCE,GL_FLOAT,NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMapID, 0);

        kkkk = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

        if(kkkk!=GL_FRAMEBUFFER_COMPLETE)
            qDebug("framebufferobject is not complete!");


        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);

        generateMaps();

     //  generateMapsWithRandomDots();






       // qDebug("externsions: %s",glGetString(GL_EXTENSIONS));
}

void DrawIllustrativeData::generateMapsWithRandomDots()
{

    QImage i(32,32,QImage::Format_Mono);
    QPainter painter(&i);

    dotMap=new GLfloat[32*32*32];

    for(int e=0;e<32;++e)
    {

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::white);


        painter.drawRect(0,0,32,32);

        painter.setBrush(Qt::black);
        painter.setPen(Qt::black);

       int pointCount=((int)((float)(31-e)/4.0))*200.0;

       for(int i=0;i<pointCount;++i)
           painter.drawPoint(rand()%32,rand()%32);



        i.save(QString("dotmap%1.png").arg(e));


        for(int y=0;y<32;++y)
            for(int x=0;x<32;++x)
            {

            if(i.pixel(x,y)==-1)
            {
                 //qDebug("pixel: %d",1);
                dotMap[(31-e)*32*32+y*32+x]=1.0f;
            }
            else
            {
                //qDebug("pixel: %d",0);
                dotMap[(31-e)*32*32+y*32+x]=0.0f;
            }
                }


    }


    glEnable(GL_TEXTURE_3D);
    glGenTextures(1, &dotMapID);
    glBindTexture(GL_TEXTURE_3D, dotMapID);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY,  32,32,32, 0, GL_LUMINANCE, GL_FLOAT, dotMap);


    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R,GL_REPEAT);

}

void DrawIllustrativeData::generateMaps()
{
    QImage i(32,32,QImage::Format_Mono);
    QPainter painter(&i);
    float r=4*1.41421356254;

    dotMap=new GLfloat[32*32*32];

    for(int e=0;e<32;++e)
    {

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::white);

  //      painter.setBrush(QColor::fromRgb(e/31.0*255,e/31.0*255,e/31.0*255,e/31.0*255));

        painter.drawRect(0,0,32,32);

        painter.setBrush(Qt::black);

        float cr=r*(31.0f-e)/31.0f;

        for(int x=0;x<4;++x)
        for(int y=0;y<4;++y)
        painter.drawEllipse(8.0*x,8.0*y,cr,cr);



        i.save(QString("dotmap%1.png").arg(e));

        for(int y=0;y<32;++y)
            for(int x=0;x<32;++x)
            {

            if(i.pixel(x,y)==-1)
            {
                 //qDebug("pixel: %d",1);
                dotMap[(31-e)*32*32+y*32+x]=1.0f;
            }
            else
            {
                //qDebug("pixel: %d",0);
                dotMap[(31-e)*32*32+y*32+x]=0.0f;
            }
                }


    }


    glEnable(GL_TEXTURE_3D);
    glGenTextures(1, &dotMapID);
    glBindTexture(GL_TEXTURE_3D, dotMapID);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY,  32,32,32, 0, GL_LUMINANCE, GL_FLOAT, dotMap);


    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R,GL_REPEAT);

}


void DrawIllustrativeData::getBestLineMatch(std::vector<GGL::Point3f> pointList,float &b1,float &b2,float &b3,GGL::Point3f &centerOfGravity)
{
    double matrix[3][3]={0};

    double vector[3]={0};

 //   GGL::Point3f centerOfGravity(0,0,0);

    for(int i=0;i<pointList.size();++i)
    {
  //      pointList[i].Z()=0;
        centerOfGravity+=pointList[i];
    }

    centerOfGravity/=(float)pointList.size();

    for(int i=0;i<pointList.size();++i)
        pointList[i]-=centerOfGravity;

    qDebug("center of gravity: %f,%f,%f\n",centerOfGravity.X(),centerOfGravity.Y(),centerOfGravity.Z());


    for(int i=0;i<pointList.size();++i)
    {

    //    qDebug("(%f,%f,%f)\n",pointList[i].X(),pointList[i].Y(),pointList[i].Z());

        matrix[0][0]+=pointList[i].X()*pointList[i].X();
        matrix[0][1]+=pointList[i].X()*pointList[i].Y();
        matrix[0][2]+=pointList[i].X()*pointList[i].Z();

        matrix[1][1]+=pointList[i].Y()*pointList[i].Y();
        matrix[1][2]+=pointList[i].Y()*pointList[i].Z();

        matrix[3][3]+=pointList[i].Z()*pointList[i].Z();
    }

    matrix[1][0]=matrix[0][1];
    matrix[2][0]=matrix[0][2];
    matrix[2][1]=matrix[1][2];

    double eigen[3][3]={0};
    double v[3]={0};

    eigen_decomposition(matrix,eigen,v);



/*
    for (int i = 0; i < 3; ++i)
                     {
                             double temp = eigen[i][0];
                             eigen[i][0] = eigen[i][2];
                             eigen[i][2] = temp;
                     }

*/

    double closeToZero=abs(v[0]);
    int closeToZeroID=0;
    for(int i=1;i<3;++i)
    {
        if(closeToZero>abs(v[i]))
        {
            closeToZero=v[i];
            closeToZeroID=i;
        }

        qDebug("v%d: %f (%f,%f,%f)\n",i,v[i],eigen[0][i],eigen[1][i],eigen[2][i]);

    }

    b1=eigen[0][closeToZeroID];
    b2=eigen[1][closeToZeroID];
    b3=eigen[2][closeToZeroID];

}

 void DrawIllustrativeData::loadResultFromFile(const QString &filename)
 {


     QFile data(filename);
     if (data.open(QFile::ReadOnly))
     {
         QTextStream in(&data);

         int clusterCount=0;
         in >> clusterCount;


         while(clusterCount--)
         {
             std::vector<StreamSampleLine> aCluster;

             int streamlineCount=0;

             in >> streamlineCount;

             for(int i=0;i<streamlineCount;++i)
             {

                StreamSampleLine n;

                int pointCount=0;

                in >> pointCount;

               // qDebug("pointcount %d\n",pointCount);

                while(pointCount--)
                {
                    float x=0;
                    float y=0;
                    float z=0;

                    in >> x;
                    in >> y;
                    in >> z;

                    // x=0;


                    n.samples.push_back(GGL::Point3f(x,y,z));
                }

                aCluster.push_back(n);
             }



             clusterlist.push_back(aCluster);

             int mr=0;
             in >> mr;

             int mk=0;
             in>>mk;

         //    mostRepresentative.push_back(0);
             largestEntropy.push_back(mk);
             smallestEntropy.push_back(mr);

             float k;
             in >> k;

             printf("variation %f\n",k);
         }
     }

     printf("f");

  /*   for(int e=0;e<clusterlist.size();++e)

     computeSections(clusterlist[e]);
*/
  //   computeAverageTape();

     computeAverateTapeFromAverageStartPoint(GGL::Point3f(30,30,10));

     ClusterColorScheme::getSingleton().resize(clusterlist.size());
 }

 void DrawIllustrativeData::computeAverateTapeFromAverageStartPoint(const GGL::Point3f &start)
 {



 //generateATapeFromAStartPoint(GGL::Point3f(39  ,39,10));

 //     generateATapeFromAStartPoint(GGL::Point3f(42  ,42,10));

   //  return;

     for(int i=0;i<clusterlist.size();++i)
     {
         GGL::Point3f avg(0,0,0);

      /*   GGL::Box3f largestBox;

         int largestID=0;

         for(int e=0;e<clusterlist[i].size();++e)
         {
             GGL::Box3f bbox((clusterlist[i])[e].samples[0],(clusterlist[i])[e].samples[0]);

             for(int h=0;h<(clusterlist[i])[e].samples.size();++h)
                bbox.Add((clusterlist[i])[e].samples[h]);

             if(bbox>largestBox)
             {
                largestBox=bbox;
                largestID=e;
             }
         }
*/
         avg+= (clusterlist[i])[/*largestID*/ largestEntropy[i]].samples[0];

   /*      for(int e=0;e<(clusterlist[i].size());++e)
         {
generateATapeFromRepresentativeLine(i,e);

         }
     */      //  generateATapeFromAStartPoint(avg);
           //  break;
         //generateATapeFromRepresentativeLine(i,mostRepresentative[i]);
         qDebug("Generate %d tape",i);
            //      generateATapeFromRepresentativeLineWithTorsion(i,0);
         if(isDrawLargestEntropy)
         generateATapeFromRepresentativeLineWithTorsion(i,largestEntropy[i]);

         if(isDrawSmallestEntropy)
             generateATapeFromRepresentativeLineWithTorsion(i,smallestEntropy[i]);

         if(isDrawCenter)
             generateATapeFromRepresentativeLineWithTorsion(i,0);

        // break;
     }

      //   avg/=(clusterlist[i]).size();
                 //   generateATapeFromAStartPoint(avg,_eye);



 }

 void DrawIllustrativeData::computeAverageTape()
 {
     for(int e=0;e<clusterlist.size();++e)
     {
       std::vector<GGL::Point3f> atape;
       std::vector<GGL::Point3f> tnormals;
         for(int i=0;i<49;++i)
         {

            GGL::Point3f avg(0,0,0);
            for(std::vector<StreamSampleLine>::iterator iter=clusterlist[e].begin();iter!=clusterlist[e].end();++iter)
            {

                avg+=(*iter).samples[i];



            }

            avg/=clusterlist[e].size();

            atape.push_back(avg);
            atape.push_back(avg+GGL::Point3f(10,0,0));

            tnormals.push_back(GGL::Point3f(0,0,0));
            tnormals.push_back(GGL::Point3f(0,0,0));
           }
            tapes.push_back(atape);






            for(int i=0;i+2<atape.size();++i)
            {
                int a=i;
                int b=i+1;
                int c=i+2;

                GGL::Point3f e1=atape[b]-atape[a];
                GGL::Point3f e2=atape[c]-atape[a];

                GGL::Point3f nor=e1^e2;

                nor.Normalize();

                tnormals[a]=tnormals[a]+nor;


                GGL::Point3f e3=atape[c]-atape[b];
                GGL::Point3f e4=atape[a]-atape[b];

                nor=e3^e4;
                nor.Normalize();

                tnormals[b]=tnormals[b]+nor;

                GGL::Point3f e5=atape[a]-atape[c];
                GGL::Point3f e6=atape[b]-atape[c];

                nor=e5^e6;
                nor.Normalize();


                tnormals[c]=tnormals[c]+nor;

            }

            for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
                iter->Normalize();

            tapeNormals.push_back(tnormals);
     }
 }

 void DrawIllustrativeData::computeSections(std::vector<StreamSampleLine>& input)
 {
     std::vector<GGL::Point3f> atape;
     std::vector<GGL::Point3f> tnormals;

    for(int count=0;count<49;++count)
    {
          std::vector<GGL::Point3f> samples;
        for(std::vector<StreamSampleLine>::iterator iter=input.begin();iter!=input.end();++iter)
        {
            samples.push_back((*iter).samples[count]);
        }


        GGL::Point3f center(0,0,0);
        GGL::Point3f bestSurfaceNormal;

        getBestLineMatch(samples,bestSurfaceNormal.X(),bestSurfaceNormal.Y(),bestSurfaceNormal.Z(),center);

    //    Sample n1;
      //  n1.initializeWithPos(center);

       // n1.generateJacobian();

      //  qDebug("sample %d : b1=%f,b2=%f,b3=%f\n",count,bestSurfaceNormal.X(),bestSurfaceNormal.Y(),bestSurfaceNormal.Z());

        GGL::Point3f xAxis=samples[0]-bestSurfaceNormal*(samples[0]*bestSurfaceNormal);
        GGL::Point3f yAxis=bestSurfaceNormal^xAxis;

        xAxis.Normalize();
        yAxis.Normalize();

        GGL::Point3f bestLineSeg=computekIn2D(samples,xAxis,yAxis);

        GGL::Point3f pointA=bestLineSeg*-2.0f;
        GGL::Point3f pointB=bestLineSeg*2.0f;

        qDebug("(%f,%f,%f)\n",bestLineSeg.X(),bestLineSeg.Y(),bestLineSeg.Z());
        qDebug("(%f,%f,%f)\n",center.X(),center.Y(),center.Z());

        qDebug("(%f,%f,%f),(%f,%f,%f)\n",pointA.X(),pointA.Y(),pointA.Z(),pointB.X(),pointB.Y(),pointB.Z());

        atape.push_back(pointA+center);
        atape.push_back(pointB+center);

        tnormals.push_back(GGL::Point3f(0,0,0));
        tnormals.push_back(GGL::Point3f(0,0,0));


       // break;
    }

    tapes.push_back(atape);






    for(int i=0;i+2<atape.size();++i)
    {
        int a=i;
        int b=i+1;
        int c=i+2;

        GGL::Point3f e1=atape[b]-atape[a];
        GGL::Point3f e2=atape[c]-atape[a];

        GGL::Point3f nor=e1^e2;

        nor.Normalize();

        tnormals[a]=tnormals[a]+nor;


        GGL::Point3f e3=atape[c]-atape[b];
        GGL::Point3f e4=atape[a]-atape[b];

        nor=e3^e4;
        nor.Normalize();

        tnormals[b]=tnormals[b]+nor;

        GGL::Point3f e5=atape[a]-atape[c];
        GGL::Point3f e6=atape[b]-atape[c];

        nor=e5^e6;
        nor.Normalize();


        tnormals[c]=tnormals[c]+nor;

    }

    for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
        iter->Normalize();

    tapeNormals.push_back(tnormals);


 }


 GGL::Point3f DrawIllustrativeData::computekIn2D(std::vector<GGL::Point3f> &pointSamples,GGL::Point3f &xaxis,GGL::Point3f &yaxis)
 {
     double overallxy=0;
     double overallyy=0;
     for(int i=0;i<pointSamples.size();++i)
     {
         double x=(pointSamples[i]*xaxis);
         double y=(pointSamples[i]*yaxis);

        overallxy+=x;
        overallyy+=y;
     }

     double vx=1.0;
     double vy=overallyy/overallxy;


     return (xaxis+yaxis*vy).Normalize();
 }


 void DrawIllustrativeData::testRepresentativeLine()
 {
     srand(0);
    std::vector<GGL::Point3f> pointList;

    for(int i=0;i<100;++i)
    {
        float l=(rand()%128-64)*0.5f;
        GGL::Point3f p(l,0,0);

        pointList.push_back(p);
    }

    float b1=0,b2=0,b3=0;
    GGL::Point3f center;
    getBestLineMatch(pointList,b1,b2,b3,center);

    qDebug("[%f,%f,%f]\n",b1,b2,b3);

    GGL::Point3f xAxis=pointList[0]-GGL::Point3f(b1,b2,b3)*(pointList[0]*GGL::Point3f(b1,b2,b3));
    GGL::Point3f yAxis=GGL::Point3f(b1,b2,b3)^xAxis;

    xAxis.Normalize();
    yAxis.Normalize();

    qDebug("[%f,%f,%f]\n",xAxis.X(),xAxis.Y(),xAxis.Z());
    qDebug("[%f,%f,%f]\n",yAxis.X(),yAxis.Y(),yAxis.Z());

    GGL::Point3f bestLineSeg=computekIn2D(pointList,xAxis,yAxis);

    qDebug("[%f,%f,%f]\n",bestLineSeg.X(),bestLineSeg.Y(),bestLineSeg.Z());

 }

void DrawIllustrativeData::generateATapeFromRepresentativeLine(const int clusterid,const int rlid)
{
    std::vector<GGL::Point3f> presavedPointList;




    for(int i=0;i<clusterlist[clusterid][rlid].samples.size();++i)
    {
        presavedPointList.push_back(clusterlist[clusterid][rlid].samples[i]);
    }

    std::vector<GGL::Point3f> atape;
    std::vector<GGL::Point3f> tnormals;

    std::vector<GGL::Point3f> dirs;

    for(int i=1;i<clusterlist[clusterid][rlid].samples.size()-1;++i)
    {
        GGL::Point3f currentP=presavedPointList[i];
        GGL::Point3f nxtP=presavedPointList[i+1];

        GGL::Point3f preP=presavedPointList[i-1];

        GGL::Point3f dir=(nxtP-currentP)^(preP-currentP);

        dir.Normalize();

        dirs.push_back(dir);


    }

    std::vector<GGL::Point3f> averageDir;

    averageDir.resize(dirs.size());

    for(int e=0;e<8;++e)
    {

      for(int i=0;i<dirs.size();++i)
      {
          int pre=i-1;
          int nxt=i+1;

          GGL::Point3f ad=dirs[i];

          if(pre>=0)
              ad+=dirs[pre];
          if(nxt<dirs.size())
              ad+=dirs[nxt];

          ad.Normalize();

          averageDir[i]=ad;
      }

      std::copy(averageDir.begin(),averageDir.end(),dirs.begin());

    }

    for(int i=1;i<clusterlist[clusterid][rlid].samples.size()-1;++i)
    {
        GGL::Point3f currentP=presavedPointList[i];

        GGL::Point3f dir=averageDir[i-1];

        atape.push_back(currentP+dir*2.5f);//*(i+10)/(float)clusterlist[clusterid][rlid].samples.size());
        atape.push_back(currentP-dir*2.5f);//*(i+10)/(float)clusterlist[clusterid][rlid].samples.size());

        tnormals.push_back(GGL::Point3f(0,0,0));
        tnormals.push_back(GGL::Point3f(0,0,0));


    }


    tapes.push_back(atape);


    for(int i=0;i+2<atape.size();++i)
    {
        int a=i;
        int b=i+1;
        int c=i+2;

        GGL::Point3f e1=atape[b]-atape[a];
        GGL::Point3f e2=atape[c]-atape[a];

        GGL::Point3f nor=e1^e2;

        nor.Normalize();

        tnormals[a]=tnormals[a]+nor;


        GGL::Point3f e3=atape[c]-atape[b];
        GGL::Point3f e4=atape[a]-atape[b];

        nor=e3^e4;
        nor.Normalize();

        tnormals[b]=tnormals[b]+nor;

        GGL::Point3f e5=atape[a]-atape[c];
        GGL::Point3f e6=atape[b]-atape[c];

        nor=e5^e6;
        nor.Normalize();


        tnormals[c]=tnormals[c]+nor;

    }

    for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
        iter->Normalize();

    tapeNormals.push_back(tnormals);
}


void DrawIllustrativeData::generateATapeFromAStartPoint(const GGL::Point3f &startPoint)
  {
      std::vector<GGL::Point3f> presavedPointList;

      GGL::Point3f currentPoint=startPoint;

      presavedPointList.push_back(currentPoint);

      for(int i=0;i<150;++i)
      {
          currentPoint=movePoint(currentPoint.X(),currentPoint.Y(),currentPoint.Z());
          presavedPointList.push_back(currentPoint);
      }

      std::vector<GGL::Point3f> atape;
      std::vector<GGL::Point3f> tnormals;

      std::vector<GGL::Point3f> dirs;
      std::vector<float> torsions;

      std::vector<float> curvatures;

      float largestTorsion=0;
      float largestCurvature=0;

      //for(int i=1;i<clusterlist[clusterid][rlid].samples.size()-1;++i)
      for(int i=1;i<149;++i)
      {
          GGL::Point3f currentP=presavedPointList[i];
          GGL::Point3f nxtP=presavedPointList[i+1];

          GGL::Point3f preP=presavedPointList[i-1];

         // GGL::Point3f dir=(nxtP-currentP)^(preP-currentP);

          GGL::Point3f dir=computeBiNormalDirection(currentP);

          //dir.Normalize();

          dirs.push_back(dir);

          float t=computeTorsion(currentP);

          float c=computeCurvature(currentP);

        //  float c=


         // qDebug("local torsion:%f\n",t);
          torsions.push_back(t);
         curvatures.push_back(c);

          if(t>largestTorsion)
              largestTorsion=t;

          if(c>largestCurvature)
              largestCurvature=c;
      }

      if(largestTorsion==0.0)
          largestTorsion=1.0f;

      for(int i=0;i<torsions.size();++i)
      {
          torsions[i]=1.0-torsions[i]/largestTorsion;
          curvatures[i]=curvatures[i]/largestCurvature;

          if(curvatures[i]<0.2)
              curvatures[i]=0;
          else curvatures[i]=1.0;
      }



      std::vector<GGL::Point3f> averageDir;

      std::vector<float> averageT;
      std::vector<float> averageC;

      averageDir.resize(dirs.size());

      averageT.resize(torsions.size());
      averageC.resize(curvatures.size());

      for(int e=0;e<(smoothness*0.5f);++e)
      {

        for(int i=0;i<torsions.size();++i)
        {
            int pre=i-1;
            int nxt=i+1;


            float ds=1.0;

            float at=torsions[i];

            float ac=curvatures[i];

            if(pre>=0)
            {
                at+=torsions[pre];
                ac+=curvatures[pre];
                ds+=1.0f;
            }
            if(nxt<torsions.size())
            {
                ac+=curvatures[nxt];
               at+=torsions[nxt];
                ds+=1.0f;
            }

            at/=ds;
            ac/=ds;

            averageT[i]=at;
            averageC[i]=ac;
        }

        std::copy(averageT.begin(),averageT.end(),torsions.begin());
        std::copy(averageC.begin(),averageC.end(),curvatures.begin());

      }




      for(int e=0;e<smoothness;++e)
      {

        for(int i=0;i<dirs.size();++i)
        {
            int pre=i-1;
            int nxt=i+1;

            GGL::Point3f ad=dirs[i];



            if(pre>=0)
            {
                ad+=dirs[pre];
            }
            if(nxt<dirs.size())
            {
                ad+=dirs[nxt];
            }

            ad.Normalize();

            averageDir[i]=ad;
        }

        std::copy(averageDir.begin(),averageDir.end(),dirs.begin());
       // std::copy(averageT.begin(),averageT.end(),torsions.begin());

      }

      //for(int i=1;i<clusterlist[clusterid][rlid].samples.size()-1;++i)
       for(int i=1;i<149;++i)
      {
          GGL::Point3f currentP=presavedPointList[i];

          GGL::Point3f dir=averageDir[i-1];

          float tapeWidth=lineWidthBase+torsions[i-1]*lineWidthFlex;

          atape.push_back(currentP+dir*(tapeWidth));//*(i+10)/(float)clusterlist[clusterid][rlid].samples.size());
          atape.push_back(currentP-dir*(tapeWidth));//*(i+10)/(float)clusterlist[clusterid][rlid].samples.size());

          tnormals.push_back(GGL::Point3f(0,0,0));
          tnormals.push_back(GGL::Point3f(0,0,0));


      }


      tapes.push_back(atape);
         tapeCurvatures.push_back(torsions);

         tapeTorsions.push_back(torsions);

      for(int i=0;i+2<atape.size();++i)
      {
          int a=i;
          int b=i+1;
          int c=i+2;

          GGL::Point3f e1=atape[b]-atape[a];
          GGL::Point3f e2=atape[c]-atape[a];

          GGL::Point3f nor=e1^e2;

          nor.Normalize();

          tnormals[a]=tnormals[a]+nor;


          GGL::Point3f e3=atape[c]-atape[b];
          GGL::Point3f e4=atape[a]-atape[b];

          nor=e3^e4;
          nor.Normalize();

          tnormals[b]=tnormals[b]+nor;

          GGL::Point3f e5=atape[a]-atape[c];
          GGL::Point3f e6=atape[b]-atape[c];

          nor=e5^e6;
          nor.Normalize();


          tnormals[c]=tnormals[c]+nor;

      }

      for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
          iter->Normalize();

      tapeNormals.push_back(tnormals);
  }

float DrawIllustrativeData::computeCurvature(GGL::Point3f &currentPos)
{
    GGL::Point3f tangent;

   float d = (tangent=VectorField::getSingleton().getVector(currentPos.X(),currentPos.Y(),currentPos.Z())).length();

   GGL::Point3f nextSample=movePoint(currentPos.X(),currentPos.Y(),currentPos.Z(),0.001);

   GGL::Point3f derivitive=VectorField::getSingleton().getVector(nextSample.X(),nextSample.Y(),nextSample.Z())-VectorField::getSingleton().getVector(currentPos.X(),currentPos.Y(),currentPos.Z());

   derivitive/=0.001;

   GGL::Point3f nextSampleNext=movePoint(nextSample.X(),nextSample.Y(),nextSample.Z(),0.001);

   GGL::Point3f sampleDerivitive=VectorField::getSingleton().getVector(nextSampleNext.X(),nextSampleNext.Y(),nextSampleNext.Z())-VectorField::getSingleton().getVector(nextSample.X(),nextSample.Y(),nextSample.Z());

   GGL::Point3f derivitive2=sampleDerivitive-derivitive;

   derivitive2/=0.001;

   d = tangent.length();



   float u  = tangent.X();
   float v  = tangent.Y();
   float w  =tangent.Z();

  float dxx  = derivitive.X();
  float dyy  = derivitive.Y();
  float dzz  = derivitive.Z();

  float cxx = -w * dyy + v * dzz;
  float cyy =  w * dxx - u * dzz;
  float czz = -v * dxx + u * dyy;

 float  k = sqrt(cxx * cxx + cyy * cyy + czz * czz) / (d * d * d);

   k = fabs(k);


   GGL::Point3f a1=(nextSampleNext-nextSample).Normalize();
   GGL::Point3f a2=(currentPos-nextSample).Normalize();

    a1.Normalize();
    a2.Normalize();

   k=(a1*a2);

   k=fabs(k);

  // float c=(tangent.length()-VectorField::getSingleton().minMag)/(VectorField::getSingleton().maxMag);

   qDebug()<<"curv"<<k;

  // return c;

   return k;
}

float DrawIllustrativeData :: computeTorsion(GGL::Point3f &currentPos)
{

    GGL::Point3f tangent;

   float d = (tangent=VectorField::getSingleton().getVector(currentPos.X(),currentPos.Y(),currentPos.Z())).length();

   GGL::Point3f nextSample=movePoint(currentPos.X(),currentPos.Y(),currentPos.Z(),0.001);

   GGL::Point3f derivitive=VectorField::getSingleton().getVector(nextSample.X(),nextSample.Y(),nextSample.Z())-VectorField::getSingleton().getVector(currentPos.X(),currentPos.Y(),currentPos.Z());

   derivitive/=0.001;

   GGL::Point3f nextSampleNext=movePoint(nextSample.X(),nextSample.Y(),nextSample.Z(),0.001);

   GGL::Point3f sampleDerivitive=VectorField::getSingleton().getVector(nextSampleNext.X(),nextSampleNext.Y(),nextSampleNext.Z())-VectorField::getSingleton().getVector(nextSample.X(),nextSample.Y(),nextSample.Z());

   GGL::Point3f derivitive2=sampleDerivitive-derivitive;

   derivitive2/=0.001;

    float u0  = tangent.X();
   float v0  = tangent.Y();
  float  w0  = tangent.Z();

   float u1  = derivitive.X();
 float   v1  = derivitive.Y();
   float w1  = derivitive.Z();

  float  u2  = derivitive2.X();
   float v2  = derivitive2.Y();
   float w2  = derivitive2.Z();

/*  float  h  = u0 * (v1 * w2 - v2 * w1)
        -u1 * (v0 * w2 - v2 * w0)
        +u2 * (v0 * w1 - v1 * w0);

 float   cxx = -w0 * v1 + v0 * w1;
  float  cyy =  w0 * u1 - u0 * w1;
   float czz = -v0 * u1 + u0 * v1;

  float  q = cxx * cxx + cyy * cyy + czz * czz;
*/


   float h=w2*(u0*v1-v0*u1)+w1*(u2*v0-u0*v2)+w0*(u1*v2+u2*v1);

   float q=(u0*u0+v0*v0+w0*w0)*(u1*u1+v1*v1+w1*w1);


    if (q == 0) {
        return 0;
        //continue;
    }

 float   t = h / q;

    t = fabs(t);
    return t;
}

GGL::Point3f  DrawIllustrativeData::    computeBiNormalDirection(GGL::Point3f &currentPos)
{
    GGL::Point3f tangenta=VectorField::getSingleton().getVector(currentPos.X(),currentPos.Y(),currentPos.Z());
    GGL::Point3f nextPos=movePoint(currentPos.X(),currentPos.Y(),currentPos.Z(),0.001);

    GGL::Point3f tangentb=VectorField::getSingleton().getVector(nextPos.X(),nextPos.Y(),nextPos.Z());

    GGL::Point3f normal=(tangentb-tangenta).Normalize();

    return (tangenta^normal).Normalize();
}

 void DrawIllustrativeData::generateATapeFromRepresentativeLineWithTorsion(const int clusterid,const int rlid)
 {
     std::vector<GGL::Point3f> presavedPointList;




     for(int i=0;i<clusterlist[clusterid][rlid].samples.size();++i)
     {
         presavedPointList.push_back(clusterlist[clusterid][rlid].samples[i]);
     }

     std::vector<GGL::Point3f> atape;
     std::vector<GGL::Point3f> tnormals;

     std::vector<GGL::Point3f> dirs;
     std::vector<float> torsions;

     std::vector<float> curvatures;

     float largestTorsion=0;
     float largestCurvature=0;

     for(int i=1;i<clusterlist[clusterid][rlid].samples.size()-1;++i)
     {
         GGL::Point3f currentP=presavedPointList[i];
         GGL::Point3f nxtP=presavedPointList[i+1];

         GGL::Point3f preP=presavedPointList[i-1];

        // GGL::Point3f dir=(nxtP-currentP)^(preP-currentP);

         GGL::Point3f dir=computeBiNormalDirection(currentP);

         //dir.Normalize();

         dirs.push_back(dir);

      //   float t=computeTorsion(currentP);

         float t=(currentP-GGL::Point3f(49.5,49.5,49.5)).length();



         float c=computeCurvature(currentP);

        // qDebug("local torsion:%f\n",t);
         torsions.push_back(t);
        curvatures.push_back(c);

         if(t>largestTorsion)
             largestTorsion=t;

         if(c>largestCurvature)
             largestCurvature=c;


     }

     if(largestTorsion==0.0)
         largestTorsion=1.0f;

     for(int i=0;i<torsions.size();++i)
     {
         torsions[i]=/*1.0-*/torsions[i]/largestTorsion;
         curvatures[i]=curvatures[i]/largestCurvature;

         if(curvatures[i]<0.2)
             curvatures[i]=0;
         else curvatures[i]=1.0;
     }

     float smallestTorsion=torsions[0];
     float smallestCurvature=curvatures[0];

     for(int i=1;i<torsions.size();++i)
     {
         if(torsions[i]==0.0f)
         {
             torsions[i]=smallestTorsion;
             continue;
         }

         if(smallestTorsion>torsions[i])
             smallestTorsion=torsions[i];

         if(smallestCurvature>curvatures[i])
             smallestCurvature=curvatures[i];



     }



  /*   qDebug()<<"torsion=======before=================";

     for(int e=0;e<torsions.size();++e)
         qDebug()<<torsions[e];

     qDebug()<<"============================";*/

     qDebug()<<"smallestTorsion"<<smallestTorsion;

     for(int i=0;i<torsions.size();++i)
     {
         torsions[i]=(torsions[i]-smallestTorsion)/(1.0f-smallestTorsion);

        // curvatures[i]=(curvatures[i]-smallestCurvature)/(1.0f-smallestCurvature);

         if(tapes.size()%11!=0)

         torsions[i]=torsions[i];
         else
             torsions[i]=1.0;
     }

/*     qDebug()<<"torsion=========after===============";

     for(int e=0;e<torsions.size();++e)
         qDebug()<<torsions[e];

     qDebug()<<"============================";*/

     std::vector<GGL::Point3f> averageDir;

     std::vector<float> averageT;
     std::vector<float> averageC;

     averageDir.resize(dirs.size());

     averageT.resize(torsions.size());
     averageC.resize(curvatures.size());

     for(int e=0;e<(smoothness*0.5f);++e)
     {

       for(int i=0;i<torsions.size();++i)
       {
           int pre=i-1;
           int nxt=i+1;


           float ds=1.0;

           float at=torsions[i];

           float ac=curvatures[i];

           if(pre>=0)
           {
               at+=torsions[pre];
               ac+=curvatures[pre];
               ds+=1.0f;
           }
           if(nxt<torsions.size())
           {
               ac+=curvatures[nxt];
              at+=torsions[nxt];
               ds+=1.0f;
           }

           at/=ds;
           ac/=ds;

           averageT[i]=at;
           averageC[i]=ac;
       }

       std::copy(averageT.begin(),averageT.end(),torsions.begin());
       std::copy(averageC.begin(),averageC.end(),curvatures.begin());

     }


     for(int i=1;i<dirs.size();++i)
     {
         GGL::Point3f adpre=dirs[i-1];
         GGL::Point3f ad=dirs[i];

         if(ad*adpre<0.0)
             dirs[i]=-ad;
     }



     for(int e=0;e<smoothness;++e)
     {

       for(int i=0;i<dirs.size();++i)
       {
           int pre=i-1;
           int nxt=i+1;

           GGL::Point3f ad=dirs[i];



           if(pre>=0)
           {

               ad+=dirs[pre];
           }
           if(nxt<dirs.size())
           {
               ad+=dirs[nxt];
           }

           ad.Normalize();

           averageDir[i]=ad;
       }

       std::copy(averageDir.begin(),averageDir.end(),dirs.begin());
      // std::copy(averageT.begin(),averageT.end(),torsions.begin());

     }

     GGL::Point3f offset(0,0,0);

 /*    if(tapes.size()==0)
     {
        offset.vec(0.0,-2.0,-0);
     }
     else
         if(tapes.size()==11)
         {
         offset.vec(0.5,0,2);
         }
*/
for(int i=1;i<clusterlist[clusterid][rlid].samples.size()-1;++i)
     {
         GGL::Point3f currentP=presavedPointList[i];

         GGL::Point3f dir=averageDir[i-1];

         qDebug()<<"dir"<<dir.X()<<dir.Y()<<dir.Z();

         float tapeWidth=lineWidthBase+torsions[i-1]*lineWidthFlex;

          tapeWidth=2.0f;
     //    if(tapeWidth<0.2)
       //      break;

         atape.push_back(currentP+dir*(tapeWidth)+offset);//*(i+10)/(float)clusterlist[clusterid][rlid].samples.size());
         atape.push_back(currentP-dir*(tapeWidth)+offset);//*(i+10)/(float)clusterlist[clusterid][rlid].samples.size());

         tnormals.push_back(GGL::Point3f(0,0,0));
         tnormals.push_back(GGL::Point3f(0,0,0));


     }


     tapes.push_back(atape);
        tapeCurvatures.push_back(curvatures);
        tapeTorsions.push_back(torsions);

     for(int i=0;i+2<atape.size();++i)
     {
         int a=i;
         int b=i+1;
         int c=i+2;

         GGL::Point3f e1=atape[b]-atape[a];
         GGL::Point3f e2=atape[c]-atape[a];

         GGL::Point3f nor=e1^e2;

         nor.Normalize();

         tnormals[a]=tnormals[a]+nor;


         GGL::Point3f e3=atape[c]-atape[b];
         GGL::Point3f e4=atape[a]-atape[b];

         nor=e3^e4;
         nor.Normalize();

         tnormals[b]=tnormals[b]+nor;

         GGL::Point3f e5=atape[a]-atape[c];
         GGL::Point3f e6=atape[b]-atape[c];

         nor=e5^e6;
         nor.Normalize();


         tnormals[c]=tnormals[c]+nor;

     }

     for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
         iter->Normalize();

     tapeNormals.push_back(tnormals);
 }

 void DrawIllustrativeData::generateATapeFromAStartPoint(const GGL::Point3f &startPoint,const GGL::Point3f &eye)
 {
    std::vector<GGL::Point3f> presavedPointList;

    GGL::Point3f currentPoint=startPoint;

    presavedPointList.push_back(currentPoint);

    for(int i=0;i<150;++i)
    {
        currentPoint=movePoint(currentPoint.X(),currentPoint.Y(),currentPoint.Z());
        presavedPointList.push_back(currentPoint);
    }

    GGL::Point3f dir=VectorField::getSingleton().getVector(currentPoint.X(),currentPoint.Y(),currentPoint.Z());

    GGL::Point3f viewDir=eye-currentPoint;

    GGL::Point3f tapeDir=(dir^viewDir).Normalize()*0.1f;

    std::vector<GGL::Point3f> presavedTape;

    currentPoint=currentPoint+tapeDir;

    presavedTape.push_back(currentPoint);

    for(int i=0;i<150;++i)
    {
        currentPoint=movePointInBackward(currentPoint.X(),currentPoint.Y(),currentPoint.Z());
        presavedTape.push_back(currentPoint);
    }

    std::vector<GGL::Point3f> atape;
    std::vector<GGL::Point3f> tnormals;
    for(int i=0;i<150;++i)
    {
        GGL::Point3f tapePoint=presavedTape[150-i];
        GGL::Point3f originalPoint=presavedPointList[i];

        GGL::Point3f dir=tapePoint-originalPoint;

        dir.Normalize();

        atape.push_back(originalPoint+dir*2.0f);
        atape.push_back(originalPoint-dir*2.0f);

        tnormals.push_back(GGL::Point3f(0,0,0));
        tnormals.push_back(GGL::Point3f(0,0,0));
    }

    tapes.push_back(atape);


    for(int i=0;i+2<atape.size();++i)
    {
        int a=i;
        int b=i+1;
        int c=i+2;

        GGL::Point3f e1=atape[b]-atape[a];
        GGL::Point3f e2=atape[c]-atape[a];

        GGL::Point3f nor=e1^e2;

        nor.Normalize();

        tnormals[a]=tnormals[a]+nor;


        GGL::Point3f e3=atape[c]-atape[b];
        GGL::Point3f e4=atape[a]-atape[b];

        nor=e3^e4;
        nor.Normalize();

        tnormals[b]=tnormals[b]+nor;

        GGL::Point3f e5=atape[a]-atape[c];
        GGL::Point3f e6=atape[b]-atape[c];

        nor=e5^e6;
        nor.Normalize();


        tnormals[c]=tnormals[c]+nor;

    }

    for(std::vector<GGL::Point3f>::iterator iter=tnormals.begin();iter!=tnormals.end();++iter)
        iter->Normalize();

    tapeNormals.push_back(tnormals);
 }
