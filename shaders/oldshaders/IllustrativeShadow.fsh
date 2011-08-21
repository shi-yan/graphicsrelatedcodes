uniform sampler2D shadowmap;

varying vec3 normal;
varying vec3 viewDir;

varying vec2 shadowmapcoord;
varying float distance;

void main()
{
	//float dis=texture2D(shadowmap,shadowmapcoord).w;
	//gl_FragColor=vec4(0,0,0,1);
	//if(distance<dis)
	//{
		float dotr=dot(normal,viewDir);
		float illuminant =dotr- 0.1;
	
	gl_FragColor.r=illuminant;

	/*}
	else
		gl_FragColor.r=1.0;*/
}
