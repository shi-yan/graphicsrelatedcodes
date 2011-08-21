#pragma once
#include "Point3.h"

class Material
{
private:

	GGL::Point3f ambient;
	GGL::Point3f diffuse;
	GGL::Point3f specular;

	float shininess;
	GGL::Point3f emission;


public:
	Material(void);
	~Material(void);

	void setMaterial();

	GGL::Point3f getAmbient() const
	{
		return ambient;
	}

	GGL::Point3f getDiffuse() const
	{
		return diffuse;
	}

	GGL::Point3f getSpecular() const
	{
		return specular;
	}

	float getShiniess() const
	{
		return shininess;
	}

	GGL::Point3f getEmission()
	{
		return emission;
	}

	void setAmbient(GGL::Point3f &amb);
	void setDiffuse(GGL::Point3f &dif);
	void setSpecular(GGL::Point3f &spc);

	void setShininess(float shn);
	void setEmission(GGL::Point3f &emi);
};
