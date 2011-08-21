#pragma once
#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>

#include <vector>
#include "Vertex.h"
#include <iostream>
#include "Camera.h"
#include <QtCore/QHash>


class Model;
class SceneItem;

class Scene
{
private:
	int ItemUniqueID;
private:
	unsigned short *cuttingIds;
	unsigned short *cuttingPlanes;
	float *surfels;
	bool hasInited;
	float *centerofgravities;

	Model *model;

	QList<SceneItem*> itemList;

	std::vector<unsigned int> selectionList;

public:

	enum EditLevel
	{
		ObjectLevel,
		FacetLevel,
		EdgeLevel,
		PointLevel,
		SplitLevel,
	};

	void drawForSelectionStencil();
	void drawForSelectionColorCode();

	enum EditLevel currentEditLevel;

	/*void setLevel(enum EditLevel editLevel)
	{
		if(editLevel==ObjectLevel)
		{
			currentEditLevel=editLevel;
			assert(selectionList.size()==1);
			//itemList[selectionList[i]]
		}
		else
		{
			if(selectionList.size()==1)
			{
				//itemList[selectionList[i]]
				currentEditLevel=editLevel;
			}
		}

	};*/

	bool isGlyphOn(int x,int y,Camera *currentCamera);

	void select(QHash<unsigned int,unsigned int> &newSelection,bool isIncremental);

	void loadKDTResult(char *filename);

	void setFragmentLightingShader();
	static Scene & getSingleton()
	{
		static Scene obj;
		return obj;
	};

	std::vector<Vertex> vertexPool;
	GGL::Point3f updateAPoint(float x,float y,float z);
	void advectVertices();
	void setShaderParameters(Camera &camera);
	void prepareVertexPool();
	void draw(int width,int height,Camera *currentCamera);
	void updateTree();
	void testDraw();

	void testDrawForPillow(Camera *currentCamera);
	void upsampling();
	int cuttingPlaneIndexSize;
	int surfelSize;
	int cuttingPlaneSize;
	int centerofgravitySize;
	void readFromFile();
	GLuint cuttingPlaneIndexTable;
	GLuint cuttingPlaneTable;
	GLuint surfelTable;
	GLuint centerofgravityTable;
	void outputCuttingPlaneInfo(int listID);

	void loadNext(int loadCount);

	void init();

	void testInitForPillow();



	void drawObject(Camera *currentCamera);

	void setPerFragmentLightingShader();
	
private:
	Scene(void);
	~Scene(void);
};
