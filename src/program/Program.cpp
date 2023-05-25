#include "Program.h"

#include "src/core/Application.h"
#include "src/media/Rendering.h"
#include "src/media/Audio.h"
#include "src/core/Input.h"
#include "src/core/Window.h"
#include "src/core/Logging.h"
#include "src/core/Scripts.h"

void Program::Init()
{
	Lua_RegisterFunction("main", Program::L_main);

	Lua_RunScriptFile("game/scripts/main.lua");
}

void Program::OnUpdate()
{
	input();
}

void Program::Finalise()
{

}

void Program::input()
{
	if (GetKeyDown(SDL_SCANCODE_ESCAPE) == true)
	{
		App_Quit();
	}
	if (GetMouseButtonPressed(Mouse_LeftButton))
	{
		App_Quit();
	}
}

int Program::L_main(lua_State* L)
{
	LOG_INFO("hiiiiiiiiiiiiiiiiiiiiiiiii");

	return 0;
}

int Program::L_image(lua_State* L)
{


	return 0;
}

int Program::L_audio(lua_State* L)
{


	return 0;
}