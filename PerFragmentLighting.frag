varying vec3 normal,lightDir,halfVector;
varying vec4 ecPosition;
varying vec3 ecPosition3;

uniform int NumEnabledLights;



vec4 CookTorrance(int i,vec3 normal,vec3 eye)
{  
  // Sample the textures
  vec3  Normal        = normalize( 2.0 * normal - 1.0 );
  vec3  Specular      = gl_FrontMaterial.specular.xyz;
  vec3  Diffuse       = gl_FrontMaterial.diffuse.xyz;
  vec2  Roughness     = gl_FrontMaterial.ambient.xy;
  
  Roughness.r           *= 3.0;
  
  // Correct the input and compute aliases
  
  vec3  ViewDir         = normalize( eye );
  
    vec3  LightDir  ;
    if(gl_LightSource[i].position.w < 0.5)
    {
        // Directiona Light
        LightDir=normalize(gl_LightSource[i].position.xyz);
    }
    else
    {
      LightDir        = normalize( vec3(gl_LightSource[i].position) - ecPosition3 );
    }
  
  
 // vec3  LightDir        = normalize( vec3(gl_LightSource[i].position) - ecPosition3 );
  vec3  vHalf           = normalize( 	 LightDir + eye );
 
  float  NormalDotHalf    = dot( Normal, vHalf );
  float  ViewDotHalf      = dot( vHalf,  ViewDir );
  float  NormalDotView    = dot( Normal, ViewDir );
  float  NormalDotLight   = dot( Normal, LightDir );
  
  // Compute the geometric term
  float  G1          = ( 2.0 * NormalDotHalf * NormalDotView ) / ViewDotHalf;
  float  G2          = ( 2.0 * NormalDotHalf * NormalDotLight ) / ViewDotHalf;
  float  G           = min( 1.0, max( 0.0, min( G1, G2 ) ) );
  
  // Compute the fresnel term
  float  F          = Roughness.g + ( 1.0 - Roughness.g ) * pow( 1.0 - NormalDotView, 5.0 );
  
  // Compute the roughness term
  float  R_2        = Roughness.r * Roughness.r;
  float  NDotH_2    = NormalDotHalf * NormalDotHalf;
  float  A          = 1.0 / ( 4.0 * R_2 * NDotH_2 * NDotH_2 );
  float  B          = exp( -( 1.0 - NDotH_2 ) / ( R_2 * NDotH_2 ) );
  float  R          = A * B;
  
  // Compute the final term
  vec3  S          = Specular * ( ( G * F * R ) / ( NormalDotLight * NormalDotView ) );
  vec3  Final      = gl_LightSource[i].specular.rgb * max( 0.0, NormalDotLight ) * ( Diffuse + S );
  
  return vec4( Final, 1.0 );
}


