#ifndef CLUSTERCOLORSCHEME_H
#define CLUSTERCOLORSCHEME_H

#include <vector>
#include <QObject>

struct ClusterColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

class ClusterColorScheme:public QObject
{
    Q_OBJECT
private:
    std::vector<ClusterColor> colorList;

private:
    ClusterColorScheme();

public:
    static ClusterColorScheme & getSingleton()
    {
        static ClusterColorScheme obj;
        return obj;
    };


    void save(const QString &filename);
    void load(const QString &filename);

    void resize(int _size);

    void initializeWithColorSchemeA();
    void initializeWithColorSchemeB();
    void initializeWithColorSchemeC();
    void initializeWithColorSchemeD();
    void initializeWithColorSchemeE();
    void initializeWithColorSchemeF();
    void initializeWithColorSchemeG();

    ClusterColor & operator[](unsigned int id)
    {
        return colorList[id];
    };

    unsigned int getClusterColorSize()
    {
        return colorList.size();
    };

  signals:
    void clusterColorChanged();
};

#endif // CLUSTERCOLORSCHEME_H
