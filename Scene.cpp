#include "Scene.h"
#include "LoaderOfCube.h"
#include <QDir>

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_scale( 1.0f ),
    m_cube( 0 )
{

}

Scene::~Scene()
{
    delete m_cube;
}

void Scene::initializeGL()
{
    glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    // Create a shader program
    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );
    if ( !m_program.link() )
        return;

    m_vertexAttrLoc = m_program.attributeLocation( "vertexAttr" );
    m_colorAttrLoc = m_program.attributeLocation( "colorAttr" );
    m_normalAttrLoc = m_program.attributeLocation( "normalAttr" );

    // Create a cube
    QString path = QDir::currentPath() + QString( "/Models/ColorCube.obj" );
    LoaderOfCube loader( path );
    if ( !loader.isSuccessfully )
        return;

    m_cube = new Cube( &m_program, m_vertexAttrLoc, m_colorAttrLoc, m_normalAttrLoc );
    m_cube->fillFromLoader( &loader );

    m_cameraMatrix.setToIdentity();
    m_cameraMatrix.translate( 0.0f, 0.0f, -5.0f );

    m_modelViewMatrixLoc = m_program.uniformLocation( "modelViewMatrix" );
    m_normalMatrixLoc = m_program.uniformLocation( "normalMatrix" );
    m_projectionMatrixLoc = m_program.uniformLocation( "projectionMatrix" );

    m_program.bind();
    m_lightPosLoc = m_program.uniformLocation( "lightPos" );
    m_program.setUniformValue( m_lightPosLoc, QVector3D( 0.0f, 0.0f, 50.0f ) );
    m_program.release();
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    m_program.setUniformValue( m_projectionMatrixLoc, m_projectionMatrix );

    m_worldMatrix.setToIdentity();
    m_worldMatrix.rotate( 180.0f - ( m_xRot / 16.0f ), 1.0f, 0.0f, 0.0f );
    m_worldMatrix.rotate( float ( m_yRot ) / 16.0f, 0.0f, 1.0f, 0.0f );
    m_worldMatrix.rotate( float( m_zRot ) / 16.0f, 0.0f, 0.0f, 1.0f );
    m_worldMatrix.scale( m_scale );
    m_program.setUniformValue( m_modelViewMatrixLoc,
                               m_cameraMatrix * m_worldMatrix );

    QMatrix3x3 normalMatrix;
    normalMatrix = m_worldMatrix.normalMatrix();
    m_program.setUniformValue( m_normalMatrixLoc, normalMatrix );

    if ( m_cube != 0 )
        m_cube->draw();

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    if ( h == 0 )
        h = 1;

    glViewport( 0, 0, w, h );

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective( 45.0f, float( w ) / float( h ), 0.01f, 500.0f );
}

void Scene::mousePressEvent( QMouseEvent *event )
{
    m_lastPos = event->pos();
}

void Scene::mouseMoveEvent( QMouseEvent *event )
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if ( event->buttons() & Qt::LeftButton )
    {
        setXRotation( m_xRot + 8 * dy );
        setYRotation( m_yRot + 8 * dx );
    }
    else if ( event->buttons() & Qt::RightButton )
    {
        setXRotation( m_xRot + 8 * dy );
        setYRotation( m_zRot + 8 * dx );
    }

    m_lastPos = event->pos();
}

static void qNormalizeAngle( int &angle )
{
    while ( angle < 0 )
        angle += 360 * 16;

    while ( angle > 360 * 16 )
        angle -= 360 * 16;
}

void Scene::setXRotation( int angle )
{
    qNormalizeAngle( angle );

    if ( angle != m_xRot )
    {
        m_xRot = angle;
        update();
    }
}

void Scene::setYRotation( int angle )
{
    qNormalizeAngle( angle );

    if ( angle != m_yRot )
    {
        m_yRot = angle;
        update();
    }
}

void Scene::setZRotation( int angle )
{
    qNormalizeAngle( angle );

    if ( angle != m_zRot )
    {
        m_zRot = angle;
        update();
    }
}

void Scene::wheelEvent( QWheelEvent *event )
{
    if ( event->delta() > 0 )
        scalePlus();
    else if ( event->delta() < 0 )
        scaleMinus();

    update();
}

void Scene::scalePlus()
{
    m_scale *= 1.1f;
}

void Scene::scaleMinus()
{
    m_scale /= 1.1f;
}
