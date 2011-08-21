#pragma once
#include <QtCore/QObject>
#include "Box3.h"

class Camera;

class SceneItem:public QObject
{
	Q_OBJECT
public:
	enum ShadingMode
	{
		Facet,
		Smooth,
		WireFrame,
		Ghosted,
		Locked,
		Toon,
	};

	enum SelectionRenderMode
	{
		Points,
		Lines,
		Facets,
		Object,
	};

	enum SelectionRenderType
	{
		Stencil,
		ColorCode,
	};

public:
	SceneItem(void);
	SceneItem(QString &name);
	virtual ~SceneItem(void);

	bool isVisable()
	{
		return m_isVisable;
	}
	
	bool isFreezed()
	{
		return m_isFreezed;
	}

	bool isShowWireFrame()
	{
		return m_isShowWireFrame;
	}

	QString getItemName()
	{
		return itemName;
	}

	int getUniqueID()
	{
		return uniqueID;
	}

	virtual void draw(int mode=0,Camera *currentCamera=0)=0;
	virtual void drawForSelection(int mode=Object,int type=Stencil,unsigned int ID=0)=0;

	void setVisable(bool _isVisable)
	{
		m_isVisable=_isVisable;
	};

	void setFreezed(bool _isFreezed)
	{
		m_isFreezed=_isFreezed;
	};

	void setShowWireFrame(bool _isShowWireFrame)
	{
		m_isShowWireFrame=_isShowWireFrame;
	};

	void select()
	{
		m_isSelected=true;
	};

	bool isSelected()
	{
		return m_isSelected;
	};

	void unselect()
	{
		m_isSelected=false;
	};

	virtual void updateBoundingBox()=0;

	GGL::Box3f getBoundingBox()
	{
		return m_boundingBox;
	};

private:
	bool m_isVisable;
	bool m_isFreezed;
	bool m_isShowWireFrame;
	QString itemName;
	bool m_isSelected;



	int uniqueID;

protected:
	enum ShadingMode shadingMode;

	GGL::Box3f m_boundingBox;

};
