#pragma once

#include <Engine/Object/Component.h>

#include <vector>
#include <string>
using namespace std;

#include <AL/al.h>
#include <AL/alc.h>

pair<int, vector<int16_t>> GetAudioSamples(const char* fileNameMP3);

class AudioSource : public Component {
public:
	void Mainloop();
	void Initialise();

	void Play();
	void Pause();
	void Stop();

	void SetPositionTime(float time);
	void SetPositionDecimal(float percentageDecimal);

	float volume = 1.0f;
	float attenuationFactor = 1.0f;

	ALuint sourceID;
	ALuint bufferID;

	pair<int, vector<int16_t>> rawAudioData;
	string audioFileMP3Filename;
};