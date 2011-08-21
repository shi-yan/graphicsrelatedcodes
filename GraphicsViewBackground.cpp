#include <GL/glew.h>
#include "GraphicsViewBackground.h"
#include "CoordinateGrid.h"
#include <cassert>
#include "Scene.h"
#include "LightManager.h"
#include "GLCanvas.h"
#include "AxisGlyph.h"
#include <cstdio>

GraphicsViewBackground::~GraphicsViewBackground(void)
{
	setStyleSheet(tr("QGraphicsView{border:none;}"));

}


void GraphicsViewBackground::init()
{
	GLViewport->makeCurrent();
	{
		glShadeModel(GL_SMOOTH);
		glPixelStorei(GL_PACK_ROW_LENGTH, 0);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glEnable(GL_DEPTH_TEST);

		GLenum err = glewInit();
		if (err != GLEW_OK ) 	
		{
			assert(0);
		}

		CoordinateGrid::getSingleton().prepare();
		AxisGlyph::getSingleton().init();

		glGenFramebuffersEXT(1, &GLCanvas::fbo);
		glGenRenderbuffersEXT(1, &GLCanvas::renderbuffer);


		Scene::getSingleton().testInitForPillow();
		LightManager::getSingleton().init();
	}

	int maxLights = 0;
glGetIntegerv(GL_MAX_LIGHTS, &maxLights);

	printf("Supported Lights:%d\n",maxLights);
}
    
