#include "Rendering\Components\RenderComponent.h"
#include "Rendering\ResourceManager.h"
#include "General/GameObject.h"

#include <GLFW\glfw3.h>


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

		if (ResourceManager::getInstance()->getCurrentShaderID() != m_Shader_) {
			ResourceManager::getInstance()->useShader(m_Shader_); //Error check for false shader switch.
		}
		ResourceManager::getInstance()->GetShader(m_Shader_).UpdateShaderUniforms();
		ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mProjection", pProj);
		ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mView", pView);

		if (m_Models_.size() > 0) {
			for (int i = 0; i < m_Models_.size(); i++) {
				m_Models_[i].Render(m_Shader_);
			}
		}


		//if (m_Meshes_.size() > 0) {
		//	if (ResourceManager::getInstance()->getCurrentShaderID() != m_Shader_) {
		//		ResourceManager::getInstance()->useShader(m_Shader_); //Error check for false shader switch.
		//	}


		//	m_Material_.UpdateUniforms(m_Shader_);

		//	m_Material_.BindTextures(m_Shader_);


		//	

		//	//Set the Projection and View Matrices. 
		//	ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mProjection", pProj);
		//	ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mView", pView);

		//	//Set a default colour.
		//	for (t_Mesh_vector_Iterator_ iter = m_Meshes_.begin(); iter != m_Meshes_.end(); ++iter) {
		//		glm::vec3 p, r, s;
		//		p = transformComponent->getPosition() + (*iter)->getPosition();
		//		r = transformComponent->getRotation();
		//		s = transformComponent->getScale() + (*iter)->getScale();


		//		glm::mat4 model(1.0f);
		//		model = glm::translate(model, p);
		//		glm::vec3 temp = p - transformComponent->getPosition();



		//		//Rotate the mesh in relation to the parent transform.
		//		model = glm::translate(model, glm::vec3(-temp.x, -temp.y, -temp.z));
		//		model = glm::rotate(model, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
		//		model = glm::rotate(model, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
		//		model = glm::rotate(model, r.z, glm::vec3(0.0f, 0.0f, 1.0f));

		//		model = glm::translate(model, glm::vec3(temp.x, temp.y, temp.z));

		//		//Rotate the mesh itself around its pivot point.
		//		model = glm::translate(model, (*iter)->getPivotPoint());

		//		model = glm::rotate(model, (*iter)->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		//		model = glm::rotate(model, (*iter)->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
		//		model = glm::rotate(model, (*iter)->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

		//		model = glm::translate(model, -(*iter)->getPivotPoint());

		//		model = glm::scale(model, s);


		//		ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("mModel", model);
		//		glBindVertexArray(*(*iter)->getRenderData());
		//		glEnableVertexAttribArray(0);
		//		glEnableVertexAttribArray(1);
		//		glEnableVertexAttribArray(2);

		//		if ((*iter)->getIndices() > 0)
		//			glDrawElements(GL_TRIANGLES, (*iter)->getIndices(), GL_UNSIGNED_INT, 0);
		//		else
		//			glDrawArrays(GL_TRIANGLES, 0, (*iter)->getDrawSize());
		//	}
		//}
	}
}




