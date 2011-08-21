uniform vec3 light;
varying float distance;

void main ()
{
	distance=(length(light-gl_Vertex.xyz)+1.1)/300.0;
	gl_Position=ftransform();
}
