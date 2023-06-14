gcc -shared -Iluart process.c -Lluart -llua54 -o process.dll
luart useprocess.lua
pause
