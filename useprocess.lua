local process = require "process"

local dpldata,ID = process.FindWindow("notepad++")
--local written = process.WriteProcessMemory(ID,10824828,"Hacked!")
local memory = process.ReadProcessMemory(ID,10824828,121)

print("Process -: "..tostring(dpldata)..", "..ID)
print("Process -: "..memory..", size of "..#memory.." bytes")
--print("Process written memory -; "..tostring(written))
print("Done")
--print(0x23E82498)