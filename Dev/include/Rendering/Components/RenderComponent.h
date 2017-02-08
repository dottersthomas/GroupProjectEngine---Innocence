#ifndef _RENDER_COMPONENT_H_
#define _RENDER_COMPONENT_H_

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Component.h"
#include "Rendering\Mesh.h"
#include "Physics\Components\TransformComponent.h"

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

	//Type to render.
	int m_RenderType_;

	//If the render component should actually render.
	bool shouldDraw = true;

public:

	RenderComponent(GameObject * pParent, std::string sShader, int pType = COLOUR);

	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();

	//Attach a mesh to the render component to be rendered. Rendering occurs in the order they are attached.
	void AttachMesh(Mesh* pMesh);

	//Render function.
	void Render(glm::mat4 pProj, glm::mat4 pView);

	void toggleDrawing(bool pToggle) {
		shouldDraw = pToggle;
	}
};





#endif 
