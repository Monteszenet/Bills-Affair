#include "Application.h"

#include <iostream>

#include "libs/sdl/include/SDL.h"
#include "src/media/Media.h"
#include "Scripts.h"
#include "Input.h"
#include "Window.h"
#include "Logging.h"
#include "src/program/Program.h"

Application* app;

void Application::Run()
{
	// Base application configuration and init.

	try {
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);		LOG_INFO("Initialised SDL.");

		EnterScriptingContext();

		CompileLuaToMSZNT("game\\scripts");

		InitLuaFunctions();

		RunScript(0);

		CreateWindow(m_name, m_window_x, m_window_y);

		InitMedia();

		InitInput();

		Program program;
		program.Init();				LOG_INFO("Initialised program.");

		Window_Show();				LOG_INFO("Showed window.");

		m_running = true;

		LOG_INFO(LOG_DEMARCATION);	 LOG_INFO("Entering program runtime.");

		while (m_running == true)
		{
			

			handle_input();

			program.OnUpdate();

			//OnUpdateContexts();

			//OnUpdateMedia();
		}

		LOG_INFO(LOG_DEMARCATION); LOG_INFO("Exiting program runtime.");

		program.Finalise();

		ExitScriptingContext();
		FinaliseMedia();
		FinaliseInput();
		DestroyWindow();
		SDL_Quit();

	}
	catch (MLog error)
	{
		LOG_INFO(LOG_DEMARCATION); LOG_INFO("Quitting program due to fatal error.");
		return;
	};

	return;
}

void Application::SetBaseDirectory(std::string base_dir)
{
	m_base_directory = base_dir;
}

void Application::handle_input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_TEXTINPUT:
			//*GetTextInputString() += e.text.text;
			break;
		case SDL_TEXTEDITING:
			//composition = e.edit.text;
			//cursor = e.edit.start;
			//selection_len = e.edit.length;
			break;
		}
		UpdateKey(e.type, e.key.keysym.scancode);
		UpdateMouse(e);
	}
	UpdateInput();
}



void App_Config(std::string title, std::string version, int w, int h)
{
	app->m_name = title;
	app->m_version = version;
	app->m_window_x = w;
	app->m_window_y = h;
}

void App_Quit()
{
	app->m_running = false;
}

Application* CreateApplication(std::string base_directory)
{
	app = new Application;
	app->SetBaseDirectory(base_directory);
	return app;
}

void DeleteApplication()
{
	delete app;
	app = NULL;
}
