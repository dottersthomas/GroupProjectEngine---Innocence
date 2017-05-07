#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Component.h"
#include "Rendering\Mesh.h"
#include "Physics\Components\TransformComponent.h"
#include "Rendering\Material.h"
#include "Rendering\Model.h"

//Type of Component to be rendered, if it is a solid colour, or if it uses a Texture for rendering.
enum ComponentType {
	COLOUR,
	TEXTURE
};


//The Render component. This holds all meshes to be rendered and processes them accordingly.
class RenderComponent : public Component {

private:

	//Vectors of meshes and its iterators.
	typedef std::vector<Mesh*> t_Mesh_vector_;
	typedef t_Mesh_vector_::iterator t_Mesh_vector_Iterator_;

	//Shader to be used by the render component. 1 Shader per component.
	std::string m_Shader_;
	t_Mesh_vector_ m_Meshes_;
	TransformComponent* transformComponent;

	std::vector<Model> m_Models_;

	//Type to render.
	int m_RenderType_;

	//If the render component should actually render.
	bool shouldDraw = true;
	bool cullBackFace = true;

	Material m_Material_;

public:

	RenderComponent(GameObject * pParent, std::string sShader, int pType = COLOUR);

	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();

	//Attach a mesh to the render component to be rendered. Rendering occurs in the order they are attached.
	void AttachMesh(Mesh* pMesh);

	int AttachModel(Model pModel) {
		m_Models_.push_back(pModel);
		return m_Models_.size() - 1;
	}

	void RemoveModel(int position) {
		m_Models_.erase(m_Models_.begin() + position);
	}

	//Render function.
	void Render(glm::mat4 pProj, glm::mat4 pView, std::string pShader = "");

	void toggleDrawing(bool pToggle) {
		shouldDraw = pToggle;
	}

	void toggleBackCulling(bool pToggle) {
		cullBackFace = pToggle;
	}

	void attachMaterial(Material pMat) {
		m_Material_ = pMat;
	}

	Material& getMaterial() {
		return m_Material_;
	}

	std::vector<Model>& getModels() {
		return m_Models_;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<RenderComponent, Component>("RenderComponent")
			.addConstructor<void(*)(GameObject*, std::string, int)>()
			.addFunction("toggleDrawing", &RenderComponent::toggleDrawing)
			.endClass();
	}
};

#endif 
