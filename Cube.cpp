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

#include "Cube.h"

Cube::Cube( QOpenGLShaderProgram *program, int vertexAttrLoc,
            int colorAttrLoc, int normalAttrLoc ) :
    m_program( program ),
    m_vertexAttrLoc( vertexAttrLoc ),
    m_colorAttrLoc( colorAttrLoc ),
    m_normalAttrLoc( normalAttrLoc )
{

}

Cube::~Cube()
{

}

void Cube::draw()
{
    draw( verticesOfFront, colorsOfFront, normalsOfFront );
    draw( verticesOfTop, colorsOfTop, normalsOfTop );
    draw( verticesOfBottom, colorsOfBottom, normalsOfBottom );
    draw( verticesOfLeft, colorsOfLeft, normalsOfLeft );
    draw( verticesOfRight, colorsOfRight, normalsOfRight );
    draw( verticesOfBack, colorsOfBack, normalsOfBack );
}

void Cube::fillFromLoader( const LoaderOfCube *loader )
{
    verticesOfFront = loader->verticesOfFront;
    colorsOfFront = loader->colorsOfFront;
    normalsOfFront = loader->normalsOfFront;

    verticesOfTop = loader->verticesOfTop;
    colorsOfTop = loader->colorsOfTop;
    normalsOfTop = loader->normalsOfTop;

    verticesOfBottom = loader->verticesOfBottom;
    colorsOfBottom = loader->colorsOfBottom;
    normalsOfBottom = loader->normalsOfBottom;

    verticesOfLeft = loader->verticesOfLeft;
    colorsOfLeft = loader->colorsOfLeft;
    normalsOfLeft = loader->normalsOfLeft;

    verticesOfRight = loader->verticesOfRight;
    colorsOfRight = loader->colorsOfRight;
    normalsOfRight = loader->normalsOfRight;

    verticesOfBack = loader->verticesOfBack;
    colorsOfBack = loader->colorsOfBack;
    normalsOfBack = loader->normalsOfBack;
}

void Cube::draw( std::vector<float> &vertices,
                 std::vector<float> &colors,
                 std::vector<float> &normals )
{
    m_program->setAttributeArray( m_vertexAttrLoc, vertices.data(), 3 );
    m_program->setAttributeArray( m_colorAttrLoc, colors.data(), 3 );
    m_program->setAttributeArray( m_normalAttrLoc, normals.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttrLoc );
    m_program->enableAttributeArray( m_colorAttrLoc );
    m_program->enableAttributeArray( m_normalAttrLoc );

    glDrawArrays( GL_TRIANGLES, 0, vertices.size() / 3 );

    m_program->disableAttributeArray( m_vertexAttrLoc );
    m_program->disableAttributeArray( m_colorAttrLoc );
    m_program->disableAttributeArray( m_normalAttrLoc );
}
