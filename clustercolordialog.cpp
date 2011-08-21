#include "clustercolordialog.h"
#include "clustercolorscheme.h"
#include <QColorDialog>
#include <QFileDialog>

ClusterColorDialog::ClusterColorDialog(const QString &title,QWidget *parent):DockWidget(title,parent),currentClusterIndex(0)
{
    setObjectName(QString::fromUtf8("Cluster Color Dialog"));
    dockWidgetContents = new QWidget(this);
    dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));

    verticalLayout = new QVBoxLayout(dockWidgetContents);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

    clusterListWidget = new QListWidget(dockWidgetContents);
    clusterListWidget->setObjectName(QString::fromUtf8("clusterListWidget"));

    verticalLayout->addWidget(clusterListWidget);

    setColorPushButton = new QPushButton(dockWidgetContents);
    setColorPushButton->setObjectName(QString::fromUtf8("setColorPushButton"));

    verticalLayout->addWidget(setColorPushButton);

    savePushButton = new QPushButton(dockWidgetContents);
    savePushButton->setObjectName(QString::fromUtf8("savePushButton"));

    verticalLayout->addWidget(savePushButton);

    loadPushButton = new QPushButton(dockWidgetContents);
    loadPushButton->setObjectName(QString::fromUtf8("loadPushButton"));

    verticalLayout->addWidget(loadPushButton);

          setColorPushButton->setText(QApplication::translate("clusterListWidget", "Set Color", 0, QApplication::UnicodeUTF8));
          savePushButton->setText(QApplication::translate("clusterListWidget", "Save ", 0, QApplication::UnicodeUTF8));
          loadPushButton->setText(QApplication::translate("clusterListWidget", "Load", 0, QApplication::UnicodeUTF8));
          setWidget(dockWidgetContents);
    QMetaObject::connectSlotsByName(this);

    connect(&ClusterColorScheme::getSingleton(),SIGNAL(clusterColorChanged()),this,SLOT(onClusterColorChanged()));

    connect(clusterListWidget,SIGNAL(currentRowChanged(int)),this,SLOT(onRowChanged(int)));

    connect(setColorPushButton,SIGNAL(clicked()),this,SLOT(onSetColorClicked()));

    connect(savePushButton,SIGNAL(clicked()),this,SLOT(onSave()));
    connect(loadPushButton,SIGNAL(clicked()),this,SLOT(onLoad()));
}

void ClusterColorDialog::onSave()
{
  QString fileName = QFileDialog::getSaveFileName(this,
        tr("Open Color Scheme"), "./", tr("Color Scheme Files (*.cs)"));
  if(!fileName.isEmpty())
    ClusterColorScheme::getSingleton().save(fileName);
}

void ClusterColorDialog::onLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Open Color Scheme"), "./", tr("Color Scheme Files (*.cs)"));
    if(!fileName.isEmpty())
    ClusterColorScheme::getSingleton().load(fileName);
    onClusterColorChanged();
}

void ClusterColorDialog::onSetColorClicked()
{
    QColorDialog cd;
    QColor c=cd.getColor();

    int id=currentClusterIndex;

    ClusterColorScheme::getSingleton()[id].r=c.red();
    ClusterColorScheme::getSingleton()[id].g=c.green();
    ClusterColorScheme::getSingleton()[id].b=c.blue();

    onClusterColorChanged();
}

void ClusterColorDialog::onRowChanged(int id)
{
     ClusterColor c=ClusterColorScheme::getSingleton()[id];
    QPalette p(setColorPushButton->palette());
      // Set background colour to black
      p.setColor(QPalette::Background, QColor(c.r, c.g, c.b, 255));
     setColorPushButton-> setPalette(p);

     currentClusterIndex=id;
}

void ClusterColorDialog::onClusterColorChanged()
{
          clusterListWidget->setSortingEnabled(false);
          clusterListWidget->clear();

          int colorSize=ClusterColorScheme::getSingleton().getClusterColorSize();

          for(int i=0;i<colorSize;++i)
          {

              ClusterColor c=ClusterColorScheme::getSingleton()[i];
              QBrush brush(QColor(c.r, c.g, c.b, 255));
                    brush.setStyle(Qt::SolidPattern);
                    QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(clusterListWidget);
                    __qlistwidgetitem->setBackground(brush);
          __qlistwidgetitem->setText(QApplication::translate("clusterListWidget", QString("Cluster %1").arg(i).toStdString().c_str(), 0, QApplication::UnicodeUTF8));
         }
};
