#include "stdafx.h"
#include "SoundObject.h"

using namespace std;

int MIN_VELOCITY = 0;
int MAX_VELOCITY = 125;

SoundObject::SoundObject()
{
	this->velocity = MIN_VELOCITY;
	this->wavCount = 0;

	this->soundEngine.init();

	wavFiles = new vector<Wav>();
	wavNames = new vector<string>();
}


SoundObject::~SoundObject()
{
	this->soundEngine.deinit();
}

void SoundObject::setVelocity(int velocity)
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

int SoundObject::getVelocity()
{
	return this->velocity;
}

int SoundObject::getWavCount()
{
	return this->wavCount;
}

void SoundObject::addWav(string newWav)
{
	Wav tmp;
	this->wavFiles->push_back(tmp);
	this->wavNames->push_back(newWav);
	this->wavCount++;
}

void SoundObject::playWavNumber(int index)
{	
	index = index - 1;

	this->wavFiles->at(index).load(this->wavNames->at(index).c_str());
	this->wavFiles->at(index).setLooping(1);
	int handle = this->soundEngine.play(this->wavFiles->at(index));

	

}
