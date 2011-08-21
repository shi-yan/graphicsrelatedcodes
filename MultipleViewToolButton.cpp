#include "MultipleViewToolButton.h"
#include <QtGui/QPainter>

MultipleViewToolButton::MultipleViewToolButton(QWidget *parent):QPushButton(parent)
{/*
	setStyleSheet(QApplication::translate("MainWindow", "QPushButton {width:14px;height:14px;\n"
"    background: transparent; \n"
"	background-color: rgb(54, 66, 65,150);\n"
"border-style: outset;\n"
"     border-width: 1px;\n"
"border-color: black;\n"
"     border-radius: 4px;\n"
"     font: bold 14px;\n"
"     padding: 4px;\n"
" }\n"
"\n"
"QPushButton:hover {\n"
"     \n"
"	background-color: rgb(247, 129, 31,200);\n"
"border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"border-color: black;\n"
"     font: bold 14px;\n"
"     padding: 4px;\n"
" }\n"
"\n"
"QPushButton:pressed {\n"
"     \n"
"	background-color: rgb(54, 66, 65,200);\n"
"border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"border-color: black;\n"
"     font: bold 14px;\n"
"     padding: 4px;\n"
" }\n"
"\n"
"\n"
"QPushButton:checked {\n"
"     \n"
"	background-color: rgb(247, 129, 31,150);\n"
"border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"border-color: black;\n"
"     font: bold 14px;\n"
"     padding: 4px;\n"
" }", 0, QApplication::UnicodeUTF8));*/

	setStyleSheet(tr("QPushButton{background:transparent;height:29px;}"));
}

MultipleViewToolButton::~MultipleViewToolButton(void)
{
}

void MultipleViewToolButton::paintEvent(QPaintEvent *event)
{
QPainter painter(this);

if(underMouse())
{
	painter.drawImage(QRect(0,0,29,29),QImage("MultiViewToolButtonbgHover.png"));

	icon().paint(&painter,QRect(0,0,29,29));
}
else if(isChecked())
{
	painter.drawImage(QRect(0,0,29,29),QImage("MultiViewToolButtonbgChecked.png"));

	icon().paint(&painter,QRect(0,0,29,29));
}
else
{
	painter.drawImage(QRect(0,0,29,29),QImage("MultiViewToolButtonbg.png"));

	icon().paint(&painter,QRect(0,0,29,29));
}
painter.end();
}