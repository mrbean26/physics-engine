#define MINIMP3_IMPLEMENTATION
#include <MP3/minimp3.h>
#include <MP3/minimp3_ex.h>

#include <Engine/Engine.h>
#include <Engine/Components/AudioSource.h>

pair<int, vector<int16_t>> GetAudioSamples(const char* fileNameMP3) {
	mp3dec_t mp3Decoder;
	mp3dec_file_info_t fileInfo;

	if (mp3dec_load(&mp3Decoder, fileNameMP3, &fileInfo, NULL, NULL)) {
		cout << "MP3 Load Error" << endl;
		return make_pair<int, vector<int16_t>>(0, {});
	}

	vector<int16_t> allSamples(fileInfo.samples);
	if (fileInfo.channels == 1) {
		for (int i = 0; i < fileInfo.samples; i++) {
			allSamples[i] = fileInfo.buffer[i];
		}
	}
	
	int sampleRate = fileInfo.hz;
	return make_pair(sampleRate, allSamples);
}

void AudioSource::Mainloop() {
	Initialise();

	Transform* parentTransform = ParentObject()->GetComponent<Transform*>();

	vec3 parentPosition = parentTransform->GetFullWorldPosition();
	alSource3f(sourceID, AL_POSITION, parentPosition.x, parentPosition.y, parentPosition.z);
		
	alSourcef(sourceID, AL_ROLLOFF_FACTOR, attenuationFactor);
	alSourcef(sourceID, AL_GAIN, volume);
}
void AudioSource::Initialise() {
	if (initialised) {
		return;
	}

	rawAudioData = GetAudioSamples(audioFileMP3Filename.data());
	
	alGenBuffers(1, &bufferID);
	alBufferData(bufferID, AL_FORMAT_MONO16, &rawAudioData.second[0], rawAudioData.second.size() * sizeof(ALshort), rawAudioData.first);
	
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);

	alDistanceModel(AL_INVERSE_DISTANCE);

	initialised = true;
}

void AudioSource::Play() {
	alSourcePlay(sourceID);
}
void AudioSource::Pause() {
	alSourcePause(sourceID);
}
void AudioSource::Stop() {
	alSourceStop(sourceID);
}

void AudioSource::SetPositionTime(float time) {
	int sampleOffset = time * rawAudioData.first;
	alSourcef(sourceID, AL_SAMPLE_OFFSET, sampleOffset);
}
void AudioSource::SetPositionDecimal(float percentageDecimal) {
	int sampleOffset = percentageDecimal * rawAudioData.second.size();
	alSourcef(sourceID, AL_SAMPLE_OFFSET, sampleOffset);
}