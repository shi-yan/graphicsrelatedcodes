varying vec3 normal;
varying vec4 color;
varying vec4 diffusep;
varying float NdotLv;

void main()
{	
	gl_TexCoord[0]=gl_MultiTexCoord0;
	gl_TexCoord[1]=gl_MultiTexCoord1;
	
	normal=gl_Normal;
	gl_Position = gl_Vertex;
	
	//Lighting
			
	vec3 normall, lightDir, viewVector, halfVector;
	vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
	float NdotL,NdotHV;
	
	/* first transform the normal into eye space and normalize the result */
	normall = normalize(gl_NormalMatrix * gl_Normal);
	
	/* now normalize the light's direction. Note that according to the
	OpenGL specification, the light is stored in eye space. Also since 
	we're talking about a directional light, the position field is actually 
	direction */
	lightDir = normalize(vec3(gl_LightSource[0].position));
	
	/* compute the cos of the angle between the normal and lights direction. 
	The light is directional so the direction is constant for every vertex.
	Since these two are normalized the cosine is the dot product. We also 
	need to clamp the result to the [0,1] range. */
	
	NdotL = max(dot(normall, lightDir), 0.0);
	
	/* Compute the diffuse, ambient and globalAmbient terms */
	diffuse = gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	
	/* compute the specular term if NdotL is  larger than zero */
	if (NdotL > 0.0) {

		NdotHV = max(dot(normall, normalize(gl_LightSource[0].halfVector.xyz)),0.0);
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
	}
	
	color = globalAmbient + ambient + specular;
	diffusep=diffuse;
	NdotLv=NdotL;
	
	//color.w=0.5;
	
	color=gl_Color;
}
