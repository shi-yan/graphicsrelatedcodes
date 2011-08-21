#include "Vertex.h"

Vertex::Vertex(void):startIdx(-1),cuttingPlaneLength(-1),uid(-1),listID(-1)
{
}

Vertex::Vertex(GGL::Point3f &_position,GGL::Point3f &_normal,float _r):position(_position),color(),normal(_normal),r(_r),debugID(0),startIdx(-1),cuttingPlaneLength(-1),uid(-1),listID(-1)
{
}

Vertex::Vertex(GGL::Point3f &_position,GGL::Point3f &_normal):position(_position),normal(_normal),r(0),debugID(0),color(),startIdx(-1),cuttingPlaneLength(-1),uid(-1),listID(-1)
{
}

Vertex::~Vertex(void)
{
}
