#pragma once
#include <QtCore/QObject>
#include <vector>

#include "Camera.h"

class QMenu;

class UserCameraManager:public QObject
{
	Q_OBJECT
private:
	UserCameraManager(void);
	~UserCameraManager(void);
private:
	std::vector<Camera *> userCameraList;

public:
	static UserCameraManager & getSingleton()
	{
		static UserCameraManager obj;
		return obj;
	}

	int addCamera(Camera *);
	void removeCamera(Camera *);

	Camera * getCameraByID(int id);

	void setUserCameraMenu(QMenu &);

	std::vector<Camera *> & getCameraList();

signals:
	void onCameraAdded(int cameraID);
};
