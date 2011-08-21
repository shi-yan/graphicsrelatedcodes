#pragma once
#include <QtOpenGL/QGLWidget>

class GLViewport:public QGLWidget
{
	Q_OBJECT

public:
	void initializeGL();
public:
	GLViewport(void);
	~GLViewport(void);
};
