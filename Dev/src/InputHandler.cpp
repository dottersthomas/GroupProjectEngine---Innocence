#include "InputHandler.h"
#include <iostream>
#include <GLFW\glfw3.h>


bool InputHandler::keys[65536];
bool InputHandler::buttons[8];

void InputHandler::invokeKey(int key, int scancode, int action, int mods) {
		keys[key] = action != GLFW_RELEASE;
}

bool InputHandler::isKeyDown(int key) {
	return keys[key];
}

void InputHandler::invokeButton(int button, int action, int mods) {
	if (button < 8)
		buttons[button] = action != GLFW_RELEASE;
}

bool InputHandler::isButtonDown(int button) {
	if (button < 8)
		return buttons[button];
	return false;
}
