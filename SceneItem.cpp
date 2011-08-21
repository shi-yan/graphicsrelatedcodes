#include "SceneItem.h"

SceneItem::SceneItem(void):m_isVisable(true),m_isFreezed(false),itemName("Unnamed Scene Item"),uniqueID(-1),shadingMode(Smooth),m_isSelected(false)
{

}


SceneItem::SceneItem(QString &name):m_isVisable(true),m_isFreezed(false),itemName(name),uniqueID(-1),shadingMode(Smooth),m_isSelected(false)
{

}

SceneItem::~SceneItem(void)
{
}