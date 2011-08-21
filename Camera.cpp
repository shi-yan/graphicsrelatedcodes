#include "Camera.h"

Camera::Camera(QObject* parent) : QObject(parent),m_farPlane(1000.0f),m_nearPlane(0.1f),m_fov(45.0f),m_from(0.0f,0.0f,0.0f),m_to(0.0f,0.0f,0.0f),m_up(0.0f,0.0f,1.0f),isDragging(false),oldX(0),oldY(0),motionType(None),m_cameraName("Camera"),m_isShowInfo(false),m_isDraw(false),m_isLightOn(true)
{
}

Camera::Camera(QString _name,QObject* parent) : QObject(parent),m_farPlane(1000.0f),m_nearPlane(0.1f),m_fov(45.0f),m_from(0.0f,0.0f,0.0f),m_to(0.0f,0.0f,0.0f),m_up(0.0f,0.0f,1.0f),isDragging(false),oldX(0),oldY(0),motionType(None),m_cameraName(_name),m_isShowInfo(false),m_isDraw(false),m_isLightOn(true)
{
}

Camera::~Camera(void)
{
}

void Camera::openEditDialog()
{
	emit onOpenEditDialog(this);
}

	
void Camera::setCameraName(const QString &cameraName)
{
	m_cameraName=cameraName;
	emit onPropertyChanged(this);
}

	
void Camera::setFov(const float fov)
{
	m_fov=fov;
	emit onPropertyChanged(this);
}

	
void Camera::setFarPlane(const float farPlane)
{
	m_farPlane=farPlane;
	emit onPropertyChanged(this);
}


void Camera::setNearPlane(const float nearPlane)
{
	m_nearPlane=nearPlane;
	emit onPropertyChanged(this);
}
	
void Camera::setFrom(const GGL::Point3f &from)
{
	m_from=from;
	emit onPropertyChanged(this);
}

	
void Camera::setTo(const GGL::Point3f &to)
{
	m_to=to;
	emit onPropertyChanged(this);
}


void Camera::setUp(const GGL::Point3f &up)
{
	m_up=up;
	emit onPropertyChanged(this);
}

	
void Camera::setIsShowInfo(const bool isShowInfo)
{
	m_isShowInfo=isShowInfo;
	emit onPropertyChanged(this);
}

void Camera::setIsDraw(const bool isDraw)
{
	m_isDraw=isDraw;
	emit onPropertyChanged(this);
}

void Camera:: setIsLightOn(const bool isLightOn)
{
	m_isLightOn=isLightOn;
}