void DoLight(in int i,
             in vec3 Eye,
             in vec3 Normal,inout vec4 Ambient,inout vec4 Diffuse,inout vec4 Specular)
{
    vec3  LightVector;     // direction from surface to light position
    vec3  VertexToEye;
    float LdotN;      // normal . light direction
    float VdotN;      // normal . light half vector
    float SpotDot;    //
    float pf;         // power factor
    float Att = 1.0;  // computed attenuation factor
    float SpottAtt;   // computed spot attenuation factor
    float Dist;       // distance from surface to light source
    float AngleViewNormal;
    float AngleLightNormal;
    float AngleDifference;
    float Irradiance;
    float Alpha;
    float Beta;
    float A;
    float B;
float RoughnessSquared=0.01; 
    // Get the vector from the eye to the vertex in object space
    VertexToEye = normalize(Eye);

    // Compute vector from surface to light position
    LightVector = gl_LightSource[i].position.xyz - ecPosition3;    

    if(gl_LightSource[i].constantAttenuation < 1.0) // Attenuation is on
    {
        // Compute distance between surface and light position    
        Dist = length(LightVector);

        // Compute attenuation
        Att = 1.0 / (gl_LightSource[i].constantAttenuation + gl_LightSource[i].linearAttenuation * Dist + gl_LightSource[i].quadraticAttenuation * Dist * Dist);
    }

    LightVector = normalize(LightVector);    

    if( gl_LightSource[i].spotCutoff < 180.0  ) // Spot Light
    {
        // Spot Attenuation
        SpotDot = dot(-LightVector, normalize(gl_LightSource[i].spotDirection));
       
        if (SpotDot > gl_LightSource[i].spotCosCutoff)
        {
            SpottAtt = pow(SpotDot, gl_LightSource[i].spotExponent);

            Att *= SpottAtt;
        }
        else
        {
            return;
        }
    }

    // Compute Ambient
    Ambient  += gl_LightSource[i].ambient * Att;

    // Compute Diffuse
    if(gl_LightSource[i].position.w < 0.5)
    {
        // Directiona Light
        LdotN = dot(normalize(gl_LightSource[i].position.xyz), Normal);
    }
    else
    {
        // Point or Spot Light
        LdotN = dot(LightVector, Normal);
    }

    VdotN = dot(VertexToEye, Normal);

    Irradiance = max(0.0, LdotN);

    AngleViewNormal  = acos(VdotN);

    AngleLightNormal = acos(LdotN);

    AngleDifference = max (0.0, dot(normalize(VertexToEye - Normal * VdotN), normalize(LightVector - Normal * LdotN)));

    Alpha = max(AngleViewNormal, AngleLightNormal);

    Beta  = min(AngleViewNormal, AngleLightNormal);    

    A = 1.0 - (0.5 * RoughnessSquared) / (RoughnessSquared + 0.33);

    B = (0.45 * RoughnessSquared) / (RoughnessSquared + 0.09);


    Diffuse  += gl_LightSource[i].diffuse * (A + B * AngleDifference * sin(Alpha) * tan(Beta)) * Irradiance * Att;    
    
    	float nDotVP = max(0.0, dot(normal,normalize(vec3(gl_LightSource[i].position))));
	float nDotHV = max(0.0, dot(normal, vec3(gl_LightSource[i].halfVector)));


		pf = pow(nDotHV, gl_FrontMaterial.shininess);
    
   // Specular += pf*Att*gl_LightSource[i].specular ;

} 

vec4 DirectionalLight(in int i,in vec3 normal, in vec3 eye,inout vec4 ambient,inout vec4 diffuse,inout vec4 specular)
{
	float nDotVP; // normal . light direction
	float nDotHV; // normal . light half vector
	float pf; // power factor
	nDotVP = max(0.0, dot(normal,normalize(vec3(gl_LightSource[i].position))));
	nDotHV = max(0.0, dot(normal, vec3(gl_LightSource[i].halfVector)));
	
	if (nDotVP == 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, gl_FrontMaterial.shininess);
		
	//ambient += gl_LightSource[i].ambient;
	diffuse += gl_LightSource[i].diffuse;// * OrenNayarDiffuse(i,eye,normal,0.5);
//	specular += gl_LightSource[i].specular * pf;
	
	return CookTorrance(i,normal,eye);
}

vec4 PointLight(in int i,in vec3 eye,in vec3 ecPosition3,in vec3 normal,inout vec4 ambient,inout vec4 diffuse,inout vec4 specular)
{
	float nDotVP; // normal . light direction
	float nDotHV; // normal . light half vector
	float pf; // power factor
	float attenuation; // computed attenuation factor
	float d; // distance from surface to light source
	vec3 VP; // direction from surface to light position
	vec3 halfVector; // direction of maximum highlights
	
	// Compute vector from surface to light position
	VP = vec3(gl_LightSource[i].position) - ecPosition3;
	
	// Compute distance between surface and light position
	d = length(VP);
	// Normalize the vector from surface to light position
	VP = normalize(VP);
	// Compute attenuation
	attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
	gl_LightSource[i].linearAttenuation * d +
	gl_LightSource[i].quadraticAttenuation * d * d);
	halfVector = normalize(VP + eye);
	nDotVP = max(0.0, dot(normal, VP));
	nDotHV = max(0.0, dot(normal, halfVector));
	
	if (nDotVP == 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, gl_FrontMaterial.shininess);
		
