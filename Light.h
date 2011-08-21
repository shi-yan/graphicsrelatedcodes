#pragma once
#include "TempColor.h"
#include <QObject>
#include <QString>
#include "Point3.h"

class Light:public QObject
{
	Q_OBJECT
public:

	enum LightType
	{
		UNKNOWN,
		DIRECTIONAL,
		POINT,
		SPOT,
	};

	Light(void);
	Light(QString name);
	virtual ~Light(void);
	QString getLightName(){return lightName;};
	virtual enum LightType getType()=0;
	virtual void draw()=0;
	virtual void setLight(int GLLightIndex)=0;
	
	void setPosition(GGL::Point3f &pos);
	void setDirection(GGL::Point3f &dir);

	void setAmbient(GGL::Point3f &amb);
	void setDiffuse(GGL::Point3f &dif);
	void setSpecular(GGL::Point3f &spc);

protected:

	struct TempColor color;
	float lineWidth;
	bool isVisable;
	

	QString lightName;
	GGL::Point3f position;
	GGL::Point3f direction;

	GGL::Point3f ambient;
	GGL::Point3f diffuse;
	GGL::Point3f specular;

	float spotExponent;
	float spotCutoff;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};
