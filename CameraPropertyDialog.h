#pragma once
#include "PropertyDialog.h"
#include "CameraPropertyModelDelegate.h"

class CameraPropertyModel;
class Camera;



class CameraPropertyDialog:public PropertyDialog
{
	Q_OBJECT
public:
	CameraPropertyDialog(QString title,QWidget *parent=0);
	~CameraPropertyDialog(void);
		 void addModel(QAbstractItemModel* propertyObject);

	public slots:
		void onCameraPropertyChanged(Camera *);

private:
	CameraPropertyModelDelegate cameraPropertyModelDelegate;
};
