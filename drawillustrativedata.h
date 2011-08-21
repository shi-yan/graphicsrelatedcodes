#ifndef DRAWILLUSTRATIVEDATA_H
#define DRAWILLUSTRATIVEDATA_H

#include <vector>
#include "Point3.h"
#include <QGLShaderProgram>
#include <QtOpenGL>
#include "matrix44.h"


struct StreamSampleLine
{
    std::vector<GGL::Point3f> samples;
   // std::vector<float> curvatures;
};

struct BestLine
{
    float b1;
    float b2;
    float b3;
};

class DrawIllustrativeData
{
private:

    bool isDrawSmallestEntropy;
    bool isDrawLargestEntropy;
    bool isDrawCenter;

    float lineWidthBase;
    float lineWidthFlex;

    int smoothness;

    GGL::Point3f _eye;

     std::vector< std::vector<StreamSampleLine> > clusterlist;
     std::vector<int> largestEntropy;
     std::vector<int> smallestEntropy;
     std::vector<float> variations;




    DrawIllustrativeData();
    ~DrawIllustrativeData();

    std::vector< std::vector<GGL::Point3f> > tapes;
    std::vector< std::vector<float> > tapeCurvatures;
    std::vector<std::vector<float> > tapeTorsions;
    std::vector< std::vector<GGL::Point3f> > tapeNormals;

    GLfloat tmodelview[16];
    GLfloat tprojection[16];

    GGL::Matrix44f pt;
    GGL::Matrix44f mt;

    QGLShaderProgram *illustrativeShaderProgram;
    QGLShader *vshader;
    QGLShader *fshader;
	
    QGLShaderProgram *illustrativeAntiAliasingShaderProgram;
    QGLShader *vashader;
    QGLShader *fashader;

    QGLShaderProgram *illustrativeShadowShaderProgram;
    QGLShader *vsshader;
    QGLShader *fsshader;

    QGLShaderProgram *dotShaderProgram;
    QGLShader *vdotshader;
    QGLShader *fdotshader;

    QGLShaderProgram *finalShaderProgram;
    QGLShader *vfinalshader;
    QGLShader *ffinalshader;

    QGLShaderProgram *shadowMapProgram;
    QGLShader *vshadowmapshader;
    QGLShader *fshadowmapshader;

    int eyePositionUniform;
	
    int mapUniform;
    int widthUniform;
    int heightUniform;
    int thresholdUniform;

    int lightUniform;
    int projectionUniform;
    int modelviewUniform;
    int shadowmapUniform;
    int lightpositionUniform;

    int dotEyePositionUniform;

    int dotOriginalUniform;
    int dotWidthUniform;
    int dotHeightUniform;
    int dotmapUniform;

    int finalmapUniform;

    GLuint fbo;
    GLuint depthbuffer;

    GLuint fboAntiAliasing;
    GLuint antiAliasingDepthbuffer;

    GLuint fboshadow;
    GLuint shadowDepthbuffer;
    GLuint shadowImg;


    GLuint fboshadowmap;
    GLuint shadowMapID;
    GLuint shadowMapDepthbuffer;

    GLuint img;

    GLuint dotMapID;

    GLuint antiAliasingMapID;

    int screenWidth;
    int screenHeight;

    float _threshold;

    void drawSilhouette(const GGL::Point3f &eye);
    void drawDotShadow(const GGL::Point3f &eye);
    void drawFinal();
    void generateShadowMap(const GGL::Point3f &light);

    void generateMaps();
    void generateMapsWithRandomDots();

    void drawColor();

    GLfloat *dotMap;

public:

    void setLineWidthBaseAndFlex(float base,float flex)
    {
        lineWidthBase=base;
        lineWidthFlex=flex;
    }

    void clear()
    {
           variations.clear();
             smallestEntropy.clear();
               largestEntropy.clear();
                 clusterlist.clear();
                   tapes.clear();
                     tapeNormals.clear();
                     tapeCurvatures.clear();
    }

    void setSmoothness(int _s)
    {
        smoothness=_s;
    }

    void setDrawSmallestEntropy(bool _isDraw)
    {
        isDrawSmallestEntropy=_isDraw;
    };

    void setDrawLargestEntropy(bool _isDraw)
    {
        isDrawLargestEntropy=_isDraw;
    };

    void setDrawCenter(bool _isDraw)
    {
    isDrawCenter=_isDraw;
    }

    static DrawIllustrativeData & getSingleton()
    {
        static DrawIllustrativeData obj;
        return obj;
    };

    void setThreshold(float _i)
    {
        _threshold=_i;
    };

    float getThreshold()
    {
        return _threshold;
    };

    void generateATape(const GGL::Point3f &p1,const GGL::Point3f &p2);
    GGL::Point3f movePoint(float x,float y,float z);
    GGL::Point3f movePoint(float x, float y, float z,float deltaT);
    GGL::Point3f movePointInBackward(float x,float y,float z);

    void draw(const GGL::Point3f &eye);
    void init();
	
    void resize(int width,int height);

    void getBestLineMatch(std::vector<GGL::Point3f> pointList,float &b1,float &b2,float &b3,GGL::Point3f &center);

    void loadResultFromFile(const QString &filename);

    void computeSections(std::vector<StreamSampleLine>&);

    void computeAverageTape();

    GGL::Point3f computekIn2D(std::vector<GGL::Point3f> &pointSamples,GGL::Point3f &xaxis,GGL::Point3f &yaxis);

    void testRepresentativeLine();

    void generateATapeFromAStartPoint(const GGL::Point3f &startPoint,const GGL::Point3f &eye);

    void generateATapeFromAStartPoint(const GGL::Point3f &startPoint);

    void generateATapeFromRepresentativeLine(const int clusterid,const int rlid);

    void generateATapeFromRepresentativeLineWithTorsion(const int clusterid,const int rlid);

    void computeAverateTapeFromAverageStartPoint(const GGL::Point3f &start);

    GGL::Point3f computeBiNormalDirection(GGL::Point3f &currentPos);

    float computeTorsion(GGL::Point3f &currentPos);

    float computeCurvature(GGL::Point3f &currentPos);
};

#endif // DRAWILLUSTRATIVEDATA_H
