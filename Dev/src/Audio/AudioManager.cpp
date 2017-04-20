#include "Audio/AudioManager.h"

#include <iostream>

// Variables
std::shared_ptr<AudioManager> instance;

// --- Constructor

AudioManager::AudioManager()
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

AudioManager::~AudioManager()
{
	m_System->release();
}

// --- Methods

void AudioManager::update() const
{
	// Needs to be updated every frame to prevent unwanted behaviour
	m_System->update();
}

// --- Functions

FMOD::System* AudioManager::getSystem() const
{
	return m_System;
}

std::shared_ptr<AudioManager> AudioManager::getInstance()
{
	if (!instance)
		instance = std::shared_ptr<AudioManager>(new AudioManager());
	return instance;
}