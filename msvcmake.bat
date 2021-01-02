cls
:: Compile to obj file
cl /c /O1 /GS- /GL GOL.c
:: Link with no static libraries
link /NODEFAULTLIB /ENTRY:main /SUBSYSTEM:CONSOLE /ALIGN:16 /LTCG GOL.obj ucrt.lib
::Crinkler.exe /NODEFAULTLIB /ENTRY:main /SUBSYSTEM:CONSOLE /ALIGN:32 GOL.obj ucrt.lib user32.lib
