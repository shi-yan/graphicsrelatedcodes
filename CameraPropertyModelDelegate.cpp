#include "CameraPropertyModelDelegate.h"
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>
#include "CameraPropertyModel.h"
#include <QtGui/QStyleOptionFrameV2>
#include <QtGui/QApplication>
//#include <QtGui/QStyledItemDelegatePrivate>

CameraPropertyModelDelegate::CameraPropertyModelDelegate(QObject *parent):QStyledItemDelegate(parent)
{
}

CameraPropertyModelDelegate::~CameraPropertyModelDelegate(void)
{
}

QWidget *CameraPropertyModelDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
 {	 
	 switch(index.internalId())
	 {
	 case CameraPropertyModel::CAMERANAME:
		{
			QLineEdit *editor = new QLineEdit(parent);
			return editor;	
		}
		break;
	 case CameraPropertyModel::FOV:
		 {
			 QDoubleSpinBox *editor=new QDoubleSpinBox(parent);
			 editor->setRange(0,180);
			 return editor; 
		 }
		 break;
	 case CameraPropertyModel::FARPLANE:
	 case CameraPropertyModel::NEARPLANE:		
		 {
			 QDoubleSpinBox *editor=new QDoubleSpinBox(parent);
			 editor->setRange(0,10000);
			 return editor;
		 }
		 break;
	 case CameraPropertyModel::FROMX:
	 case CameraPropertyModel::FROMY:		 		
	 case CameraPropertyModel::FROMZ:
	 case CameraPropertyModel::TOX:
	 case CameraPropertyModel::TOY:
	 case CameraPropertyModel::TOZ:
	 case CameraPropertyModel::UPX:
	 case CameraPropertyModel::UPY:
	 case CameraPropertyModel::UPZ:
		 { 
			 QDoubleSpinBox *editor=new QDoubleSpinBox(parent);
			 editor->setRange(-2147483647,2147483647);
			 return editor;
		 }
		 break;

	 case CameraPropertyModel::SCALE:
		 {
			 QDoubleSpinBox *editor=new QDoubleSpinBox(parent);
			 editor->setRange(0,2147483647);
			 return editor;
		 }
		 break;

	 case CameraPropertyModel::ISSHOWINFO:
		 { 
			 QCheckBox *editor=new QCheckBox(parent);
			 connect(editor,SIGNAL(stateChanged(int)),this,SLOT(onCheckBoxStateChanged(int)));
			 return editor;
		 }
		 break;

	 case CameraPropertyModel::ISDRAW:
		 {
			 QCheckBox *editor=new QCheckBox(parent);
			 connect(editor,SIGNAL(stateChanged(int)),this,SLOT(onCheckBoxStateChanged(int)));
			 return editor;
		 }
		 break;
	 }

	 return QStyledItemDelegate::createEditor(parent,option,index);
 }

void CameraPropertyModelDelegate::onCheckBoxStateChanged(int)
{
	   QCheckBox *editor = qobject_cast<QCheckBox *>(sender());
    emit commitData(editor);
 //   emit closeEditor(editor);

}

void CameraPropertyModelDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
 {
	 switch(index.internalId())
	 {
	 case CameraPropertyModel::CAMERANAME:	 
		 { 
			 QString value=index.model()->data(index,Qt::EditRole).toString();
			 QLineEdit *lineEdit=static_cast<QLineEdit*>(editor);
			 lineEdit->setText(value);
			 return;
		 }
		 break;
	 case CameraPropertyModel::FOV:
	 case CameraPropertyModel::FARPLANE:
	 case CameraPropertyModel::NEARPLANE:
	 case CameraPropertyModel::FROMX:
	 case CameraPropertyModel::FROMY:
	 case CameraPropertyModel::FROMZ:
	 case CameraPropertyModel::TOX:
	 case CameraPropertyModel::TOY:
	 case CameraPropertyModel::TOZ:
	 case CameraPropertyModel::UPX:
	 case CameraPropertyModel::UPY:
	 case CameraPropertyModel::UPZ:
	 case CameraPropertyModel::SCALE:
		 {
			 float value = index.model()->data(index, Qt::EditRole).toFloat();
			 QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
			 spinBox->setValue(value);
			 return;
		 }
		 break;
	 case CameraPropertyModel::ISSHOWINFO:
	 case CameraPropertyModel::ISDRAW:
		 { 
			 bool value=index.model()->data(index,Qt::EditRole).toBool();
			 QCheckBox *checkBox=static_cast<QCheckBox*>(editor);
			 checkBox->setChecked(value);
			 return;
		 }
		 break;
	 }

	 return QStyledItemDelegate::setEditorData(editor,index);
 }

void CameraPropertyModelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
 {
	 switch(index.internalId())
	 {
	 case CameraPropertyModel::CAMERANAME:	 
		 { 
			 QLineEdit *lineEdit=static_cast<QLineEdit*>(editor);
			 QString value=lineEdit->text();
			 model->setData(index,value,Qt::EditRole);
			 return;
		 }
		 break;

	 case CameraPropertyModel::FOV:
	 case CameraPropertyModel::FARPLANE:
	 case CameraPropertyModel::NEARPLANE:
	 case CameraPropertyModel::FROMX:
	 case CameraPropertyModel::FROMY:
	 case CameraPropertyModel::FROMZ:
	 case CameraPropertyModel::TOX:
	 case CameraPropertyModel::TOY:
	 case CameraPropertyModel::TOZ:
	 case CameraPropertyModel::UPX:
	 case CameraPropertyModel::UPY:
	 case CameraPropertyModel::UPZ:
	 case CameraPropertyModel::SCALE:
		 { 
			 QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
			 spinBox->interpretText();
			 int value = spinBox->value();
			 model->setData(index, value, Qt::EditRole);
			 return;
		 }
		 break;
	 case CameraPropertyModel::ISSHOWINFO:
	 case CameraPropertyModel::ISDRAW:
		 { 
			 QCheckBox *checkBox=static_cast<QCheckBox*>(editor);
			 bool value=checkBox->isChecked();
			 model->setData(index,value,Qt::EditRole);
			 return;
		 }
		 break;
	 }

	return QStyledItemDelegate::setModelData(editor,model,index);
}

void CameraPropertyModelDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }

void CameraPropertyModelDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{	 
	if(index.column() == 1)
	{
		switch(index.internalId())
		{
		case CameraPropertyModel::ISSHOWINFO:
		case CameraPropertyModel::ISDRAW:
		{
			bool isChecked = index.data().toBool();
			QStyleOptionButton checkBoxOption;
			checkBoxOption.rect = option.rect;
			checkBoxOption.state=isChecked?QStyle::State_On:QStyle::State_Off;
			QApplication::style()->drawControl (  QStyle::CE_CheckBox,&checkBoxOption,painter );
			return;
		} 
		break;
		}
		return QStyledItemDelegate::paint(painter,  option, index );
	}
	else
		return QStyledItemDelegate::paint(painter,  option, index );
}
