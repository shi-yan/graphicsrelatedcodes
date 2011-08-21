#include "MenuItemWithOptionButton.h"

MenuItemWithOptionButton::MenuItemWithOptionButton(QString text,QWidget *parent):QWidget(parent)
{
	    horizontalLayout = new QHBoxLayout(this);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
   horizontalLayout->setSpacing(2);
        horizontalLayout->setMargin(0);     
		majorButton = new QPushButton(this);
        majorButton->setObjectName(QString::fromUtf8("pushButton"));
		majorButton->setText(text);
        horizontalLayout->addWidget(majorButton);

        optionButton = new QToolButton(this);
        optionButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(optionButton);

		      QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(majorButton->sizePolicy().hasHeightForWidth());
        majorButton->setSizePolicy(sizePolicy);

		optionButton->setText(tr("..."));
		setStyleSheet(tr(
			" QPushButton {\n"
"	color: rgb(174, 182, 177);\n"
"     padding: 2px 25px 2px 20px;\n"
"     border: 1px solid transparent; /* reserve space for selection border */\n"
" }\n"
"\n"
" QPushButton:hover {\n"
"background: rgb(51, 114, 135);\n"
"	color: rgb(255, 255, 255);\n"
"     \n"
" }\n"
"\n"

" QToolButton {width:16px;\n"
"	color: rgb(174, 182, 177);\n"
"     padding: 2px 2px 2px 2px;\n"
"     border: 1px solid transparent; /* reserve space for selection border */\n"
" }\n"
"\n"
" QToolButton:hover {\n"
"background: rgb(51, 114, 135);\n"
"	color: rgb(255, 255, 255);\n"
"     \n"
" }\n"
"\n"		
			));

		connect(majorButton,SIGNAL(clicked()),this,SLOT(onMajorButtonClicked()));
		connect(optionButton,SIGNAL(clicked()),this,SLOT(onOptionButtonClicked()));

  }
void MenuItemWithOptionButton::onMajorButtonClicked()
{
	emit majorButtonClicked();
}

void MenuItemWithOptionButton::onOptionButtonClicked()
{
	emit optionButtonClicked();
}


MenuItemWithOptionButton::~MenuItemWithOptionButton(void)
{
}

MenuItemWithOptionButtonAction::MenuItemWithOptionButtonAction(QObject *parent):QWidgetAction(parent)
{
}

QWidget * MenuItemWithOptionButtonAction::createWidget ( QWidget * parent )
{
	MenuItemWithOptionButton *menuItem=new MenuItemWithOptionButton(text(),parent);

	connect( menuItem,SIGNAL(majorButtonClicked()),this,SLOT(onMajorButtonClicked()));
	connect(menuItem,SIGNAL(optionButtonClicked()),this,SLOT(onOptionButtonClicked()));
	return menuItem;
}

void MenuItemWithOptionButtonAction::onMajorButtonClicked()
{
	QAction::trigger();
}

void MenuItemWithOptionButtonAction::onOptionButtonClicked()
{
	emit optionButtonTriggered();
}