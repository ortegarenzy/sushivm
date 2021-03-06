
/*
 * This file is part of SushiVM
 * Copyright (c) 2019-2020 Eqela Oy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "lib_bcrypt.h"

int generate_salt(lua_State* state)
{
	int factor = luaL_checkint(state, 2);
	char salt[BCRYPT_HASHSIZE];
	int ret = bcrypt_gensalt(factor, salt);
	if(ret == 1) {
		lua_pushstring(state, "");
		return 1;
	}
	lua_pushstring(state, salt);
	return 1;
}

int hash_password(lua_State* state)
{
	const char* password = luaL_checkstring(state, 2);
	const char* salt = luaL_checkstring(state, 3);
	char hash[BCRYPT_HASHSIZE];
	int ret = bcrypt_hashpw(password, salt, hash);
	if(ret == 1) {
		lua_pushstring(state, "");
		return 1;
	}
	lua_pushstring(state, hash);
	return 1;
}

int check_password(lua_State* state)
{
	const char* password = luaL_checkstring(state, 2);
	const char* hash = luaL_checkstring(state, 3);
	int v = bcrypt_checkpw(password, hash);
	lua_pushnumber(state, v);
	return 1;
}

static const luaL_Reg funcs[] = {
	{ "generate_salt", generate_salt },
	{ "hash_password", hash_password },
	{ "check_password", check_password }
};

void lib_bcrypt_init(lua_State* state)
{
	luaL_newlib(state, funcs);
	lua_setglobal(state, "_bcrypt");
}
