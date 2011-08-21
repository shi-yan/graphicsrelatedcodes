#include "CameraPropertyModel.h"
#include "UserCameraManager.h"
#include "OrthogonalCamera.h"
CameraPropertyModel::CameraPropertyModel(void):QAbstractItemModel(),cameraID(-8)
{
}

CameraPropertyModel::~CameraPropertyModel(void)
{
}


CameraPropertyModel::CameraPropertyModel(int _cameraID):QAbstractItemModel(),cameraID(_cameraID)
{

}

/*
		CAMERANAME,
		FOV,
		FARPLANE,
		NEARPLANE,
		FROM,
		FROMX,
		FROMY,
		FROMZ,
		TO,
		TOX,
		TOY,
		TOZ,
		UP,
		UPX,
		UPY,
		UPZ,
		ISSHOWINFO,
		ISDRAW,
		SCALE,
*/


bool CameraPropertyModel::setData ( const QModelIndex & index, const QVariant & value, int role )   
{

   if (!index.isValid())
        return false;

	if (role != Qt::EditRole)
        return false;

	Camera *camera=UserCameraManager::getSingleton().getCameraByID(cameraID);

	if(camera)
	if(index.column()==1)
	{
		switch(index.internalId())
		{
		case CAMERANAME:
			camera->setCameraName(value.toString());
			break;
		case FOV:
		case FARPLANE:
			camera->setFarPlane(value.toFloat());
			break;
		case NEARPLANE:
			camera->setNearPlane(value.toFloat());
			break;
		case FROMX:
			camera->setFrom(GGL::Point3f(value.toFloat(),camera->from().Y(),camera->from().Z()));
			break;
		
		case FROMY:
			camera->setFrom(GGL::Point3f(camera->from().X(),value.toFloat(),camera->from().Z()));
			break;
		case FROMZ:
			camera->setFrom(GGL::Point3f(camera->from().X(),camera->from().Y(),value.toFloat()));
			break;

		case TOX:
			camera->setTo(GGL::Point3f(value.toFloat(),camera->from().Y(),camera->from().Z()));
			break;
		case TOY:
					camera->setTo(GGL::Point3f(camera->from().X(),value.toFloat(),camera->from().Z()));
			break;
		case TOZ:
					camera->setTo(GGL::Point3f(camera->from().X(),camera->from().Y(),value.toFloat()));
			break;

		case UPX:
			camera->setUp(GGL::Point3f(value.toFloat(),camera->from().Y(),camera->from().Z()));
			break;
		case UPY:
				camera->setUp(GGL::Point3f(camera->from().X(),value.toFloat(),camera->from().Z()));
			break;
		case UPZ:
					camera->setUp(GGL::Point3f(camera->from().X(),camera->from().Y(),value.toFloat()));
			break;
		case SCALE:

			(static_cast<OrthogonalCamera*>(camera))->setScale(value.toFloat());
	break;
		case ISSHOWINFO:
			camera->setIsShowInfo(value.toBool());
			break;
		case ISDRAW:
			camera->setIsDraw(value.toBool());
			
			break;
		}
	}
	emit dataChanged(index,index);
	return true;
}

Qt::ItemFlags CameraPropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;



	if(index.column()==1 && !(index.internalId()==FROM || index.internalId()==TO || index.internalId()==UP))
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}

	return Qt::NoItemFlags;
}

QModelIndex CameraPropertyModel::index ( int row, int column, const QModelIndex & parent ) const
{
	//printf("#%d,%d#\n",row,column);
    if (!hasIndex(row, column, parent))
        return QModelIndex();

	Camera *camera=UserCameraManager::getSingleton().getCameraByID(cameraID);

    if (!parent.isValid())
	{
		
			switch(row)
			{
			case 0:
				return createIndex(row,column,CAMERANAME);
			case 1:
				return createIndex(row,column,FOV);
			case 2:
				return createIndex(row,column,FARPLANE);
			case 3:
				return createIndex(row,column,NEARPLANE);
			case 4:
				return createIndex(row,column,FROM);
			case 5:
				return createIndex(row,column,TO);
			case 6:
				return createIndex(row,column,UP);
			case 7:
				return createIndex(row,column,ISSHOWINFO);
			case 8:
				return createIndex(row,column,ISDRAW);
			case 9:
				return createIndex(row,column,SCALE);
			}
		
	}
	else
	{
		if((int)parent.internalId()==FROM)
		{
			switch(row)
			{
			case 0:
				return createIndex(row,column,FROMX);
			case 1:
				return createIndex(row,column,FROMY);
			case 2:
				return createIndex(row,column,FROMZ);
			}
		}
		else if(parent.internalId()==TO)
		{
			switch(row)
			{
			case 0:
				return createIndex(row,column,TOX);
			case 1:
				return createIndex(row,column,TOY);
			case 2:
				return createIndex(row,column,TOZ);
			}
		}
		else if(parent.internalId()==UP)
		{
			switch(row)
			{
			case 0:
				return createIndex(row,column,UPX);
			case 1:
				return createIndex(row,column,UPY);
			case 2:
				return createIndex(row,column,UPZ);
			}
		}
	}

	return QModelIndex();
}

