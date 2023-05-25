#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "libs/lua/include/lua.hpp"

#define M_SCRIPT unsigned int
#define NULL_SCRIPT 0

void EnterScriptingContext();
void ExitScriptingContext();

void InitLuaEnvironment();

void CompileLuaToMSZNT(std::string path);

M_SCRIPT GetScript(std::string script);
void RunScript(M_SCRIPT script);