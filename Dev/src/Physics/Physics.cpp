#include "Physics\Physics.h"


Physics::Physics(GLFWwindow * pWindow) {
	m_Window_ = pWindow;
}

void Physics::Render() {}

void Physics::setScene(Scene * pScene) {
	m_CurrentScene_ = pScene;
}

void Physics::update(float dt) {

	EulerMove(dt);
	CollisionDetection(dt);

}

void Physics::CollisionDetection(float dt)
{
	bool collided; 
	for (std::vector<GameObject>::iterator iter = m_sceneGameObjectsCollide_.begin(); iter != m_sceneGameObjectsCollide_.end(); ++iter) {
		

		BoxCollider * test = iter->GetComponentByType<BoxCollider>();
		for (std::vector<GameObject>::iterator iter2 = m_sceneGameObjectsCollide_.begin(); iter2 != m_sceneGameObjectsCollide_.end(); ++iter2)
		{
			BoxCollider * test2 = iter2->GetComponentByType<BoxCollider>();
			if (test != test2)
			{
				test->Update(dt);
				test2->Update(dt);
				collided = AABBAABBCollision(test, test2);
				if (collided)
				{
					//cout << "Collided" << endl;
					glm::vec3 diff = test2->GetBounds().GetMax() - test->GetBounds().GetMin();
					glm::vec3 diff2 = test2->GetBounds().GetMin() - test->GetBounds().GetMax();

			
					CollisionData *  cd = new CollisionData(*iter2, diff, diff2);
					ResolveCollision(*iter,cd);

				}
				else
				{
					if (test->getTrigger() == true && test->getCollided() == true)
					{
						GameObject  go = *iter2;
						CollisionData go2;
						if (iter->GetComponentByType<BoxCollider>()->getCD() != nullptr)
						{
							go2 = *iter->GetComponentByType<BoxCollider>()->getCD();
							if (go2.target.m_Name_ == go.m_Name_)
							{
								test->OnTriggerExit();
							}
						}
					}
				}
		
				//	std::cout << collided << endl;
			}
		}



	}
}

void Physics::Stop(GameObject go)
{
	if (go.CheckComponentTypeExists<RigidBody>())
	{
		go.GetComponentByType<RigidBody>()->SetVel(glm::vec3(0, 0, 0));
	}
}
void Physics::EulerMove(float dt)
{
	for (std::vector<GameObject>::iterator iter = m_sceneGameObjectsMove_.begin(); iter != m_sceneGameObjectsMove_.end(); ++iter)
	{
		RigidBody * body = iter->GetComponentByType<RigidBody>();
		TransformComponent * transform = iter->GetComponentByType<TransformComponent>();
		glm::vec3 g = glm::vec3(0, 0, 0);
		if (body->GetGround() == false)
		{
			g = gravity * glm::vec3(0, -1, 0) * body->GetGravityScale()*dt;
		}
		glm::vec3 f = friction * 0.5f * glm::vec3(1, 0, 1)*dt;

		

		body->SetVel(body->GetVel() + (body->GetAcc())*dt);

		body->SetVel(body->GetVel() - body->GetVel()*f + g);

		if (body->GetVel().x < 0.001f && body->GetVel().x > -0.001f)
		{
			body->SetVel(glm::vec3(0,body->GetVel().y, body->GetVel().z));
		}
		if (body->GetVel().z < 0.001f && body->GetVel().z > -0.001f)
		{
			body->SetVel(glm::vec3(body->GetVel().x, body->GetVel().y, 0));
		}
		glm::vec3 newPos = transform->getPosition() + body->GetVel() *dt;
		
		transform->setPosition(newPos);
		body->SetAcc(glm::vec3(0, 0, 0));
	}

}

bool Physics::AABBAABBCollision(BoxCollider * boxC1, BoxCollider * boxC2)
{
	Box box1 = boxC1->GetBounds();
	Box box2 = boxC2->GetBounds();
	return(box1.GetMax().x >= box2.GetMin().x &&
		box1.GetMin().x <= box2.GetMax().x &&
		box1.GetMax().y >= box2.GetMin().y &&
		box1.GetMin().y <= box2.GetMax().y &&
		box1.GetMax().z >= box2.GetMin().z &&
		box1.GetMin().z <= box2.GetMax().z);
}

void Physics::ResolveCollision(GameObject& go, CollisionData * cd) {

	BoxCollider * bc = go.GetComponentByType<BoxCollider>();
	if (bc->getTrigger())
	{
		if (!bc->getCollided())
		{
			bc->OnTriggerEnter(cd);
		}
		else
		{
			if (bc->getCollided())
			{
				bc->OnTriggerStay(cd);
			}
		}
	}
	else
	{
		bc->OnCollided(cd);
	}

}

void Physics::updateObjects()
{
	if (m_CurrentScene_->M_bIsDirty) {
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

	}
	
	
	
}