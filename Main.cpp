#include "Scene.h"
#include "MainWindow.h"

#include <QtGui/QPlastiqueStyle>

#include "VectorField.h"
//#include "GraphicsViewBackground.h"
//#include "WidgetScene.h"


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
	QApplication::setStyle(new QPlastiqueStyle);
    MainWindow mainWindow;
    mainWindow.showMaximized();
    return app.exec();
}