
cl /c /O1 /GS- /GL GOL.c
link /NODEFAULTLIB /ENTRY:main /SUBSYSTEM:CONSOLE /ALIGN:16 /LTCG GOL.obj ucrt.lib
