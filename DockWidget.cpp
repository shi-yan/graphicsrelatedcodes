#include "DockWidget.h"
#include <QtGui/QApplication>

DockWidget::DockWidget(const QString &title,QWidget *parent):QDockWidget(title,parent)
{
	 setStyleSheet(QApplication::translate("MainWindow", " QDockWidget {\n"
"     border: 2px solid rgb(159,177,163);color:rgb(59,90,74);\n"
"\n"
"   titlebar-close-icon: url(close.png);\n"
"     titlebar-normal-icon: url(float.png);\n"
"	font:14px;\n"
"  background-color: rgb(197, 211, 194);\n"
" }\n"
"\n"
"QWidget\n"
"{color:rgb(67,80,74);\n"
" border: 1px solid rgb(220,217,228);\n"
"background-color: rgb(214,222,212);\n"
" \n"
"}\n"
"\n"
" QDockWidget::title {     text-align: left;background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(230, 234, 229, 255), stop:1 rgba(215, 222, 213, 255));padding-left:5px;}"
"\n"
" QDockWidget::close-button, QDockWidget::float-button {\n"
"      	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(230, 234, 229, 255), stop:1 rgba(215, 222, 213, 255));\n"
"border:1px solid rgb(175,190,176);\n"
"border-radius:4px;\n"
" }\n"
"\n"
" QDockWidget::close-button:hover, QDockWidget::float-button:hover {\n"
"    	background-color: qlineargradient(sprea"
                        "d:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(236, 239, 236, 255), stop:1 rgba(225, 230, 224, 255));\n"
"border:1px solid rgb(175,190,176);\n"
"border-radius:4px;\n"
" }\n"
"\n"
" QDockWidget::close-button:pressed, QDockWidget::float-button:pressed {\n"
"     padding: 1px -1px -1px 1px;\n"
" }\n"
"\n"
" QDockWidget::close-button {\n"
"     subcontrol-position: top right;\n"
"     subcontrol-origin: margin;\n"
"     position: absolute;\n"
"     top: 0px; left: 0px; bottom: 0px;right: 5px;\n"
"     width: 14px;\n"
" }\n"
"\n"
" QDockWidget::float-button {\n"
"     subcontrol-position: top right;\n"
"     subcontrol-origin: margin;\n"
"     position: absolute;\n"
"     top: 0px; left: 0px; bottom: 0px;right:22px;\n"
"     width: 14px;\n"
" }"

"QPushButton"
"{"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));"
"padding:2 2 2 2;"
"border:1px solid rgb(174,190,178);"
"border-radius:6px;"
"color:rgb(94,117,112);"
"}"

"QPushButton:hover"
"{"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229, 234, 228, 255));"

"border:1px solid rgb(174,190,178);"
"border-radius:6px;"
"color:rgb(94,117,112);"
"}"

"QPushButton:pressed"
"{"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249, 251, 249, 255));"

"border:1px solid rgb(174,190,178);"
"border-radius:6px;"
"color:rgb(94,117,112);"
"}"

"QLineEdit {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
 "    padding: 0 8px;"
  "   background: rgb(54,66,65);"
  "   selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

" QDoubleSpinBox {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
   "  padding: 0 8px;"
    " background: rgb(54,66,65);"
     "selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

 "QDoubleSpinBox::up-button {"
  "   subcontrol-origin: border;"
  "   subcontrol-position: top right; "/* position at the top right corner */

   "  width: 16px; "/* 16 + 2*1px border-width = 15px padding + 3px parent border*/

"border:none;"
 "}"

 "QCheckBox{background:transparent;border:none;}"

 "QDoubleSpinBox::up-arrow {"
"	image: url(up-arrow.png);"
 "    width: 8px;"
  "   height: 8px;"
 "}"

 "QDoubleSpinBox::up-arrow:hover {"
"image: url(up-arrow-hover.png);"
   "  width: 10px;"
  "   height: 10px;"
 "}"


 "QDoubleSpinBox::up-arrow:pressed {"
"image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

" QDoubleSpinBox::up-arrow:disabled, QDoubleSpinBox::up-arrow:off {" /* off state when value is max */
  " image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"
	
								"		   QGroupBox {"
										
										"   border: 1px solid gray;"
										"	   border-radius: 5px;"
									"		   margin-top: 1ex; /* leave space at the top for the title */"
										"   }"
										   
										"   QGroupBox::title {"
										"	   subcontrol-origin: margin;"
									"		   subcontrol-position: top center;" /* position at the top center */
									"	   padding: 0 3px;"
									"		   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
																		"		 stop: 0 #FFOECE, stop: 1 #FFFFFF);"
 "}"
										   

 "QDoubleSpinBox::down-button {"
   "  subcontrol-origin: border;"
  "   subcontrol-position: bottom right;" /* position at bottom right corner */

 "    width: 16px;"
