#include "Vertex.h"



Vertex::Vertex()
	: pos(Vec3(0.0f,0.0f,0.0f))
	, uv(UVData(0.0f,0.0f))
	, normal(Vec3(0.0f,0.0f,0.0f))
	, diffuse(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	
}
Vertex::Vertex(float x, float y, float z)
	: pos(Vec3(x, y, z))
	, uv(UVData(0.0f, 0.0f))
	, normal(Vec3(0.0f, 0.0f, 0.0f))
	, diffuse(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	
}
Vertex::Vertex(float x, float y, float z, float uvX, float uvY)
	: pos(Vec3(x, y, z))
	, uv(UVData(uvX, uvY))
	, normal(Vec3(0.0f, 0.0f, 0.0f))
	, diffuse(Vec4(1.0f, 1.0f, 1.0f,1.0f))
{
	
}
Vertex::Vertex(const Vertex& vertex)
	: pos(vertex.pos)
	, uv(vertex.uv)
	, normal(vertex.normal)
	, diffuse(vertex.diffuse)
{
	
}

Vertex::~Vertex()
{

}