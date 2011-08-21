#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include "Scene.h"
#include "VectorField.h"
#include "GLSLShader.h"
#include "Camera.h"
#include "model.h"
#include <QtCore/QString>
#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "AxisGlyph.h"
#include "SceneItem.h"
#include <QtGui/QImage>
#include "StreamLine.h"
#include "featuredetectiondata.h"
#include "drawillustrativedata.h"
#include "seedingideadata.h"



inline float tac( Vertex t, size_t k ) { return t.position[k]; }

float *drawCenterofgravity=0;
int drawCenterofgravitySize=0;
static float *magnitudeField=0;

struct COLORID
{
	char r;
	char g;
	char b;
	char a;
};

struct COLORID intToColor(int _in)
{
	struct COLORID result;
	result.a=0;
	result.r=0;
	result.g=0;
	result.b=0;

	result=*((struct COLORID*)(void *)&_in);

	return result;
}

int colorToInt(struct COLORID _color)
{
	int result=*((int *)((void *)&_color));

	return result;
}

bool compareTwoVertices(Vertex &a,Vertex &b)
{
	return (a.tempDistance<b.tempDistance);
}


std::ostream& operator<<(std::ostream& out, Vertex const& T)
{
	return out << '(' << T.position.X() << ',' << T.position.Y() << ',' << T.position.Z() << ')';
}

Scene::Scene(void):cuttingIds(0),cuttingPlanes(0),cuttingPlaneIndexSize(0),surfelSize(0),cuttingPlaneSize(0),hasInited(false),surfels(0),model(0),ItemUniqueID(0),currentEditLevel(ObjectLevel),centerofgravities(0),centerofgravitySize(0)
{
}

GGL::Point3f Scene::updateAPoint(float x,float y,float z)
{
	//2.5f for tornado
	//0.05 for solar
	/*const float deltaT=2.5f;
	//const float deltaT=0.01f;
	
	GGL::Point3f pos(x,y,z);

         dir=VectorField::getSingleton().getVector(x,y,z);

	GGL::Point3f dd(dir.x,dir.y,dir.z);

	GGL::Point3f k1(dd*deltaT);

	GGL::Point3f tempP=pos+(k1*0.5f);

	dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

	dd.vec(dir.x,dir.y,dir.z);

	GGL::Point3f k2=dd*deltaT;

	tempP=pos+k2*0.5f;

	dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());


	dd.vec(dir.x,dir.y,dir.z);

	GGL::Point3f k3=dd*deltaT;

	tempP=pos+(k3*0.5f);

	dir=VectorField::getSingleton().getVector(tempP.X(),tempP.Y(),tempP.Z());

	dd.vec(dir.x,dir.y,dir.z);

	GGL::Point3f k4=dd*deltaT;

	pos+=(k1+k2*2.0f+k3*3.0f+k4)*(1.0f/6.0f);

	return pos;*/

    return GGL::Point3f();
}


/*
struct TempColor mapScalar2Color(float value)
{
	struct TempColor result;

	value=(value-VectorField::getSingleton().minMag)/(VectorField::getSingleton().maxMag-VectorField::getSingleton().minMag)*VectorField::getSingleton().overall;

	int color[3];

	VectorField::getSingleton().getColor(value,color);

	result.r=color[0];
	result.g=color[1];
	result.b=color[2];


	return result;
}*/

/*
struct TempColor getColor(GGL::Point3f pos)
{
	struct FVector v=VectorField::getSingleton().getVector(pos.X(),pos.Y(),pos.Z());

	GGL::Point3f vec(v.x,v.y,v.z);

	return mapScalar2Color(vec.Norm());
}
*/

GGL::Point3f findPerpendicular(GGL::Point3f &in)
{


	GGL::Point3f z(0,0,1);

	if(in.X()==0 && in.Y()==0)
	{
		return GGL::Point3f(1,0,0);
	}
	else
	{
		GGL::Point3f perpen=z^in;
		return perpen.Normalize();
	}
}

