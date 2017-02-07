#include "SceneManager.h"
#include "Rendering\GUI\CanvasButton.h"

#include "Proxy.h"

#include "XML\XMLParser.h"
#include "Rendering\GUI\Text2D.h"



SceneManager::SceneManager() {
	m_CurrentScene_ = nullptr;
	m_Unswitched_ = nullptr;
}

bool SceneManager::LoadScene(std::string pPath) {
	
	ResourceManager::getInstance()->attachButtonFunction("load", [this]()->void {LoadScene("XML/Scene.xml"); });
	ResourceManager::getInstance()->attachButtonFunction("exit", [this]()->void {exit(EXIT_SUCCESS); });
	ResourceManager::getInstance()->attachButtonFunction("loadMenu", [this]()->void {LoadScene("XML/MainMenu.xml"); });


	XMLParser parser;
	parser.Parse(pPath);
	m_Unswitched_ = nullptr;

	m_Unswitched_ = parser.LoadScene();
	Proxy::getInstance()->setUIFocus(true);
	m_switch_ = true;


	return true;
}


void SceneManager::switchScene() {
	if (m_Unswitched_ != nullptr)
		m_CurrentScene_ = m_Unswitched_;

	m_switch_ = false;
}

void SceneManager::DeleteScene() {

	delete m_CurrentScene_;
}

void SceneManager::UpdateRenderers(Renderer * pRenderer, GUIRenderer * pGUIRenderer) {
	pRenderer->setScene(m_CurrentScene_);
	pGUIRenderer->setScene(m_CurrentScene_);
}
