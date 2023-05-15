#include "FileSystem.h"

#include "libs/sdl/include/SDL.h"

std::string GetFileDirectory()
{
	return SDL_GetPrefPath("msznt", "BillsAffair");
}