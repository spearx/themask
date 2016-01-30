//
//  Shader.vsh
//  Simon
//
//  Created by Ruben Lopez on 11/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

attribute vec4 position;
attribute vec3 normal;
attribute vec2 texcoord0;

//varying lowp vec4 colorVarying;
varying vec2 tex_coord;
varying vec3 eye_normal;

uniform mat4 mvp;
uniform mat3 normalMatrix;

void main()
{
    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 lightPosition = vec3(0.0, 0.0, 1.0);
    vec4 diffuseColor = vec4(0.4, 0.4, 1.0, 1.0);
    
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
                 
    //vec4 colorVarying = diffuseColor * nDotVP;
    tex_coord = texcoord0;
	eye_normal = normal;
    //tex_coord = colorVarying.xy;
    
    gl_Position = position * mvp;
}
