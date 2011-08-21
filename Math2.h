#pragma once

// Please note that this file assume that you have already included your 
// gl-extension wrapping utility, and that therefore all the extension symbol are already defined.

#include "matrix44.h"
#include "similarity.h"
//#include <GL/glew.h> // please do not include it!


namespace GGL 
{

	inline void glMultMatrixE(const Matrix44f &matrix) 
	{
		//glMultMatrixf((const GLfloat *)(matrix[0]));  
		if(glMultTransposeMatrixf) 
			glMultTransposeMatrixf((const GLfloat *)(matrix[0])); 
		else  
		{
			Matrix44f tmp(matrix);
			Transpose(tmp);
			glMultMatrixf((const GLfloat *)(tmp[0]));
		}
	}

	inline void glMultMatrix(const Matrix44f &matrix) 
	{
		Matrix44f tmp(matrix);
		Transpose(tmp);
		glMultMatrixf((const GLfloat *)(tmp[0]));
	}

	inline void glMultMatrixE(const Matrix44d &matrix) 
	{
		if(glMultTransposeMatrixd)
			glMultTransposeMatrixd((const GLdouble *)(matrix[0])); 
		else  
		{
			Matrix44d tmp(matrix);
			Transpose(tmp);
			glMultMatrixd((const GLdouble *)(tmp[0]));
		}
	}

	inline void glMultMatrix(const Matrix44d &matrix) 
	{
		Matrix44d tmp(matrix);
		Transpose(tmp);
		glMultMatrixd((const GLdouble *)(tmp[0]));
	}

	inline void glMultMatrixDirect(const Matrix44f &matrix) 
	{
		glMultMatrixf((const GLfloat *)(matrix[0]));
	}

	inline void glMultMatrixDirect(const Matrix44d &matrix) 
	{
		glMultMatrixd((const GLdouble *)(matrix[0]));
	}

	inline void glMultMatrix(const Similarityf &s) 
	{
		glTranslatef(s.tra[0], s.tra[1], s.tra[2]);
		glScalef(s.sca, s.sca, s.sca);
		float alpha;
		Point3f axis;
		s.rot.ToAxis(alpha, axis);    
		glRotatef(Math::ToDeg(alpha), axis[0], axis[1], axis[2]);    
	}

	inline void glMultMatrix(const Similarityd &s) 
	{
		glTranslated(s.tra[0], s.tra[1], s.tra[2]);
		double alpha;
		Point3d axis;
		s.rot.ToAxis(alpha, axis);
		glRotated(Math::ToDeg(alpha), axis[0], axis[1], axis[2]);
		glScaled(s.sca, s.sca, s.sca);
	}

	inline void glGetv(const GLenum  pname, Matrix44f  & m)
	{
		glGetFloatv(pname,&m[0][0]);
		Transpose(m);
	}

	inline void glGetv(const GLenum  pname, Matrix44d  & m)
	{
		glGetDoublev(pname,&m[0][0]);
		Transpose(m);
	}

	inline void glGetDirectv(const GLenum  pname, Matrix44f  & m)
	{
		glGetFloatv(pname,&m[0][0]);
	}

	inline void glGetDirecv(const GLenum  pname, Matrix44d  & m)
	{
		glGetDoublev(pname,&m[0][0]);
	}

}//namespace
