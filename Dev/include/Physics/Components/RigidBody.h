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
	bool grounded;


public:

	RigidBody();

	void Update(double dt);

	//Called at the end of every tick, mainly for maintenance uses.
	void LateUpdate(double dt);

	//Called when the component is destroyed.
	void Destroy();

	//Called when the component starts.
	void Start();

	glm::vec3 GetVel() const
	{
		return velocity;
	}

	glm::vec3 GetAcc() const
	{
		return acceleration;
	}

	float GetGravityScale() const
	{
		return gravityScale;
	}

	bool GetGround() const
	{
		return grounded;
	}

	void setGrounded(bool b)
	{
		grounded = b;
	}

	void SetGravScale(float f)
	{
		gravityScale = f;
	}

	void SetVel(glm::vec3 vel)
	{
		velocity = vel;
	}

	void SetAcc(glm::vec3 acc)
	{
		acceleration = acc;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<RigidBody, Component>("RigidBody")
			.addConstructor<void(*)()>()
			.addProperty<glm::vec3>("velocity", &RigidBody::GetVel, &RigidBody::SetVel)
			.addProperty<glm::vec3>("acceleration", &RigidBody::GetAcc, &RigidBody::SetAcc)
			.addProperty<float>("gravityScale", &RigidBody::GetGravityScale, &RigidBody::SetGravScale)
			.addProperty<bool>("grounded", &RigidBody::GetGround, &RigidBody::setGrounded)
			.endClass();
	}
};