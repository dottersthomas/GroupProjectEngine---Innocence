#include "Physics\Components\BoxCollider.h"

BoxCollider::BoxCollider(GameObject * pParent, bool isTrigger)
{
	m_GameObjectParent_ = pParent;
	BoxCollider::isTrigger = isTrigger;
	RenderComponent * rc = m_GameObjectParent_->GetComponentByType<RenderComponent>();
	vector<Model> model = rc->getModels();

	glm::vec3 tempMin = rc->getModels().at(0).getBoundingMin();
	glm::vec3 tempMax = rc->getModels().at(0).getBoundingMax();

	for (auto m : model)
	{
		glm::vec3 temp = m.getBoundingMax();
		if (temp.x > tempMax.x)
		{
			tempMax.x = temp.x;
		}
		if (temp.y > tempMax.y)
		{
			tempMax.y = temp.y;
		}
		if (temp.z > tempMax.z)
		{
			tempMax.z = temp.z;
		}
		temp = m.getBoundingMin();
		if (temp.x < tempMin.x)
		{
			tempMin.x = temp.x;
		}
		if (temp.y < tempMin.y)
		{
			tempMin.y = temp.y;
		}
		if (temp.z < tempMin.z)
		{
			tempMin.z = temp.z;
		}

	}

	boundingBox = Box(tempMin, tempMax);
}
BoxCollider::~BoxCollider()
{

}



void BoxCollider::Destroy()
{

}
void BoxCollider::Start()
{

}


void BoxCollider::CustomBounds(glm::vec3 min, glm::vec3 max)
{
	boundingBox = Box(min, max);
}

void BoxCollider::Update(double dt)
{
	glm::vec3 newMax = boundingBox.GetOMax();
	newMax = newMax * m_GameObjectParent_->GetComponentByType<TransformComponent>()->getScale();
	newMax += m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition();

	glm::vec3 newMin = boundingBox.GetOMin();
	newMin = newMin * m_GameObjectParent_->GetComponentByType<TransformComponent>()->getScale();
	newMin += m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition();

	 boundingBox.SetMax(newMax.x, newMax.y, newMax.z);
	 boundingBox.SetMin(newMin.x, newMin.y, newMin.z);


}

void BoxCollider::LateUpdate(double dt)
{

}

