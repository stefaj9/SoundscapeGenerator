#include "stdafx.h"
#include "AudioFile.h"



AudioFile::AudioFile(SoLoud::Wav soundFile, std::string name)
{
	this->soundFile = soundFile;
	this->name = name;
	this->isLoaded = false;
}

AudioFile::~AudioFile()
{
}
