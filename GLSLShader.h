#pragma once
#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <cstdio>
#include <iostream>



class GLSLShader
{
public:
static char *textFileRead(char *fn) 
{
	FILE *fp;
	char *content = NULL;
	int count=0;

	if (fn != NULL) 
	{
		fp = fopen(fn,"rt");
		if (fp != NULL) 
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0) 
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

static void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);

		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("printShaderInfoLog: %s\n",infoLog);

		free(infoLog);
	}
	else
	{
		printf("Shader Info Log: OK\n");	
	}	
}
		
static void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("printProgramInfoLog: %s\n",infoLog);
		free(infoLog);
	}
	else
	{
	 	printf("Program Info Log: OK\n");
	}
}


public:
	GLSLShader(void);
	~GLSLShader(void);
};
