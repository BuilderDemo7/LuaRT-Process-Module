local process = require "process"

local data,ID = process.FindWindow("notepad++")
process.WriteProcessMemory(ID,10824828,"Hacked!")
local memory = process.ReadProcessMemory(ID,10824828,121)

print("Process -: "..tostring(data)..", "..ID)
print("Process -: "..memory..", size of "..#memory.." bytes")
print("Done.")
