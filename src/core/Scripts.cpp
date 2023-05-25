#include "Scripts.h"

#include <unordered_map>

#include "Application.h"
#include "Logging.h"
#include "LuaGlue.h"

struct Scripts
{
	lua_State* L = NULL;
	std::unordered_map<M_SCRIPT, std::string> scripts;

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
		LOG_ERROR("[LUA ERROR]: " + lua_error);
		return false;
	}
	return true;
}

void InitLuaEnvironment()
{
	/* Logging enums */ {
		lua_pushinteger(L, LOGTYPE_LUA);
		lua_setglobal(L, "LOG_LUA");
		lua_pushinteger(L, LOGTYPE_DEBUG);
		lua_setglobal(L, "LOG_DEBUG");
		lua_pushinteger(L, LOGTYPE_INFO);
		lua_setglobal(L, "LOG_INFO");
		lua_pushinteger(L, LOGTYPE_WARN);
		lua_setglobal(L, "LOG_WARN");
		lua_pushinteger(L, LOGTYPE_ERROR);
		lua_setglobal(L, "LOG_ERROR");
		lua_pushinteger(L, LOGTYPE_FATAL);
		lua_setglobal(L, "LOG_FATAL");
	}

	lua_register(L, "AppConfig", L_AppConfig);
	lua_register(L, "Log", L_Log);
}

void CompileLuaToMSZNT(std::string path)
{
	scripts.scripts[NULL_SCRIPT] = "";
	scripts.scripts[(M_SCRIPT)scripts.scripts.size()] = "game/scripts/config.lua";
}

M_SCRIPT GetScript(std::string script)
{
	for (auto& s : scripts.scripts)
	{
		if (s.second == script)
			return s.first;
	}
	LOG_ERROR("Couldn't locate script: " + script);
	return NULL_SCRIPT;
}

void RunScript(M_SCRIPT script)
{
	if (scripts.scripts.find(script) != scripts.scripts.end())
	{
		if (CheckLua(luaL_dofile(L, scripts.scripts[script].c_str())) == false)
			LOG_FATAL("Failed to run script.");
#ifdef M_DEBUG
		LOG_INFO("Ran script: " + scripts.scripts[script]);
#endif
		return;
	}
	else
	{
		LOG_FATAL("Attempted to run invalid/unknown script.");
		return;
	}
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
