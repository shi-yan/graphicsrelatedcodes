#extension GL_EXT_gpu_shader4 : enable

uniform usampler2D indexTable;
uniform usampler2D cuttingPlaneTable;
uniform sampler2D surfelTable;
uniform sampler2D centerofgravityTable;
uniform int cuttingPlaneTableHeight;
uniform int surfelTableHeight;
uniform int centerofgravityTableHeight;

uniform sampler2D gaussianKernel;

uniform float near;
uniform float far;

varying vec4 position;

varying float dis;

varying vec3 onor;

varying vec3 originalPos;

vec2 getTexCoordForSurfels(int index, int height)
{
	int k=index/4092;
	float iny=(float(k)+0.5)/float(height);
	float inx=(float(index-k*4092)+0.5)/4092.0;
	
	return vec2(inx,iny);
}

vec2 getTexCoord( int index,int height)
{
	int k=index/4096;
	
	float iny=(float(k)+0.5)/float(height);
		
	float inx=(float(int(index)-k*4096)+0.5)/4096.0;
	
	return vec2(inx,iny);
}

float gaussian(float _dis)
{
	return exp(-(_dis)*(_dis)/(0.12));
}

void main()
{
	float alpha=gaussian(sqrt((gl_TexCoord[2].x-0.5f)*(gl_TexCoord[2].x-0.5)+(gl_TexCoord[2].y-0.5)*(gl_TexCoord[2].y-0.5)));
	alpha=0.100;

	if(gl_TexCoord[0].z>0.5)
	{	
		//float depth=log (dis-near + 1.0) /log (far-near + 1.0);
		float depth= (dis-near ) / (far-near );
		
		gl_FragColor=vec4(depth,depth,depth,1);
		gl_FragDepth=depth;
		return;
	}
	else
	{
		int startID = texture2D(indexTable,gl_TexCoord[0].st).x*65530+texture2D(indexTable,vec2(gl_TexCoord[0].s+1.0/4095.0,gl_TexCoord[0].t)).x;
		int endID   = texture2D(indexTable,vec2(gl_TexCoord[0].s+2.0/4095.0,gl_TexCoord[0].t)).x*65530+texture2D(indexTable,vec2(gl_TexCoord[0].s+3.0/4095.0,gl_TexCoord[0].t)).x;
		bool shouldDraw=true;

		int i=0;
		
		//vec3 centerofgravity=vec3(texture2D(centerofgravityTable,gl_TexCoord[1].st).x,texture2D(centerofgravityTable,vec2(gl_TexCoord[1].s+1.0/4092,gl_TexCoord[1].t)).x,texture2D(centerofgravityTable,vec2(gl_TexCoord[1].s+2.0/4092,gl_TexCoord[1].t)).x);
		
		vec3 centerofgravity=vec3(texture2D(centerofgravityTable,gl_TexCoord[1].st).x,texture2D(centerofgravityTable,vec2(gl_TexCoord[1].s+1.0/4091.0,gl_TexCoord[1].t)).x,texture2D(centerofgravityTable,vec2(gl_TexCoord[1].s+2.0/4091.0,gl_TexCoord[1].t)).x);

		
		for( i=0;i<200;++i)
		{
		
			if(endID<unsigned short(i))
				break;
				
			int cuttingPlaneID=texture2D(cuttingPlaneTable,getTexCoord((startID+i)*2,cuttingPlaneTableHeight)).x*65530+texture2D(cuttingPlaneTable,getTexCoord((startID+i)*2+1,cuttingPlaneTableHeight)).x;
		
			float p1=texture2D(surfelTable,getTexCoordForSurfels(cuttingPlaneID,surfelTableHeight)).x;
			float p2=texture2D(surfelTable,getTexCoordForSurfels(cuttingPlaneID+1,surfelTableHeight)).x;
			float p3=texture2D(surfelTable,getTexCoordForSurfels(cuttingPlaneID+2,surfelTableHeight)).x;
		
			vec3 point=vec3(p1,p2,p3);
		
			float n1=texture2D(surfelTable,getTexCoordForSurfels(cuttingPlaneID+3,surfelTableHeight)).x;
			float n2=texture2D(surfelTable,getTexCoordForSurfels(cuttingPlaneID+4,surfelTableHeight)).x;
			float n3=texture2D(surfelTable,getTexCoordForSurfels(cuttingPlaneID+5,surfelTableHeight)).x;
		
			vec3 normal=vec3(n1,n2,n3);
			
			float offset =dot( point, normal);// cutting plane offset
			float distance=dot(position.xyz,normal)-offset; // distance between the point and the cutting plane
			float oridis=dot(centerofgravity,normal)-offset; //distance between the surfel origin to the cutting plane
			
			
			if(oridis>=0.0)
			{

					if(distance<-0.08)
					{
						shouldDraw=false;
						break;
					}
			}
			else
			{
					if(distance>0.08)
					{
						shouldDraw=false;
						break;
					}
			}
		}
	
		if(shouldDraw)
		{
			//float depth=log (dis-near + 1.0) /log (far-near + 1.0);
					float depth= (dis-near ) / (far-near );

			gl_FragColor=vec4(depth,depth,depth,1);
					gl_FragDepth=depth;

		}
		else
		{
			discard;
		}
	}
}
