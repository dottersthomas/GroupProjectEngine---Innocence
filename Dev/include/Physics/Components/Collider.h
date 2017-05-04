#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "CollisionData.h"



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

	void OnTriggerEnter(CollisionData cd) {
		std::cout << "Enter" << endl;
		collided = true;
	};
	void OnTriggerStay(CollisionData cd) {
		std::cout << "Stay" << endl;
	};
	void OnTriggerExit() {
		std::cout << "Exit" << endl;
		collided = false;
	};
	void OnCollided(CollisionData cd) {

	};

};

#endif
