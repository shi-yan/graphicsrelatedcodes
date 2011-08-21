#pragma once
#include "Light.h"

class PointLight :
	public Light
{
public:
	PointLight(void);
	PointLight(QString &name);
	~PointLight(void);
		
		enum LightType getType()
	{
		return POINT;
	};
	void draw();
	void setLight(int GLLightIndex);

	void setConstantAttenuation(float conAtt);
	void setLinearAttenuation(float linAtt);
	void setQuadraticAttenuation(float quadAtt);

		float getConstantAttenuation() const
	{
		return constantAttenuation;
	}

	float getLinearAttenuation() const
	{
		return linearAttenuation;
	}

	float getQuadraticAttenuation() const
	{
		return quadraticAttenuation;
	}
};