"border:none;"
 "}"

 

 "QDoubleSpinBox::down-arrow {"
 
"	image: url(down-arrow.png);"
 "   width: 8px;"
    " height: 8px;"
 "}"

 "QDoubleSpinBox::down-arrow:hover {"
 
"	image: url(down-arrow-hover.png);"
    "width: 8px;"
   "  height: 8px;"
 "}"

" QDoubleSpinBox::down-arrow-pressed {"
 
"	image: url(down-arrow-pressed.png);"
"    width: 8px;"
"    height: 8px;"
" }"

" QDoubleSpinBox::down-arrow:disabled,"
" QDoubleSpinBox::down-arrow:off { "
 
"	image: url(down-arrow-pressed.png);"
 "   width: 8px;"
 "    height: 8px;"
" }"


" QDoubleSpinBox {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
   "  padding: 0 8px;"
    " background: rgb(54,66,65);"
     "selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

 "QDoubleSpinBox::up-button {"
  "   subcontrol-origin: border;"
  "   subcontrol-position: top right; "/* position at the top right corner */

   "  width: 16px; "/* 16 + 2*1px border-width = 15px padding + 3px parent border*/

"border:none;"
 "}"


 "QDoubleSpinBox::up-arrow {"
"	image: url(up-arrow.png);"
 "    width: 8px;"
  "   height: 8px;"
 "}"

 "QDoubleSpinBox::up-arrow:hover {"
"image: url(up-arrow-hover.png);"
   "  width: 10px;"
  "   height: 10px;"
 "}"


 "QDoubleSpinBox::up-arrow:pressed {"
"image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

" QDoubleSpinBox::up-arrow:disabled, QDoubleSpinBox::up-arrow:off {" /* off state when value is max */
  " image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

 "QDoubleSpinBox::down-button {"
   "  subcontrol-origin: border;"
  "   subcontrol-position: bottom right;" /* position at bottom right corner */

 "    width: 16px;"
"border:none;"
 "}"

 
////////////////////////


" QSpinBox {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
   "  padding: 0 8px;"
    " background: rgb(54,66,65);"
     "selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

 "QSpinBox::up-button {"
  "   subcontrol-origin: border;"
  "   subcontrol-position: top right; "/* position at the top right corner */

   "  width: 16px; "/* 16 + 2*1px border-width = 15px padding + 3px parent border*/

"border:none;"
 "}"


 "QSpinBox::up-arrow {"
"	image: url(up-arrow.png);"
 "    width: 8px;"
  "   height: 8px;"
 "}"

 "QSpinBox::up-arrow:hover {"
"image: url(up-arrow-hover.png);"
   "  width: 10px;"
  "   height: 10px;"
 "}"


 "QSpinBox::up-arrow:pressed {"
"image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

" QSpinBox::up-arrow:disabled, QDoubleSpinBox::up-arrow:off {" /* off state when value is max */
  " image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

 "QSpinBox::down-button {"
   "  subcontrol-origin: border;"
  "   subcontrol-position: bottom right;" /* position at bottom right corner */

 "    width: 16px;"
"border:none;"
 "}"

 

 "QSpinBox::down-arrow {"
 
"	image: url(down-arrow.png);"
 "   width: 8px;"
    " height: 8px;"
 "}"

 "QSpinBox::down-arrow:hover {"
 
"	image: url(down-arrow-hover.png);"
    "width: 8px;"
   "  height: 8px;"
 "}"

" QSpinBox::down-arrow-pressed {"
 
"	image: url(down-arrow-pressed.png);"
"    width: 8px;"
"    height: 8px;"
" }"

" QSpinBox::down-arrow:disabled,"
" QSpinBox::down-arrow:off { "
 
"	image: url(down-arrow-pressed.png);"
 "   width: 8px;"
 "    height: 8px;"
" }"


" QSpinBox {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
   "  padding: 0 8px;"
    " background: rgb(54,66,65);"
     "selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

 "QSpinBox::up-button {"
  "   subcontrol-origin: border;"
  "   subcontrol-position: top right; "/* position at the top right corner */

   "  width: 16px; "/* 16 + 2*1px border-width = 15px padding + 3px parent border*/

