uniform highp vec3 lightPos;

varying highp vec3 vertex;
varying highp vec4 color;
varying highp vec3 normal;

void main()
{
    highp vec3 lightVector = normalize( lightPos - vertex );
    highp float diffuse = max( dot( normalize( normal ), lightVector ), 0.0 );
    highp vec3 col = color.rgb;
    highp vec3 c = clamp( col * 0.2 + col * 0.8 * diffuse, 0.0, 1.0 );
    gl_FragColor = vec4( c, 1.0 );
}
