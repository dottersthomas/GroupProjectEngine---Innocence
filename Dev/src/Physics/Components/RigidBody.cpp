#include "Physics\Components\RigidBody.h"



RigidBody::RigidBody()
{
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	gravityScale = 1.f;
	grounded = false;
}

void RigidBody::Update(double dt)
{

	
}

//Called at the end of every tick, mainly for maintenance uses.
void RigidBody::LateUpdate(double dt)
{

}

//Called when the component is destroyed.
void RigidBody::Destroy()
{

}

//Called when the component starts.
void RigidBody::Start()
{

}