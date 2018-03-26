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

	int addAudioFile(std::string);
	void playAudioFile(int);
	void fadeInAudioFile(int,int);
	void fadeOutAudioFile(int, int);

	void setVolume(int, int);

	SoLoud::Soloud audioEngine;
	std::vector<AudioFile*>* audioFiles;

	int wavCount;
	long velocity;
};
