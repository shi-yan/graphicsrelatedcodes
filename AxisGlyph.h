#pragma once
#include <QtOpenGL/QGLWidget>
#include "Point3.h"

class AxisGlyph:public QObject
{
	Q_OBJECT
public:
	enum AxisOn
	{
		MOVE_X,
		MOVE_Y,
		MOVE_Z,
		MOVE_XY,
		MOVE_YZ,
		MOVE_XZ,

		ROTATE_X,
		ROTATE_Y,
		ROTATE_Z,
		ROTATE_SCREEN,

		SCALE_X,
		SCALE_Y,
		SCALE_Z,

		SCALE_XY,
		SCALE_YZ,
		SCALE_XZ,

		SCALE_ALL,
		NONE,
	};

	enum AxisType
	{
		SCALE,
		MOVE,
		ROTATE,
		COMBO,
	};

private:
	enum AxisType currentType;
	enum AxisOn currentOn;

public:
	void setType(enum AxisType type)
	{
		currentType=type;
	};

	enum AxisType getType()
	{
		return currentType;
	};

	enum AxisOn getOn()
	{
		return currentOn;
	};

signals:

	void axisGlyphMoveXOn();
	void axisGlyphMoveYOn();
	void axisGlyphMoveZOn();
	void axisGlyphMoveXYOn();
	void axisGlyphMoveYZOn();
	void axisGlyphMoveXZOn();

	void axisGlyphRotateXOn();
	void axisGlyphRotateYOn();
	void axisGlyphRotateZOn();
	void axisGlyphRotateScreenOn();

	void axisGlyphScaleXOn();
	void axisGlyphScaleYOn();
	void axisGlyphScaleZOn();

	void axisGlyphScaleXYOn();
	void axisGlyphScaleYZOn();
	void axisGlyphScaleXZOn();

	void axisGlyphScaleAllOn();

private:
	GLuint arrowCallListID;
	GLuint circleCallListID;
	GLuint sphereMaskCallistID;
	GLuint boxCallListID;

public:
	static AxisGlyph & getSingleton()
	{
		static AxisGlyph obj;
		return obj;
	}

	void init();

	void drawForSelection(float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);
	void draw(float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);

private:
	void drawMoveGlyph(float dis,GGL::Point3f &pos);
	void drawRotateGlyph(float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);
	void drawScaleGlyph(float dis,GGL::Point3f &pos);
	void drawComboGlyph(float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);

	void drawMoveGlyphForSelection(float dis,GGL::Point3f &pos);
	void drawRotateGlyphForSelection(float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);
	void drawScaleGlyphForSelection(float dis,GGL::Point3f &pos);
	void drawComboGlyphForSelection(float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);

public:
	bool isHover(int x,int y,float dis,GGL::Point3f &pos,GGL::Point3f &eyeDir);
private:
	AxisGlyph(void);
	~AxisGlyph(void);
};
