#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <memory>
#include <iostream>
#include "General\GameObject.h"
#include <functional>

class GameObject;

//Base Component Class. This class is inherited by all other components.
class Component
{
protected:
	GameObject * m_GameObjectParent_;
public:
	virtual ~Component() = default;

	std::string M_ComponentName;

	//Called every tick.
	virtual void Update(double dt) = 0;

	//Called at the end of every tick, mainly for maintenance uses.
	virtual void LateUpdate(double dt) = 0;

	//Called when the component is destroyed.
	virtual void Destroy() = 0;

	//Called when the component starts.
	virtual void Start() = 0;

	//Set the components parent.
	void setParent(GameObject * pParent)
	{
		m_GameObjectParent_ = pParent;
	}

};

#endif