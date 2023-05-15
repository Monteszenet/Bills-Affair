#pragma once

#include <string>

#include "libs/sdl/include/SDL_mixer.h"

#define M_MIXER_INFINITE_LOOP -1

struct MAudio
{

};

struct MMusic
{
	Mix_Music* handle = NULL;
};

void InitMixer();
void FinaliseMixer();

MAudio* Mixer_CreateAudio(std::string path);
MMusic* Mixer_CreateMusic(std::string path);
void Mixer_FreeMusic(MMusic* music);

void Mixer_PlayMusic(MMusic* music, int loops);
void Mixer_StopMusic();