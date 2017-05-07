#ifndef _CANVAS_BUTTON_H_
#define _CANVAS_BUTTON_H_

#include <functional>

#include "CanvasElement.h"
#include "GUIMesh.h"

#include <glm\gtc\matrix_transform.hpp>


//Button Element for GUI Rendering
class CanvasButton : public CanvasElement {

	//the click function to be ran upon the button being pressed type defintion.
	typedef std::function< void(void) > t_Click_Handler;

private:

	//Mesh of the Button for drawing.
	GUIMesh m_Mesh_;
	glm::vec4 m_Colour_;
	glm::vec4 m_HoverColour_;


	glm::mat4 m_Model_;
	//the click function to be ran upon the button being pressed
	t_Click_Handler m_ClickHandle = nullptr;


public:

	CanvasButton(CanvasElement * pParent, glm::vec4 pColour) {
		m_Parent_ = pParent;
		m_Colour_ = pColour;

		m_Mesh_ = GUIMesh(GL_STATIC_DRAW);

	}

	void Start();

	void Update(float dt);

	void Render();

	void Destroy();

	void onclick();

	glm::vec4 getHoverColour() const
	{
		return m_HoverColour_;
	}

	void setHoverColour(glm::vec4 pColour) {
		m_HoverColour_ = pColour;
	}

	void setOnClickListener(t_Click_Handler handler) {
		m_ClickHandle = handler;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<CanvasButton, CanvasElement>("CanvasButton")
			.addConstructor<void(*)(CanvasElement*, glm::vec4)>()
			.addProperty("hoverColour", &CanvasButton::getHoverColour, &CanvasButton::setHoverColour)
			.endClass();
	}
};


#endif // !_CANVAS_BUTTON_H_
