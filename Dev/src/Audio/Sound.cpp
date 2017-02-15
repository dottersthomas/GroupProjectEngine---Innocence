#include "Audio/Sound.h"
#include "Audio/AudioManager.h"

// --- Constructor(s)

Sound::Sound()
{
	setup();
}

Sound::Sound(std::string path, const bool make2D)
{
	setup();
	setPath(path, make2D);
	_3D = !make2D;
}

// --- Destructor

Sound::~Sound()
{
	_audioStream->release();
}

// --- Functions

std::string Sound::getPath() const
{
	return _path;
}

bool Sound::is3D() const
{
	return _3D;
}

bool Sound::isLooped() const
{
	return _looping;
}

bool Sound::isPaused() const
{
	return _paused;
}

float Sound::getVolume() const
{
	float volume;
	_channel->getVolume(&volume);
	return volume;
}

// --- Methods

void Sound::loop(bool loop)
{
	// Set boolean
	_looping = loop;
	// Set _channel options
	_channel->setMode(_looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}

void Sound::setPath(std::string path, const bool make2D)
{
	// TODO Fix naming conventions
	_path = path;

	// Assign to _channel
	FMOD_MODE fMode = make2D ? FMOD_2D : FMOD_3D;
	_system->createSound(path.c_str(), fMode, nullptr, &_audioStream);
	_looping = false;
	_paused = false;
}

void Sound::setup()
{
	_audioManager = AudioManager::getInstance();
	_system = _audioManager->getSystem();
}

void Sound::setVolume(float volume) const
{
	_channel->setVolume(volume);
}

void Sound::pause()
{
	_paused = true;
	_channel->setPaused(_paused);
}

void Sound::play()
{
	// Check if the sound has been loaded
	bool soundPlaying;
	_channel->isPlaying(&soundPlaying);

	if (!soundPlaying)
		playOnce();

	_paused = false;
	_channel->setPaused(_paused);
}

void Sound::playOnce()
{
	// Play audio once
	_system->playSound(_audioStream, nullptr, false, &_channel);
}

void Sound::playLoop()
{
	// Play audio on a loop
	playOnce();
	loop(true);
}

void Sound::Start()
{
	
}

void Sound::Update(double dt)
{
	// TODO Find a way of passing the player's position
}

void Sound::LateUpdate(double dt)
{
	
}

void Sound::Destroy()
{
	
}