"border:none;"
 "}"


 "QSpinBox::up-arrow {"
"	image: url(up-arrow.png);"
 "    width: 8px;"
  "   height: 8px;"
 "}"

 "QSpinBox::up-arrow:hover {"
"image: url(up-arrow-hover.png);"
   "  width: 10px;"
  "   height: 10px;"
 "}"


 "QSpinBox::up-arrow:pressed {"
"image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

" QSpinBox::up-arrow:disabled, QDoubleSpinBox::up-arrow:off {" /* off state when value is max */
  " image: url(up-arrow-pressed.png);"
   "  width: 8px;"
  "   height: 8px;"
 "}"

 "QSpinBox::down-button {"
   "  subcontrol-origin: border;"
  "   subcontrol-position: bottom right;" /* position at bottom right corner */

 "    width: 16px;"
"border:none;"
 "}"


///////////////



 "QComboBox {"
  "   border: 1px solid gray;"
  "   border-radius: 3px;"
  "   padding: 1px 18px 1px 3px;"
  "   min-width: 6em;"
  "color:rgb(214,248,235);"
 "}"

 "QComboBox:editable {"
  "   background: white;"
 "}"

 "QComboBox:!editable, QComboBox::drop-down:editable {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
   "  padding: 0 8px;"
    " background: rgb(54,66,65);"
     "selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

 /* QComboBox gets the "on" state when the popup is open */
 "QComboBox:!editable:on, QComboBox::drop-down:editable:on {"
 "    border: 1px solid black;"
  "   border-radius: 6px;"
   "  padding: 0 8px;"
    " background: rgb(54,66,65);"
     "selection-background-color: rgb(62,142,183);"
"color:rgb(214,248,235);"
 "}"

 "QComboBox:on {" /* shift the text when the popup opens */
  "   padding-top: 3px;"
"     padding-left: 4px;"
 "}"

 "QComboBox::drop-down {"
 "    subcontrol-origin: padding;"
  "   subcontrol-position: top right;"
 "    width: 15px;"

  "   border-left-width: 1px;"
  "   border-left-color: darkgray;"
  "   border-left-style: solid;" /* just a single line */
  "   border-top-right-radius: 3px;" /* same radius as the QComboBox */
 "    border-bottom-right-radius: 3px;"
 "}"

" QComboBox::down-arrow {"
 "    image: url(down-arrow.png);"
" }"

 "QComboBox::down-arrow:hover {" /* shift the arrow when popup is open */
  "    image: url(down-arrow-hover.png);"
 "}"

 "QComboBox::down-arrow:on {" /* shift the arrow when popup is open */
  "    image: url(down-arrow-pressed.png);"
  "   top: 1px;"
  "   left: 1px;"
 "}"

 " QComboBox QAbstractItemView {"
"	font: 8pt \"Arial\";\n"
"	background-color: rgb(42, 55, 55);\n"
"     margin: 0px; /* some spacing around the menu */\n"
"    border: 1px solid rgb(42,55,55); \n"
"	color: rgb(174, 182, 177);\n"
"selection-background-color: rgb(51, 114, 135);"
" }"


" QComboBox QAbstractItemView::item {"
"	font: 8pt \"Arial\";\n"
"	background-color: rgb(42, 55, 55);\n"
"     margin: 0px; /* some spacing around the menu */\n"
"    border: 1px solid rgb(42,55,55); \n"
"	color: rgb(174, 182, 177);\n"
" }"




"QScrollBar:horizontal {\n"
"     border: 1px solid rgb(158,177,162);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(197, 211, 194), stop:1 rgb(204, 217, 200));\n"
"     height: 15px;\n"
"     margin: 0px 18px 0px 18px;\n"
" border-radius: 4px; \n"
"}\n"
"\n"
" QScrollBar:left-arrow:horizontal {\n"
"   \n"
"   \n"
"	image: url(scrollleft.png);\n"
" }\n"
"\n"
" QScrollBar::right-arrow:horizontal\n"
"{\n"
"	image: url(scrollright.png);\n"
"}\n"
"\n"
" QSlider::groove:horizontal {\n"
"     border: 1px solid #999999;\n"
"     height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"     background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"     margin: 2px 0;\n"
" }\n"
" QScrollBar::handle:horizontal {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));\n"
" border-r"
                        "adius: 3px;\n"
