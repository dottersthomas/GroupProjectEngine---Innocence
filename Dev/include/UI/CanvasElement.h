#ifndef _CANVAS_ELEMENT_H_	
#define _CANVAS_ELEMENT_H_

#include <glm\glm.hpp>

#include <vector>
#include <iostream>

#include "CanvasElementVectorWrapper.h"
#include "GuiStates.h"

#include <GL\glew.h>


struct CanvasElementVectorWrapper;

//Mostly abstract class to allow a Canvas component to hold many types of element sharing a common class.
class CanvasElement {

protected:

	//each element has a parent element, to create a tree.
	CanvasElement * m_Parent_;

	//Its parents absolute position.
	glm::vec3 m_ParentAbsolutePosition_;

	//Position and Scale. Rotation isnt necessary right now so isn't implemented.
	glm::vec2 m_Position_; 
	glm::vec2 m_Scale_; 

	glm::vec4 m_Colour_;

	//current state for the element.
	GuiStates m_CurrentState_;

	CanvasElementVectorWrapper::t_Canvas_Elements_Vector_ m_Children_;

	std::string m_Shader_;


public:

	virtual void Start() = 0;

	virtual void Update(float dt) = 0;

	//Update all the children for the element.
	void UpdateChildren(float dt) {
		if(m_Children_.size() > 0)
			for (CanvasElementVectorWrapper::t_Canvas_Elements_Iter iter = m_Children_.begin(); iter != m_Children_.end(); ++iter) {
				(*iter)->Update(dt);
			}
	}

	virtual void Render() = 0;
	virtual void Destroy() = 0;


	std::string RequestShader() const {
		return m_Shader_;
	}

	void SetShader(std::string pShader) {
		m_Shader_ = pShader;
	}


	glm::vec2 getPosition() const {
		return m_Position_;
	}

	glm::vec2 getScale() const {
		return m_Scale_;
	}


	void setPosition(glm::vec2 pPosition) {
		m_Position_ = pPosition;
	}


	void setScale(glm::vec2 pScale) {
		m_Scale_ = pScale;
	}

	void setColour(glm::vec4 pColour) {
		m_Colour_ = pColour;
	}

	glm::vec4 getColour() const {
		return m_Colour_;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<CanvasElement>("CanvasElement")
			.addProperty("shader", &CanvasElement::RequestShader, &CanvasElement::SetShader)
			.addProperty("position", &CanvasElement::getPosition, &CanvasElement::setColour)
			.addProperty("scale", &CanvasElement::getScale, &CanvasElement::setScale)
			.addProperty("colour", &CanvasElement::getColour)
			.endClass();
	}
};


#endif