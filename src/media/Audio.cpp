#include "Audio.h"

#include <unordered_map>

#include "libs/sdl/include/SDL_mixer.h"

#include "src/core/Logging.h"

#define Channels std::unordered_map<std::string, int>

struct MAudioData
{
	Channels channels;

} * mixer = NULL;

void InitMixer()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	mixer = new MAudioData;

	mixer->channels["sound"] = 0;
}

void FinaliseMixer()
{
	delete mixer;

	Mix_CloseAudio();
}

MMusic* Mixer_CreateMusic(std::string path)
{
	MMusic* new_music = new MMusic;

	new_music->handle = Mix_LoadMUS(path.c_str());

	if (new_music->handle == NULL)
		LOG_ERROR("Unable to load audio. Path given: '" + path + "'");

	return new_music;
}
void Mixer_FreeMusic(MMusic* music)
{
	Mix_FreeMusic(music->handle);
	music->handle = NULL;
}

void Mixer_PlayMusic(MMusic* music, int loops)
{
	Mix_PlayMusic(music->handle, loops);
}
void Mixer_StopMusic()
{
	Mix_HaltMusic();
}