#pragma once
#include "Camera.h"
#include "SpotLight.h"

class PerspectiveCamera:public Camera
{
	Q_OBJECT
public:
	PerspectiveCamera(void);
	PerspectiveCamera(QString _name);
	~PerspectiveCamera(void);

	enum CameraType getCameraType()
	{
		return Perspective;
	};

	QString getCameraInfo()
	{
		QString result;
		result=QString("%1 Camera\n from:%2,%3,%4\n to:%5,%6,%7\n").arg(cameraName()).arg(from().X()).arg(from().Y()).arg(from().Z()).arg(to().X()).arg(to().Y()).arg(to().Z());
		return result;
	}

	void lookAt(GGL::Point3f &_from,GGL::Point3f &_to);

	 void onMouseMove(int x,int y);

	 void onMouseWheel(float notch);

	 void setCamera(float width,float height,float ratio);

	  void setCameraForSelection(int x,int y,int selectionWidth,int selectionHeight,float width,float height,float ratio);


	  Light * getCameraLight();

          void save(const QString &filename);
        void load(const QString &filename);

private:
	SpotLight light;
};
