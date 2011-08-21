uniform vec3 eyePos;

void main()
{
	gl_Position = ftransform();

    	lowp vec3 Nw = normalize(gl_Normal);
    
            
	highp vec3 Vw = vec3(eyePos - gl_Vertex.xyz);
	
	highp float e2odist=length(Vw);
	
	gl_FrontColor=normalize((vec4(gl_NormalMatrix*Nw,0.0)+vec4(1.0,1.0,1.0,0.0))*0.5)*(length(gl_Vertex.xyz-vec3(49.5,49.5,49.5))/49.5);
	
	gl_FrontColor.w=(e2odist-0.1)/(300.0-0.1);
	//gl_FrontColor=vec4(0.5,0,0,0.5);
}
