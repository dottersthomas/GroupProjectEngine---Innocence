#ifndef _RENDERING_MODEL_H_
#define _RENDERING_MODEL_H_


#include "Rendering\Mesh.h"
#include "Rendering\ResourceManager.h"
#include "Rendering\Material.h"


class Model {


public:
	Model() {}
	Model(std::vector<Mesh> mesh);

	void Render(std::string pShader);
private:

	Material m_Material_;

	std::vector<Mesh> m_Meshes_;

};


#endif