#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_


#include "Component.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//The Transform component. All Objects are given a transform component by default, which if necessary could be removed later.
class TransformComponent : public Component
{
private:
	//Position, Rotation and Scale.
	glm::vec3 m_Position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale_ = glm::vec3(1.0f, 1.0f, 1.0f);


	//Right and Direction vectors of the transformations.
	glm::vec3 m_Right_;
	glm::vec3 m_Direction_;

	//Model Matrix.
	glm::mat4 m_Model_;



	//If the transform is dirty and requires and update.
	bool m_bDirty_;

public:
	TransformComponent(GameObject * pParent);


	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();

	glm::vec3 getPosition() const
	{
		return m_Position_;
	}

	glm::vec3 getRotation() const
	{
		return m_Rotation_;
	}

	glm::vec3 getScale() const
	{
		return m_Scale_;
	}

	glm::vec3 getRight() const
	{
		return m_Right_;
	}

	glm::vec3 getDirection() const
	{
		return m_Direction_;
	}

	void setPosition(glm::vec3 pPosition)
	{
		m_Position_ = pPosition;
		m_bDirty_ = true;
	}

	void setRotation(glm::vec3 pRotation)
	{
		m_Rotation_ = pRotation;
		m_bDirty_ = true;

	}

	void setScale(glm::vec3 pScale)
	{
		m_Scale_ = pScale;
		m_bDirty_ = true;
	}

	void setRight(glm::vec3 pRight)
	{
		m_Right_ = pRight;
	}

	void setDirection(glm::vec3 pDirection)
	{
		m_Direction_ = pDirection;
	}

	glm::mat4 getModelMatrix()
	{
		return m_Model_;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<TransformComponent, Component>("TransformComponent")
			.addProperty("position", &TransformComponent::getPosition, &TransformComponent::setPosition)
			.addProperty("rotation", &TransformComponent::getRotation, &TransformComponent::setRotation)
			.addProperty("scale", &TransformComponent::getScale, &TransformComponent::setScale)
			.addProperty("direction", &TransformComponent::getDirection, &TransformComponent::setDirection)
			.addProperty("right", &TransformComponent::getRight, &TransformComponent::setRight)
			.endClass();
	}
};

#endif // !_TRANSFORMCOMPONENT_H_#
