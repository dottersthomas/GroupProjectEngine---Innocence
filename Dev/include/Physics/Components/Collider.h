#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "CollisionData.h"
#include "RigidBody.h"

#define TRIGGER_NONE 0
#define TRIGGER_ENTER 1
#define TRIGGER_STAY 2
#define TRIGGER_EXIT 3

class Collider : public Component
{
protected:
	bool isTrigger = false;
	bool collided = false;


	CollisionData* m_CD;
	int triggerStatus = TRIGGER_NONE;

public:
	Collider() {};
	Collider(GameObject * pParent) {
		m_GameObjectParent_ = pParent;
	}
	~Collider() {};

	CollisionData* getCD()
	{
		return m_CD;
	}

	bool getTrigger() const
	{
		return isTrigger;
	}

	bool getCollided() const
	{
		return collided;
	}

	virtual void Update(double dt) = 0;
	virtual void LateUpdate(double dt) = 0;

	virtual void Destroy() = 0;
	virtual void Start() = 0;

	void OnTriggerEnter(CollisionData * cd) {
		collided = true;
		triggerStatus = TRIGGER_ENTER;
		m_CD = cd;
	};

	void OnTriggerStay(CollisionData * cd) {
		triggerStatus = TRIGGER_STAY;
		m_CD = cd;
	};

	void OnTriggerExit() {
		collided = false;
		triggerStatus = TRIGGER_EXIT;
		m_CD = nullptr;
	};

	void resetTriggerStatus()
	{
		triggerStatus = TRIGGER_NONE;
	}

	void OnCollided(CollisionData * cd) {
		
		if (m_GameObjectParent_->CheckComponentTypeExists<RigidBody>())
		{
			if (!cd->target.GetComponentByType<Collider>()->getTrigger())
			{
				RigidBody * rb = m_GameObjectParent_->GetComponentByType<RigidBody>();
				glm::vec3 newPos = m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition();

				if (rb->GetVel().x > 0)
				{
					
					
						if (cd->diff2.x < 0 && cd->diff2.x > -1)
						{
							newPos.x += cd->diff2.x + 0.1;
							rb->SetVel(glm::vec3(0, rb->GetVel().y, 0));
						}
					

				}
				else if (rb->GetVel().x < 0)
				{
					
					
						if (cd->diff.x > 0 && cd->diff.x < 1)
						{
							newPos.x += cd->diff.x - 0.1;
							rb->SetVel(glm::vec3(0, rb->GetVel().y, 0));

						}
					
				}

				if (rb->GetVel().z > 0)
				{
					
					
						if (cd->diff2.z < 0 && cd->diff2.z > -1)
						{
							newPos.z += cd->diff2.z - 0.10;
							rb->SetVel(glm::vec3(0, rb->GetVel().y, 0));
						}
					

				}
				else if (rb->GetVel().z < 0)
				{
					
					
						if (cd->diff.z > 0 && cd->diff.z < 1)
						{
							newPos.z += cd->diff.z + 0.10;
							rb->SetVel(glm::vec3(0, rb->GetVel().y, 0));
						}
					
				}
				//	if (rb->GetGround() == false)
				//	{
				if (rb->GetVel().y > 0)
				{
					if (cd->diff.y < 1)
						newPos.y += cd->diff.y - 0.01;
					rb->SetVel(glm::vec3(rb->GetVel().x, 0, rb->GetVel().z));


				}
				else if (rb->GetVel().y < 0)
				{
					if (cd->diff.y < 1)
						newPos.y += cd->diff.y + 0.01;
					rb->SetVel(glm::vec3(rb->GetVel().x, 0, rb->GetVel().z));
					

				}

				if (cd->target.m_Name_ == "Ground")
				{
					rb->setGrounded(true);
				}
				



			//	}
				m_GameObjectParent_->GetComponentByType<TransformComponent>()->setPosition(newPos);
			}
		}

	};

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<Collider>("Collider")
			.addData<int>("triggerStatus", &Collider::triggerStatus, false)
			.addProperty("trigger", &Collider::getTrigger)
			.addData<CollisionData*>("otherCollider", &Collider::m_CD)
			.endClass();
	}
};

#endif
