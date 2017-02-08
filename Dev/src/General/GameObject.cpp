#include "General\GameObject.h"
#include "Physics\Components\TransformComponent.h"


GameObject::GameObject(const char* pName) {
	M_Name_ = pName;
	m_Components_.reserve(10);
	registerComponent(new TransformComponent(this)); //Every GameObject has a transform component, can be removed later as its easier to assume it exists.
}

bool GameObject::checkComponentExists(std::string pName) {

	for (int i = m_Components_.size(); i--;)
		if (m_Components_[i]->M_ComponentName == pName)
			return true;
	return false;

}


void GameObject::registerComponent(Component * pComponent) {
	pComponent->setParent(this);
	m_Components_.push_back(pComponent);
}
void GameObject::removeComponent(Component * pComponent) {
	//TODO add removal of components.
}

void GameObject::UpdateComponents(double dt) {
	for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
		(*iter)->Update(dt);
}

void GameObject::LateUpdateComponents() {
	for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
		(*iter)->LateUpdate(0.0);
}




