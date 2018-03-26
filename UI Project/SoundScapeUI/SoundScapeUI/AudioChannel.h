#pragma once

#include "soloud.h"
#include "soloud_wav.h"
#include "AudioFile.h"
#include <vector>

class AudioChannel
{
public:
	AudioChannel();
	~AudioChannel();

	void addAudioFile(std::string);
	void playAudioFile(int);

	void setVolume(int, int);

	SoLoud::Soloud audioEngine;
	std::vector<AudioFile*>* audioFiles;

	int wavCount;
};

