#pragma once
#include "Component.h"
#include "glm\common.hpp"

class RigidBody : public Component
{
private:
	
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass;


public:

	RigidBody()
	{

	}

	glm::vec3 GetVel()
	{
		return velocity;
	}

	glm::vec3 GetAcc()
	{
		return acceleration;
	}

	void SetVel(glm::vec3 vel)
	{
		velocity = vel;
	}

	void SetAcc(glm::vec3 acc)
	{
		acceleration = acc;
	}

};