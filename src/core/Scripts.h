#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "libs/lua/include/lua.hpp"

#define LuaCFunction lua_CFunction
#define M_SCRIPT unsigned int
#define NULL_SCRIPT 0

void EnterScriptingContext();
void ExitScriptingContext();

void InitLuaEnvironment();
void Lua_RegisterFunction(std::string name, LuaCFunction function);

void CompileLuaToMSZNT(std::string path);

M_SCRIPT Lua_GetScript(std::string script);
void Lua_RunScript(M_SCRIPT script);
void Lua_RunScriptFile(std::string path);
void Lua_RunScript(std::string script);