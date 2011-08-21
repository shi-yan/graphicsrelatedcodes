#pragma once
#include <QtOpenGL/QGLWidget>


class CoordinateGrid
{
public:
	enum GridMode
	{
		XY,
		XZ,
		YZ,
	};
private:
	GLuint CoordinateGridCallIDXY;
	GLuint CoordinateGridCallIDYZ;
	GLuint CoordinateGridCallIDXZ;

private:
	CoordinateGrid(void);
	~CoordinateGrid(void);
public:
	static CoordinateGrid & getSingleton()
	{
		static CoordinateGrid obj;
		return obj;
	}
	void prepare();
	void draw(enum GridMode mode);

};
