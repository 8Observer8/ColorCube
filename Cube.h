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

#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLShaderProgram>
#include <vector>
#include "LoaderOfCube.h"

class Cube
{
public:
    Cube( QOpenGLShaderProgram *program, int vertexAttrLoc,
          int colorAttrLoc, int normalAttrLoc );
    ~Cube();

    void draw();

    void fillFromLoader( const LoaderOfCube *loader );

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
    void draw( std::vector<float> &vertices,
               std::vector<float> &colors,
               std::vector<float> &normals );

    QOpenGLShaderProgram *m_program;
    int m_vertexAttrLoc;
    int m_colorAttrLoc;
    int m_normalAttrLoc;
};

#endif // CUBE_H
