#include "Physics\Physics.h"


Physics::Physics(GLFWwindow * pWindow) {
	m_Window_ = pWindow;
}

void Physics::Render() {}

void Physics::setScene(Scene * pScene) {}

void Physics::update(float dt) {

	std::vector<GameObject> temp = *m_CurrentScene_->getGameObjects();
	for (std::vector<GameObject>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
		if ((*iter).CheckComponentTypeExists<BoxCollider>()) {
			m_sceneGameObjectsCollide_.push_back(*iter); //Add GameObject to the list.
		}
		if ((*iter).CheckComponentTypeExists<RigidBody>())
		{
			m_sceneGameObjectsMove_.push_back(*iter);
		}
	}

	EulerMove(dt);
	CollisionDetection();

}

void Physics::CollisionDetection()
{
	bool collided; 
	for (std::vector<GameObject>::iterator iter = m_sceneGameObjectsCollide_.begin(); iter != m_sceneGameObjectsCollide_.end(); ++iter) {
		
		BoxCollider * test = iter->GetComponentByType<BoxCollider>();
		for (std::vector<GameObject>::iterator iter2 = m_sceneGameObjectsCollide_.begin(); iter2 != m_sceneGameObjectsCollide_.end(); ++iter2)
		{
			BoxCollider * test2 = iter->GetComponentByType<BoxCollider>();
			if (test != test2)
			{
				collided = AABBAABBCollision(test, test2);
			}
		}
		

		
	}
}

void Physics::EulerMove(float dt)
{
	for (std::vector<GameObject>::iterator iter = m_sceneGameObjectsMove_.begin(); iter != m_sceneGameObjectsMove_.end(); ++iter)
	{
		RigidBody * body = iter->GetComponentByType<RigidBody>();
		TransformComponent * transform = iter->GetComponentByType<TransformComponent>();
		body->SetVel(body->GetVel() += body->GetAcc()*dt * friction);
		glm::vec3 newPos = transform->getPosition() + body->GetVel() *dt;
		transform->setPosition(newPos);
		body->SetAcc(glm::vec3(0, 0, 0));
	}
	
}

bool Physics::AABBAABBCollision(BoxCollider * boxC1, BoxCollider * boxC2)
{
	Box box1 = boxC1->GetBounds();
	Box box2 = boxC2->GetBounds();
	return(box1.GetMax().x > box2.GetMin().x &&
		box1.GetMin().x < box2.GetMax().x &&
		box1.GetMax().y > box2.GetMin().y &&
		box1.GetMin().y < box2.GetMax().y &&
		box1.GetMax().z > box2.GetMin().z &&
		box1.GetMin().z < box2.GetMax().z);
}

void Physics::ResolveCollision() {

}