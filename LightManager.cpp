
#include "GLSLShader.h"
#include <GL/glew.h>
#include <QGLWidget>
#include "LightManager.h"


LightManager::LightManager(void):currentLightIndex(-1),


	 perFragmentLightingVertexShaderID(0),
	 perFragmentLightingFragmentShaderID(0),
	 perFragmentLightingShaderID(0),

	 pointLightGlyphCallID(0),
	 directionalLightGlyphCallID(0),
	 spotLightGlyphCallID(0)
{
}

LightManager::~LightManager(void)
{
	glDeleteLists(pointLightGlyphCallID,3);

	QList<Light *>::iterator iter=lightList.begin();

	for(;iter!=lightList.end();)
	{
		Light *toBeDeleted=(*iter);
		iter++;
		delete toBeDeleted;
	}
}

void LightManager::setFragmentLightingShader()
{
	char *vs;
	char *fs;
	
	perFragmentLightingVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	perFragmentLightingFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);	

	vs = GLSLShader::textFileRead("perFragmentLighting.vert");
	fs = GLSLShader::textFileRead("perFragmentLighting.frag");
	
	const char * vv = vs;
	const char * ff = fs;
	
	glShaderSource(perFragmentLightingVertexShaderID, 1, &vv,NULL);
	glShaderSource(perFragmentLightingFragmentShaderID, 1, &ff,NULL);
	
	free(vs);
	free(fs);
	
	glCompileShader(perFragmentLightingVertexShaderID);
	glCompileShader(perFragmentLightingFragmentShaderID);

	perFragmentLightingShaderID = glCreateProgram();
		
	glAttachShader(perFragmentLightingShaderID,perFragmentLightingVertexShaderID);
	glAttachShader(perFragmentLightingShaderID,perFragmentLightingFragmentShaderID);
	
	glLinkProgram(perFragmentLightingShaderID);
	glUseProgram(perFragmentLightingShaderID);

	GLSLShader::printShaderInfoLog(perFragmentLightingVertexShaderID);
	GLSLShader::printShaderInfoLog(perFragmentLightingFragmentShaderID);
	GLSLShader::printProgramInfoLog(perFragmentLightingShaderID);

	GLint params;

	glGetProgramiv(perFragmentLightingShaderID,GL_LINK_STATUS,&params);
	printf("Link shader result:%d\n",params);
}


void LightManager::beginLighting()
{
		glUseProgram(perFragmentLightingShaderID);

	glEnable(GL_LIGHTING);

	GLfloat lmodel_ambient[]={0.1,0.1,0.1,1.0};
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	
	currentLightIndex=-1;
}

void LightManager::endLighting()
{
	currentLightIndex=-1;
	glDisable(GL_LIGHTING);
}

void LightManager::addLight(Light *light)
{
	lightList.push_back(light);
}

bool LightManager::setLights(Light *cameraLight)
{

	int GLLightIndex=GL_LIGHT0;

	if(currentLightIndex==-1 && cameraLight!=0)
	{
		cameraLight->setLight(GLLightIndex);

		int loopSize=lightList.size()<8 ? lightList.size():7;

		for(int i=0;i<loopSize;++i)
		{
			lightList[i]->setLight(++GLLightIndex);
		}

		
		glUniform1i(glGetUniformLocation(perFragmentLightingShaderID,"NumEnabledLights"),loopSize+1);

		currentLightIndex+=8;

		return true;
	}
	else if(currentLightIndex==-1 && cameraLight==0)
	{
		int loopSize=lightList.size()<9 ? lightList.size():8;

		if(loopSize==0)
			return false;

		for(int i=0;i<loopSize;++i)
		{
			lightList[i]->setLight(GLLightIndex++);
		}

		glUniform1i(glGetUniformLocation(perFragmentLightingShaderID,"NumEnabledLights"),loopSize);


		currentLightIndex+=9;

		return true;
	}
	else
	{
		if(currentLightIndex>lightList.size()-1)
			return false;
		else
		{
			int loopSize=lightList.size()<(currentLightIndex+8)?lightList.size():currentLightIndex+8;

			for(int i=0;i<loopSize;++i)
			{
				lightList[i]->setLight(GLLightIndex++);
			}

			glUniform1i(glGetUniformLocation(perFragmentLightingShaderID,"NumEnabledLights"),loopSize);
		}

		currentLightIndex+=8;
	}


	return false;
}

void LightManager::drawLightGlyphs()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);

	QList<Light *>::iterator iter=lightList.begin();

	for(;iter!=lightList.end();++iter)
	{
		(*iter)->draw();
	}
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLineWidth(1.0);

}

void LightManager::init()
{

	//setFragmentLightingShader();

	pointLightGlyphCallID=glGenLists(3);
	directionalLightGlyphCallID=pointLightGlyphCallID+1;
	spotLightGlyphCallID=pointLightGlyphCallID+2;

	glNewList(pointLightGlyphCallID,GL_COMPILE);

	glBegin(GL_LINE_STRIP);
	
	glVertex3f(1,0,0);
	glVertex3f(0,0,1);
	glVertex3f(0,1,0);
	glVertex3f(1,0,0);
	glVertex3f(0,-1,0);
	glVertex3f(0,0,1);
	glVertex3f(-1,0,0);
	glVertex3f(0,-1,0);
	glVertex3f(0,0,-1);
	glVertex3f(-1,0,0);
	glVertex3f(0,1,0);
	glVertex3f(0,0,-1);
	glVertex3f(1,0,0);

	glEnd();

	glEndList();

	glNewList(directionalLightGlyphCallID,GL_COMPILE);

	

	glEndList();

	glNewList(spotLightGlyphCallID,GL_COMPILE);

	

	glEndList();


}