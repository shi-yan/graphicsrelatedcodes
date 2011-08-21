varying vec3 normal,lightDir,halfVector;
varying vec4 ecPosition;
varying vec3 ecPosition3;

void main()
{	
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	lightDir = normalize(vec3(gl_LightSource[0].position));

	halfVector = normalize(gl_LightSource[0].halfVector.xyz);
		
	ecPosition = gl_ModelViewMatrix * gl_Vertex;

	ecPosition3 = (vec3(ecPosition)) / ecPosition.w;
		
	gl_Position = ftransform();
} 
