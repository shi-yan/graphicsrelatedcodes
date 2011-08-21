#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D map;
uniform sampler3D dotmap;
uniform float width;
uniform float height;

void main()
{
	highp vec2 center = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);

	highp vec2 c2=vec2(gl_FragCoord.x/26.0,gl_FragCoord.y/26.0);

	//vec3(gl_FragCoord.x /32.0, gl_FragCoord.y / 32.0,gl_FragCoord.x*2.0/width)

	float l=texture3D(dotmap, vec3(c2, 1.0-texture2D(map,center).x) ).w;

	//l=texture2D(map,center).r;

	gl_FragColor=vec4(l,l,l,1);    

//gl_FragColor=vec4(0,0,1,1);
}
