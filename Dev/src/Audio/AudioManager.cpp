#include "Audio/AudioManager.h"

#include <iostream>

// Variables
std::shared_ptr<AudioManager> instance;

// --- Constructor

AudioManager::AudioManager()
{
	// Initialisation
	_result = FMOD::System_Create(&_system);

	// TODO Replace with logging _system output
	if (_result != FMOD_OK)
		std::cout << "FMOD Error: " << FMOD_ErrorString(_result) << "\n";

	/*
	 *  First paramater is the number of virtual channels to use, FMOD will use any free _channel.
	 *  If there are more sounds than channels, running sounds may get cut-off.
	 *  */
	_result = _system->init(512, FMOD_INIT_NORMAL, nullptr);
}

// --- Destructor

AudioManager::~AudioManager()
{
	_system->release();
}

// --- Methods

void AudioManager::update() const
{
	// Needs to be updated every frame to prevent unwanted behaviour
	_system->update();
}

// --- Functions

FMOD::System* AudioManager::getSystem() const
{
	return _system;
}

std::shared_ptr<AudioManager> AudioManager::getInstance()
{
	if (!instance)
		instance = std::shared_ptr<AudioManager>(new AudioManager());
	return instance;
}