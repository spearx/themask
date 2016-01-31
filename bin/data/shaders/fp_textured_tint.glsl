//
//  Shader.fsh
//  Simon
//
//  Created by Ruben Lopez on 11/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

varying vec2 tex_coord;
uniform sampler2D diffuse;
uniform vec4 tint_color;

void main()
{
    vec4 texcolor = texture2D(diffuse,tex_coord);
  	gl_FragColor = texcolor*tint_color;
;
}
