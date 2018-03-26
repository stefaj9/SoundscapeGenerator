#include "stdafx.h"
#include "AudioChannel.h"
#include <iostream>


AudioChannel::AudioChannel()
{
	audioEngine.init();
	audioFiles = new std::vector<AudioFile*>();
	wavCount = 0;
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

void AudioChannel::addAudioFile(std::string uri)
{
	SoLoud::Wav newWav;

	AudioFile* newAudioFile = new AudioFile(newWav, uri);

	this->audioFiles->push_back(newAudioFile);
	wavCount++;
}

void AudioChannel::playAudioFile(int index)
{
	if (index <= wavCount) {
		index--;
		if (!audioFiles->at(index)->isLoaded) {
			this->audioFiles->at(index)->soundFile.load(
				this->audioFiles->at(index)->name.c_str());
			this->audioFiles->at(index)->soundFile.setLooping(1);
			this->audioFiles->at(index)->isLoaded = true;
			
		}
		this->audioFiles->at(index)->ID = this->audioEngine.play(this->audioFiles->at(index)->soundFile);
	}
}

void AudioChannel::setVolume(int index, int volume)
{
	index--;
	if (audioFiles->at(index)->isLoaded) {
		//this->audioEngine.setVolume(this->audioFiles->at(index)->ID, volume);
	}

	std::cout << volume << std::endl;

}
