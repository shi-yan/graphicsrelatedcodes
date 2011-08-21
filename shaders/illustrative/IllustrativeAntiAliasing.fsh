uniform sampler2D map;
uniform float width;
uniform float height;
uniform float threshold;

void main()
{
	highp vec2 center = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);
	highp vec2 off    = vec2((0.8/width), (0.8/height));

	// North west texture access
	highp vec2 tex_nw = vec2(center.x+off.x, center.y+off.y);
	highp vec4 val_nw = texture2D(map, tex_nw.xy);
	val_nw.xyz = (normalize(val_nw.xyz) *2.0)-1.0;
	
	// North east texture access
	highp vec2 tex_ne = vec2(center.x-off.x, center.y+off.y);
	highp vec4 val_ne = texture2D(map, tex_ne.xy);
	val_ne.xyz = (normalize(val_ne.xyz) *2.0)-1.0;

	// South west texture access
	highp vec2 tex_sw = vec2(center.x+off.x, center.y-off.y);
	highp vec4 val_sw = texture2D(map, tex_sw.xy);
	val_sw.xyz = (normalize(val_sw.xyz) *2.0)-1.0;

	// South east texture access
	highp vec2 tex_se = vec2(center.x-off.x, center.y-off.y);
	highp vec4 val_se = texture2D(map, tex_se.xy);
	val_se.xyz = (normalize(val_se.xyz) *2.0)-1.0;

	float distance=1.0-length(texture2D(map,center).xyz);
	
	// Calculate discontinuities
	highp vec3 discontinuity = vec3(0.0, 0.0, 0.0);

	// (north west DOT south east) AND (north east DOT south west)
	highp float dot0 = dot(val_nw.xyz, val_se.xyz);
	highp float dot1 = dot(val_ne.xyz, val_sw.xyz);
	discontinuity.x = 0.01*(dot0+dot1);

	// (north west DEPTH DISCONT. south east) AND (north east DEPTH DISCONT. south west)
	highp float depth_discont0 = abs(val_nw.w - val_se.w);
	highp float depth_discont1 = abs(val_ne.w - val_sw.w);
	

	discontinuity.y = depth_discont0 + depth_discont1;
	
	discontinuity.z =discontinuity.x +  discontinuity.y *100.0;

//gl_FragColor=texture2D(map,center);
	
	if(discontinuity.z<.8)
	{
		//gl_FragColor=vec4(1.0,1.0,1.0,1.0);	
discard;
	}
	else 
	{
		//discard;
		//gl_FragColor=  discontinuity.z*discontinuity.z*discontinuity.z*discontinuity.z*discontinuity.z*vec4(1.0,1.0,1.0,1.0);
		gl_FragColor=vec4(distance,distance,distance,1);		
		gl_FragColor.w=1.0;	
	}

	//gl_FragColor=vec4(discontinuity.y,0,0,1);
	//gl_FragColor=vec4(0,0,0,1);
	//gl_FragColor=texture2D(map,center);
	/*
	if(texture2D(map,center).w>0.2)
	gl_FragColor=vec4(0,1,0,1);
	*/
    
}
