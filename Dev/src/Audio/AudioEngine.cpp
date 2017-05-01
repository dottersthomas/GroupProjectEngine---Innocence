#include "Audio/AudioEngine.h"

#include <iostream>

// Variables
std::shared_ptr<AudioEngine> instance;

// --- Constructor

AudioEngine::AudioEngine()
{
	// Initialisation
	m_Result = FMOD::System_Create(&m_System);

	// TODO Replace with logging m_System output
	if (m_Result != FMOD_OK)
		std::cout << "FMOD Error: " << FMOD_ErrorString(m_Result) << "\n";

	/*
	 *  First paramater is the number of virtual channels to use, FMOD will use any free m_Channel.
	 *  If there are more sounds than channels, running sounds may get cut-off.
	 *  */
	m_Result = m_System->init(512, FMOD_INIT_NORMAL, nullptr);
}

// --- Destructor

AudioEngine::~AudioEngine()
{
	m_System->release();
}

// --- Methods

void AudioEngine::update() const
{
	// Needs to be updated every frame to prevent unwanted behaviour
	m_System->update();
}

// --- Functions

FMOD::System* AudioEngine::getSystem() const
{
	return m_System;
}

std::shared_ptr<AudioEngine> AudioEngine::getInstance()
{
	if (!instance)
		instance = std::shared_ptr<AudioEngine>(new AudioEngine());
	return instance;
}