void Scene::advectVertices()
{
	std::vector<Vertex>::iterator iter=vertexPool.begin();

	int i=0;
	for(;iter!=vertexPool.end();++iter)
	{
		if(i==20000)
			printf("sf");
		GGL::Point3f updated=updateAPoint(iter->position.X(),iter->position.Y(),iter->position.Z());

		GGL::Point3f u=findPerpendicular(iter->normal);
		GGL::Point3f v=iter->normal^u;

		GGL::Point3f pointu=iter->position+u*0.1f;
		GGL::Point3f pointv=iter->position+v*0.1f;

		GGL::Point3f updatedPointu=updateAPoint(pointu.X(),pointu.Y(),pointu.Z());
		GGL::Point3f updatedPointv=updateAPoint(pointv.X(),pointv.Y(),pointv.Z());

		u=updatedPointu-updated;
		v=updatedPointv-updated;

		GGL::Point3f newnormal=u^v;
		newnormal.Normalize();




	/*	if(newnormal.Norm()<=0)
			printf("dsf");*/

		iter->normal=newnormal;		

		iter->position=updated;
		i++;
	}
}

void Scene::upsampling()
{
		 
}

static float *testPointArray;

static float *testLeastSquares;

static float *newPointsArray;

static float *nearbyPointsArray;

static int iNumElements=0;
static int leastCount=0;
static int nearbyCount=0;

void Scene::init()
{



}

float *kk;
int psi;

void Scene::testInitForPillow()
{
//	model=new Model(QString("girl.obj"));



	

	//itemList.push_back(aTestBall);

	/*OpenMeshHalfEdge *aTestCylinder=new OpenMeshHalfEdge(QString("A Test Cylinder"));

	aTestCylinder->createCylinder();
	
	itemList.push_back(aTestCylinder);


	OpenMeshHalfEdge *aTestBall=new OpenMeshHalfEdge(QString("A Test Ball"));

	aTestBall->createBall(OpenMeshHalfEdge::DIRECTIONZ,30,0,0,5,20,10);

	itemList.push_back(aTestBall);
*/

	//LightManager::getSingleton().addLight(new DirectionalLight(QString("test light")));

	//PointLight *the2ndLight=new PointLight(QString("2nd light"));
	
	//the2ndLight->setPosition(GGL::Point3f(100,100,100));

	//SpotLight *the3rdLight=new SpotLight(QString("3rd light"));

	//the3rdLight->setPosition(GGL::Point3f(100,-100,100));
	//the3rdLight->setDirection(GGL::Point3f(-1,1,-1));

	//LightManager::getSingleton().addLight(the2ndLight);
	//LightManager::getSingleton().addLight(the3rdLight);
	

	/*FILE *fp=fopen("finalfinalduffingpppbbb04.ppp","rb");

	fread(&psi,sizeof(int),1,fp);

	kk=new float[psi];

	fread(kk,sizeof(float),psi,fp);

	fclose(fp);*/


    DrawIllustrativeData::getSingleton().init();
}

void Scene::testDrawForPillow(Camera *currentCamera)
{
//	glMatrixMode(GL_MODELVIEW);
//	glPushMatrix();
//	glScalef(10,10,10);
//	glMatrixMode(GL_MODELVIEW);
//	glPopMatrix();


	glPolygonMode(GL_FRONT, GL_FILL);

        VectorField::getSingleton().draw();

        FeatureDetectionData::getSingleton().draw();

        SeedingIdeaData::getSingleton().draw();

        if(Streamline::streamlinePool.size())
        {
            for(std::vector<Streamline>::iterator iter=Streamline::streamlinePool.begin();iter!=Streamline::streamlinePool.end();++iter)
            {
                iter->draw();
            }
        }

        DrawIllustrativeData::getSingleton().draw(currentCamera->from());

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	Material mat;

	mat.setMaterial();

	QList<SceneItem*>::iterator iter=itemList.begin();
	for(;iter!=itemList.end();++iter)
	{
		(*iter)->draw(SceneItem::Smooth,currentCamera);

		//(*iter)->drawForSelection(SceneItem::Facets,currentCamera);
	}

	
	
	glDisable(GL_CULL_FACE);
	glUseProgram(0);

	glPointSize(5);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glColor3ub(0,0,255);
	glBegin(GL_POINTS);
	int psiz=psi/3;
	for(int i=0;i<psiz;++i)
	{
		glVertex3f(kk[i*3],kk[i*3+1],kk[i*3+2]);
	}
	glEnd();

	//AxisGlyph::getSingleton().draw(10,GGL::Point3f(10,10,10),currentCamera->from()-currentCamera->to());


}

