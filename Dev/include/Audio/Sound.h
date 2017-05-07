#pragma once

#include "AudioEngine.h"
#include "Component.h"

#include <fmod.hpp>
#include <lua.hpp>
#include <LuaBridge.h>

// Website used: https://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/
// Website used: https://tannhausergame.wordpress.com/2015/09/09/implementing-3d-audio-with-fmod/

/// <summary>
/// Used for creating and manipulating audio files.
/// </summary>
/// <seealso cref="Component" />
class Sound : public Component
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Sound"/> class.
	/// </summary>
	/// <param name="path">The path to the audio file.</param>
	/// <param name="make3D">Used to determine whether or not the sound should be 3D.</param>
	Sound(std::string path, bool make3D);

	/// <summary>
	/// Finalizes an instance of the <see cref="Sound"/> class.
	/// </summary>
	~Sound();

	/// <summary>
	/// Returns a value indicating whether or not the sound is being played in 3D.
	/// </summary>
	/// <returns>bool</returns>
	bool is3D() const;

	/// <summary>
	/// Determines whether this instance is looped.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is looped; otherwise, <c>false</c>.
	/// </returns>
	bool isLooped() const;
	
	/// <summary>
	/// Determines whether this instance is playing.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is playing; otherwise, <c>false</c>.
	/// </returns>
	bool isPlaying() const;

	/// <summary>
	/// Determines whether this instance is paused.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is paused; otherwise, <c>false</c>.
	/// </returns>
	bool isPaused() const;

	/// <summary>
	/// Returns the path to the audio file.
	/// </summary>
	/// <returns>std::string</returns>
	std::string getPath() const;

	/// <summary>
	/// Loops the audio.
	/// </summary>
	/// <param name="loop"><c>true</c> to loop the audio; otherwise, <c>false</c>.</param>
	void loop(bool loop);

	/// <summary>
	/// Pauses the audio.
	/// </summary>
	void pause();

	/// <summary>
	/// Plays the audio.
	/// </summary>
	void play();

	/// <summary>
	/// Plays the audio in a loop.
	/// </summary>
	void playLoop();

	/// <summary>
	/// Sets the volume.
	/// </summary>
	/// <param name="volume">The volume level.</param>
	void setVolume(float volume);

	/// <summary>
	/// Returns the volume level.
	/// </summary>
	/// <returns>float</returns>
	float getVolume() const;

	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;

	/// <summary>
	/// Registers the class for use with Lua.
	/// </summary>
	/// <param name="L">The lua_State to be used.</param>
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<Sound, Component>("Sound")
			.addConstructor<void(*)(std::string, bool)>()
			.addProperty("threeD", &Sound::is3D)
			.addProperty("path", &Sound::getPath)
			.addProperty("loop", &Sound::isLooped, &Sound::loop)
			.addProperty("volume", &Sound::getVolume, &Sound::setVolume)
			.addProperty("playing", &Sound::isPlaying)
			.addFunction("pause", &Sound::pause)
			.addFunction("play", &Sound::play)
			.addFunction("playLoop", &Sound::playLoop)
			.endClass();
	}
private:
	/// <summary>
	/// Used to manipulate the sound.
	/// </summary>
	FMOD::Channel *m_Channel;

	/// <summary>
	/// A pointer to the handle of the audio file.
	/// </summary>
	FMOD::Sound *m_AudioStream;

	/// <summary>
	/// Base interface. All FMOD objects are created from this. Points to an instance from the AudioEngine.
	/// </summary>
	FMOD::System *m_System;

	/// <summary>
	/// Holds an instance of the AudioEngine.
	/// </summary>
	AudioEngine *m_AudioEngine;

	/// <summary>
	/// Marks whether the sound is looping.
	/// </summary>
	bool m_Looping;

	/// <summary>
	/// Marks whether the sound is paused.
	/// </summary>
	bool m_Paused;

	/// <summary>
	/// Marks whether the sound is to be played in 3D.
	/// </summary>
	bool m_3D;;

	/// <summary>
	/// The path to the audio file.
	/// </summary>
	std::string m_path;
};