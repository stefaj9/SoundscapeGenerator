#pragma once
#include <vector>
#include <string>
#include "soloud.h"
#include "soloud_wav.h"
#include "soundObject.h"

using namespace std;
using namespace SoLoud;

class SoundChannel
{
public:
	SoundChannel();
	~SoundChannel();
	void setVelocity(int);
	int getVelocity();
	int getWavCount();
	void addWav(std::string);
	void playWavNumber(int);
	void fadeInWavNumber(int, int);
	void fadeOutWavNumber(int, int);

	Soloud soundEngine;
	vector<SoundObject*>* wav;

private:
	int velocity;
	int wavCount;
};

