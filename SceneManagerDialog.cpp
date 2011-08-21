#include "SceneManagerDialog.h"

SceneManagerDialog::SceneManagerDialog(QString &title,QWidget *parent):PropertyDialog(title, parent)
{
	/*TempColor one;
	TempColor two;

	one.a=255;
	one.r=244;
	one.g=222;
	one.b=255;

	two.a=255;
	two.r=234;
	two.g=191;
	two.b=255;

	setRowColors(one,two);*/


	
}

SceneManagerDialog::~SceneManagerDialog(void)
{
}

void SceneManagerDialog::addModel(QAbstractItemModel* modelObject)
{
	if(propertyEditor->model())
	{
	}

	QItemSelectionModel *m = propertyEditor->selectionModel();
	
		propertyEditor->setModel(modelObject);
	
	if(m)
		m->deleteLater();
}