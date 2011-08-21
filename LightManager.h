#pragma once
#include <QtOpenGL/QGLWidget>
#include <QtCore/QObject>
#include <QtCore/QList>
#include "Light.h"

class LightManager:public QObject
{
	Q_OBJECT
private:
	LightManager(void);
	~LightManager(void);

	GLuint pointLightGlyphCallID;
	GLuint directionalLightGlyphCallID;
	GLuint spotLightGlyphCallID;


	
	GLuint perFragmentLightingVertexShaderID;
	GLuint perFragmentLightingFragmentShaderID;
	GLuint perFragmentLightingShaderID;

public:
	static LightManager & getSingleton()
	{
		static LightManager obj;
		return obj;
	};

	GLuint getPointLightGlyphCallID() const
	{
		return pointLightGlyphCallID;
	};

	GLuint getDirectionalLightGlyphCallID() const
	{
		return directionalLightGlyphCallID;
	};

	GLuint getSpotLightGlyphCallID() const
	{
		return spotLightGlyphCallID;
	};

	void init();

	void beginLighting();
	void endLighting();
	bool setLights(Light *cameraLight=0);
	void addLight(Light *light);

	void drawLightGlyphs();
private:
	QList<Light *> lightList;
	int currentLightIndex;

	void setFragmentLightingShader();
};
