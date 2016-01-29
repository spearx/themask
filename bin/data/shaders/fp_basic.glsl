//
//  Shader.fsh
//  Simon
//
//  Created by Ruben Lopez on 11/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//varying lowp vec4 colorVarying;

varying vec2 tex_coord;
uniform sampler2D diffuse;

void main()
{
    //color = color * colorVarying;
    gl_FragColor = texture2D(diffuse,tex_coord);
    //gl_FragColor = vec4(1, tex_coord.x, tex_coord.y, 1);
}
