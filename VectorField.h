#ifndef __VectorField__
#define __VectorField__

#include <QtCore/QObject>
#include "Point3.h"


class VectorField:public QObject
{

    Q_OBJECT

    struct FVector
    {
    float x;
    float y;
    float z;

    void operator=(const FVector &in)
    {

            x=in.x;
            y=in.y;
            z=in.z;
    };

    };

private:
    QString dataName;

public:

    QString getDataName()
    {
        return dataName;
    };

	float deltaT;
	float maxMag;
	float minMag;


	float overall;

	int colorSize;

	struct FVector *vectorField;
	
	 int xSize;
	 int ySize;
	 int zSize;
	
	static VectorField & getSingleton()
	{
		static VectorField obj;
		return obj;
	}
	
        void init(const char *filename,int _sizex,int _sizey,int _sizez,const QString & dataName);


        GGL::Point3f getVector(float x,float y,float z);

	void draw();
	
        GGL::Point3f getCenter();
	float getRadius();


private:
        VectorField():deltaT(0.8f),maxMag(-1.0f),minMag(10000000000.0f),colorSize(8),vectorField(NULL),xSize(0),ySize(0),zSize(0)
        {

        }
        ~VectorField(void)
        {
                if(vectorField)
                        delete [] vectorField;
        }

         signals:
                void dataUpdated();
};

#endif
