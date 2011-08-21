#ifndef AUTOSEEDINGDIALOG_H
#define AUTOSEEDINGDIALOG_H

#include "DockWidget.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class AutoSeedingDialog:public DockWidget
{
    Q_OBJECT

    QVBoxLayout *verticalLayout;
    QPushButton *generateBoundaryPushButton;
    QCheckBox *shouldDrawCheckBox;
    QPushButton *preprocessPushButton;
    QPushButton *generateStreamlinePushButton;
    QPushButton *generateStreamSurfacePushButton;
    QSpacerItem *verticalSpacer;
    QWidget *content;
public:
    AutoSeedingDialog(const QString &title,QWidget *parent=0);

public slots:
    void onCreateBoundary();
};

#endif // AUTOSEEDINGDIALOG_H
