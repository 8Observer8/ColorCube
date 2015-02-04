/*
    The Cube Example

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
