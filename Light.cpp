#include "Light.h"

Light::Light(void):lightName(QString("Unnamed Light")),

	position(100.0f,100.0f,100.0f),
	ambient(0.0f,0.0f,0.0f),
	diffuse(1.0f,1.0f,1.0f),
	specular(1.0f,1.0f,1.0f),

	
	 spotExponent(0.0f),
	 spotCutoff(180.0f),
	 constantAttenuation(1.0f),
	 linearAttenuation(0.0f),
	 quadraticAttenuation(0.0f),lineWidth(2),isVisable(true)
{
	color.r=255;
	color.g=252;
	color.b=0;
}

Light::Light(QString name):lightName(name),
position(100.0f,100.0f,100.0f),
ambient(0.0f,0.0f,0.0f),
diffuse(1.0f,1.0f,1.0f),
specular(1.0f,1.0f,1.0f),


spotExponent(1.0f),
spotCutoff(180.0f),
constantAttenuation(1.0f),
linearAttenuation(0.0f),
quadraticAttenuation(0.0f),lineWidth(2),isVisable(true)
{
	color.r=255;
	color.g=252;
	color.b=0;
}


Light::~Light(void)
{
}

void Light::setPosition(GGL::Point3f &pos)
{
	position=pos;
}

void Light::setDirection(GGL::Point3f &dir)
{
	direction=dir;
}

void Light::setAmbient(GGL::Point3f &amb)
{
	ambient=amb;
}
void Light::setDiffuse(GGL::Point3f &dif)
{
	diffuse=dif;
}
void Light::setSpecular(GGL::Point3f &spc)
{
	specular=spc;
}