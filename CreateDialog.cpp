#include "CreateDialog.h"
#include <QtGui/QApplication>

CreateDialog::CreateDialog(QWidget *_parent):QDockWidget(QString("Create"),_parent)
{
			   
      setObjectName(QString::fromUtf8("create dialog"));
		
	  setWindowTitle(QString("Scene"));

       QWidget * dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
      
		setWidget(dockWidgetContents);

  
}

CreateDialog::~CreateDialog(void)
{
}
