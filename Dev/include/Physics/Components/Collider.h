#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"



class Collider : public Component
{
protected:
	bool isTrigger = false;
public:
	Collider() {};
	Collider(GameObject * pParent) {
		m_GameObjectParent_ = pParent;
	}
	~Collider() {};


	virtual void Update(double dt) = 0;
	virtual void LateUpdate(double dt) = 0;

	virtual void Destroy() = 0;
	virtual void Start() = 0;

	//void OnTriggerEnter() {
	//};
	//void OnTriggerStay() {};
	//void OnTriggerExit() {};
	//void OnCollided() {};

};

#endif
