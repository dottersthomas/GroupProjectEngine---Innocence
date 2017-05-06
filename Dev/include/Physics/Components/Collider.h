#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "CollisionData.h"
#include "RigidBody.h"




class Collider : public Component
{
protected:
	bool isTrigger = false;
	bool collided = false;
	CollisionData cd;
public:
	Collider() {};
	Collider(GameObject * pParent) {
		m_GameObjectParent_ = pParent;
	}
	~Collider() {};

	bool getTrigger()
	{
		return isTrigger;
	}
	bool getCollided()
	{
		return collided;
	}
	virtual void Update(double dt) = 0;
	virtual void LateUpdate(double dt) = 0;

	virtual void Destroy() = 0;
	virtual void Start() = 0;

	void OnTriggerEnter(CollisionData * cd) {
		std::cout << "Enter" << endl;
		collided = true;
	};
	void OnTriggerStay(CollisionData * cd) {

		std::cout << "Stay" << endl;
	};
	void OnTriggerExit() {
		std::cout << "Exit" << endl;
		collided = false;
	};
	void OnCollided(CollisionData * cd) {
		
		if (m_GameObjectParent_->CheckComponentTypeExists<RigidBody>())
		{
			RigidBody * rb = m_GameObjectParent_->GetComponentByType<RigidBody>();
			glm::vec3 newPos = m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition();
			
			if (rb->GetVel().x > 0)
			{
				if (rb->GetVel().x > std::fabs(rb->GetVel().z))
				{
					if (cd->diff2.x < 0 && cd->diff2.x > -1)
					{
						newPos.x += cd->diff2.x + 0.01;
						rb->SetVel(glm::vec3(0, rb->GetVel().y, rb->GetVel().z));
					}
				}

			}
			else if(rb->GetVel().x < 0)
			{
 				if (rb->GetVel().x < std::fabs(rb->GetVel().z))
				{
					if (cd->diff.x > 0 && cd->diff.x < 1)
					{
						newPos.x += cd->diff.x - 0.01;
						rb->SetVel(glm::vec3(0, rb->GetVel().y, rb->GetVel().z));

					}
				}
			}
			
			if (rb->GetVel().z > 0)
			{
				if (rb->GetVel().z > std::fabs(rb->GetVel().x))
				{
					if (cd->diff2.z < 0 && cd->diff2.z > -1)
					{
						newPos.z += cd->diff2.z - 0.10;
						rb->SetVel(glm::vec3(rb->GetVel().x, rb->GetVel().y, 0));
					}
				}

			}
			else if (rb->GetVel().z < 0 )
			{     
				if (rb->GetVel().z < std::fabs(rb->GetVel().x))
				{
					if (cd->diff.z > 0 && cd->diff.z < 1)
					{
						newPos.z += cd->diff.z + 0.01;
						rb->SetVel(glm::vec3(rb->GetVel().x, rb->GetVel().y, 0));
					}
				}
			}
		//	if (rb->GetGround() == false)
		//	{
				if (rb->GetVel().y > 0)
				{
					if (cd->diff.y < 1)
					newPos.y += cd->diff.y-0.01;
					rb->SetVel(glm::vec3(rb->GetVel().x, 0, rb->GetVel().z));
	

				}
				else if (rb->GetVel().y < 0)
				{
					if (cd->diff.y < 1)
					newPos.y += cd->diff.y + 0.01;
					rb->SetVel(glm::vec3(rb->GetVel().x, 0, rb->GetVel().z));
				
				}

			//	rb->setGrounded(true);
				

				
		//	}
			m_GameObjectParent_->GetComponentByType<TransformComponent>()->setPosition(newPos);
		}

	};

};

#endif
