#include "PropertyDialog.h"

PropertyDialog::PropertyDialog(QString &title,QWidget *parent):DockWidget(title,parent)
{
	rowbg.a=255;
	rowbg.r=255;
	rowbg.g=242;
	rowbg.b=222;

	arowbg.a=255;
	arowbg.r=255;
	arowbg.g=230;
	arowbg.b=191;

	        
	propertyEditor = new QTreeView(this);    
	propertyEditor->setObjectName(QString::fromUtf8("m_propertyEditor"));		
	propertyEditor->setAlternatingRowColors(true);
	propertyEditor->setAnimated ( true );
	propertyEditor->setRootIsDecorated ( true );

	
		
	propertyEditor->setStyleSheet(QString(
	"	QTreeView {"
"selection-color: black;"
                         "selection-background-color: blue;"
	"paint-alternating-row-colors-for-empty-area:true;"

  "show-decoration-selected: 1;"
"background-color:rgb(%1,%2,%3);"
"  alternate-background-color: rgb(%4,%5,%6);"



 "}"

 " QTreeView::item {"

 "}"

 "QTreeView::item:hover {"
 "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
" }"

" QTreeView::item:selected {"
   "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
" }"

" QTreeView::item:selected:active{"
   "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
" }"

" QTreeView::item:root:active{"
    "//background:transparent;"
" }"
).arg(rowbg.r).arg(rowbg.g).arg(rowbg.b).arg(arowbg.r).arg(arowbg.g).arg(arowbg.b));



	setWidget(propertyEditor);	
	propertyEditor->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void PropertyDialog::setRowColors(struct TempColor &bg,struct TempColor &abg)
{
	rowbg=bg;
	arowbg=abg;

			propertyEditor->setStyleSheet(QString(
	"	QTreeView {"
"selection-color: yellow;"
                         "selection-background-color: blue;"
	"paint-alternating-row-colors-for-empty-area:true;"

  "show-decoration-selected: 0;"
"background:transparent;"
"background-color:rgb(%1,%2,%3);"
"  alternate-background-color: rgb(%4,%5,%6);"



 "}"

 " QTreeView::item {"
"background:transparent;"
"background-color:green;"
"  alternate-background-color: yellow;"

 "     border: 1px solid #d9d9d9;"
 "    border-top-color: transparent;"
 "    border-bottom-color: transparent;"
 "}"

 "QTreeView::item:hover {"
 "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);"
  "   border: 1px solid #bfcde4;"
" }"

" QTreeView::item:selected {"
 "    border: 1px solid #567dbc;"
" }"

" QTreeView::item:selected:active{"
   "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
" }"

" QTreeView::item:root:active{"
   "  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);"
" }"

		


).arg(rowbg.r).arg(rowbg.g).arg(rowbg.b).arg(arowbg.r).arg(arowbg.g).arg(arowbg.b));


}

PropertyDialog::~PropertyDialog(void)
{
}
