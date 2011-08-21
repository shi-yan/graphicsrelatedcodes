uniform vec3 eyePos;
uniform mat4 modelview;
uniform mat4 projection;
uniform vec3 lightposition;

varying vec3 normal;
varying vec3 viewDir;
varying vec2 shadowmapcoord;
varying float distance;

void main()
{
	//shadowmapcoord=((projection*modelview*gl_Vertex).xy+vec2(1.0,1.0))*0.5;

	//distance=length(lightposition-gl_Vertex.xyz)/300.0;

	gl_Position=ftransform();

	viewDir=normalize(eyePos-gl_Vertex.xyz);

	float viewdotnormal=dot(viewDir,gl_Normal);

	normal=gl_Normal;
	if(viewdotnormal<0.0)
		normal=-gl_Normal;

}
