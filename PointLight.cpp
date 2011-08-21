#include <QtOpenGL/QGLWidget>
#include "PointLight.h"
#include "LightManager.h"

PointLight::PointLight(void):Light(QString("Unnamed Point Light"))
{
}

PointLight::PointLight(QString &name):Light(name)
{

}

PointLight::~PointLight(void)
{
}

void PointLight::draw()
{
	if(isVisable)
	{
		glColor3ub(color.r,color.g,color.b);
		glLineWidth(lineWidth);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(position.X(),position.Y(),position.Z());
		glCallList(LightManager::getSingleton().getPointLightGlyphCallID());
		glPopMatrix();
	}
}

void PointLight::setLight(int GLLightIndex)
{
	GLfloat light_ambient[]={ambient.X(),ambient.Y(),ambient.Z(),1.0f};
	GLfloat light_diffuse[]={diffuse.X(),diffuse.Y(),diffuse.Z(),1.0f};
	GLfloat light_specular[]={specular.X(),specular.Y(),specular.Z(),1.0f};
	GLfloat light_position[]={position.X(),position.Y(),position.Z(),1.0f};

	glLightfv(GLLightIndex,GL_AMBIENT,light_ambient);
	glLightfv(GLLightIndex,GL_DIFFUSE,light_diffuse);
	glLightfv(GLLightIndex,GL_SPECULAR,light_specular);
	glLightfv(GLLightIndex,GL_POSITION,light_position);

	glLightf(GLLightIndex,GL_CONSTANT_ATTENUATION,constantAttenuation);
	glLightf(GLLightIndex,GL_LINEAR_ATTENUATION,linearAttenuation);
	glLightf(GLLightIndex,GL_QUADRATIC_ATTENUATION,quadraticAttenuation);

	glEnable(GLLightIndex);
}

void PointLight::setConstantAttenuation(float conAtt)
{
	constantAttenuation=conAtt;
}

void PointLight::setLinearAttenuation(float linAtt)
{
	linearAttenuation=linAtt;
}

void PointLight::setQuadraticAttenuation(float quadAtt)
{
	quadraticAttenuation=quadAtt;
}
