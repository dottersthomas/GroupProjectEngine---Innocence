#pragma once
#include "General\GameObject.h"
class CollisionData
{

public:

	GameObject target;
	CollisionData()
	{

	}
	CollisionData(GameObject bc)
	{
		target = bc;
	}

};