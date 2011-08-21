#include "PerspectiveCamera.h"
#include "matrix44.h"
#include <QtOpenGL/QGLWidget>
#include <cstdio>

PerspectiveCamera::PerspectiveCamera(void):Camera(QString("Perspective")),light(QString("Perspective Camera Light"))
{
	isShowInfo()=true;
	GGL::Point3f efrom(32,32,32);
	GGL::Point3f eto(0,0,0);
	lookAt(efrom,eto);

	light.setPosition(from());
	GGL::Point3f dir(to()-from());
	light.setDirection(dir);
	light.setSpotCutoff(fov());
}

PerspectiveCamera::PerspectiveCamera(QString _name):Camera(_name),light(QString("%1 Camera Light").arg(_name))
{
	isShowInfo()=true;
	GGL::Point3f efrom(32,32,32);
	GGL::Point3f eto(0,0,0);
	lookAt(efrom,eto);

	light.setPosition(from());
	GGL::Point3f dir(to()-from());
	light.setDirection(dir);
	light.setSpotCutoff(fov());
}


PerspectiveCamera::~PerspectiveCamera(void)
{
}

void PerspectiveCamera::save(const QString &filename)
{
        FILE *fp=fopen(filename.toStdString().c_str(),"wb");

	float sfov=fov();

	float sfarPlane=farPlane();
	float snearPlane=nearPlane();

	GGL::Point3f sfrom=from();
	GGL::Point3f sto=to();
	GGL::Point3f sup=up();


	fwrite(&sfov,sizeof(float),1,fp);
	fwrite(&sfarPlane,sizeof(float),1,fp);
	fwrite(&snearPlane,sizeof(float),1,fp);

	float vsfrom[3];
	vsfrom[0]=from().X();
	vsfrom[1]=from().Y();
	vsfrom[2]=from().Z();

	fwrite(vsfrom,sizeof(float),3,fp);

	float vsto[3];
	vsto[0]=to().X();
	vsto[1]=to().Y();
	vsto[2]=to().Z();

	fwrite(vsto,sizeof(float),3,fp);

	float vsup[3];

	vsup[0]=up().X();
	vsup[1]=up().Y();
	vsup[2]=up().Z();


	fwrite(vsup,sizeof(float),3,fp);


	fclose(fp);
}

void PerspectiveCamera::load(const QString &filename)
{
        FILE *fp=fopen(filename.toStdString().c_str(),"rb");

	float sfov=0;

	float sfarPlane=0;
	float snearPlane=0;

	GGL::Point3f sfrom;
	GGL::Point3f sto;
	GGL::Point3f sup;


	fread(&sfov,sizeof(float),1,fp);
        qDebug("fov:%f",sfov);
	fread(&sfarPlane,sizeof(float),1,fp);
        qDebug("far plane:%f",sfarPlane);
	fread(&snearPlane,sizeof(float),1,fp);
        qDebug("near plane:%f",snearPlane);
	float vsfrom[3];

	fread(vsfrom,sizeof(float),3,fp);
        qDebug("from:%f,%f,%f",vsfrom[0],vsfrom[1],vsfrom[2]);

	float vsto[3];

	fread(vsto,sizeof(float),3,fp);
        qDebug("to:%f,%f,%f",vsto[0],vsto[1],vsto[2]);
	float vsup[3];
	fread(vsup,sizeof(float),3,fp);

        qDebug("up:%f,%f,%f",vsup[0],vsup[1],vsup[2]);

	fclose(fp);


	setFov(sfov);
	setFarPlane(sfarPlane);
	setNearPlane(snearPlane);
	setFrom(GGL::Point3f(vsfrom[0],vsfrom[1],vsfrom[2]));
	setTo(GGL::Point3f(vsto[0],vsto[1],vsto[2]));
	setUp(GGL::Point3f(vsup[0],vsup[1],vsup[2]));
}

void PerspectiveCamera::lookAt(GGL::Point3f &_from,GGL::Point3f &_to)
{
	from()=_from;
	to()=_to;
	GGL::Point3f zAxis(0,0,1);
	up()=(from()-to())^(zAxis^(from()-to()));

	light.setPosition(from());
	GGL::Point3f dir=to()-from();
	light.setDirection(dir);
	light.setSpotCutoff(fov());
					
	emit onCameraMotion(this);

}

void PerspectiveCamera::setCameraForSelection(int x,int y,int selectionWidth,int selectionHeight,float width,float height,float ratio)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
/*
	glColor3ub(255,0,0);
	glBegin(GL_QUADS);
	glVertex2f(-1,-1);
glVertex2f(-1,1);
glVertex2f(1,1);
glVertex2f(1,-1);
	glEnd();
*/


	gluPickMatrix(x+selectionWidth*0.5f,viewport[3]-y-selectionHeight*0.5f,selectionWidth,selectionHeight,viewport);

	gluPerspective(fov(), ratio, nearPlane(), farPlane());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(from()[0],from()[1],from()[2] ,to()[0],to()[1], to()[2],up()[0],up()[1],up()[2]);
}


void PerspectiveCamera::setCamera(float width,float height,float ratio)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//qDebug("%f,%f,",nearPlane(),farPlane());
	gluPerspective(fov(), ratio, nearPlane(), farPlane());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(from()[0],from()[1],from()[2] ,to()[0],to()[1], to()[2],up()[0],up()[1],up()[2]);
}

void PerspectiveCamera::onMouseMove(int x,int y)
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
				GGL::Point3f dir=to()-from();
	light.setDirection(dir);
	light.setSpotCutoff(fov());

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

					light.setPosition(from());
				GGL::Point3f dir=to()-from();
	light.setDirection(dir);
	light.setSpotCutoff(fov());

				emit onCameraMotion(this);

			}
			break;
		case Zoom:
			{
				int disy=y-oldY;
				GGL::Point3f newfrom=from()+((to()-from()).Normalize())*0.01*disy;

				if((to()-newfrom)*((to()-from()).Normalize())>0.001f)
				{
					from()=newfrom;
				}
				else
				{
					from()=(from()-to()).Normalize()*0.1f+to();
				}

					light.setPosition(from());
				GGL::Point3f dir=to()-from();
	light.setDirection(dir);
	light.setSpotCutoff(fov());
								emit onCameraMotion(this);

			}
			break;
	}
}

void PerspectiveCamera::onMouseWheel(float notch)
{				
	GGL::Point3f newfrom=from()+((to()-from()).Normalize())*notch;

	if((to()-newfrom)*((to()-from()).Normalize())>0.001f)
	{
		from()=newfrom;

	}
	else
	{
		from()=(from()-to()).Normalize()*0.1f+to();
	}

		light.setPosition(from());
	GGL::Point3f dir=to()-from();
	light.setDirection(dir);
	light.setSpotCutoff(fov());
	
	emit onCameraMotion(this);
}

Light * PerspectiveCamera::getCameraLight()
{
	if(isLightOn())
	{
		return &light;
	}
	else
		return 0;
}
