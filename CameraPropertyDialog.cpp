#include "CameraPropertyDialog.h"
#include "CameraPropertyModel.h"
#include "CameraPropertyModelDelegate.h"
#include "UserCameraManager.h"


CameraPropertyDialog::CameraPropertyDialog(QString title,QWidget *parent):PropertyDialog(title,parent)
{
		propertyEditor->setItemDelegate(&cameraPropertyModelDelegate);

	}

CameraPropertyDialog::~CameraPropertyDialog(void)
{
}


void CameraPropertyDialog::onCameraPropertyChanged(Camera *)
{
	propertyEditor->update();
}


void CameraPropertyDialog::addModel(QAbstractItemModel* modelObject)

{
	if(propertyEditor->model())
	{
		int oldCameraID=(static_cast<CameraPropertyModel*>(propertyEditor->model()))->getCameraID();
		Camera *oldCamera=UserCameraManager::getSingleton().getCameraByID(oldCameraID);
		if(oldCamera)
		{
			disconnect(oldCamera,SIGNAL(onCameraMotion(Camera*)),this,SLOT(onCameraPropertyChanged(Camera *)));
		}
	}

	QItemSelectionModel *m = propertyEditor->selectionModel();
	Camera *camera=UserCameraManager::getSingleton().getCameraByID((static_cast<CameraPropertyModel*>(modelObject))->getCameraID());
	if(camera)
	{
		propertyEditor->setModel(modelObject);
		connect(camera,SIGNAL(onCameraMotion(Camera*)),this,SLOT(onCameraPropertyChanged(Camera *)));
	}
	if(m)
		m->deleteLater();
}