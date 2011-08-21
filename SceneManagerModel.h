#pragma once
#include <QtCore/QAbstractItemModel>

class SceneManagerModel:public QAbstractItemModel
{
	Q_OBJECT
public:
	SceneManagerModel(void);
	~SceneManagerModel(void);
	
public:
//	bool setData ( const QModelIndex & index, const QVariant & value, int role )   ;
	QModelIndex index(int,int,const QModelIndex &) const;
	QModelIndex parent ( const QModelIndex & index ) const;
	int rowCount ( const QModelIndex & parent = QModelIndex() ) const ;
	int columnCount ( const QModelIndex & parent = QModelIndex() ) const  ;
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const  ;
	QVariant headerData(int section, Qt::Orientation orientation,int role) const;
	//Qt::ItemFlags flags(const QModelIndex &index) const;

public:
	enum ROOTNODEID
	{
		CAMERA=-1,
		LIGHT=-2,
		OBJECT=-3,
		MARTIRIAL=-4,
	};
};
