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
varying vec3 eye_dir;
varying vec3 world_normal;

uniform mat4 mvp;
uniform mat4 world;
uniform vec3 eye_pos;

void main()
{
    world_normal = normalize((world * vec4(normal - position.xyz,1.0)).xyz);
	eye_dir = normalize(eye_pos - position.xyz);
    //vec3 lightDir = vec3(0.0, 0.0, 1.0);
    //vec4 diffuseColor = vec4(0.4, 0.4, 1.0, 1.0);
   
    //float nDotVP = max(0.0, dot(worldNormal, normalize(lightDir)));
                 
    //colorVarying = diffuseColor * nDotVP;
    tex_coord = texcoord0;
	
    //tex_coord = colorVarying.xy;
    
    gl_Position = position * mvp;
}
