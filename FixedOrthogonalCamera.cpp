#include "FixedOrthogonalCamera.h"

FixedOrthogonalCamera::FixedOrthogonalCamera(void):OrthogonalCamera(QString("FixedOrthogonal"))
{
}

FixedOrthogonalCamera::FixedOrthogonalCamera(QString &_name):OrthogonalCamera(_name)
{
}

FixedOrthogonalCamera::FixedOrthogonalCamera(enum CameraType type):OrthogonalCamera(QString(""))
{
	switchCamera(type);
	light.setPosition(from());
	GGL::Point3f dir=from()-to();
	light.setDirection(dir);
}


FixedOrthogonalCamera::~FixedOrthogonalCamera(void)
{
}

void FixedOrthogonalCamera::lookAt(GGL::Point3f &_from,GGL::Point3f &_to)
{
}

void FixedOrthogonalCamera::switchCamera(enum CameraType type)
{
	switch(type)
	{
		case Left:
		{
			cameraName()=(tr("Left"));
			GGL::Point3f from(0,100,0);
			GGL::Point3f to(0,0,0);
			OrthogonalCamera::lookAt(from,to);
			setUp(GGL::Point3f(0,0,1));
		}
		break;
		case Right:
		{
			cameraName()=(tr("Right"));
			GGL::Point3f from(0,-100,0);
			GGL::Point3f to(0,0,0);
			OrthogonalCamera::lookAt(from,to);
			setUp(GGL::Point3f(0,0,1));
		}
		break;
		case Top:
		{
			cameraName()=(tr("Top"));
			GGL::Point3f from(0,0,100);
			GGL::Point3f to(0,0,0);
			OrthogonalCamera::lookAt(from,to);
			setUp(GGL::Point3f(1,0,0));
		}
		break;
		case Bottom:
		{
			cameraName()=(tr("Bottom"));
			GGL::Point3f from(0,0,-100);
			GGL::Point3f to(0,0,0);
			OrthogonalCamera::lookAt(from,to);
			setUp(GGL::Point3f(1,0,0));
		}
		break;
		case Front:
		{
			cameraName()=(tr("Front"));
			GGL::Point3f from(100,0,0);
			GGL::Point3f to(0,0,0);
			OrthogonalCamera::lookAt(from,to);
			setUp(GGL::Point3f(0,0,1));
		}
		break;
		case Back:
		{
			cameraName()=(tr("Back"));
			GGL::Point3f from(-100,0,0);
			GGL::Point3f to(0,0,0);
			OrthogonalCamera::lookAt(from,to);
			setUp(GGL::Point3f(0,0,1));
		}
		break;
	}
}
	 
void FixedOrthogonalCamera::onMouseMove(int x,int y)
{
	switch(motionType)
	{
		case Rotate:
			{
	/*			int disx=x-oldX;
				int disy=y-oldY;

				GGL::Point3f zAxis(0,0,1);

				float angle=-0.0002f*disx;

				GGL::Matrix44f rotation;
				rotation.SetRotate(angle,zAxis);
				up=rotation*up;
				from=rotation*(from-to)+to;

				GGL::Point3f roAxis=up^(from-to);

				angle=-0.0002f*disy;

				rotation.SetRotate(angle,roAxis);
				from=rotation*(from-to)+to;
				up=rotation*up;*/
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