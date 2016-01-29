attribute vec4 position;
attribute vec3 normal;
attribute vec2 texcoord0;

varying vec4 colorVarying;
varying vec2 tex_coord;

uniform mat4 mvp;
uniform mat4 world;
uniform vec4 diffuse_color;
uniform vec4 ambient_color;

void main()
{
    vec4 eyeNormal = normalize(world * vec4(normal,1.0));
    vec4 lightDir = vec4(normalize(vec3(0.0, 0.5, 0.5)),1.0);
    //vec4 diffuseColor = vec4(0.4, 0.4, 1.0, 1.0);
	//vec4 ambientColor = vec4(0.2, 0.2, 0.2, 1.0);
    
    float nDotVP = max(0.0, dot(eyeNormal, lightDir));
                 
    colorVarying = diffuse_color * nDotVP + ambient_color;
	//colorVarying = eyeNormal + ambient_color;
	//colorVarying = diffuse_color;
    tex_coord = texcoord0;
    
    gl_Position = position * mvp;
}
