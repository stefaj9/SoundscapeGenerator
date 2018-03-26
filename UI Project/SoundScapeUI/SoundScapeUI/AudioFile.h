#pragma once

#include "soloud_wav.h"
#include <string>

class AudioFile
{
public:
	AudioFile(SoLoud::Wav, std::string);
	~AudioFile();

	
	int ID;
	SoLoud::Wav soundFile;
	std::string name;
	bool isLoaded;	
};

