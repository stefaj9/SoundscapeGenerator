#include "stdafx.h"
#include "AudioChannel.h"
#include <iostream>


AudioChannel::AudioChannel()
{
	audioEngine.init();
	audioFiles = new std::vector<AudioFile*>();
	wavCount = 0;
	velocity = 0;
	isFaded = false;

	gLPFilter.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 44100, 20000, 0.1f);
}


AudioChannel::~AudioChannel()
{
	audioEngine.deinit();
	/*
	for (int i = 0; i < audioFiles->size; i++) {
		delete audioFiles->at(i);
	}

	delete audioFiles;
	*/
}

int AudioChannel::addAudioFile(std::string uri)
{
	SoLoud::Wav newWav;

	AudioFile* newAudioFile = new AudioFile(newWav, uri);

	this->audioFiles->push_back(newAudioFile);

	wavCount++;

	return wavCount;
}

void AudioChannel::playOnce(int index) {
	if (index <= wavCount && !this->audioFiles->at(index-1)->isPlaying) {
		index--;
		if (!audioFiles->at(index)->isLoaded) {
			this->audioFiles->at(index)->soundFile.load(
				this->audioFiles->at(index)->name.c_str());
			this->audioFiles->at(index)->soundFile.setFilter(0, &gLPFilter);
			this->audioFiles->at(index)->isLoaded = true;
		}
		this->audioFiles->at(index)->ID = this->audioEngine.play(this->audioFiles->at(index)->soundFile);
	}
}

void AudioChannel::playAudioFile(int index)
{
	if (index <= wavCount && !this->audioFiles->at(index-1)->isPlaying) {
		index--;
		if (!audioFiles->at(index)->isLoaded) {
			this->audioFiles->at(index)->soundFile.load(
				this->audioFiles->at(index)->name.c_str());
			this->audioFiles->at(index)->soundFile.setLooping(1);
			this->audioFiles->at(index)->soundFile.setFilter(0, &gLPFilter);
			this->audioFiles->at(index)->isLoaded = true;			
		}
		this->audioFiles->at(index)->ID = this->audioEngine.play(this->audioFiles->at(index)->soundFile);
		this->audioFiles->at(index)->isPlaying = true;
	}
}

void AudioChannel::fadeInAudioFile(int index, int seconds)
{
	if (index <= wavCount && !this->audioFiles->at(index-1)->isPlaying) {
		playAudioFile(index);
		setVolume(index, 0);
		this->audioEngine.fadeVolume(this->audioFiles->at(index - 1)->ID, 1, seconds);
	}
}

void AudioChannel::fadeOutAudioFile(int index, int seconds)
{
	if (index <= wavCount && this->audioFiles->at(index-1)->isPlaying) {
		this->audioEngine.fadeVolume(this->audioFiles->at(index-1)->ID, 0, seconds);
		this->audioFiles->at(index-1)->isPlaying = false;
	}
}

void AudioChannel::fadeInFilter()
{
	if (!this->isFaded) {
		for (int i = 0; i < wavCount; i++) {
			this->audioEngine.fadeFilterParameter(this->audioFiles->at(i)->ID, 0,
				SoLoud::BiquadResonantFilter::FREQUENCY, 400, 4.0f);
		}
		gLPFilter.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 44100, 400, 0.4f);
		this->isFaded = true;
	}
}

void AudioChannel::fadeOutFilter()
{
	if (this->isFaded) {
		for (int i = 0; i < wavCount; i++) {
			this->audioEngine.fadeFilterParameter(this->audioFiles->at(i)->ID, 0,
				SoLoud::BiquadResonantFilter::FREQUENCY, 20000, 6.0f);
		}
		gLPFilter.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 44100, 20000, 0.4f);
		this->isFaded = false;
	}
}


void AudioChannel::setVolume(int index, int volume)
{
	index--;
	if (audioFiles->at(index)->isLoaded) {
		this->audioEngine.setVolume(this->audioFiles->at(index)->ID, (float)volume/100);
	}
}

void AudioChannel::setGlobalVolume(int volume)
{
	float newVol = (float)volume * 0.4f;

	this->audioEngine.setGlobalVolume(1.0f + newVol);
}
