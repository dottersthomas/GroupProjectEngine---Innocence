#include "General\InputHandler.h"
#include <iostream>
#include <GLFW\glfw3.h>

// Static variable initialisation
static double m_ButtonTimeOut = 0;
static double m_KeyTimeOut = 0;

int InputHandler::m_LastKey = 0;

bool InputHandler::keys[65536];
bool InputHandler::buttons[8];

void InputHandler::invokeKey(int key, int scancode, int action, int mods)
{
	keys[key] = action != GLFW_RELEASE;
	m_LastKey = key;
}

bool InputHandler::isKeyDown(int key, int timeout)
{
	double currentTime = glfwGetTime();
	if (currentTime < m_KeyTimeOut) return false;
	m_KeyTimeOut = currentTime + timeout / 1000.0;
	return keys[key];
}

void InputHandler::invokeButton(int button, int action, int mods)
{
	if (button < 8)
		buttons[button] = action != GLFW_RELEASE;
}

bool InputHandler::isButtonDown(int button, int timeout)
{
	if (button < 8)
	{
		double currentTime = glfwGetTime();
		if (currentTime < m_ButtonTimeOut) return false;
		m_ButtonTimeOut = currentTime + timeout / 1000.0;

		return buttons[button];
	}
	return false;
}

bool InputHandler::wasKeyReleased(int key)
{
	if (key == m_LastKey)
	{
		// Reset variable
		m_LastKey = 0;
		return true;
	}

	return false;
}