#include "stdafx.h"
#include "SoundObject.h"


SoundObject::SoundObject(Wav wav, string name)
{
	this->wav = wav;
	this->name = name;
}


SoundObject::~SoundObject()
{
}
