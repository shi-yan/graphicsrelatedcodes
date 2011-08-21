#pragma once
#include "Point3.h"
#include <QtCore/QString>
#include <QtCore/QObject>

class Light;

class Camera:public QObject
{
	Q_OBJECT
		/*
	Q_PROPERTY(QString CameraName READ cameraName WRITE setCameraName DESIGNABLE true USER true)
	Q_PROPERTY(float Fov READ fov WRITE setFov DESIGNABLE true USER true)
	Q_CLASSINFO("Fov", "minimum=0;maximum=180;decimals=4;singleStep=0.001;");
	Q_PROPERTY(float NearPlane READ nearPlane WRITE setNearPlane DESIGNABLE true USER true)
	Q_CLASSINFO("NearPlane", "minimum=0;maximum=2147483647;decimals=4;singleStep=0.001;");
	Q_PROPERTY(float FarPlane READ farPlane WRITE setFarPlane DESIGNABLE true USER true)
	Q_CLASSINFO("FarPlane", "minimum=0;maximum=2147483647;decimals=4;singleStep=0.001;");
	Q_PROPERTY(GGL::Point3f From READ from WRITE setFrom DESIGNABLE true USER true)
	Q_CLASSINFO("From", "minimumX=-2147483647;maximumX=2147483647;minimumY=-2147483647;maximumY=2147483647;minimumZ=-2147483647;maximumZ=2147483647;");
	Q_PROPERTY(GGL::Point3f To READ to WRITE setTo DESIGNABLE true USER true)
	Q_CLASSINFO("To", "minimumX=-2147483647;maximumX=2147483647;minimumY=-2147483647;maximumY=2147483647;minimumZ=-2147483647;maximumZ=2147483647;");
	Q_PROPERTY(GGL::Point3f Up READ up WRITE setUp DESIGNABLE true USER true)
	Q_CLASSINFO("Up", "minimumX=-2147483647;maximumX=2147483647;minimumY=-2147483647;maximumY=2147483647;minimumZ=-2147483647;maximumZ=2147483647;");
	Q_PROPERTY(bool IsShowInfo READ isShowInfo WRITE setIsShowInfo DESIGNABLE true USER true)
*/
public:
	enum CameraType
	{
		Orthogonal,
		Perspective,
	};

	enum MotionType
	{
		Rotate,
		Zoom,
		Pan,
		None,
	};

public:
	void openEditDialog();

signals:
	void onOpenEditDialog(Camera *);
	void onPropertyChanged(Camera *);
	void onCameraMotion(Camera *);

public:


private:

	QString m_cameraName;

	float m_fov;

	float m_farPlane;
	float m_nearPlane;

	GGL::Point3f m_from;
	GGL::Point3f m_to;
	GGL::Point3f m_up;

	bool m_isShowInfo;

	bool m_isDraw;

	bool m_isLightOn; 


public:

	QString & cameraName()  {return m_cameraName;};
	void setCameraName(const QString &cameraName);

	float & fov()  {return m_fov;};
	void setFov(const float fov);

	float & farPlane()  {return m_farPlane;};
	void setFarPlane(const float farPlane);

	float & nearPlane() {return m_nearPlane;};
	void setNearPlane(const float nearPlane);

	GGL::Point3f & from() {return m_from;};
	void setFrom(const GGL::Point3f &from);

	GGL::Point3f & to()  {return m_to;};
	void setTo(const GGL::Point3f &to);

	GGL::Point3f & up()  {return m_up;};
	void setUp(const GGL::Point3f &up);

	bool & isShowInfo(){return m_isShowInfo;};
	void setIsShowInfo(const bool isShowInfo);

	bool & isDraw(){return m_isDraw;};
	void setIsDraw(const bool isDraw);

	bool & isLightOn(){return m_isLightOn;};
	void setIsLightOn(const bool isLightOn);


protected:
	int oldX;
	int oldY;

	bool isDragging;
	enum MotionType motionType;



public:
	virtual void onMouseMove(int x,int y)=0;
	virtual void onMouseWheel(float notch)=0;
	virtual QString getCameraInfo()=0;
	virtual enum CameraType getCameraType()=0;
	virtual void lookAt(GGL::Point3f &_from,GGL::Point3f &_to)=0;
	virtual void setCamera(float width,float height,float ratio)=0;
	virtual void setCameraForSelection(int x,int y,int selectionWidth,int selectionHeight,float width,float height,float ratio)=0;
        virtual void save(const QString &filename)=0;
        virtual void load(const QString &filename)=0;

	virtual Light * getCameraLight(){ return 0; };

	void onDragBegin(int x,int y,enum MotionType mtype)
	{
		oldX=x;
		oldY=y;
		isDragging=true;
		motionType=mtype;
	};

	void onDragStop()
	{
		oldX=0;
		oldY=0;
		isDragging=false;
		motionType=None;
	}

	Camera(QObject* parent = 0);
	Camera(QString _name,QObject* parent = 0);
	virtual ~Camera(void);
};
