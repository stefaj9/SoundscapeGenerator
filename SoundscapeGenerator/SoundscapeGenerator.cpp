// SoundscapeGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "soloud.h"
#include "soloud_wav.h"
#include <random>

#include "SoundChannel.h"

using namespace std;

int main()
{


	
	SoundChannel* wind;

	wind = new SoundChannel();
	wind->addWav("Audio/Wind/sWindLoop1.wav");
	wind->addWav("Audio/Wind/sWindLoop2.wav");
	wind->addWav("Audio/Wind/sWindLoop3.wav");

	wind->playWavNumber(1);

	while (true) {
		char q;
		cin >> q;




	}



    return 0;
}

