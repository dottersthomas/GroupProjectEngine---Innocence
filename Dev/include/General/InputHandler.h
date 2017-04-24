#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <lua.hpp>
#include <LuaBridge.h>


//Static class to be used anywhere, allows for the checking of key states with the only limit being the hardware.
class InputHandler {

public:
	static bool keys[65536]; //Maximum possible keys, most likely very overkill but well out of the range of errors.
	static bool buttons[8]; //GLFW can only record 8 individual mouse buttons.


	//Invoke a key or button press.

	static void invokeKey(int key, int scancode, int action, int mods);
	static void invokeButton(int button, int action, int mods);


	//Check if a key or button is pressed down.
	static bool isKeyDown(int key);
	static bool isButtonDown(int button);
	
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<InputHandler>("Input")
				.addStaticFunction("isKeyDown", &InputHandler::isKeyDown)
				.addStaticFunction("isButtonDown", &InputHandler::isButtonDown)
			.endClass();
	}

private:
	InputHandler() {}

};





#endif 
