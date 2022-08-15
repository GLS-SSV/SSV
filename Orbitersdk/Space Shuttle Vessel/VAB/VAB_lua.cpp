/******* SSV File Modification Notice *******
Date         Developer
2020/06/20   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#include "VAB.h"
#include <stdio.h>

extern "C" {
#include "lua\lua.h"
#include "lua\lualib.h"
#include "lua\lauxlib.h"
}

// ==========================================================================
// API function prototypes

VAB *lua_toVAB (lua_State *L, int idx = 1);
//int dgGear (lua_State *L);
int vabMoveVLCDoor (lua_State *L);
int vabOpenVLCDoor (lua_State *L);
int vabCloseVLCDoor (lua_State *L);
int vabStopVLCDoor (lua_State *L);
int vabGetVLCDoorPos (lua_State *L);
int vabStopCurrentVLCAction(lua_State *L);

// ==========================================================================
// API initialisation

int VAB::Lua_InitInterpreter (void *context)
{
	lua_State *L = (lua_State*)context;

	// load atmospheric autopilot
	//luaL_dofile (L, "Script\\dg\\aap.lua");

	return 0;
}

int VAB::Lua_InitInstance (void *context)
{
	lua_State *L = (lua_State*)context;

	// check if interpreter has DG table loaded already
	luaL_getmetatable (L, "VESSEL.VAB");

	if (lua_isnil (L, -1)) { // register new functions
		lua_pop (L, 1);
		static const struct luaL_reg vabLib[] = {
			{"MoveVLCDoor", vabMoveVLCDoor},
			{"OpenVLCDoor", vabOpenVLCDoor},
			{"CloseVLCDoor", vabCloseVLCDoor},
			{"StopVLCDoor", vabStopVLCDoor},
			{"GetVLCDoorPos", vabGetVLCDoorPos},
			{NULL, NULL}
		};

		// create metatable for vessel userdata
		luaL_newmetatable (L, "VAB.vtable");

		// create a table for the overloaded methods
		luaL_openlib (L, "VAB.method", vabLib, 0);

		// create metatable for accessing inherited methods from VESSEL
		luaL_newmetatable (L, "VAB.base");
		lua_pushstring (L, "__index");
		luaL_getmetatable (L, "VESSEL.vtable");
		lua_settable (L, -3);

		// set DG.base as metatable for DG.method
		lua_setmetatable (L, -2);

		// point vessel userdata to VAB.method
		lua_pushstring (L, "__index");
		lua_pushvalue (L, -2); // push VAB.method
		lua_settable (L, -4);

		// pop DG.method from the stack
		lua_pop (L, 1);
	}

	lua_setmetatable (L, -2);

	return 0;
}

// ==========================================================================
// Script API functions

VAB *lua_toVAB (lua_State *L, int idx)
{
	VESSEL **pv = (VESSEL**)lua_touserdata (L, idx);
	VAB *vab = (VAB*)*pv;
	return vab;
}

int vabMoveVLCDoor(lua_State *L) {

	return 0;
}

int vabOpenVLCDoor (lua_State *L) {
	VAB* vab = lua_toVAB(L, 0);
	unsigned int bay = (unsigned int)lua_tonumber(L, 1);
	unsigned int seg = (unsigned int)lua_tonumber(L, 1);
	bool res = vab->openTo(bay, seg);
	lua_pushboolean(L, res);
	return 1;
}

int vabCloseVLCDoor (lua_State *L) {
	return 1;
}
int vabStopVLCDoor (lua_State *L) {
	return 1;
}

int vabGetVLCDoorPos (lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int bay = (int)lua_tonumber(L, 1);
	//---
	lua_pushinteger(L, 0);
	lua_pushstring(L, "stopped");
	lua_pushnumber(L, 0.0);
	return 3;
}