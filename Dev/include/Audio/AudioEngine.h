#pragma once

// Website used: https://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/
// Website used: http://www.fmod.org/documentation/#content/generated/overview/getting_started.html

#include "fmod.hpp"
#include "fmod_errors.h"
#include <memory>

/// <summary>
/// Manages the audio system and performs error-checking on Sound objects.
/// </summary>
class AudioEngine
{
private:
	/// <summary>
	/// Prevents a default instance of the <see cref="AudioEngine"/> class from being created.
	/// </summary>
	AudioEngine();

	/// <summary>
	/// Base interface. All FMOD objects are created from this.
	/// </summary>
	FMOD::System *m_System;

	/// <summary>
	/// Used for error-checking.
	/// </summary>
	FMOD_RESULT m_Result;

public:
	/// <summary>
	/// Finalizes an instance of the <see cref="AudioEngine"/> class.
	/// </summary>
	~AudioEngine();

	/// <summary>
	/// Updates this instance. Should be called once per frame to prevent unwanted behaviour on certain platforms.
	/// </summary>
	void update() const;

	/// <summary>
	/// Returns a pointer of type FMOD::System. Used for creating Sound objects.
	/// </summary>
	/// <returns>FMOD::System*</returns>
	FMOD::System* getSystem() const;

	/// <summary>
	/// Returns an instance of the AudioEngine.
	/// </summary>
	/// <returns>std::shared_ptr&lt;AudioEngine&gt;</returns>
	static std::shared_ptr<AudioEngine> getInstance();
};