#ifndef LOADEROFCUBE_H
#define LOADEROFCUBE_H

#include <QString>
#include <vector>
#include <assimp/scene.h>

class LoaderOfCube
{
public:
    LoaderOfCube( const QString &fileName );
    ~LoaderOfCube();

    bool isSuccessfully;

    std::vector<float> verticesOfFront;
    std::vector<float> colorsOfFront;
    std::vector<float> normalsOfFront;

    std::vector<float> verticesOfTop;
    std::vector<float> colorsOfTop;
    std::vector<float> normalsOfTop;

    std::vector<float> verticesOfBottom;
    std::vector<float> colorsOfBottom;
    std::vector<float> normalsOfBottom;

    std::vector<float> verticesOfLeft;
    std::vector<float> colorsOfLeft;
    std::vector<float> normalsOfLeft;

    std::vector<float> verticesOfRight;
    std::vector<float> colorsOfRight;
    std::vector<float> normalsOfRight;

    std::vector<float> verticesOfBack;
    std::vector<float> colorsOfBack;
    std::vector<float> normalsOfBack;

private:
    void init( const aiScene *scene );

    void fillVertices( const aiMesh *mesh,
                       std::vector<float> &vertices );

    void fillColors( const aiMesh *mesh, const aiMaterial *material,
                     std::vector<float> &colors );

    void fillNormals( const aiMesh *mesh,
                      std::vector<float> &normals );
};

#endif // LOADEROFCUBE_H
