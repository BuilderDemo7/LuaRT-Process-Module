#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <luart.h>
#include <process.h>
//using namespace std;

// process.FindWindow(windowName) method
// returns a userdata and the ID of the of the process
LUA_METHOD(process, FindWindow)
{
  if (LUA_TSTRING == lua_type(L, 1)) {
  const char *windowName = lua_tostring(L, -1); // lua string to char
  
  HWND win = FindWindowA(windowName,NULL); // find the window
  DWORD pID = 0; // the window ID
  GetWindowThreadProcessId(win, &pID); // get the window ID

  lua_pushlightuserdata(L, win); // returns the userdata
  lua_pushinteger(L, pID); // and the ID
  return 2;
  }
}

/*
    static int process_new(lua_State* L)
    {
            Process ** udata = (Process **)lua_newuserdata(L, sizeof(Process));
            *udata = new Process();
            luaL_getmetatable(L, "Process");
            lua_setmetatable(L, -1);
            return 1;
    }
*/

// process.WriteProcessMemory(processID,address,string)
// returns false if failed and true if succeded
LUA_METHOD(process, WriteProcessMemory)
{
  if (LUA_TNUMBER == lua_type(L, 1) && LUA_TNUMBER == lua_type(L, 2) && LUA_TSTRING == lua_type(L, 3)) {
  const int pID = lua_tonumber(L, 1);
  const int address = lua_tonumber(L,2);
  const char* bytes = lua_tostring(L,3);
  if (pID < 1) {
	 luaL_error(L,"Invalid process ID!"); 
  }
  //char memory[sizeof(bytes)];
  
  HANDLE pHandle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, 0, pID);

  VirtualProtectEx(pHandle, (LPVOID)address, strlen(bytes), PAGE_READWRITE, NULL); // removes protection so it can be written
  
  int status = WriteProcessMemory(pHandle, (LPVOID)address, bytes, strlen(bytes), NULL); // and write it and return a status 
  int lastErr = GetLastError();
  //ReadProcessMemory(pHandle, (LPVOID)address, &memory, sizeof(bytes), NULL);
  
  CloseHandle(pHandle);

  /*
  if (memory == bytes) {
	  lua_pushboolean(L,1); // returns true if the bytes were written correctly
	  return 1;
  }
  else {
      lua_pushboolean(L,0); // returns false if the bytes wasn't written correctly
      return 1;
  }
  */
  lua_pushboolean(L,status);
  return 1;
  //lua_pushboolean(L,1);
  //return 1; // returns nothing
  }
}

// process.ReadProcessMemory(processID,address,size)
// return the readed memory
LUA_METHOD(process, ReadProcessMemory)
{
  if (LUA_TNUMBER == lua_type(L, 1) && LUA_TNUMBER == lua_type(L, 2) && LUA_TNUMBER == lua_type(L, 3)) {
  const int pID = lua_tonumber(L, 1);
  const int address = lua_tonumber(L,2);
  const int size = lua_tonumber(L,3);
  char memory[size];
  if (pID < 1) {
	 luaL_error(L,"Invalid process ID!"); 
  }
  
  HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);

  ReadProcessMemory(pHandle, (LPVOID)address, &memory, size, NULL);
  
  CloseHandle(pHandle);

  lua_pushstring(L,memory);
  return 1; // returns nothing
  }
  else {
	  luaL_error(L,"Bad argument at method ReadProcessMemory");
  }
}



//--------------- The finalizer function called when the module is garbage collected
int process_finalize(lua_State *L)
{
  //--- finalizer functions returns nothing
  return 0;
}


        
static const luaL_Reg process_properties[] = {
  {NULL, NULL}
};

static const luaL_Reg processlib[] = {
      {"FindWindow",		process_FindWindow}, // FindWindow method 
	  {"WriteProcessMemory", process_WriteProcessMemory}, // WriteProcessMemory method
	  {"ReadProcessMemory", process_ReadProcessMemory}, // ReadProcessMemory
      {NULL, NULL}
};



int __declspec(dllexport) luaopen_process(lua_State *L)
{
    //luaL_register(L, "MyObj", processlib);
	lua_regmodulefinalize(L, process);
    return 1;
}
