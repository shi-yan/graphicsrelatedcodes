#ifndef SEEDINGIDEADATA_H
#define SEEDINGIDEADATA_H

#include <QObject>
#include <vector>
#include "Point3.h"

class SVertex
{
public:
    GGL::Point3f pos;
    float inorout;

public:
    SVertex():pos(),inorout(0)
    {};

    SVertex(const SVertex &in):pos(in.pos),inorout(in.inorout)
    {}

    void operator=(const SVertex &in)
    {
        pos=in.pos;
        inorout=in.inorout;
    }
};

class SeedingIdeaData:public QObject
{
   Q_OBJECT

private:
    std::vector<SVertex> vertexList;
    std::vector<unsigned int> vertexIndices;

    SeedingIdeaData();

public:

    static SeedingIdeaData &getSingleton()
    {
        static SeedingIdeaData obj;
        return obj;
    }

    void draw();
    void drawBoundary();

public slots:
    void onVectorFieldLoaded();


};

#endif // SEEDINGIDEADATA_H
