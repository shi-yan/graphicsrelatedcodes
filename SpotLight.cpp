#include <QtOpenGL/QGLWidget>
#include "SpotLight.h"

SpotLight::SpotLight(void):Light(QString("Unnamed Spot Light"))
{
	spotCutoff=30.0f;
}

SpotLight::SpotLight(QString name):Light(name)
{
	spotCutoff=30.0f;
}


SpotLight::~SpotLight(void)
{
}

	
void SpotLight::draw()
{

}
	
void SpotLight::setLight(int GLLightIndex)
{
	GLfloat light_ambient[]={ambient.X(),ambient.Y(),ambient.Z(),1.0f};
	GLfloat light_diffuse[]={diffuse.X(),diffuse.Y(),diffuse.Z(),1.0f};
	GLfloat light_specular[]={specular.X(),specular.Y(),specular.Z(),1.0f};
	GLfloat light_position[]={position.X(),position.Y(),position.Z(),1.0f};

	GLfloat light_spotDirection[]={direction.X(),direction.Y(),direction.Z()};
	GLfloat light_spotCutoff[]={spotCutoff};
	GLfloat light_spotExponent[]={spotExponent};

	glLightfv(GLLightIndex,GL_AMBIENT,light_ambient);
	glLightfv(GLLightIndex,GL_DIFFUSE,light_diffuse);
	glLightfv(GLLightIndex,GL_SPECULAR,light_specular);
	glLightfv(GLLightIndex,GL_POSITION,light_position);

	
	glLightfv(GLLightIndex,GL_SPOT_DIRECTION,light_spotDirection);
	glLightfv(GLLightIndex,GL_SPOT_CUTOFF,light_spotCutoff);
	glLightfv(GLLightIndex,GL_SPOT_EXPONENT,light_spotExponent);

	glLightf(GLLightIndex,GL_CONSTANT_ATTENUATION,constantAttenuation);
	glLightf(GLLightIndex,GL_LINEAR_ATTENUATION,linearAttenuation);
	glLightf(GLLightIndex,GL_QUADRATIC_ATTENUATION,quadraticAttenuation);

	glEnable(GLLightIndex);
}

void SpotLight::setConstantAttenuation(float conAtt)
{
	constantAttenuation=conAtt;
}

void SpotLight::setLinearAttenuation(float linAtt)
{
	linearAttenuation=linAtt;
}

void SpotLight::setQuadraticAttenuation(float quadAtt)
{
	quadraticAttenuation=quadAtt;
}

void SpotLight::setSpotExponent(float sex)
{
	spotExponent=sex;
}

void SpotLight::setSpotCutoff(float scu)
{
	spotCutoff=scu;
}