//	ambient += gl_LightSource[i].ambient * attenuation;
	diffuse += gl_LightSource[i].diffuse;// * OrenNayarDiffuse(i,eye,normal,0.5) * attenuation;
//	specular += gl_LightSource[i].specular * pf * attenuation;
	
	return CookTorrance(i,normal,eye)*attenuation;
}

vec4 SpotLight(in int i,in vec3 eye,in vec3 ecPosition3,in vec3 normal,inout vec4 ambient,inout vec4 diffuse,inout vec4 specular)
{
	float nDotVP; // normal . light direction
	float nDotHV; // normal . light half vector
	float pf; // power factor
	float spotDot; // cosine of angle between spotlight
	float spotAttenuation; // spotlight attenuation factor
	float attenuation; // computed attenuation factor
	float d; // distance from surface to light source
	vec3 VP; // direction from surface to light position
	vec3 halfVector; // direction of maximum highlights
	
	// Compute vector from surface to light position
	VP = vec3(gl_LightSource[i].position) - ecPosition3;
	// Compute distance between surface and light position
	d = length(VP);
	// Normalize the vector from surface to light position
	VP = normalize(VP);
	
	// Compute attenuation
	attenuation = 1.0 / (gl_LightSource[i].constantAttenuation +
	gl_LightSource[i].linearAttenuation * d +
	gl_LightSource[i].quadraticAttenuation * d * d);
	// See if point on surface is inside cone of illumination
	spotDot = dot(-VP, normalize(gl_LightSource[i].spotDirection));
	
	if (spotDot < gl_LightSource[i].spotCosCutoff)
		spotAttenuation = 0.0; // light adds no contribution
	else
		spotAttenuation = pow(spotDot, gl_LightSource[i].spotExponent);
		
	// Combine the spotlight and distance attenuation.
	attenuation *= spotAttenuation;
	halfVector = normalize(VP + eye);
	nDotVP = max(0.0, dot(normal, VP));
	nDotHV = max(0.0, dot(normal, halfVector));
	if (nDotVP == 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, gl_FrontMaterial.shininess);
		
		
//	ambient += gl_LightSource[i].ambient * attenuation;
	diffuse += gl_LightSource[i].diffuse;// * OrenNayarDiffuse(i,eye,normal,0.5) * attenuation;
//	specular += gl_LightSource[i].specular * pf * attenuation;
	
	return CookTorrance(i,normal,eye)*attenuation;
}

void main()
{
	vec3 n,halfV,viewV,ldir;
	float NdotL,NdotHV;
	
	vec4 ambient=vec4(0.0,0.0,0.0,1.0);
	vec4 diffuse=vec4(0.0,0.0,0.0,1.0);
	vec4 specular=vec4(0.0,0.0,0.0,1.0);
	vec3 eye = -normalize(ecPosition3);
	
	n = normalize(normal);
	
	NdotL = max(dot(n,lightDir),0.0);
	
	//DirectionalLight(0,n,ambient,  diffuse,  specular);
	int i=0;
	
	vec4 color=vec4(0.0,0.0,0.0,1.0);
	
	for (i = 0; i < NumEnabledLights; i++)
	{
		if (gl_LightSource[i].position.w == 0.0)
			//color+=DirectionalLight(i, n,eye, ambient, diffuse, specular);
			DoLight(i,eye,n,ambient,diffuse,specular);
		else if (gl_LightSource[i].spotCutoff == 180.0)
			//color+=PointLight(i, eye, ecPosition3, n, ambient, diffuse, specular);
			DoLight(i,eye,n,ambient,diffuse,specular);
		else
			//color+=SpotLight(i, eye, ecPosition3, n, ambient, diffuse, specular);
			DoLight(i,eye,n,ambient,diffuse,specular);
	}
	

 color = gl_FrontLightModelProduct.sceneColor +ambient * gl_FrontMaterial.ambient +diffuse * gl_FrontMaterial.diffuse+ specular * gl_FrontMaterial.specular;

	gl_FragColor = color;
}
