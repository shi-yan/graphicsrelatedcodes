uniform sampler2D finalmap;

void main()
{
	//float dis=.w;
	
//gl_FragColor=vec4(0,0,0,1);
gl_FragColor=vec4(0,0,0,1.0-texture2D(finalmap,gl_TexCoord[0].xy).r);
	
}
