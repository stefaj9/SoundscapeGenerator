// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "al.h"
#include "alc.h"

using namespace std;

int endWithError(char* msg, int error=0) {
	cout << msg << endl;
	system("PAUSE");
	return error;
}

int main()
{
	FILE *fp = NULL;
	fp = fopen("Amen.wav","rb");

	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F') {
		char msg[8] = "No RIFF";
		return endWithError(msg);
	}
	fread(&size, sizeof(DWORD),1,fp);
	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E') {
		char msg[9] = "Not WAVE";
		return endWithError(msg);
	}
	fread(type, sizeof(char), 4, fp);
	if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ') {
		char msg[9] = "Not fmt ";
		return endWithError(msg);
	}

	fread(&chunkSize,sizeof(DWORD),1,fp);
	fread(&formatType,sizeof(short),1,fp);
	fread(&channels,sizeof(short),1,fp);
	fread(&sampleRate,sizeof(DWORD),1,fp);
	fread(&avgBytesPerSec,sizeof(DWORD),1,fp);
	fread(&bytesPerSample,sizeof(short),1,fp);
	fread(&bitsPerSample,sizeof(short),1,fp);

	fread(type, sizeof(char), 4, fp);
	if(type[0] !='d' || type[1] != 'a' || type[2] != 't' || type[3] != 'a'){
		char msg[13] = "Missing DATA";
		return endWithError(msg);
	}

	fread(&dataSize, sizeof(DWORD), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf,sizeof(BYTE),dataSize,fp);

	ALCdevice *device;
	ALCcontext *context;

	device = alcOpenDevice(NULL);
	if (!device) {
		char msg[16] = "No sound device";
		return endWithError(msg);
	}
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) {
		char msg[17] = "No sound context";
		return endWithError(msg);
	}

	ALuint source;
	ALuint buffer;
	ALuint frequency = sampleRate;
	ALuint format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	if (bitsPerSample == 8) {
		if(channels == 1) {
			format = AL_FORMAT_MONO8;
		}
		else if (channels == 2) {
			format = AL_FORMAT_STEREO8;
		}
	}
	else if (bitsPerSample == 16) {
		if(channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else if (channels == 2){
			format = AL_FORMAT_STEREO16;
		}
	}

	alBufferData(buffer, format, buf, dataSize, frequency);

	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 0.8f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSourcefv(source, AL_POSITION, SourcePos);
	alSourcefv(source, AL_VELOCITY, SourceVel);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	alSourcePlay(source);

	int i = 0;

	while (true) {
		i++;

		cout << i << endl;

		if (i > 10000) {
			alSourcef(source, AL_PITCH, 0.9f);
		}

		if (i > 20000) {
			alSourcef(source, AL_PITCH, 1.2f);
		}

	}
	
    return 0;
}
