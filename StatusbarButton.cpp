#include "StatusbarButton.h"

StatusbarButton::StatusbarButton(QWidget *parent):QPushButton(parent)
{
	setStyleSheet(tr(
			"QPushButton{\n"
"	background-color: rgb(91, 117, 106);\n"
"\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"     border-color:black;\n"
"color: rgb(166,177,174);\n"
"     font: 10px;\n"
"     min-width: 80px;padding:100px 108px 1px 18px; height: 10px;\n"
"     padding: 2px;\n"
" }\n"
"\n"

"QPushButton:pressed {\n"
"	background-color: rgb(59, 90, 74);\n"
"\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"     border-color:black;\n"
"color: rgb(255,255,255);\n"
"     font: 10px;\n"
"     min-width: 80px;padding:100px 108px 1px 18px;height: 10px;\n"
"     padding: 2px;\n"
" }"

"QPushButton:checked{\n"
"	background-color: rgb(255, 135, 119);\n"
"\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"     border-color:black;\n"
"color: rgb(255,255,255);\n"
"     font: 10px;\n"
"     min-width: 80px;padding:100px 108px 1px 18px;height: 10px;\n"
"     padding: 2px;\n"
" }"

"QPushButton:hover{\n"
"	background-color: rgb(104, 135, 119);\n"
"\n"
"     border-style: outset;\n"
"     border-width: 1px;\n"
"     border-radius: 4px;\n"
"     border-color:black;\n"
"color: rgb(255,255,255);\n"
"     font: 10px;\n"
"     min-width: 80px;padding:100px 108px 1px 18px;height: 10px;\n"
"     padding: 2px;\n"
" }"
			
			
			));
}

StatusbarButton::~StatusbarButton(void)
{
}
