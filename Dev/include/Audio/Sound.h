#pragma once

#include "AudioManager.h"
#include "Component.h"

#include <fmod.hpp>

// Website used: https://katyscode.wordpress.com/2012/10/05/cutting-your-teeth-on-fmod-part-1-build-environment-initialization-and-playing-sounds/
// Website used: https://tannhausergame.wordpress.com/2015/09/09/implementing-3d-audio-with-fmod/

class Sound : public Component
{
private:
	FMOD::Channel *_channel;
	FMOD::Sound *_audioStream;
	FMOD::System *_system;

	std::shared_ptr<AudioManager> _audioManager;

	bool _looping, _paused, _3D;
	std::string _path;

	void setup();
public:
	Sound();
	Sound(std::string& path, const bool make2D);
	~Sound();

	bool is3D() const;
	bool isLooped() const;
	bool isPaused() const;

	void setPath(std::string& path, const bool make2D);
	std::string getPath() const;

	void loop(bool loop);
	void pause();
	void play();
	void playOnce();
	void playLoop();

	void setVolume(float volume) const;
	float getVolume() const;

	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;
};