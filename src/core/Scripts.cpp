#include "Scripts.h"

#include "Application.h"
#include "Logging.h"
#include "LuaGlue.h"

struct Scripts
{
	lua_State* L = NULL;
	std::vector<std::string> scripts;

} scripts;

lua_State* L = scripts.L;

bool CheckLua(int r);



void EnterScriptingContext()
{
	L = luaL_newstate();

	luaopen_base(L);
	luaopen_string(L);
	luaopen_math(L);
	luaL_openlibs(L);
}

void ExitScriptingContext()
{
	lua_close(L);
}

bool CheckLua(int r)
{
	if (r != LUA_OK)
	{
		std::string lua_error = lua_tostring(L, -1);
		LOG_LUA("[LUA ERROR]: " + lua_error);
		return false;
	}
	return true;
}

void InitLuaFunctions()
{
	lua_register(L, "AppConfig", L_AppConfig);
}

void CompileLuaToMSZNT(std::string path)
{
	scripts.scripts.push_back("game/scripts/config.lua");
}

void RunScript(M_SCRIPT script)
{
	if (CheckLua(luaL_dofile(L, scripts.scripts[script].c_str())) == false)
		LOG_FATAL("Failed to run config lua script.");
}









//void RunConfigScript()
//{
//	if (CheckLua(luaL_dofile(L, scripts.scripts[0].c_str())) == false)
//	{
//		LOG_FATAL("Failed to run config lua script.");
//	}
//	
//	lua_getglobal(L, "AppConfig");
//	if (lua_istable(L, -1))
//	{
//		lua_pushstring(L, "Title");
//		lua_gettable(L, -2);
//		SetStrApplicationConfig("Title", lua_tostring(L, -1));
//		lua_pop(L, 1);
//
//		lua_pushstring(L, "Version");
//		lua_gettable(L, -2);
//		SetStrApplicationConfig("Version", lua_tostring(L, -1));
//		lua_pop(L, 1);
//
//		lua_pushstring(L, "WindowWidth");
//		lua_gettable(L, -2);
//		SetIntApplicationConfig("WindowWidth", (int)lua_tointeger(L, -1));
//		lua_pop(L, 1);
//
//		lua_pushstring(L, "WindowHeight");
//		lua_gettable(L, -2);
//		SetIntApplicationConfig("WindowHeight", (int)lua_tonumber(L, -1));
//		lua_pop(L, 1);
//	}
//}
