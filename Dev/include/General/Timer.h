#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

class Timer
{
private:
	bool m_Paused = false;
	double m_StartTime = 0;
	double m_PausedTime = 0;
public:
	Timer() {};
	~Timer() {};

	void start();
	void pause();
	void reset();

	double getTime() const;

	// Register class with lua
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;
	
		getGlobalNamespace(L)
			.beginClass<Timer>("Timer")
			.addConstructor<void(*)()>()
			.addFunction("start", &Timer::start)
			.addFunction("pause", &Timer::pause)
			.addFunction("reset", &Timer::reset)
			.addProperty("currentTime", &Timer::getTime)
			.endClass();
	}
};