//
//  Shader.fsh
//  Simon
//
//  Created by Ruben Lopez on 11/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

varying vec2 tex_coord;
uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture2D(diffuse,tex_coord);
}
