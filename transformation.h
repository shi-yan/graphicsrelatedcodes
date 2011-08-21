#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Point3.h"
#include "Matrix33.h"

class Transformation
{
private:
    GGL::Point3f translation;
    GGL::Matrix33f rotation;
    float scale;
    GGL::Point3f rotationAxis;

    int pairID;

public:
    Transformation();
    ~Transformation();

    Transformation(const GGL::Point3f &_t,const GGL::Matrix33f _r,const float _s);
    Transformation(const Transformation &in);
    void operator=(const Transformation &in);
    bool operator==(const Transformation &in);

    void setRotationAxis(const GGL::Point3f _ra);

    GGL::Point3f & getRotationAxis()
    {
       return rotationAxis;
    };

    GGL::Matrix33f & getRotationMatrix()
    {
        return rotation;
    }

    void setRotationMatrix(const GGL::Matrix33f &_rm);

    void setPairID(const int _id)
    {
        pairID=_id;
    };

    int getPairID()
    {
        return pairID;
    };
};

#endif // TRANSFORMATION_H
