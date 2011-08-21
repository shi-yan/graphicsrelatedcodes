#ifndef CLUSTERCOLORDIALOG_H
#define CLUSTERCOLORDIALOG_H
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "DockWidget.h"

class ClusterColorDialog : public DockWidget
{
    Q_OBJECT

private:
    QVBoxLayout *verticalLayout;
    QListWidget *clusterListWidget;
    QPushButton *setColorPushButton;
    QPushButton *savePushButton;
    QPushButton *loadPushButton;
    QWidget *dockWidgetContents;

    int currentClusterIndex;

public:
    ClusterColorDialog(const QString& title,QWidget *parent=0);

public slots:
    void onClusterColorChanged();
    void onRowChanged(int);
    void onSetColorClicked();
    void onSave();
    void onLoad();


signals:
    void colorChanged(int id,int r,int g,int b);
};

#endif // CLUSTERCOLORDIALOG_H
