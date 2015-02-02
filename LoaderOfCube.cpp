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
        aiNode *node = scene->mRootNode->mChildren[i];
        aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];

        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

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
