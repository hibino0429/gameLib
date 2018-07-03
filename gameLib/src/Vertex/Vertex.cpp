#include "Vertex.h"



Vertex::Vertex()
	: x(0.0f),y(0.0f),z(0.0f)
{
	
}
Vertex::Vertex(float x, float y, float z)
	: x(x),y(y),z(z)
{

}
Vertex::Vertex(float x, float y, float z, float color0, float color1)
	: x(x),y(y),z(z)
{
	color[0] = color0;
	color[1] = color1;
}
Vertex::Vertex(const Vertex& vertex)
	: x(vertex.x),y(vertex.y),z(vertex.z)
{

}

Vertex::~Vertex()
{

}