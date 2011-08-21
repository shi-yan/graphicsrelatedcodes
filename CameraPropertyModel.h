#pragma once
#include <QtCore/QAbstractItemModel>

class CameraPropertyModel:public QAbstractItemModel
{
	Q_OBJECT
public:
	CameraPropertyModel(void);
	CameraPropertyModel(int);
	~CameraPropertyModel(void);

private:
	int cameraID;

public:
	bool setData ( const QModelIndex & index, const QVariant & value, int role )   ;
	QModelIndex index(int,int,const QModelIndex &) const;
		QModelIndex parent ( const QModelIndex & index ) const;
		int rowCount ( const QModelIndex & parent = QModelIndex() ) const ;
		int columnCount ( const QModelIndex & parent = QModelIndex() ) const  ;
		QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const  ;
		QVariant headerData(int section, Qt::Orientation orientation,int role) const;

		int getCameraID(){return cameraID;};

public:

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

	enum POINT3FID
	{
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
		SCALE,
		ISSHOWINFO,
		ISDRAW,
	};

	Qt::ItemFlags flags(const QModelIndex &index) const;
};
