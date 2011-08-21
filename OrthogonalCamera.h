#pragma once
#include "DirectionalLight.h"
#include "Camera.h"


class OrthogonalCamera :
	public Camera
{
	Q_OBJECT
public:
	OrthogonalCamera(void);
	OrthogonalCamera(QString _name);
	virtual ~OrthogonalCamera(void);

	enum CameraType getCameraType()
	{
		return Orthogonal;
	}

	QString getCameraInfo()
	{
		QString result;
		result=QString("%1 Camera\n from:%2,%3,%4\n to:%5,%6,%7\n").arg(cameraName()).arg(from().X()).arg(from().Y()).arg(from().Z()).arg(to().X()).arg(to().Y()).arg(to().Z());
		return result;
	}
		
	void lookAt(GGL::Point3f &_from,GGL::Point3f &_to);
	 
	void onMouseMove(int x,int y);
 
	void onMouseWheel(float notch);

	Light * getCameraLight();

	
	 void setCamera(float width,float height,float ratio);

	  void setCameraForSelection(int x,int y,int selectionWidth,int selectionHeight,float width,float height,float ratio);


	 float getScale(){return scale;};
	 
	 void setScale(float _scale){scale=_scale;};

         void load(const QString &filename){};
         void save(const QString &filename){};
protected:
	float scale;
	DirectionalLight light;
};
