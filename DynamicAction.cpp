#include "DynamicAction.h"

DynamicAction::DynamicAction(QObject *parent):QAction(parent)
{
	connect(this,SIGNAL(triggered()),this,SLOT(onBaseTriggered()));
}

DynamicAction::~DynamicAction(void)
{
}

void DynamicAction::onBaseTriggered()
{
	emit triggered(this);
}
