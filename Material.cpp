#include <QtOpenGL/QGLWidget>
#include "Material.h"

Material::Material(void):ambient(0.2f,0.2f,0.2f),diffuse(215.0f/255.0f,220.0f/255.0f,224.0f/255.0f),specular(200.0f/255.0f,55.0f/255.0f,22.0f/255.0f),shininess(15.0f),emission(0.0f,0.0f,0.0f)
{
}

Material::~Material(void)
{
}

void Material::setAmbient(GGL::Point3f &amb)
{
	ambient=amb;
}

void Material::setDiffuse(GGL::Point3f &dif)
{
	diffuse=dif;
}

void Material::setSpecular(GGL::Point3f &spc)
{
	specular=spc;
}

void Material::setShininess(float shn)
{
	shininess=shn;
}

void Material::setEmission(GGL::Point3f &emi)
{
	emission=emi;
}

void Material::setMaterial()
{
	GLfloat mat_ambient[]={ambient.X(),ambient.Y(),ambient.Z(),1.0f};
	GLfloat mat_diffuse[]={diffuse.X(),diffuse.Y(),diffuse.Z(),1.0f};
	GLfloat mat_specular[]={specular.X(),specular.Y(),specular.Z(),1.0f};
	GLfloat mat_shininess[]={shininess};

	GLfloat mat_emission[]={emission.X(),emission.Y(),emission.Z(),1.0f};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);

}
