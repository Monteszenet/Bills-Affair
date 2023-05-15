#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "libs/lua/include/lua.hpp"

#define M_SCRIPT unsigned int

void EnterScriptingContext();
void ExitScriptingContext();

void InitLuaFunctions();

void CompileLuaToMSZNT(std::string path);

void RunScript(M_SCRIPT script);