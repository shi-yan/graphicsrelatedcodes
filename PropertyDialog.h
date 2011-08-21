#pragma once
#include "DockWidget.h"
#include "TempColor.h"
#include <QTreeView>

class PropertyDialog:public DockWidget
{
	Q_OBJECT
public:
	PropertyDialog(QString &title,QWidget *parent=0);
	void setRowColors(struct TempColor &bg,struct TempColor &abg);

	virtual void addModel(QAbstractItemModel* propertyObject)=0;

virtual	~PropertyDialog(void);
protected:
	QTreeView *propertyEditor;
	struct TempColor rowbg;
	struct TempColor arowbg;

};
