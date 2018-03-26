#pragma once

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_biquadresonantfilter.h"
#include "AudioFile.h"
#include <vector>

class AudioChannel
{
public:
	AudioChannel();
	~AudioChannel();

	int addAudioFile(std::string);
	void playAudioFile(int);
	void playOnce(int);
	void fadeInAudioFile(int,int);
	void fadeOutAudioFile(int, int);

	void fadeInFilter();
	void fadeOutFilter();

	void setVolume(int, int);
	void setGlobalVolume(int);

	SoLoud::Soloud audioEngine;
	SoLoud::BiquadResonantFilter gLPFilter;
	std::vector<AudioFile*>* audioFiles;

	int wavCount;
	long velocity;
	bool isFaded;
};
