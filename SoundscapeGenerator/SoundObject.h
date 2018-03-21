#pragma once
#include "soloud_wav.h"
#include <string>

using namespace std;
using namespace SoLoud;

class SoundObject
{
public:
	SoundObject(Wav wav, string name);
	~SoundObject();

	Wav wav;
	string name;
};

