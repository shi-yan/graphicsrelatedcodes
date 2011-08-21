#pragma once
#include "Light.h"

class SpotLight :
	public Light
{
public:
	SpotLight(void);
	SpotLight(QString name);
	~SpotLight(void);

	enum LightType getType()
	{
		return SPOT;
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

	float getSpotExponent() const
	{}

	float getSpotCutoff() const 
	{
	}
	
	void setSpotExponent(float);
	void setSpotCutoff(float);

};
