#include "seedingideadata.h"
#include "VectorField.h"
#include <map>
#include <QtOpenGL/QGLWidget>

SeedingIdeaData::SeedingIdeaData()
{
  //  connect(&VectorField::getSingleton(),SIGNAL(dataUpdated()),this,SLOT(onVectorFieldLoaded()));
}

void SeedingIdeaData::draw()
{
    drawBoundary();
}

void SeedingIdeaData::drawBoundary()
{
    if(vertexIndices.size())
    {
        glDisable(GL_LIGHTING);

        glBegin(GL_QUADS);

        for(int i=0;i<vertexIndices.size();++i)
        {
            SVertex v=vertexList[vertexIndices[i]];

            if(v.inorout>0.5)
                   glColor3ub(255.0*v.inorout,0,0);
            else
                   glColor3ub(0,0,255.0*-v.inorout);
            glVertex3f(v.pos.X(),v.pos.Y(),v.pos.Z());
        }

        glEnd();

    }
}

void SeedingIdeaData::onVectorFieldLoaded()
{
    std::map<unsigned int, unsigned int> uniqueVertices;

    vertexList.reserve(1000);

    for(int x=0;x<VectorField::getSingleton().xSize-1;++x)
        for(int y=0;y<VectorField::getSingleton().ySize-1;++y)
        {
            unsigned int indexALow=0;
            unsigned int indexBLow=0;
            unsigned int indexCLow=0;
            unsigned int indexDLow=0;

            unsigned int indexAHigh=0;
            unsigned int indexBHigh=0;
            unsigned int indexCHigh=0;
            unsigned int indexDHigh=0;

            int fieldIDALow=0+y*VectorField::getSingleton().xSize+x;
            int fieldIDBLow=0+y*VectorField::getSingleton().xSize+x+1;
            int fieldIDCLow=0+(y+1)*VectorField::getSingleton().xSize+x;
            int fieldIDDLow=0+(y+1)*VectorField::getSingleton().xSize+x+1;

            int fieldIDAHigh=(VectorField::getSingleton().zSize-1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+y*VectorField::getSingleton().xSize+x;
            int fieldIDBHigh=(VectorField::getSingleton().zSize-1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+y*VectorField::getSingleton().xSize+x+1;
            int fieldIDCHigh=(VectorField::getSingleton().zSize-1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(y+1)*VectorField::getSingleton().xSize+x;
            int fieldIDDHigh=(VectorField::getSingleton().zSize-1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(y+1)*VectorField::getSingleton().xSize+x+1;

            if(uniqueVertices.find(fieldIDALow)==uniqueVertices.end())
            {
                indexALow=uniqueVertices[fieldIDALow]=vertexList.size();
                SVertex v;
                v.pos.vec(x,y,0);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,y,0);

                v.inorout=tangent.length();

                if(tangent.Z()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

            }
            else
            {
                indexALow=uniqueVertices[fieldIDALow];
            }

            if(uniqueVertices.find(fieldIDBLow)==uniqueVertices.end())
            {
                indexBLow=uniqueVertices[fieldIDBLow]=vertexList.size();
                SVertex v;
                v.pos.vec(x+1,y,0);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,y,0);

                v.inorout=tangent.length();

                if(tangent.Z()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

             //   qDebug("f");
            }
            else
            {
                indexBLow=uniqueVertices[fieldIDBLow];
            }


            if(uniqueVertices.find(fieldIDCLow)==uniqueVertices.end())
            {
                indexCLow=uniqueVertices[fieldIDCLow]=vertexList.size();
                 SVertex v;
                v.pos.vec(x,y+1,0);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,y+1,0);

                v.inorout=tangent.length();

                if(tangent.Z()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexCLow=uniqueVertices[fieldIDCLow];
            }

            if(uniqueVertices.find(fieldIDDLow)==uniqueVertices.end())
            {
                indexDLow=uniqueVertices[fieldIDDLow]=vertexList.size();
                 SVertex v;
                v.pos.vec(x+1,y+1,0);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,y+1,0);

                v.inorout=tangent.length();

                if(tangent.Z()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexDLow=uniqueVertices[fieldIDDLow];
            }

            vertexIndices.push_back(indexALow);
            vertexIndices.push_back(indexCLow);
            vertexIndices.push_back(indexDLow);
            vertexIndices.push_back(indexBLow);




            if(uniqueVertices.find(fieldIDAHigh)==uniqueVertices.end())
            {
                indexAHigh=uniqueVertices[fieldIDAHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(x,y,VectorField::getSingleton().zSize-1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,y,VectorField::getSingleton().zSize-1);

                v.inorout=tangent.length();

                if(tangent.Z()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

            }
            else
            {
                indexAHigh=uniqueVertices[fieldIDAHigh];
            }

            if(uniqueVertices.find(fieldIDBHigh)==uniqueVertices.end())
            {
                indexBHigh=uniqueVertices[fieldIDBHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(x+1,y,VectorField::getSingleton().zSize-1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,y,VectorField::getSingleton().zSize-1);

                v.inorout=tangent.length();

                if(tangent.Z()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexBHigh=uniqueVertices[fieldIDBHigh];
            }


            if(uniqueVertices.find(fieldIDCHigh)==uniqueVertices.end())
            {
                indexCHigh=uniqueVertices[fieldIDCHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(x,y+1,VectorField::getSingleton().zSize-1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,y+1,VectorField::getSingleton().zSize-1);

                v.inorout=tangent.length();

                if(tangent.Z()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexCHigh=uniqueVertices[fieldIDCHigh];
            }

            if(uniqueVertices.find(fieldIDDHigh)==uniqueVertices.end())
            {
                indexDHigh=uniqueVertices[fieldIDDHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(x+1,y+1,VectorField::getSingleton().zSize-1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,y+1,VectorField::getSingleton().zSize-1);

                v.inorout=tangent.length();

                if(tangent.Z()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexDHigh=uniqueVertices[fieldIDDHigh];
            }

            vertexIndices.push_back(indexAHigh);
            vertexIndices.push_back(indexBHigh);
            vertexIndices.push_back(indexDHigh);
            vertexIndices.push_back(indexCHigh);


        }






    qDebug("finished one face\n");





    for(int y=0;y<VectorField::getSingleton().ySize-1;++y)
        for(int z=0;z<VectorField::getSingleton().zSize-1;++z)
        {
            unsigned int indexALow=0;
            unsigned int indexBLow=0;
            unsigned int indexCLow=0;
            unsigned int indexDLow=0;

            unsigned int indexAHigh=0;
            unsigned int indexBHigh=0;
            unsigned int indexCHigh=0;
            unsigned int indexDHigh=0;

            int fieldIDALow=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+y*VectorField::getSingleton().xSize;
            int fieldIDBLow=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(y+1)*VectorField::getSingleton().xSize;
            int fieldIDCLow=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+y*VectorField::getSingleton().xSize;
            int fieldIDDLow=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(y+1)*VectorField::getSingleton().xSize;

            int fieldIDAHigh=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+y*VectorField::getSingleton().xSize+VectorField::getSingleton().xSize-1;
            int fieldIDBHigh=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(y+1)*VectorField::getSingleton().xSize+VectorField::getSingleton().xSize-1;
            int fieldIDCHigh=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+y*VectorField::getSingleton().xSize+VectorField::getSingleton().xSize-1;
            int fieldIDDHigh=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(y+1)*VectorField::getSingleton().xSize+VectorField::getSingleton().xSize-1;

            if(uniqueVertices.find(fieldIDALow)==uniqueVertices.end())
            {
                indexALow=uniqueVertices[fieldIDALow]=vertexList.size();
                 SVertex v;
                v.pos.vec(0,y,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(0,y,z);

                v.inorout=tangent.length();

                if(tangent.X()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

            }
            else
            {
                indexALow=uniqueVertices[fieldIDALow];
            }

            if(uniqueVertices.find(fieldIDBLow)==uniqueVertices.end())
            {
                indexBLow=uniqueVertices[fieldIDBLow]=vertexList.size();
                 SVertex v;
                v.pos.vec(0,y+1,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(0,y+1,z);

                v.inorout=tangent.length();

                if(tangent.X()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexBLow=uniqueVertices[fieldIDBLow];
            }


            if(uniqueVertices.find(fieldIDCLow)==uniqueVertices.end())
            {
                indexCLow=uniqueVertices[fieldIDCLow]=vertexList.size();
                 SVertex v;
                v.pos.vec(0,y,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(0,y,z+1);

                v.inorout=tangent.length();

                if(tangent.X()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexCLow=uniqueVertices[fieldIDCLow];
            }

            if(uniqueVertices.find(fieldIDDLow)==uniqueVertices.end())
            {
                indexDLow=uniqueVertices[fieldIDDLow]=vertexList.size();
                 SVertex v;
                v.pos.vec(0,y+1,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(0,y+1,z+1);

                v.inorout=tangent.length();

                if(tangent.X()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexDLow=uniqueVertices[fieldIDDLow];
            }

            vertexIndices.push_back(indexALow);
            vertexIndices.push_back(indexCLow);
            vertexIndices.push_back(indexDLow);
            vertexIndices.push_back(indexBLow);




            if(uniqueVertices.find(fieldIDAHigh)==uniqueVertices.end())
            {
                indexAHigh=uniqueVertices[fieldIDAHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(VectorField::getSingleton().xSize-1,y,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(VectorField::getSingleton().xSize-1,y,z);

                v.inorout=tangent.length();

                if(tangent.X()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

            }
            else
            {
                indexAHigh=uniqueVertices[fieldIDAHigh];
            }

            if(uniqueVertices.find(fieldIDBHigh)==uniqueVertices.end())
            {
                indexBHigh=uniqueVertices[fieldIDBHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(VectorField::getSingleton().xSize-1,y+1,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(VectorField::getSingleton().xSize-1,y+1,z);

                v.inorout=tangent.length();

                if(tangent.X()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexBHigh=uniqueVertices[fieldIDBHigh];
            }


            if(uniqueVertices.find(fieldIDCHigh)==uniqueVertices.end())
            {
                indexCHigh=uniqueVertices[fieldIDCHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(VectorField::getSingleton().xSize-1,y,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(VectorField::getSingleton().xSize-1,y,z+1);

                v.inorout=tangent.length();

                if(tangent.X()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexCHigh=uniqueVertices[fieldIDCHigh];
            }

            if(uniqueVertices.find(fieldIDDHigh)==uniqueVertices.end())
            {
                indexDHigh=uniqueVertices[fieldIDDHigh]=vertexList.size();
                 SVertex v;
                v.pos.vec(VectorField::getSingleton().xSize-1,y+1,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(VectorField::getSingleton().xSize-1,y+1,z+1);

                v.inorout=tangent.length();

                if(tangent.X()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexDHigh=uniqueVertices[fieldIDDHigh];
            }

            vertexIndices.push_back(indexAHigh);
            vertexIndices.push_back(indexBHigh);
            vertexIndices.push_back(indexDHigh);
            vertexIndices.push_back(indexCHigh);

        }



    qDebug("finished one face\n");

//return;
    for(int x=0;x<VectorField::getSingleton().xSize-1;++x)
        for(int z=0;z<VectorField::getSingleton().zSize-1;++z)
        {
            unsigned int indexALow=0;
            unsigned int indexBLow=0;
            unsigned int indexCLow=0;
            unsigned int indexDLow=0;

            unsigned int indexAHigh=0;
            unsigned int indexBHigh=0;
            unsigned int indexCHigh=0;
            unsigned int indexDHigh=0;

            int fieldIDALow=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+x;
            int fieldIDBLow=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+x+1;
            int fieldIDCLow=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+x;
            int fieldIDDLow=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+x+1;

            int fieldIDAHigh=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(VectorField::getSingleton().ySize-1)*VectorField::getSingleton().xSize+x;
            int fieldIDBHigh=z*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(VectorField::getSingleton().ySize-1)*VectorField::getSingleton().xSize+x+1;
            int fieldIDCHigh=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(VectorField::getSingleton().ySize-1)*VectorField::getSingleton().xSize+x;
            int fieldIDDHigh=(z+1)*VectorField::getSingleton().ySize*VectorField::getSingleton().xSize+(VectorField::getSingleton().ySize-1)*VectorField::getSingleton().xSize+x+1;

            if(uniqueVertices.find(fieldIDALow)==uniqueVertices.end())
            {
                indexALow=uniqueVertices[fieldIDALow]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x,0,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,0,z);

                v.inorout=tangent.length();

                if(tangent.Y()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

            }
            else
            {
                indexALow=uniqueVertices[fieldIDALow];
            }

            if(uniqueVertices.find(fieldIDBLow)==uniqueVertices.end())
            {
                indexBLow=uniqueVertices[fieldIDBLow]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x+1,0,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,0,z);

                v.inorout=tangent.length();

                if(tangent.Y()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexBLow=uniqueVertices[fieldIDBLow];
            }


            if(uniqueVertices.find(fieldIDCLow)==uniqueVertices.end())
            {
                indexCLow=uniqueVertices[fieldIDCLow]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x,0,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,0,z+1);

                v.inorout=tangent.length();

                if(tangent.Y()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexCLow=uniqueVertices[fieldIDCLow];
            }

            if(uniqueVertices.find(fieldIDDLow)==uniqueVertices.end())
            {
                indexDLow=uniqueVertices[fieldIDDLow]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x+1,0,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,0,z+1);

                v.inorout=tangent.length();

                if(tangent.Y()<0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexDLow=uniqueVertices[fieldIDDLow];
            }

            vertexIndices.push_back(indexALow);
            vertexIndices.push_back(indexCLow);
            vertexIndices.push_back(indexDLow);
            vertexIndices.push_back(indexBLow);




            if(uniqueVertices.find(fieldIDAHigh)==uniqueVertices.end())
            {
                indexAHigh=uniqueVertices[fieldIDAHigh]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x,VectorField::getSingleton().ySize-1,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,VectorField::getSingleton().ySize-1,z);

                v.inorout=tangent.length();

                if(tangent.Y()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);

            }
            else
            {
                indexAHigh=uniqueVertices[fieldIDAHigh];
            }

            if(uniqueVertices.find(fieldIDBHigh)==uniqueVertices.end())
            {
                indexBHigh=uniqueVertices[fieldIDBHigh]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x+1,VectorField::getSingleton().ySize-1,z);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,VectorField::getSingleton().ySize-1,z);

                v.inorout=tangent.length();

                if(tangent.Y()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexBHigh=uniqueVertices[fieldIDBHigh];
            }


            if(uniqueVertices.find(fieldIDCHigh)==uniqueVertices.end())
            {
                indexCHigh=uniqueVertices[fieldIDCHigh]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x,VectorField::getSingleton().ySize-1,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x,VectorField::getSingleton().ySize-1,z+1);

                v.inorout=tangent.length();

                if(tangent.Y()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexCHigh=uniqueVertices[fieldIDCHigh];
            }

            if(uniqueVertices.find(fieldIDDHigh)==uniqueVertices.end())
            {
                indexDHigh=uniqueVertices[fieldIDDHigh]=vertexList.size();
                struct SVertex v;
                v.pos.vec(x+1,VectorField::getSingleton().ySize-1,z+1);

                GGL::Point3f tangent=VectorField::getSingleton().getVector(x+1,VectorField::getSingleton().ySize-1,z+1);

                v.inorout=tangent.length();

                if(tangent.Y()>0)
                    v.inorout=-v.inorout;

                vertexList.push_back(v);
            }
            else
            {
                indexDHigh=uniqueVertices[fieldIDDHigh];
            }

            vertexIndices.push_back(indexAHigh);
            vertexIndices.push_back(indexBHigh);
            vertexIndices.push_back(indexDHigh);
            vertexIndices.push_back(indexCHigh);

        }


float largestP=0;
float largestN=0;


    for(int i=0;i<vertexList.size();++i)
    {
        SVertex v=vertexList[i];

        if(v.inorout>largestP)
               largestP=v.inorout;

        if(v.inorout<largestN)
            largestN=v.inorout;

    }


    for(int i=0;i<vertexList.size();++i)
    {
        SVertex v=vertexList[i];

        if(v.inorout>0)
          vertexList[i].inorout/=largestP;
       else
           vertexList[i].inorout/=-largestN;

        qDebug("%f\n",vertexList[i].inorout);
        qDebug("df");
    }





}
