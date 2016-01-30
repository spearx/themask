//
//  Shader.fsh
//  Simon
//
//  Created by Ruben Lopez on 11/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

varying vec2 tex_coord;
varying vec3 eye_normal;
uniform sampler2D diffuse;
uniform vec3 eye_pos;

void main()
{
	float multiplier = dot(eye_normal,normalize(vec3(1.0,1.0,0.0)));

    gl_FragColor = multiplier*texture2D(diffuse,vec2(tex_coord.x,1.0-tex_coord.y));
}
