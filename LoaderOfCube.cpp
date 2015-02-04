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

#include "LoaderOfCube.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

LoaderOfCube::LoaderOfCube( const QString &fileName ) :
    isSuccessfully( true )
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( fileName.toStdString(),
                                              aiProcess_Triangulate );

    if ( scene == 0 )
    {
        std::cout << "Error in 'LoaderOfCube::LoaderOfCube(...)': "
                     "scene == 0, unable to openg the file " +
                     fileName.toStdString() << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE )
    {
        std::cout << "Error in 'LoaderOfCube::LoaderOfCube(...)': "
                     "scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE" << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( scene->mRootNode == 0 )
    {
        std::cout << "Error in 'LoaderOfCube::LoaderOfCube(...)': "
                     "scene->mRootNode == 0" << std::endl;
        isSuccessfully = false;
        return;
    }

    init( scene );
}

LoaderOfCube::~LoaderOfCube()
{

}

void LoaderOfCube::init( const aiScene *scene )
{
    for ( unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i )
    {
        const aiNode *node = scene->mRootNode->mChildren[i];
        const aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];

        const aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

        aiString name;
        mat->Get( AI_MATKEY_NAME, name );

        if ( std::string( name.C_Str() ) == std::string( "FrontMaterial" ) )
        {
            fillVertices( mesh, verticesOfFront );
            fillColors( mesh, mat, colorsOfFront );
            fillNormals( mesh, normalsOfFront );
        }
        else if ( std::string( name.C_Str() ) == std::string( "TopMaterial" ) )
        {
            fillVertices( mesh, verticesOfTop );
            fillColors( mesh, mat, colorsOfTop );
            fillNormals( mesh, normalsOfTop );
        }
        else if ( std::string( name.C_Str() ) == std::string( "BottomMaterial" ) )
        {
            fillVertices( mesh, verticesOfBottom );
            fillColors( mesh, mat, colorsOfBottom );
            fillNormals( mesh, normalsOfBottom );
        }
        else if ( std::string( name.C_Str() ) == std::string( "LeftMaterial" ) )
        {
            fillVertices( mesh, verticesOfLeft );
            fillColors( mesh, mat, colorsOfLeft );
            fillNormals( mesh, normalsOfLeft );
        }
        else if ( std::string( name.C_Str() ) == std::string( "RightMaterial" ) )
        {
            fillVertices( mesh, verticesOfRight );
            fillColors( mesh, mat, colorsOfRight );
            fillNormals( mesh, normalsOfRight );
        }
        else if ( std::string( name.C_Str() ) == std::string( "BackMaterial" ) )
        {
            fillVertices( mesh, verticesOfBack );
            fillColors( mesh, mat, colorsOfBack );
            fillNormals( mesh, normalsOfBack );
        }
    }
}

void LoaderOfCube::fillVertices( const aiMesh *mesh,
                                 std::vector<float> &vertices )
{
    float x, y, z;

    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        x = mesh->mVertices[i].x;
        y = mesh->mVertices[i].y;
        z = mesh->mVertices[i].z;

        vertices.push_back( x );
        vertices.push_back( y );
        vertices.push_back( z );
    }
}

void LoaderOfCube::fillColors( const aiMesh *mesh, const aiMaterial *material,
                               std::vector<float> &colors )
{
    aiColor4D color;
    aiGetMaterialColor( material, AI_MATKEY_COLOR_DIFFUSE, &color );

    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        colors.push_back( color.r );
        colors.push_back( color.g );
        colors.push_back( color.b );
    }
}

void LoaderOfCube::fillNormals( const aiMesh *mesh,
                                std::vector<float> &normals )
{
    float x, y, z;

    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        x = mesh->mNormals[i].x;
        y = mesh->mNormals[i].y;
        z = mesh->mNormals[i].z;

        normals.push_back( x );
        normals.push_back( y );
        normals.push_back( z );
    }
}
