#include "core/Application.h"
#include "core/Logging.h"
#include "core/Utility.h"

#include "libs/sdl/include/SDL.h"

#include <iostream>

int main(int argc, char* args[])
{
    InitLogging("files\\log.txt");

    LOG_INFO(LOG_DEMARCATION);	 LOG_INFO("Entering program init-time.");
    LOG_INFO("Initialised logging.");

    Application* app = CreateApplication({ GetFileDirectory(), GetCLArgs(argc, args) });
    app->Run();
    DeleteApplication();

    FlushLog();

    FinaliseLogging();

    return 0;
}