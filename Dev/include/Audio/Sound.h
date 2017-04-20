#pragma once

#include "AudioManager.h"
#include "Component.h"

#include <fmod.hpp>
#include <lua.hpp>
#include <LuaBridge.h>

// Website used: https://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/
// Website used: https://tannhausergame.wordpress.com/2015/09/09/implementing-3d-audio-with-fmod/

class Sound : public Component
{
public:
	Sound(std::string path, const bool make3D);
	~Sound();

	bool is3D() const;
	bool isLooped() const;
	bool isPaused() const;

	std::string getPath() const;

	void loop(const bool loop);
	void pause();
	void play();
	void playLoop();

	void setVolume(const float volume);
	float getVolume() const;

	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<Sound>("Sound")
			.addConstructor<void(*)(std::string, bool)>()
			.addProperty("threeD", &Sound::is3D)
			.addProperty("path", &Sound::getPath)
			.addProperty("loop", &Sound::isLooped, &Sound::loop)
			.addProperty("volume", &Sound::getVolume, &Sound::setVolume)
			.addFunction("pause", &Sound::pause)
			.addFunction("play", &Sound::play)
			.addFunction("playLoop", &Sound::playLoop)
			.endClass();
	}
private:
	FMOD::Channel *m_Channel;
	FMOD::Sound *m_AudioStream;
	FMOD::System *m_System;

	std::shared_ptr<AudioManager> m_AudioManager;

	bool m_Looping, m_Paused, m_3D;
	std::string m_path;
};