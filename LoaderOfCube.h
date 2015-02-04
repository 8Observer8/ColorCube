/*
    The Color Cube Example

    Copyright (C) 2015  Enzhaev Ivan

    Email: 8observer8@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
