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
