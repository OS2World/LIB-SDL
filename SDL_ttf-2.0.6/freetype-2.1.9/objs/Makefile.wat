#=============================================================================
#          This is a Watcom makefile to build SDLTTF.DLL for OS/2
#
#
#=============================================================================

object_files=autofit.obj &
autohint.obj &
ftapi.obj &
ftbase.obj &
ftbbox.obj &
ftbdf.obj &
ftdebug.obj &
ftglyph.obj &
ftinit.obj &
ftmm.obj &
ftpfr.obj &
ftstroke.obj &
ftsynth.obj &
ftsystem.obj &
fttype1.obj &
ftwinfnt.obj &
ftxf86.obj &
bdf.obj &
ftcache.obj &
cff.obj &
type1cid.obj &
ftgzip.obj &
ftlzw.obj &
pcf.obj &
pfr.obj &
psaux.obj &
pshinter.obj &
psnames.obj &
raster.obj &
sfnt.obj &
smooth.obj &
truetype.obj &
type1.obj &
type42.obj &
winfnt.obj

# Extra stuffs to pass to C compiler:
ExtraCFlags=

#
#==============================================================================
#
!include ..\..\Watcom.mif

.c: ..\src\autofit;..\src\autohint;..\src\base;..\src\bdf;..\src\cache;..\src\cff;..\src\cid;..\src\gzip;..\src\lzw;..\src\otlayout;..\src\pcf;..\src\pfr;..\src\psaux;..\src\pshinter;..\src\psnames;..\src\raster;..\src\sfnt;..\src\smooth;..\src\truetype;..\src\type1;..\src\type42;..\src\winfonts
.before
    @set include=$(%include);.\;..\include;..\src;

all : $(object_files)

clean : .SYMBOLIC
    @if exist *.lib del *.lib
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.res del *.res
    @if exist *.lst del *.lst
