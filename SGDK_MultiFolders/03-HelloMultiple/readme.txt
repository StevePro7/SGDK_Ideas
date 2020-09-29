readme
28/09/2020

Remember that I had to manually rebuild all the dependent folders in "out"
because I remove the "pre-build" step that does this for me in my version
of makefile.gen


01.
I setup the folders e.g. "engine" and I got this working today by following
moon-watcher git repo for AbbeyMD
D:\Github\moon-watcher\AbbayeMD


02.
For completeness I want to have *.c file in src folder to refer to *.h file in inc folder
without all the ugly relative directory crap e.g. inc\engine and src\engine

Easy to do this for x86 builds - just update the project properties
C/C++ | General | Additional Include Directories
$(SolutionDir)..\lib;$(ProjectDir)inc;$(ProjectDir)inc\engine;$(ProjectDir)res;$(GDK_WIN)\inc;$(IncludePath)


in order to get this to work for SGDK we must update our custom makefile.gen
esp. INCLUDE= inc
e.g.
INCS= -I$(INCLUDE) -I$(INCLUDE)/engine -I$(SRC) -I$(RES) -I$(LIBINCLUDE) -I$(LIBRES)




20/09/2020
Today, I tried to replicate a stripped down version of the SGDK makefile
i.e.
~/dev/makefile.gen


Here are the assumptions for this to work:

01.
copy under "src" the "boot" folder with 2x files from here
E:\SGDK\src\boot


02.
manually create the "out" directory and the 2x sub directories
res
src
