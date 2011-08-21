#ifndef FEATUREDETECTIONDATA_H
#define FEATUREDETECTIONDATA_H

#include <QtCore/QObject>
#include "Signature.h"
#include "Pair.h"
#include "transformation.h"
#include "cluster.h"
#include "Point2.h"

class FeatureDetectionData:public QObject
{
    Q_OBJECT

private:
    FeatureDetectionData();
    ~FeatureDetectionData();

    std::vector<Signature> sampleList;
    std::vector<SamplePair> samplePairList;
    std::vector<Transformation> transformationList;

    GGL::Point2f translateCoordinate(const GGL::Point2f &);
    GGL::Point2f translateCoordinate2(const GGL::Point2f &);

public:
    static FeatureDetectionData & getSingleton()
    {
        static FeatureDetectionData obj;
        return obj;
    }

    void draw();

    void generateSamples(int count);

    void collectPairs();

    int getPairSize()
    {
        return samplePairList.size();
    }

    std::vector<Signature> & getSampleList()
    {
        return sampleList;
    }

    void computeTransformation();
    void clusterRotationAxis();

    void outputRotationAxisCloud();
signals:
    void pairsCollected();
};

#endif // FEATUREDETECTIONDATA_H
