#include "Audio/Sound.h"
#include "Audio/AudioEngine.h"
#include "Physics/Components/TransformComponent.h"

// --- Constructor(s)

Sound::Sound(std::string path, bool make3D)
{
	// Initilaise variables
	m_AudioEngine = &AudioEngine::getInstance();
	m_System = m_AudioEngine->getSystem();

	// Set path
	m_path = path;

	// Assign to m_Channel
	FMOD_MODE fMode = make3D ? FMOD_3D : FMOD_2D;
	m_System->createSound(path.c_str(), fMode, nullptr, &m_AudioStream);
	m_Looping = false;
	m_Paused = false;
	m_3D = make3D;
}

// --- Destructor

Sound::~Sound()
{
	m_AudioStream->release();
}

// --- Functions

std::string Sound::getPath() const
{
	return m_path;
}

bool Sound::is3D() const
{
	return m_3D;
}

bool Sound::isLooped() const
{
	return m_Looping;
}

bool Sound::isPlaying() const
{
	bool result;
	m_Channel->isPlaying(&result);
	return result;
}

bool Sound::isPaused() const
{
	return m_Paused;
}

float Sound::getVolume() const
{
	float volume;
	m_Channel->getVolume(&volume);
	return volume;
}

// --- Methods

void Sound::loop(bool loop)
{
	// Required: Has to be set after the sound has begun playing

	// Set boolean
	m_Looping = loop;
	// Set m_Channel options
	m_Channel->setMode(m_Looping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}

void Sound::setVolume(float volume)
{
	m_Channel->setVolume(volume);
}

void Sound::pause()
{
	m_Paused = true;
	m_Channel->setPaused(m_Paused);
}

void Sound::play()
{
	// Check if the sound has been loaded
	bool soundPlaying;
	m_Channel->isPlaying(&soundPlaying);

	if (!soundPlaying)
		m_System->playSound(m_AudioStream, nullptr, false, &m_Channel);

	m_Paused = false;
	m_Channel->setPaused(m_Paused);
}

void Sound::playLoop()
{
	// Play audio on a loop
	play();
	loop(true);
}

void Sound::Start()
{

}

void Sound::Update(double dt)
{
	// TODO Set listener position to gameObject position
	//glm::vec3 goPos = this->m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition();
}

void Sound::LateUpdate(double dt)
{

}

void Sound::Destroy()
{

}