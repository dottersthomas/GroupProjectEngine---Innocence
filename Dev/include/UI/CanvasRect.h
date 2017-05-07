#ifndef _CANVAS_ELEMENT_RECT_H_
#define _CANVAS_ELEMENT_RECT_H_

#include "CanvasElement.h"
#include "GUIMesh.h"

#include <glm\gtc\matrix_transform.hpp>


//Canvas element for drawing a simple rectangle.
class CanvasRect : public CanvasElement {

private:

	//GUI Mesh to be rendered.
	GUIMesh m_Mesh_;
	glm::vec4 m_Colour_;


	glm::mat4 m_Model_;

public:

	CanvasRect(CanvasElement * pParent, glm::vec4 pColour) {
		m_Parent_ = pParent;
		m_Colour_ = pColour;

		m_Mesh_ = GUIMesh(GL_STATIC_DRAW);
	}
	void Start();

	void Update(float dt);

	void Render();


	void Destroy();

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<CanvasRect, CanvasElement>("CanvasRect")
			.addConstructor<void(*)(CanvasElement*, glm::vec4)>()
			.endClass();
	}
};

#endif