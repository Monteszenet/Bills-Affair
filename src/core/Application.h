#pragma once

#include <string>

#include "libs/lua/include/lua.hpp"

class Application
{	
public:
	void Run();

public:
	void SetBaseDirectory(std::string base_dir);

private:
	const std::string auto_m_name = "MSZNT";
	const std::string auto_m_version = "0.00";
	const int auto_m_window_x = 960;
	const int auto_m_window_y = 720;

	const std::string auto_m_current_context = "NONE";

private:
	std::string m_name = auto_m_name;
	std::string m_version = auto_m_version;
	std::string m_base_directory;
	bool m_running = false;
	int m_window_x = auto_m_window_x;
	int m_window_y = auto_m_window_y;

private:
	void handle_input();

	friend void App_Config(std::string title, std::string version, int w, int h);
	friend void App_Quit();
};

void App_Config(std::string title, std::string version, int w, int h);
void App_Quit();

Application* CreateApplication(std::string base_directory);
void DeleteApplication();