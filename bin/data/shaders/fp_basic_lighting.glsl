varying vec4 colorVarying;

varying vec2 tex_coord;

void main()
{
    gl_FragColor = colorVarying;
	//gl_FragColor = vec4(1,1,0,1);
}