" border: 1px solid rgb(174,190,178);\n"
"     min-width: 20px;\n"
" }\n"
"\n"
" QScrollBar::handle:horizontal:hover {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229,234, 228,255));\n"
" border-radius: 3px;\n"
" border: 1px solid rgb(174,190,178);\n"
"     min-width: 20px;\n"
" }\n"
"\n"
" QScrollBar::handle:horizontal:pressed {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249,251, 249,255));\n"
" border-radius: 3px;\n"
" border: 1px solid rgb(174,190,178);\n"
"     min-width: 20px;\n"
" }\n"
"\n"
" QScrollBar::add-line:horizontal {\n"
"   border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));\n"
" border-radius: 3px;\n"
"     width: 15px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
""
                        " QScrollBar::add-line:horizontal:hover{\n"
"   border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229,234, 228,255));\n"
" border-radius: 3px;\n"
"     width: 15px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::add-line:horizontal:pressed{\n"
"   border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249,251, 249,255));\n"
" border-radius: 3px;\n"
"     width: 15px;\n"
"     subcontrol-position: right;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:horizontal {\n"
"    border: 1px solid rgb(174,190,178);\n"
"  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));\n"
" border-radius: 3px;\n"
"     width: 15px;\n"
"     subcontrol-position: left;\n"
""
                        "     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:horizontal:hover {\n"
"    border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229,234, 228,255));\n"
" border-radius: 3px;\n"
"     width: 15px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:horizontal:pressed {\n"
"    border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249,251, 249,255));\n"
" border-radius: 3px;\n"
"     width: 15px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
"     background: none;\n"
" }"





"QScrollBar:vertical {\n"
"     border: 1px solid rgb(158,177,162);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(197, 211, 194), stop:1 rgb(204, 217, 200));\n"
"     height: 15px;\n"
"     margin: 18px 0px 18px 0px;\n"
" border-radius: 4px; \n"
"}\n"
"\n"
" QScrollBar:up-arrow:vertical {\n"
"   \n"
"	image: url(scrollup.png);\n"
" }\n"
"\n"
" QScrollBar::down-arrow:vertical\n"
"{\n"
"	image: url(scrolldown.png);\n"
"}\n"
"\n"
"\n"
"\n"
" QSlider::groove:vertical {\n"
"     border: 1px solid #999999;\n"
"     height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"     background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"     margin: 2px 0;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));\n"
" border-radius: 3px;\n"
""
                        " border: 1px solid rgb(174,190,178);\n"
"     min-height: 20px;\n"
" }\n"
"\n"
" QScrollBar::handle:vertical:hover {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229,234, 228,255));\n"
" border-radius: 3px;\n"
" border: 1px solid rgb(174,190,178);\n"
"     min-height: 20px;\n"
" }\n"
"\n"
" QScrollBar::handle:vertical:pressed {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249,251, 249,255));\n"
" border-radius: 3px;\n"
" border: 1px solid rgb(174,190,178);\n"
"     min-height: 20px;\n"
" }\n"
"\n"
" QScrollBar::add-line:vertical {\n"
"   border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));\n"
" border-radius: 3px;\n"
"     height: 15px;\n"
"     subcontrol-position: bottom;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::add"
                        "-line:vertical:hover{\n"
"   border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229,234, 228,255));\n"
" border-radius: 3px;\n"
"     height: 15px;\n"
"     subcontrol-position: bottom;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::add-line:vertical:pressed{\n"
"   border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249,251, 249,255));\n"
" border-radius: 3px;\n"
"     height: 15px;\n"
"     subcontrol-position: bottom;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:vertical {\n"
"    border: 1px solid rgb(174,190,178);\n"
"  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(222, 229, 221, 255));\n"
" border-radius: 3px;\n"
"     height: 15px;\n"
"     subcontrol-position: top;\n"
"     subcontrol-"
                        "origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:vertical:hover {\n"
"    border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(249, 251, 249, 255), stop:1 rgba(229,234, 228,255));\n"
" border-radius: 3px;\n"
"     height: 15px;\n"
"     subcontrol-position: top;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
" QScrollBar::sub-line:vertical:pressed {\n"
"    border: 1px solid rgb(174,190,178);\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(202, 211, 201, 255), stop:1 rgba(249,251, 249,255));\n"
" border-radius: 3px;\n"
"     height: 15px;\n"
"     subcontrol-position: top;\n"
"     subcontrol-origin: margin;\n"
" }\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"     background: none;\n"
" }"





, 0, QApplication::UnicodeUTF8));

}

DockWidget::~DockWidget(void)
{
}
