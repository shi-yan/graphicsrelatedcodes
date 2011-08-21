#pragma once
 #include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QHBoxLayout>
#include <QtGui/QWidgetAction>

class MenuItemWithOptionButton:public QWidget
{
	Q_OBJECT
private:
	QHBoxLayout *horizontalLayout;
	QPushButton *majorButton;
	QToolButton *optionButton;
public:
	MenuItemWithOptionButton(QString text,QWidget *parent);
	~MenuItemWithOptionButton(void);

signals:
	void majorButtonClicked();
	void optionButtonClicked();

	public slots:
		void onMajorButtonClicked();
		void onOptionButtonClicked();
};

class MenuItemWithOptionButtonAction:public QWidgetAction
{
	Q_OBJECT
public:
MenuItemWithOptionButtonAction(QObject *parent=0);
	QWidget * createWidget ( QWidget * parent );

signals:
	void optionButtonTriggered();

	public slots:
		void onMajorButtonClicked();
		void onOptionButtonClicked();

};