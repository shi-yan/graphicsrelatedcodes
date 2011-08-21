#pragma once
#include "PropertyDialog.h"

class SceneManagerDialog:public PropertyDialog
{
public:
	SceneManagerDialog(QString &title,QWidget *parent=0);
	~SceneManagerDialog(void);

	void addModel(QAbstractItemModel* modelObject);
};
