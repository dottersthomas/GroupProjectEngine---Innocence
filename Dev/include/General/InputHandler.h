#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <lua.hpp>
#include <LuaBridge.h>


//Static class to be used anywhere, allows for the checking of key states with the only limit being the hardware.
class InputHandler
{

public:
	static bool keys[65536]; //Maximum possible keys, most likely very overkill but well out of the range of errors.
	static bool buttons[8]; //GLFW can only record 8 individual mouse buttons.

	static int m_LastKey;

	//Invoke a key or button press.

	static void invokeKey(int key, int scancode, int action, int mods);
	static void invokeButton(int button, int action, int mods);


	//Check if a key or button is pressed down. Timeout in milliseconds.
	static bool isKeyDown(int key, int timeout = 0);
	static bool isButtonDown(int button, int timeout = 0);

	static bool wasKeyPressed(int key);
	static bool wasKeyReleased(int key);

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		// Add globals for defining keyboard keys and mouse buttons

		getGlobalNamespace(L)
			.beginClass<InputHandler>("Input")
			.addStaticFunction("isKeyDown", &InputHandler::isKeyDown)
			.addStaticFunction("isButtonDown", &InputHandler::isButtonDown)
			.addStaticFunction("wasKeyReleased", &InputHandler::wasKeyReleased)
			.addStaticData("lastKey", &InputHandler::m_LastKey, false)
			.endClass();
	}

private:
	InputHandler() {}
};

#endif 
