#pragma once

#include <unordered_map>

#include "src/media/Rendering.h"
#include "src/media/Audio.h"
#include "src/core/Input.h"
#include "src/core/Window.h"

class Program
{
public:
	void Init();
	void OnUpdate();
	void Finalise();

private:
	void input();

private:
	std::unordered_map<std::string, MTexture*> images;
	std::unordered_map<std::string, MTexture*> texts;
	std::unordered_map<std::string, MMusic*> audios;

	FontID BodoniModa = -1;

	int state = -1;
	bool state_event = false;

	int cooldown_max = 200;
	int cooldown = cooldown_max;
};

//class Program
//{
//public:
//	void Init();
//	void OnUpdate();
//	void Finalise();
//
//private:
//	void input();
//
//private:
//	std::unordered_map<std::string, MTexture*> images;
//	std::unordered_map<std::string, MTexture*> texts;
//	std::unordered_map<std::string, MMusic*> audios;
//
//	FONT_ID BodoniModa = -1;
//};