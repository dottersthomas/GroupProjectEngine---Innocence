#include "Physics\Components\Box.h"



Box::Box()
{
	minX = -1;
	minY = -1;
	minZ = -1;
	maxX = 1;
	maxY = 1;
	maxZ = 1;
}
Box::Box(glm::vec3 minPoints, glm::vec3 maxPoints)
{
	minX = minPoints.x;
	minY = minPoints.y;
	minZ = minPoints.z;
	maxX = maxPoints.x;
	maxY = maxPoints.y;
	maxZ = maxPoints.z;

	ominX = minX;
	ominY = minY;
	ominZ = minZ;
	omaxX = maxX;
	omaxY = maxY;
	omaxZ = maxZ;
	width = maxX - minX;
	height = maxY - minY;
	depth = maxZ - minZ;
	midPoint = glm::vec3(width / 2, height / 2, depth / 2);
	
}
Box::~Box()
{

}

glm::vec3 Box::GetMax()
{
	return glm::vec3(maxX, maxY, maxZ);
}
glm::vec3 Box::GetMin()
{
	return glm::vec3(minX, minY, minZ);
}
glm::vec3 Box::GetOMax()
{
	return glm::vec3(omaxX, omaxY, omaxZ);
}
glm::vec3 Box::GetOMin()
{
	return glm::vec3(ominX, ominY, ominZ);
}

void Box::SetMax(float x, float y, float z)
{
	maxX = x;
	maxY = y;
	maxZ = z;

	width = maxX - minX;
	height = maxY - minY;
	depth = maxZ - minZ;
	midPoint = glm::vec3(width / 2, height / 2, depth / 2);
}
void Box::SetMin(float x, float y, float z)
{
	minX = x;
	minY = y;
	minZ = z;

	width = maxX - minX;
	height = maxY - minY;
	depth = maxZ - minZ;
	midPoint = glm::vec3(width / 2, height / 2, depth / 2);
}