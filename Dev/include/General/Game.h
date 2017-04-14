#ifndef _GAME_H_
#define _GAME_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include "Rendering\Renderer.h"
#include "InputHandler.h"
#include "WindowManager.h"
#include "SceneManager.h"

#include "UI\GUIRenderer.h"

#include "General\Proxy.h"

#include <cstdlib>
#include "Audio/AudioManager.h"
#include "Audio/Sound.h"

class Proxy;

//Main Game Class, here all the code originates and the main loop exists.
class Game {
public:

	Game();

	//Start the main loop.
	void beginLoop();

	//Main update function.
	void update(double dTime);
	//Set the games score.
	
private:
	//The window manager
	WindowManager m_WindowManager_;

	//Both renderer's are stored here, as only 1 of each needs to exist  at any one point.
	Renderer * m_Renderer_;
	GUIRenderer * m_GUIRenderer_;

	void CreateScene();

	void switchScene(std::string pPath);

	//Mouse callback function.
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


};


#endif;