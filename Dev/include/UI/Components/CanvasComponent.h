#ifndef _CANVAS_COMPONENT_H_
#define _CANVAS_COMPONENT_H_

#include "Component.h"
#include "UI\CanvasElement.h"
#include "UI\CanvasElementVectorWrapper.h"

#include <vector>

class CanvasComponent : public Component {

private:
	CanvasElementVectorWrapper::t_Canvas_Elements_Vector_ m_Elements_;
public:

	//Canvas Component to hold all the GUI elements
	CanvasComponent(GameObject * pObject);

	void Update(double dt);
	void LateUpdate(double dt);
	void Render(glm::mat4 pProjection, glm::mat4 pView);

	void Destroy();
	void Start();

	void AddElement(CanvasElement * pElement) {
		m_Elements_.push_back(pElement);
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<CanvasComponent, Component>("RenderComponent")
			.addConstructor<void(*)(GameObject*)>()
			.addFunction("addElement", &CanvasComponent::AddElement)
			.endClass();
	}
};

#endif