Scene::~Scene(void)
{	
	delete [] cuttingIds;
	delete [] cuttingPlanes;
	delete [] surfels;

	QList<SceneItem*>::iterator iter=itemList.begin();
	for(;iter!=itemList.end();)
	{
		SceneItem *toBeRemoved=*iter;
		iter++;
		delete toBeRemoved;
	}
}


void Scene::drawForSelectionStencil()
{
	glPolygonMode(GL_FRONT, GL_FILL);

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	glDisable(GL_LIGHTING);

	QList<SceneItem*>::iterator iter=itemList.begin();
	for(;iter!=itemList.end();++iter)
	{
		(*iter)->drawForSelection(SceneItem::Object,SceneItem::Stencil,0);
	}

	glDisable(GL_CULL_FACE);
}

GLuint objectCallID=0;

void Scene::drawObject(Camera *currentCamera)
{
	/*if(objectCallID)
	{
				glCallList(objectCallID);


	}

	else
	*/{
	/*		objectCallID=glGenLists(1);
	glNewList(objectCallID,GL_COMPILE);
	*/int count=0;
	std::vector<Vertex>::iterator iter=vertexPool.begin();
	glBegin(GL_POINTS);
	int k=0;
	for(;iter!=vertexPool.end();++iter)
	{
	/*	if(k==139201 || k==42078 ||k==161821 || k==43344||
k==43357||
k==43067


 || k==161821
 || k==40783
 || k==61925
 || k==41879
 || k==139193
 || k==139199
 || k==43164
 || k==40883
 || k==139182
 || k==42078
 || k==139206
 || k==139211
 || k==43262
 || k==139212


 
|| k== 162608
|| k== 162603
|| k== 164987
|| k== 153559
|| k== 156029
|| k== 165301
|| k== 165214
|| k== 167398
|| k== 161135
|| k== 156453
|| k== 153704
)*/
		{
	/*if(k==40783)
				
				currentCamera->setTo(iter->position);*/
			
		
		if(iter->startIdx==-1 )
		{
			//if(iter->listID==49787 ||iter->color.Z()==1  || iter->color.Y()==1)
			{
				/*if(iter->listID==49787)
					printf("fuck 49787 color (%f,%f,%f)\n",iter->color.X(),iter->color.Y(),iter->color.Z());*/
			
				
            glMultiTexCoord3f(GL_TEXTURE0, 1, 1,1);
          //  glMultiTexCoord3f(GL_TEXTURE1, vtx[0].u1, vtx[0].v1);
				//glTexCoord3f(1,1,1);			

				//struct COLORID c=intToColor(k);
					
				//struct TempColor c=getColor(iter->position);
			struct COLORID c;

			
			if(k<60000)
			{
							c.r=255.0f;
			c.g=255.0;
			c.b=15.0;
			}
			else{
			
						c.r=255.0f;
			c.g=0.0;
			c.b=0.0;
			}

		




			c.a=255.0f;

			glColor3ub(c.r,c.g,c.b);
				//			glColor3ub(255,0,0);

/*
			struct COLORID colorid=intToColor(iter->listID);
			glColor3ub(colorid.r,colorid.g,colorid.b);
*/
		
				//currentCamera->save();
				glNormal3f(iter->normal.X(),iter->normal.Y(),iter->normal.Z());
				glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z());

			
			}
		}
		else
		{	

			


			{
					int y=iter->startIdx*2.0/4096;
					int x=iter->startIdx*2.0-y*4096;
					float yidx=(float)y/(float)cuttingPlaneIndexSize;
					float xidx=(float)x/4096.f;
				
					
					//glTexCoord3f(xidx+0.1/4095.0,yidx+0.1/4095.0,0);

					glMultiTexCoord3f(GL_TEXTURE0,xidx+0.1/4095.0,yidx+0.1/4095.0,0);}

			{

									int y=iter->startIdx*1.5/4092;
					int x=iter->startIdx*1.5-y*4092;
					float yidx=(float)y/(float)centerofgravitySize;
					float xidx=(float)x/4092.f;
				glMultiTexCoord3f(GL_TEXTURE1, xidx+0.1/4091.0,yidx+0.1/4091.0,0);
			}
					//struct TempColor c=getColor(iter->position);

		//	GGL::Point3f cg(drawCenterofgravity[iter->startIdx*3],drawCenterofgravity[iter->startIdx*3+1],drawCenterofgravity[iter->startIdx*3+2]);

		//	float len=(iter->position-cg).Norm();

		/*	if(len<0.6f)
				glColor3ub(255,0,0);
			else*/
			//	glColor3ub(0,255,0);
					//struct COLORID c=intToColor(k);


			
			struct COLORID c;
				if(k<60000)
			{
							c.r=255.0f;
			c.g=255.0;
			c.b=15.0;
			}
			else{
			
						c.r=255.0f;
			c.g=0.0;
			c.b=0.0;
			}

		




			c.a=255.0f;

		

			glColor3ub(c.r,c.g,c.b);

					glNormal3f(iter->normal.X(),iter->normal.Y(),iter->normal.Z());
					glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z());

		}	}

		++k;
	}
	glEnd();

