// SoundscapeGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "soloud.h"
#include "soloud_wav.h"

#include "SoundObject.h"

using namespace std;

int main()
{
	
	/*
	SoLoud::Soloud gSoloud; // SoLoud engine
	SoLoud::Wav drum;      // One wave file

	gSoloud.init(); // Initialize SoLoud

	drum.load("Drum.wav"); // Load a wave

	gSoloud.play(drum); // Play the wave
	*/
	

	SoundObject* wind;

	wind = new SoundObject();
	wind->addWav("Drum.wav");
	wind->addWav("sike.wav");

	wind->loadWavs();
	wind->soundEngine.play(wind->wavFiles->at(0));
	wind->soundEngine.play(wind->wavFiles->at(1));

	while (true) {

	}



    return 0;
}

