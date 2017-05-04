#pragma once
#include "Component.h"
#include "glm\common.hpp"

class RigidBody : public Component
{
private:
	
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass;
	float gravityScale;


public:

	RigidBody();

	void Update(double dt);

	//Called at the end of every tick, mainly for maintenance uses.
	void LateUpdate(double dt);

	//Called when the component is destroyed.
	void Destroy();

	//Called when the component starts.
	void Start();

	glm::vec3 GetVel()
	{
		return velocity;
	}

	glm::vec3 GetAcc()
	{
		return acceleration;
	}
	float GetGravityScale()
	{
		return gravityScale;
	}

	void SetGravScale(float f)
	{

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