#pragma once
#include "Light.h"

class DirectionalLight :public Light
{
public:
	DirectionalLight(void);
	DirectionalLight(QString name);
	~DirectionalLight(void);

	enum LightType getType()
	{
		return DIRECTIONAL;
	};

	void draw();
	void setLight(int GLLightIndex);
};