/*glUseProgram(0);

	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	iter=vertexPool.begin();
	for(;iter!=vertexPool.end();++iter)
	{
		if(iter->startIdx==-1 )
		{
			//if(iter->listID==49787 ||iter->color.Z()==1  || iter->color.Y()==1)
			{
				glVertex3f(iter->position.X()+iter->normal.X(),iter->position.Y()+iter->normal.Y(),iter->position.Z()+iter->normal.Z());
				glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z());
			}
		}
		else
		{						
			{
				//if(iter->listID==49787 ||iter->color.Z()==1 || iter->color.Y()==1)
				{

					glVertex3f(iter->position.X()+iter->normal.X(),iter->position.Y()+iter->normal.Y(),iter->position.Z()+iter->normal.Z());
					glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z());
				}
		
			}
		}	
	}

	glEnd();*/
	

	//	glEndList();
	}
}

void Scene::testDraw()
{
	/*std::vector<Vertex>::iterator iter=vertexPool.begin();
	glBegin(GL_LINES);
	int k=0;
	for(;iter!=vertexPool.end();++iter)
	{
		if(iter->normal.Norm()>0)
		{
			//glColor3ub(255,0,0);
			glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z());
			glVertex3f(iter->normal.X()+iter->position.X(),iter->normal.Y()+iter->position.Y(),iter->normal.Z()+iter->position.Z());
		}
		else
		{
		//	glColor3ub(0,0,255);
			glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z());
			glVertex3f(iter->position.X(),iter->position.Y(),iter->position.Z()+1);
		}
	}
	glEnd();*/




}

void Scene::readFromFile()
{
	
}

