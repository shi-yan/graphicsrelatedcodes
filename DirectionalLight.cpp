#include <QGLWidget>
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(void):Light(QString("Unnamed Directional Light"))
{
}

DirectionalLight::DirectionalLight(QString name):Light(name)
{
}

DirectionalLight::~DirectionalLight(void)
{
}

void DirectionalLight::draw()
{
}

void DirectionalLight::setLight(int GLLightIndex)
{
	GLfloat light_ambient[]={ambient.X(),ambient.Y(),ambient.Z(),1.0f};
	GLfloat light_diffuse[]={diffuse.X(),diffuse.Y(),diffuse.Z(),1.0f};
	GLfloat light_specular[]={specular.X(),specular.Y(),specular.Z(),1.0f};
	GLfloat light_position[]={direction.X(),direction.Y(),direction.Z(),0.0f};

	glLightfv(GLLightIndex,GL_AMBIENT,light_ambient);
	glLightfv(GLLightIndex,GL_DIFFUSE,light_diffuse);
	glLightfv(GLLightIndex,GL_SPECULAR,light_specular);
	glLightfv(GLLightIndex,GL_POSITION,light_position);

		GLfloat light_spotCutoff[]={180.0f};
			glLightfv(GLLightIndex,GL_SPOT_CUTOFF,light_spotCutoff);

	glEnable(GLLightIndex);
}