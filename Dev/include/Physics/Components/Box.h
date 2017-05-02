#pragma once
#include "glm\glm.hpp"

class Box
{
private:
	float maxX, minX, maxY, minY, maxZ, minZ;
	glm::vec3 midPoint;
public:
	Box();
	Box(glm::vec3 minPoints, glm::vec3 maxPoints);
	glm::vec3 GetMax();
	glm::vec3 GetMin();
	void SetMax(float x, float y, float z);
	void SetMin(float x, float y, float z);
	~Box();
};