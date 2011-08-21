#include "OrthogonalCamera.h"
#include "matrix44.h"
#include <QtOpenGL/QGLWidget>

OrthogonalCamera::OrthogonalCamera(void):scale(1.0f),Camera(QString("Orthogonal")),light(QString("Orthogonal Camera Light"))
{
	light.setPosition(from());
	GGL::Point3f dir(from()-to());
	light.setDirection(dir);
}

OrthogonalCamera::OrthogonalCamera(QString _name):scale(1.0f),Camera(_name),light(QString("%1 Camera Light").arg(_name))
{
	light.setPosition(from());
	GGL::Point3f dir(from()-to());
	light.setDirection(dir);
}


OrthogonalCamera::~OrthogonalCamera(void)
{
}


void OrthogonalCamera::lookAt(GGL::Point3f &_from,GGL::Point3f &_to)
{
	from()=_from;
	to()=_to;
	GGL::Point3f zAxis(0,0,1);
	up()=(from()-to())^(zAxis^(from()-to()));

	light.setPosition(from());
	GGL::Point3f dir(from()-to());
	light.setDirection(dir);
					
	emit onCameraMotion(this);
}
	 
void OrthogonalCamera::onMouseMove(int x,int y)
{
	switch(motionType)
	{
		case Rotate:
			{
				int disx=x-oldX;
				int disy=y-oldY;

				GGL::Point3f zAxis(0,0,1);

				float angle=-0.0002f*disx;

				GGL::Matrix44f rotation;
				rotation.SetRotate(angle,zAxis);
				up()=rotation*up();
				from()=rotation*(from()-to())+to();

				GGL::Point3f roAxis=up()^(from()-to());

				angle=-0.0002f*disy;

				rotation.SetRotate(angle,roAxis);
				from()=rotation*(from()-to())+to();
				up()=rotation*up();

				light.setPosition(from());
				GGL::Point3f dir=from()-to();
				light.setDirection(dir);

				emit onCameraMotion(this);
			}
			break;
		
		case Pan:
			{
				int disx=oldX-x;
				int disy=y-oldY;

				GGL::Point3f zAxis(0,0,disy*0.002);

				GGL::Point3f horizontal=(up()^(from()-to())).Normalize();
					
				horizontal*=disx*0.002;

				from()+=horizontal;
				to()+=horizontal;

				from()+=zAxis;
				to()+=zAxis;
				
				emit onCameraMotion(this);
			}
			break;
		case Zoom:
			{
				int disy=y-oldY;
				GGL::Point3f newfrom=from()+((to()-from()).Normalize())*0.01*disy;
				scale=-disy*0.0005+scale;

				if(scale<0.000001f)
					scale=0.000001f;


				if((to()-newfrom)*((to()-from()).Normalize())>0.001f)
				{
					from()=newfrom;
				}
				else
				{
					from()=(from()-to()).Normalize()*0.1f+to();
				}
								
				emit onCameraMotion(this);
			}
			break;
	}

}
 
void OrthogonalCamera::onMouseWheel(float notch)
{
	scale=-notch*0.01+scale;

	if(scale<0.000001f)
		scale=0.000001f;


	GGL::Point3f newfrom=from()+((to()-from()).Normalize())*notch;

	if((to()-newfrom)*((to()-from()).Normalize())>0.001f)
	{
		from()=newfrom;
	}
	else
	{
		from()=(from()-to()).Normalize()*0.1f+to();
	}
	
	emit onCameraMotion(this);
}

void OrthogonalCamera::setCameraForSelection(int x,int y,int selectionWidth,int selectionHeight,float width,float height,float ratio)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glViewport(0,0,selectionWidth,selectionHeight);
	gluPickMatrix(x+selectionWidth*0.5f,viewport[3]-y-selectionHeight*0.5f,selectionWidth,selectionHeight,viewport);

	glOrtho(-width*0.5f*scale, width*0.5f*scale, -height*0.5f*scale, height*0.5f*scale, -farPlane(), farPlane());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(from()[0],from()[1],from()[2] ,to()[0],to()[1], to()[2],up()[0],up()[1],up()[2]);
}

	
void OrthogonalCamera::setCamera(float width,float height,float ratio)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width*0.5f*scale, width*0.5f*scale, -height*0.5f*scale, height*0.5f*scale, -farPlane(), farPlane());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(from()[0],from()[1],from()[2] ,to()[0],to()[1], to()[2],up()[0],up()[1],up()[2]);
}

Light * OrthogonalCamera::getCameraLight()
{
	if(isLightOn())
	{
		return &light;
	}
	else
		return 0;
}
