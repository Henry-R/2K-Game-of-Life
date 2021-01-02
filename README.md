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
Any RLE file from that website should work, although the rule specifation in the header should be removed, but might still work.

## How to use
Once file is loaded, simply press enter to step life and type 'e' and enter to exit program.

## RLE Files
RLE Files are in the format specified here https://www.conwaylife.com/wiki/Run_Length_Encoded, with a few missing features.
Only the #P line is implemented to do offsets, everything else is ignored.

The #P line gives the offset from the 0, 0 top left corner.
x and y gives the size of universe life can update in.
When using a RLE file from www.conwaylife.com, and updating the position, you should also increse the x and y values to give it space.
