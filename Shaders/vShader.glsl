attribute highp vec4 vertexAttr;
attribute highp vec4 colorAttr;
attribute highp vec3 normalAttr;

uniform highp mat4 modelViewMatrix;
uniform highp mat4 projectionMatrix;
uniform highp mat3 normalMatrix;

varying highp vec3 vertex;
varying highp vec4 color;
varying highp vec3 normal;

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vertexAttr;

    vertex = vertexAttr.xyz;
    color = colorAttr;
    normal = normalMatrix * normalAttr;
}
