#include "SceneManagerModel.h"
#include "UserCameraManager.h"

SceneManagerModel::SceneManagerModel(void)
{
}

SceneManagerModel::~SceneManagerModel(void)
{
}
/*
bool SceneManagerModel::setData ( const QModelIndex & index, const QVariant & value, int role )   
{
	return false;
}*/

QModelIndex SceneManagerModel::index( int row, int column, const QModelIndex & parent ) const
{
	//printf("%d,%d\n",row,column);
	 if (!hasIndex(row, column, parent))
         return QModelIndex();

	 if (!parent.isValid())
	 {
		 return createIndex(row,column,CAMERA);
	 }
	 else
	 {
		 if(parent.internalId()==CAMERA)
		 {
			 return createIndex(row,column,row);
		 }
		else
			return QModelIndex();
	 }

}

QModelIndex SceneManagerModel::parent ( const QModelIndex & index ) const
{
	if(index.internalId()==CAMERA)
	{
		return QModelIndex();
	}
	else
		return createIndex(0,0,CAMERA);
		
}

int SceneManagerModel::rowCount ( const QModelIndex & parent ) const 
{	  
	if (parent.column() > 0)
         return 0;

	if(!parent.isValid())
	{
		return 1;
	}
	else
	{
		if(parent.internalId()==CAMERA)
			return UserCameraManager::getSingleton().getCameraList().size();
		else
			return 0;
	}
}

int SceneManagerModel::columnCount ( const QModelIndex & parent  ) const  
{
	return 2;
}

QVariant SceneManagerModel::data ( const QModelIndex & index, int role  ) const  
{
	if (!index.isValid())
        return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

	if(index.internalId()==CAMERA)
	{
		return QString("Camera");
	}
	else
	{
		Camera *camera=UserCameraManager::getSingleton().getCameraByID(index.row());
		if(camera)
		{
			if(index.column()==0)
			{
				return camera->cameraName();
			}
			else if(index.column()==1)
			{
				return index.row();
			}
		}
		else
			return QVariant();
	}

	return QVariant();
}

QVariant SceneManagerModel::headerData(int section, Qt::Orientation orientation,int role) const
{    
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch(section)
		{		
		case 0:
			return QVariant(QString("Object Name"));
			break;	
		case 1:
			return QVariant(QString("Options"));			
			break;
		}
	}

	return QVariant();
}
/*
Qt::ItemFlags SceneManagerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;


	if(index.column()==1 )
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}

	return Qt::NoItemFlags;
}*/