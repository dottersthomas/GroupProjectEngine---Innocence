#pragma once

// Website used: https://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/
// Website used: http://www.fmod.org/documentation/#content/generated/overview/getting_started.html

#include "fmod.hpp"
#include "fmod_errors.h"
#include <memory>

class AudioManager
{
private:
	// Constructor
	AudioManager();
	// Variables
	FMOD::System *_system;		// Base interface, all FMOD objects created from this
	FMOD_RESULT _result;		// Error checking
public:
	// Destructor
	~AudioManager();
	// Methods
	void update() const;
	// Functions
	FMOD::System* getSystem() const;
	static std::shared_ptr<AudioManager> getInstance();
};
