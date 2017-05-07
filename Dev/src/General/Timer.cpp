#include "General/Timer.h"

#include <GLFW\glfw3.h>
#include <iostream>

void Timer::start()
{
	// Set start time
	reset();
}

void Timer::pause(bool paused)
{
	double currentTime = glfwGetTime();

	if (m_Paused)
	{
		// Unpause
		m_StartTime += currentTime - m_PausedTime; // Add offset
		m_Paused = false;
	}
	else
	{
		// Pause
		m_PausedTime = currentTime;
		m_Paused = true;
	}
}

void Timer::reset()
{
	// Reset start time
	m_StartTime = glfwGetTime();
}

double Timer::getTime() const
{
	return (m_Paused) ? m_PausedTime - m_StartTime : (glfwGetTime() - m_StartTime);
}