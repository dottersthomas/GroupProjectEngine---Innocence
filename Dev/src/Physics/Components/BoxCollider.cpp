#include "Physics\Components\BoxCollider.h"

BoxCollider::BoxCollider(GameObject * pParent)
{
	m_GameObjectParent_ = pParent;
}
BoxCollider::~BoxCollider()
{

}



void BoxCollider::Destroy()
{

}
void BoxCollider::Start()
{
	RenderComponent * rc = m_GameObjectParent_->GetComponentByType<RenderComponent>();
	vector<Model> model = rc->getModels();

	glm::vec3 tempMin = glm::vec3(0,0,0);
	glm::vec3 tempMax = glm::vec3(0, 0, 0);
	
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

void BoxCollider::Update(double dt)
{	
	 glm::vec4 newMax = glm::vec4(boundingBox.GetMax(),1) * m_GameObjectParent_->GetComponentByType<TransformComponent>()->getModelMatrix();
	 glm::vec4 newMin = glm::vec4(boundingBox.GetMin(), 1) * m_GameObjectParent_->GetComponentByType<TransformComponent>()->getModelMatrix();

	 boundingBox.SetMax(newMax.x, newMax.y, newMax.z);
	 boundingBox.SetMin(newMin.x, newMin.y, newMin.z);

	 glLineWidth(2.5);
	 glColor3f(1.0, 0.0, 0.0);
	 glBegin(GL_LINES);
	 glVertex3f(0.0, 0.0, 0.0);
	 glVertex3f(15, 0, 0);
	 glEnd();


}

void BoxCollider::LateUpdate(double dt)
{

}

