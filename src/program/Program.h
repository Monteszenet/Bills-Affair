#pragma once

#include <unordered_map>

#include "src/media/Rendering.h"
#include "src/media/Audio.h"
#include "src/core/Input.h"
#include "src/core/Window.h"
#include "src/core/Scripts.h"

class Program
{
public:
	void Init();
	void OnUpdate();
	void Finalise();

private:
	void input();

	int static L_main(lua_State* L);
	int static L_image(lua_State* L);
	int static L_audio(lua_State* L);

private:
	std::unordered_map<std::string, MTexture*> images;
	std::unordered_map<std::string, MTexture*> texts;
	std::unordered_map<std::string, MMusic*> audios;

	FONT_ID BodoniModa = -1;
};