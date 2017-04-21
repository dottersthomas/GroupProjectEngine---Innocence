#include "General\SceneManager.h"
#include "UI\CanvasButton.h"

#include "General\Proxy.h"

#include "General\XML\XMLParser.h"
#include "UI\Text2D.h"



SceneManager::SceneManager() {
	m_CurrentScene_ = nullptr;
	m_Unswitched_ = nullptr;
	m_switch_ = false;
}

bool SceneManager::LoadScene(std::string pPath) {
	XMLParser parser;
	parser.Parse(pPath);
	m_Unswitched_ = nullptr;

	m_Unswitched_ = parser.LoadScene();
	Proxy::getInstance()->setUIFocus(true);
	m_switch_ = true;


	return true;
}

bool SceneManager::LoadScene(Scene * pScene) {
	m_Unswitched_ = pScene;
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
