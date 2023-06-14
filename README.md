# LuaRT-Process-Module
13/06/2023 23:46 (11:46 PM) GMT-3
I made this simple module for LuaRT and then I pubilshed it on github,

with this module you can read and write process memory through Lua 5.4.
thanks to LuaRT you can really do a module for this!

METHODS:
process.FindWindow(windowName) --> windowName: string (the window to find, no need to include .exe!)
; find the window process
; returns a userdata of the process and returns the process ID.

process.WriteProcessMemory(processID,address,string) --> processID: number (the target process ID), address: dword or number (the address to write to), string: string (bytes to be written)
; write a string to a process's memory.

process.ReadProcessMemory(processID,address,size) --> processID: number (the target process ID), address: dword or number (the address to be read), size: number (the size in bytes to read)
; read a address of the process's memory
; returns a string of the content.

thank you for reading... this module doesn't kinda work well but it's still usable.
