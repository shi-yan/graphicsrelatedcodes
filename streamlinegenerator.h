#ifndef STREAMLINEGENERATOR_H
#define STREAMLINEGENERATOR_H


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "DockWidget.h"


class StreamlineGenerator : public DockWidget
{
    Q_OBJECT

private:
      QWidget *dockWidgetContents;
      QVBoxLayout *verticalLayout;
      QLabel *generateStreamLineLabel;
      QSpinBox *randomStreamlineSpinBox;
      QPushButton *generateStreamlinePushButton;
      QPushButton *clearStreamlinePushButton;
      QSpacerItem *verticalSpacer;

public:
    StreamlineGenerator(QString name,QWidget *parent);
    ~StreamlineGenerator();

private slots:
    void onGenerate();
    void onClear();
};

#endif // STREAMLINEGENERATOR_H
