#include "LuaGlue.h"

#include <string>

#include "Application.h"
#include "Logging.h"

// Native -> Lua.

int L_AppConfig(lua_State* L)
{
	App_Config(luaL_checkstring(L, -4), luaL_checkstring(L, -3),
		(int)lua_tointeger(L, -2), (int)lua_tointeger(L, -1));

	return 0;
}