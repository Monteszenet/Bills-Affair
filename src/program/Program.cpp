#include "Program.h"

#include "src/core/Application.h"
#include "src/media/Rendering.h"
#include "src/media/Audio.h"
#include "src/core/Input.h"
#include "src/core/Window.h"
#include "src/core/Logging.h"

void Program::Init()
{

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