#pragma once
#include <vector>
#include <string>
#include "soloud.h"
#include "soloud_wav.h"

using namespace std;
using namespace SoLoud;

class SoundObject
{
public:
	SoundObject();
	~SoundObject();
	void setVelocity(int);
	int getVelocity();
	int getWavCount();
	void addWav(std::string);
	void loadWavs();

	Soloud soundEngine;
	vector<Wav>* wavFiles;
	vector<string>* wavNames;

private:
	int velocity;
	int wavCount;
	bool isLocked;
};

