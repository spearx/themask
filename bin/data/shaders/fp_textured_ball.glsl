//
//  Shader.fsh
//  Simon
//
//  Created by Ruben Lopez on 11/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

varying vec2 tex_coord;
varying vec3 eye_dir;
varying vec3 world_normal;

uniform sampler2D diffuse;
uniform vec3 eye_pos;
uniform float global_time;
uniform float threshold;

const vec4 cHashA4 = vec4 (0., 1., 57., 58.);
const vec3 cHashA3 = vec3 (1., 57., 113.);
const float cHashM = 43758.54;

vec4 Hashv4f (float p)
{
  return fract (sin (p + cHashA4) * cHashM);
}

float Noisefv2 (vec2 p)
{
  vec2 i = floor (p);
  vec2 f = fract (p);
  f = f * f * (3. - 2. * f);
  vec4 t = Hashv4f (dot (i, cHashA3.xy));
  return mix (mix (t.x, t.y, f.x), mix (t.z, t.w, f.x), f.y);
}

float Fbm2 (vec2 p)
{
  float s = 0.;
  float a = 1.;
  for (int i = 0; i < 6; i ++) {
    s += a * Noisefv2 (p);
    a *= 0.5;
    p *= 2.;
  }
  return s;
}

vec2 VortF (vec2 q, vec2 c)
{
  vec2 d = q - c;
  return 0.25 * vec2 (d.y, - d.x) / (dot (d, d) + 0.05);
}

vec2 FlowField (vec2 q)
{
  vec2 vr, c;
  float dir = 1.;
  c = vec2 (mod (global_time, 10.) - 20., 0.6 * dir);
  vr = vec2 (0.);
  for (int k = 0; k < 30; k ++) {
    vr += dir * VortF (4. * q, c);
    c = vec2 (c.x + 1., - c.y);
    dir = - dir;
  }
  return vr;
}

void main()
{	
	vec2 p = tex_coord * 2.0;
	for (int i = 0; i < 10; i ++) p -= FlowField (p) * 0.03;
	vec3 vortex = Fbm2 (5. * p + vec2 (-0.1 * global_time, 0.)) * vec3 (0.5, 0.5, 1.);
	
	vec3 lightDir     = normalize(vec3(1.0, 1.0, 1.0));
	vec3 reflDir 	  = reflect(-eye_dir,world_normal);
	float specular    = max(dot(reflDir,lightDir),0.0);
	float ilumination = max(dot(world_normal,lightDir),0.0);
	float rim         = dot(world_normal,eye_dir);
	
	float vortexMix = min(threshold,pow(rim,2.0));
	vec3 color = mix(vortex,texture2D(diffuse,vec2(tex_coord.x,1.0-tex_coord.y)),vortexMix);
	
	float ambient  	= 0.7 + 0.3*world_normal.y;
	vec3 finalcolor  = rim*rim*(min(ambient+ilumination,1.0)*color+vec3(1.0)*pow(specular,50.0));
	
	gl_FragColor = vec4(finalcolor,1.0);
}
