#include "stdafx.h"
#include "SoundChannel.h"

using namespace std;

int MIN_VELOCITY = 0;
int MAX_VELOCITY = 125;

SoundChannel::SoundChannel()
{
	this->velocity = MIN_VELOCITY;
	this->wavCount = 0;

	this->soundEngine.init();

	this->wav = new vector<SoundObject*>();
}


SoundChannel::~SoundChannel()
{
	this->soundEngine.deinit();
}

void SoundChannel::setVelocity(int velocity)
{
	if (velocity < MIN_VELOCITY) {
		this->velocity = MIN_VELOCITY;
	}
	else if (velocity > MAX_VELOCITY) {
		this->velocity = MAX_VELOCITY;
	}
	else {
		this->velocity = velocity;
	}

}

int SoundChannel::getVelocity()
{
	return this->velocity;
}

int SoundChannel::getWavCount()
{
	return this->wavCount;
}

void SoundChannel::addWav(string newWav)
{
	Wav tmp;

	SoundObject* temp = new SoundObject(tmp, newWav);

	this->wav->push_back(temp);
	this->wavCount++;
}

void SoundChannel::playWavNumber(int index)
{
	index = index - 1;

	this->wav->at(index)->wav.load(this->wav->at(index)->name.c_str());
	this->wav->at(index)->wav.setLooping(1);
	int handle = this->soundEngine.play(this->wav->at(index)->wav);



}
