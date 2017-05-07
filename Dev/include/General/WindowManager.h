#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include <iostream>
#include "SceneManager.h"

#include <GLFW\glfw3.h>

class WindowManager {
private:
	GLFWwindow * m_Window_;

	SceneManager * m_SceneManager_;

	bool m_UIFocus_ = false;

	WindowManager();
	WindowManager(int pXPos, int pYPos, int pWidth, int pHeight);
	WindowManager(std::string pTitle, int pXPos, int pYPos, int pWidth, int pHeight);
public:
	static WindowManager& getInstance()
	{
		static WindowManager instance;
		return instance;
	}
	~WindowManager();

	GLFWwindow * createWindow(std::string pTitle, int pXPos, int pYPos, int pWidth, int pHeight);
	GLFWwindow * createWindow(std::string pTitle, int pXPos, int pYPos, int pWidth, int pHeight, GLFWmonitor * pMonitor);

	//Add input manager to listen to feedback.

	bool doesWindowExist();

	void toggleVSYNC(bool pToggle);

	void toggleFullScreen(bool pToggle);

	void setCursorPosition(double pXPos, double pYPos);
	//Add get cursor position.
	void toggleCursorDraw(bool pToggle);

	void destroyWindow();

	GLFWwindow * getWindow();

	SceneManager * getSceneManager() {
		return m_SceneManager_;
	}

	void setUIfocus(bool ptoggle) {
		m_UIFocus_ = ptoggle;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<WindowManager>("WindowManager")
			.addStaticProperty("instance", &WindowManager::getInstance)
			.addData("sceneManager", &WindowManager::m_SceneManager_, false)
			.addData("uiFocus", &WindowManager::m_UIFocus_)
			.addFunction("toggleVSync", &WindowManager::toggleVSYNC)
			.addFunction("toggleFullScreen", &WindowManager::toggleFullScreen)
			.addFunction("toggleCursorDraw", &WindowManager::toggleCursorDraw)
			.addFunction("destroy", &WindowManager::destroyWindow)
			.endClass();
	}
};

#endif