/*
 * Copyright (C) 2016 "IoT.bzh"
 * Author Fulup Ar Foll <fulup@iot.bzh>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, something express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Reference:
 *   Json load using json_unpack https://jansson.readthedocs.io/en/2.9/apiref.html#parsing-and-validating-values
 */

#ifndef _LUA_CTL_INCLUDE_
#define _LUA_CTL_INCLUDE_

#define _GNU_SOURCE

// prefix start debug script
#ifndef CONTROL_DOSCRIPT_PRE
#define CONTROL_DOSCRIPT_PRE "debug"
#endif

// default event name used by LUA
#ifndef CONTROL_LUA_EVENT
#define CONTROL_LUA_EVENT "luaevt"
#endif

// default use same search path for config.json and script.lua
#ifndef CONTROL_LUA_PATH
#define CONTROL_LUA_PATH CONTROL_CONFIG_PATH
#endif

// standard lua include file
#ifdef CONTROL_SUPPORT_LUA
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#endif

#include "ctl-timer.h"

PUBLIC int LuaLibInit ();

typedef int (*Lua2cFunctionT)(char *funcname, json_object *argsJ);
typedef int (*Lua2cWrapperT) (lua_State* luaState, char *funcname, Lua2cFunctionT callback);

#define CTLP_LUALOAD Lua2cWrapperT Lua2cWrap;
#define CTLP_LUA2C(FuncName, label,argsJ, context) static int FuncName(char*label,json_object*argsJ);\
        int lua2c_ ## FuncName(lua_State* luaState){return((*Lua2cWrap)(luaState, MACRO_STR_VALUE(FuncName), FuncName, PLUGIN_NAME));};\
        static int FuncName(char* label, json_object* argsJ, void* context)

typedef enum {
    LUA_DOCALL,
    LUA_DOSTRING,
    LUA_DOSCRIPT,
} LuaDoActionT;


PUBLIC int LuaConfigLoad();
PUBLIC int LuaConfigExec();
PUBLIC void LuaL2cNewLib(const char *label, luaL_Reg *l2cFunc, int count);
PUBLIC int Lua2cWrapper(lua_State* luaState, char *funcname, Lua2cFunctionT callback);
PUBLIC int LuaCallFunc (CtlActionT *action, json_object *queryJ) ;
PUBLIC void ctlapi_lua_docall (afb_req request);
PUBLIC void ctlapi_lua_dostring (afb_req request);
PUBLIC void ctlapi_lua_doscript (afb_req request);


#endif