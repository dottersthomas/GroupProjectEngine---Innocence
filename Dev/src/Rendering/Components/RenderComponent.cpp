#include "Rendering\Components\RenderComponent.h"
#include "Rendering\ResourceManager.h"

RenderComponent::RenderComponent(GameObject * pParent, std::string sShader, int pType) {
	m_GameObjectParent_ = pParent;
	m_Shader_ = sShader;

	transformComponent = m_GameObjectParent_->GetComponentByType<TransformComponent>();
	m_RenderType_ = pType;
	M_ComponentName = "RENDER_COMPONENT";
}

void RenderComponent::Update(double dt) {


}
void RenderComponent::LateUpdate(double dt) {

}

void RenderComponent::Destroy() {

}

void RenderComponent::Start() {

}

void RenderComponent::AttachMesh(Mesh * pMesh) {
	m_Meshes_.push_back(pMesh);
}


void RenderComponent::Render(glm::mat4 pProj, glm::mat4 pView) {
	//No point processing rendering if no mesh is found, altho this is unlikely as no render component would be included.
	if (shouldDraw) {
		if (m_Meshes_.size() > 0) {
			if (ResourceManager::getInstance()->getCurrentShaderID() != m_Shader_) {
				ResourceManager::getInstance()->useShader(m_Shader_); //Error check for false shader switch.
			}

			//Set the Projection and View Matrices. 
			ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mProjection", pProj);
			ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mView", pView);

			glm::vec3 worldLight = glm::vec3(10.0f, 10.0f, 10.0f);

			ResourceManager::getInstance()->GetShader(m_Shader_).SetVector3f("Ld", 1.0f, 1.0f, 1.0f);
			ResourceManager::getInstance()->GetShader(m_Shader_).SetVector3f("La", 0.2f, 0.2f, 0.2f);
			
			ResourceManager::getInstance()->GetShader(m_Shader_).SetVector3f("LightPosition", worldLight);

			//Set a default colour.
			for (t_Mesh_vector_Iterator_ iter = m_Meshes_.begin(); iter != m_Meshes_.end(); ++iter) {
				glm::vec3 p, r, s;
				p = transformComponent->getPosition() + (*iter)->getPosition();
				r = transformComponent->getRotation();
				s = transformComponent->getScale() + (*iter)->getScale();

				if (m_RenderType_ == ComponentType::COLOUR) {
					ResourceManager::getInstance()->GetShader(m_Shader_).SetVector4f("colour", (*iter)->getColour());
				}
				else {
					//Assign and handle the texture for the mesh.
					glActiveTexture(GL_TEXTURE0);
					ResourceManager::getInstance()->GetTexture((*iter)->getTextureID()).Bind();
					ResourceManager::getInstance()->GetShader(m_Shader_).SetInteger("tex", 0);

				}

				glm::mat4 model(1.0f);
				model = glm::translate(model, p);
				glm::vec3 temp = p - transformComponent->getPosition();



				//Rotate the mesh in relation to the parent transform.
				model = glm::translate(model, glm::vec3(-temp.x, -temp.y, -temp.z));
				model = glm::rotate(model, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, r.z, glm::vec3(0.0f, 0.0f, 1.0f));

				model = glm::translate(model, glm::vec3(temp.x, temp.y, temp.z));

				//Rotate the mesh itself around its pivot point.
				model = glm::translate(model, (*iter)->getPivotPoint());

				model = glm::rotate(model, (*iter)->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::rotate(model, (*iter)->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, (*iter)->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

				model = glm::translate(model, -(*iter)->getPivotPoint());

				model = glm::scale(model, s);



				glm::mat4 mv = pView * model;
				ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix3("NormalMatrix",
					glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));

				//Draw the Mesh.

				ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mModel", model);
				glBindVertexArray(*(*iter)->getRenderData());
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);

				glDrawArrays(GL_TRIANGLES, 0, (*iter)->getDrawSize());
			}
		}
	}
}




