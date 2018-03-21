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

	SoundChannel* birds;
	birds = new SoundChannel();
	birds->addWav("Audio/Birds/birds1.wav");
	birds->addWav("Audio/Birds/birds2.wav");

	SoundChannel* rain;
	rain = new SoundChannel();
	rain->addWav("Audio/Rain/rain1.wav");


	wind->fadeInWavNumber(1,1);


	while (true) {
		int vel;
		cin >> vel;

		if (vel <= 20) {
			if (birds->wav->at(0)->isPlaying) {
				birds->fadeOutWavNumber(1,4);
			}
		}
		if (vel > 20) {
			if (!birds->wav->at(0)->isPlaying) {
				birds->fadeInWavNumber(1,4);
			}
			if (rain->wav->at(0)->isPlaying) {
				rain->fadeOutWavNumber(1,6);
			}
		}
		if (vel > 45) {
			if (!rain->wav->at(0)->isPlaying) {
				rain->fadeInWavNumber(1,6);
			}
		}


	}



    return 0;
}

