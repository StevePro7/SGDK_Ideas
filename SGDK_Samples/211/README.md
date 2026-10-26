26-Oct-2026
Today I started on the latest SGDK samples
e.g.
image

but I saw that the library generation did not update variables
e.g.
pal.h
extern const u16* const palette_black;
extern const u16 palette_grey[16];
extern const u16 palette_red[16];
extern const u16 palette_green[16];
extern const u16 palette_blue[16];


pal.c
const u16* const palette_black = NULL;
const u16 palette_grey[ 16 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const u16 palette_red[ 16 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const u16 palette_green[ 16 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const u16 palette_blue[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


so Copilot just hacked inline to get this sample working


Also - there was an issue on Ctrl+1 so I had to "clean"
cd D:\GitHub\StevePro7\SGDK_Ideas\SGDK_Samples\211\basics\image\dev
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen clean
build.bat