QModelIndex CameraPropertyModel::parent ( const QModelIndex & index ) const
{
	
    if (!index.isValid())
        return QModelIndex();


	switch(index.internalId())
	{
	case FROMX:
	case FROMY:
	case FROMZ:
		return createIndex(4,0,FROM);
	case TOX:
	case TOY:
	case TOZ:
		return createIndex(5,0,TO);
	case UPX:
	case UPY:
	case UPZ:
		return createIndex(6,0,UP);
	}

	return QModelIndex();
}

int CameraPropertyModel::rowCount ( const QModelIndex & parent  ) const 
{
	Camera *camera=UserCameraManager::getSingleton().getCameraByID(cameraID);

	if(camera)
	{
		if (!parent.isValid())
		{
			switch(camera->getCameraType())
			{
			case Camera::Perspective:

				return 9; 
				break;
			case Camera::Orthogonal:

				return 10;
				break;
			}		
			return 0;
		}
		else
		{
			if(parent.internalId()==FROM || parent.internalId()==TO || parent.internalId()==UP)
			{
				return 3;
			}
			else
				return 0;
		}
	}
	else
		return 0;
}

QVariant CameraPropertyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch(section){
			case 0:
		return QVariant(QString("Property Name"));
		break;
			case 1:
				return QVariant(QString("Value"));
				break;
		}
	}

	return QVariant();
}

int CameraPropertyModel::columnCount ( const QModelIndex & parent ) const  
{
	return 2;
}

/*
	QString m_cameraName;

	float m_fov;

	float m_farPlane;
	float m_nearPlane;

	GGL::Point3f m_from;
	GGL::Point3f m_to;
	GGL::Point3f m_up;

	bool m_isShowInfo;

	bool m_isDraw;

*/

QVariant CameraPropertyModel::data ( const QModelIndex & index, int role  ) const  
{
	if (!index.isValid())
        return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

	Camera *camera=UserCameraManager::getSingleton().getCameraByID(cameraID);

	if(camera)

	if(index.column()==0)
	{
		switch(index.internalId())
		{
		case CAMERANAME:
			return QString("Camera Name:");
		case FOV:
			return QString("Fov:");
		case FARPLANE:
			return QString("Far Plane:");
		case NEARPLANE:
			return QString("Near Plane:");
		case FROM:
			return QString("From:");
		case FROMX:
			return QString("X:");
		case FROMY:
			return QString("Y:");
		case FROMZ:
			return QString("Z:");
		case TO:
			return QString("To:");
		case TOX:
			return QString("X:");
		case TOY:
			return QString("Y:");
		case TOZ:
			return QString("Z:");
		case UP:
			return QString("Up:");
		case UPX:
			return QString("X:");
		case UPY:
			return QString("Y:");
		case UPZ:
			return QString("Z:");
		case SCALE:
			return QString("Scale:");
		case ISSHOWINFO:
			return QString("Is Show Info:");
		case ISDRAW:
			return QString("Is Draw");
		}
	}
	else if(index.column()==1)
	{
		switch(index.internalId())
		{
		case CAMERANAME:
			return camera->cameraName();
		case FOV:
			return camera->fov();
		case FARPLANE:
			return camera->farPlane();
		case NEARPLANE:
			return camera->nearPlane();
		case FROM:
			return QString("[%1,%2,%3]").arg(camera->from().X()).arg(camera->from().Y()).arg(camera->from().Z());
		case FROMX:
			return camera->from().X();
		case FROMY:
			return camera->from().Y();
		case FROMZ:
			return camera->from().Z();;
		case TO:
			return QString("[%1,%2,%3]").arg(camera->to().X()).arg(camera->to().Y()).arg(camera->to().Z());
		case TOX:
			return camera->to().X();
		case TOY:
			return camera->to().X();
		case TOZ:
			return camera->to().Z();
		case UP:
			return QString("[%1,%2,%3]").arg(camera->up().X()).arg(camera->up().Y()).arg(camera->up().Z());
		case UPX:
			return camera->up().X();
		case UPY:
			return camera->up().Y();
		case UPZ:
			return camera->up().Z();
		case SCALE:
			{
				if(camera->getCameraType()==Camera::Orthogonal)
				{
					return ((OrthogonalCamera*)camera)->getScale();
				}
				return QVariant();
			}
		case ISSHOWINFO:
			return camera->isShowInfo();
		case ISDRAW:
			return camera->isDraw();					
		}
	}

		return QVariant();
}