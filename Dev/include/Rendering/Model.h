#ifndef _RENDERING_MODEL_H_
#define _RENDERING_MODEL_H_


#include "Rendering\Mesh.h"
#include "Rendering\ResourceManager.h"
#include "Rendering\Material.h"
#include "Physics\Components\TransformComponent.h"


class Model {


public:
	Model() {}
	Model(std::vector<Mesh> mesh);

	void Render(std::string pShader, TransformComponent * transform);

	void Update(TransformComponent * transform, float dt);

	glm::vec3 getBoundingMin() {
		return m_MinPos_;
	}

	glm::vec3 getBoundingMax() {
		return m_MaxPos_;
	}

private:

	Material m_Material_;

	std::vector<Mesh> m_Meshes_;

	glm::vec3 m_MinPos_;
	glm::vec3 m_MaxPos_;
};


#endif