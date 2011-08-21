#pragma once
#include "OrthogonalCamera.h"

class FixedOrthogonalCamera :
	public OrthogonalCamera
{
public:
	enum CameraType
	{
		Left = -1,
		Right = -2,
		Top = -3,
		Bottom = -4,
		Front =-5,
		Back =-6,
	};
public:
	FixedOrthogonalCamera(void);	
	FixedOrthogonalCamera(QString &_name);
	FixedOrthogonalCamera(enum CameraType type);
	~FixedOrthogonalCamera(void);

	void lookAt(GGL::Point3f &_from,GGL::Point3f &_to);
		
	void switchCamera(enum CameraType type);
	
	void onMouseMove(int x,int y);
 };
