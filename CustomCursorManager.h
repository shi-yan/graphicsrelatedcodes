#pragma once
#include <QtGui/QBitmap>
#include <QtGui/QCursor>

class CustomCursorManager
{
public:
	enum CursorType
	{
		DoubleCross,
	};

	static CustomCursorManager & getSingleton()
	{
		static CustomCursorManager obj;
		return obj;
	};

	void init()
	{
		QBitmap doubleCrossBitmap(QPixmap(QString("doublecross.png"),0,Qt::MonoOnly));

		doubleCross=QCursor(doubleCrossBitmap,doubleCrossBitmap);

	};

	QCursor & getCursor(int type)
	{
		switch(type)
		{
		case DoubleCross:
			return doubleCross;
			break;
		}
	};
private:
	
	QCursor doubleCross;

private:
	CustomCursorManager(void);
	~CustomCursorManager(void);
};
