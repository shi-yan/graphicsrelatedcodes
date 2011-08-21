varying vec3 normal;

void main()
{	
	gl_TexCoord[0]=gl_MultiTexCoord0;
	gl_TexCoord[1]=gl_MultiTexCoord1;
	
	normal=gl_Normal;
	gl_Position = gl_Vertex;	
}
