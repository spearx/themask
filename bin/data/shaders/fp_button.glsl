varying vec4 colorVarying;

uniform vec3 button_factors;
uniform vec4 diffuse_color;

uniform sampler2D diffuse;

varying vec2 tex_coord;

void main()
{
	vec4 texcolor = texture2D(diffuse,tex_coord);

	vec3 color = mix(texcolor.xyz,mix(diffuse_color*(0.5 + 0.5*button_factors.y),vec3(1.0),button_factors.z),button_factors.x);
	
	gl_FragColor = vec4(mix(texcolor.xyz,color,texcolor.a),1.0);
}
