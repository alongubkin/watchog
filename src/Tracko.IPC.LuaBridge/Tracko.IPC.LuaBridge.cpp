#include <Windows.h>
#include <lua.h>

int luaopen_tracko_lua_ipc(lua_State *L)
{
    MessageBoxW(NULL, L"Hummus", NULL, MB_OK);
    return 0;
}