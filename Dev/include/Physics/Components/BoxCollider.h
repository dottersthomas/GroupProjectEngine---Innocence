#ifndef _BOX_COLLOIDER_H_
#define _BOX_COLLOIDER_H_
#include "General\GameObject.h"
#include "Physics\Components\Collider.h"
#include "Physics\Components\Box.h"
#include "Rendering\Components\RenderComponent.h"
#include "glm\gtx\transform.hpp"


class BoxCollider : public Collider
{
private:
	Box boundingBox;

public:
	BoxCollider(GameObject * pParent, bool isTrigger);
	BoxCollider()
	{

	}
	~BoxCollider();
	void LateUpdate(double dt);
	void Destroy();
	void Start();
	void Update(double dt);

	void CustomBounds(glm::vec3 min, glm::vec3 max);

	Box GetBounds()
	{
		return boundingBox;
	}

};

#endif