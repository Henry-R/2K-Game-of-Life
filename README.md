# 2K-Game-of-Life
## Description
Conway's Game of Life written in 2 kilobytes with the ability to read the inital starting state from RLE files.

## Building
To build the file, open the x86 Native Tools Command Prompt for VS 20xx, and execute the following commands:
``` batch
cl /c /O1 /GS- /GL GOL.c
link /NODEFAULTLIB /ENTRY:main /SUBSYSTEM:CONSOLE /ALIGN:16 /LTCG GOL.obj ucrt.lib
```

## Running
To run the program, simply call **GOL.exe < your_file.txt**
Program must be supplied a txt file through stdin

The **test.txt** file contains the RLE file from [ConwayLife.com/wiki/Gosper_glider_gun](https://www.conwaylife.com/wiki/Gosper_glider_gun)
Any RLE file from that website should work.