void Scene::draw(int width,int height,Camera *currentCamera)
{


	glViewport(0,0,width,height);


		glUseProgram(0);

	glDisable(GL_LIGHTING);

	glDisable(GL_LIGHT0);

	glDisable(GL_COLOR_MATERIAL);

	//glDisable(GL_MATERIAL);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);


	/*	glBegin(GL_POINTS);
		for(int i=0;i<drawCenterofgravitySize;++i)
		{
			if(i*3!=vertexPool[59966].startIdx*1.5) continue;
		//	printf("%f,%f,%f\n",drawCenterofgravity[i*3],drawCenterofgravity[i*3+1],drawCenterofgravity[i*3+2]);
		glVertex3f(drawCenterofgravity[i*3],drawCenterofgravity[i*3+1],drawCenterofgravity[i*3+2]);

		}
		glEnd();*/



		//glColor3ub();


	/*	glColor3ub(255,0,255);

		for(int i=0;i<nearbyCount;++i)
		{
	//		if(i!=103) continue;

		//glColor3ub(255,0,0);
				glColor3ub(i,0,255);
			glBegin(GL_LINES);

	
	

			for(int k=0;k<30;++k)
			{

				glVertex3f(nearbyPointsArray[i*60*3+k*6],nearbyPointsArray[i*60*3+k*6+1],nearbyPointsArray[i*60*3+k*6+2]);
				glVertex3f(nearbyPointsArray[i*60*3+k*6+0]+nearbyPointsArray[i*60*3+k*6+3],nearbyPointsArray[i*60*3+k*6+1]+nearbyPointsArray[i*60*3+k*6+4],nearbyPointsArray[i*60*3+k*6+2]+nearbyPointsArray[i*60*3+k*6+5]);


				
			}
			glEnd();



						glBegin(GL_POINTS);

	
	

			for(int k=0;k<30;++k)
			{

				glVertex3f(nearbyPointsArray[i*60*3+k*6],nearbyPointsArray[i*60*3+k*6+1],nearbyPointsArray[i*60*3+k*6+2]);
				//glVertex3f(nearbyPointsArray[i*60*3+k*6+0]+nearbyPointsArray[i*60*3+k*6+3],nearbyPointsArray[i*60*3+k*6+1]+nearbyPointsArray[i*60*3+k*6+4],nearbyPointsArray[i*60*3+k*6+2]+nearbyPointsArray[i*60*3+k*6+5]);

				//printf("[%f,%f,%f] [%f,%f,%f]\n",nearbyPointsArray[i*60*3+k*6+0],nearbyPointsArray[i*60*3+k*6+1],nearbyPointsArray[i*60*3+k*6+2],nearbyPointsArray[i*60*3+k*6+3],nearbyPointsArray[i*60*3+k*6+4],nearbyPointsArray[i*60*3+k*6+5]);

				
			}
			glEnd();
		}

		for(int i=0;i<leastCount;++i)
		{
			if(i!=103) continue;

			glColor3ub(i,0,255);
			//if(i!=) continue;
			for(int y=0;y<10;++y)
			{
				glBegin(GL_LINE_STRIP);
				for(int x=0;x<10;++x)
				{
					glVertex3f(testLeastSquares[(i*100+x+y*10)*6],testLeastSquares[(i*100+x+y*10)*6+1],testLeastSquares[(i*100+x+y*10)*6+2]);

			
				}
				glEnd();

				glColor3ub(0,255,255);

				glBegin(GL_LINES);

				for(int x=0;x<10;++x)
				{
					glVertex3f(testLeastSquares[(i*100+x+y*10)*6],testLeastSquares[(i*100+x+y*10)*6+1],testLeastSquares[(i*100+x+y*10)*6+2]);
					glVertex3f(testLeastSquares[(i*100+x+y*10)*6]+testLeastSquares[(i*100+x+y*10)*6+3],testLeastSquares[(i*100+x+y*10)*6+1]+testLeastSquares[(i*100+x+y*10)*6+4],testLeastSquares[(i*100+x+y*10)*6+2]+testLeastSquares[(i*100+x+y*10)*6+5]);
				}

				glEnd();
	
				glColor3ub(i,0,255);

			}

			for(int x=0;x<10;++x)
			{
				glBegin(GL_LINE_STRIP);
				for(int y=0;y<10;++y)
				{
					glVertex3f(testLeastSquares[(i*100+x+y*10)*6],testLeastSquares[(i*100+x+y*10)*6+1],testLeastSquares[(i*100+x+y*10)*6+2]);
				}
				glEnd();
			}


		}*/

		glActiveTexture(GL_TEXTURE0);
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Scene::outputCuttingPlaneInfo(int listID)
{
	FILE *fp=fopen("debugout.txt","w");
	printf("*********** - Info of point %d - **************\n",listID);
	fprintf(fp,"*********** - Info of point %d - **************\n",listID);

	printf("Position:[%f,%f,%f]\n",vertexPool[listID].position.X(),vertexPool[listID].position.Y(),vertexPool[listID].position.Z());
	fprintf(fp,"Position:[%f,%f,%f]\n",vertexPool[listID].position.X(),vertexPool[listID].position.Y(),vertexPool[listID].position.Z());

	printf("Nornal:[%f,%f,%f]\n",vertexPool[listID].normal.X(),vertexPool[listID].normal.Y(),vertexPool[listID].normal.Z());
	fprintf(fp,"Nornal:[%f,%f,%f]\n",vertexPool[listID].normal.X(),vertexPool[listID].normal.Y(),vertexPool[listID].normal.Z());

	printf("There are %d Cutting planes for this point, starting at %d\n",cuttingIds[vertexPool[listID].startIdx+1],cuttingIds[vertexPool[listID].startIdx]);
	fprintf(fp,"There are %d Cutting planes for this point, starting at %d\n",cuttingIds[vertexPool[listID].startIdx+1],cuttingIds[vertexPool[listID].startIdx]);
	
	printf("The number of cutting planes:[");
	fprintf(fp,"The number of cutting planes:[");
	
	int beginID=cuttingIds[vertexPool[listID].startIdx];
	for(int i=0;i<cuttingIds[vertexPool[listID].startIdx+1];++i)
	{
		int id=i+beginID;
		printf("%d,",cuttingPlanes[id]);
		fprintf(fp,"%d,",cuttingPlanes[id]);
	}

	printf("]\n");
	fprintf(fp,"]\n");

	printf("Surfel Detailed info:\n");
	fprintf(fp,"Surfel Detailed info:\n");

	for(int i=0;i<cuttingIds[vertexPool[listID].startIdx+1];++i)
	{
		int id=i+beginID;
		int surfelID=cuttingPlanes[id];

		printf("[(%d),(%f,%f,%f),(%f,%f,%f)],",surfelID,surfels[surfelID],surfels[surfelID+1],surfels[surfelID+2],surfels[surfelID+3],surfels[surfelID+4],surfels[surfelID+5]);
		fprintf(fp,"[(%d),(%f,%f,%f),(%f,%f,%f)],\n",surfelID,surfels[surfelID],surfels[surfelID+1],surfels[surfelID+2],surfels[surfelID+3],surfels[surfelID+4],surfels[surfelID+5]);
	}

	printf("\n****************************************");
	fprintf(fp,"\n****************************************");

	fclose(fp);
}


void Scene::loadNext(int loadCount)
{
	

}

void Scene::drawForSelectionColorCode()
{
	glPolygonMode(GL_FRONT, GL_FILL);

	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	glDisable(GL_LIGHTING);

	QList<SceneItem*>::iterator iter=itemList.begin();
	int id=0;
	for(;iter!=itemList.end();++iter)
	{
		(*iter)->drawForSelection(SceneItem::Object,SceneItem::ColorCode,id++);
	}

	glDisable(GL_CULL_FACE);
}

void Scene::select(QHash<unsigned int,unsigned int> &newSelection,bool isIncremental)
{
	if(!isIncremental)
	{
		if(selectionList.size()>0)
		{		
			std::vector<unsigned int>::iterator iter=selectionList.begin();

			for(;iter!=selectionList.end();++iter)
			{
				itemList[*iter]->unselect();
			}
			selectionList.clear();
		}
		
		QHash<unsigned int,unsigned int>::iterator hashIter=newSelection.begin();

		for(;hashIter!=newSelection.end();++hashIter)
		{
			selectionList.push_back(hashIter.value());

			int a=hashIter.value();

			itemList[hashIter.value()]->select();
		}
	}
};

void Scene::prepareVertexPool()
{	
	



}

bool Scene::isGlyphOn(int x,int y,Camera *currentCamera)
{
	GGL::Point3f dir=currentCamera->from()-currentCamera->to();
	GGL::Point3f pos(10,10,10);
	return AxisGlyph::getSingleton().isHover(x,y,10,pos,dir);
}
