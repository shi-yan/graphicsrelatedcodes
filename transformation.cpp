#include "transformation.h"

Transformation::Transformation():translation(),rotation(),scale(1.0f)
{
}

Transformation::~Transformation()
{

}

Transformation::Transformation(const GGL::Point3f &_t,const GGL::Matrix33f _r,const float _s):translation(_t),rotation(_r),scale(_s)
{

}

Transformation::Transformation(const Transformation &in):translation(in.translation),rotation(in.rotation),scale(in.scale),rotationAxis(in.rotationAxis),pairID(in.pairID)
{

}

void Transformation::operator=(const Transformation &in)
{
    translation=in.translation;
    rotation=in.rotation;
    scale=in.scale;
    rotationAxis=in.rotationAxis;
    pairID=in.pairID;
}

bool Transformation::operator==(const Transformation &in)
{
    //return translation==in.translation && rotation==in.rotation && scale==in.scale;
    return true;
}


void Transformation::setRotationAxis(const GGL::Point3f _ra)
{
    rotationAxis=_ra;
}

void  Transformation:: setRotationMatrix(const GGL::Matrix33f & _rm)
{
    rotation=_rm;
}
