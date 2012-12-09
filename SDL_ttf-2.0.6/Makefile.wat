#=============================================================================
#          This is a Watcom makefile to build SDLTTF.DLL for OS/2
#
#
#=============================================================================

dllname=SDLTTF

freetypefiles=freetype-2.1.9\objs\autofit.obj &
freetype-2.1.9\objs\autohint.obj &
freetype-2.1.9\objs\ftapi.obj &
freetype-2.1.9\objs\ftbase.obj &
freetype-2.1.9\objs\ftbbox.obj &
freetype-2.1.9\objs\ftbdf.obj &
freetype-2.1.9\objs\ftdebug.obj &
freetype-2.1.9\objs\ftglyph.obj &
freetype-2.1.9\objs\ftinit.obj &
freetype-2.1.9\objs\ftmm.obj &
freetype-2.1.9\objs\ftpfr.obj &
freetype-2.1.9\objs\ftstroke.obj &
freetype-2.1.9\objs\ftsynth.obj &
freetype-2.1.9\objs\ftsystem.obj &
freetype-2.1.9\objs\fttype1.obj &
freetype-2.1.9\objs\ftwinfnt.obj &
freetype-2.1.9\objs\ftxf86.obj &
freetype-2.1.9\objs\bdf.obj &
freetype-2.1.9\objs\ftcache.obj &
freetype-2.1.9\objs\cff.obj &
freetype-2.1.9\objs\type1cid.obj &
freetype-2.1.9\objs\ftgzip.obj &
freetype-2.1.9\objs\ftlzw.obj &
freetype-2.1.9\objs\pcf.obj &
freetype-2.1.9\objs\pfr.obj &
freetype-2.1.9\objs\psaux.obj &
freetype-2.1.9\objs\pshinter.obj &
freetype-2.1.9\objs\psnames.obj &
freetype-2.1.9\objs\raster.obj &
freetype-2.1.9\objs\sfnt.obj &
freetype-2.1.9\objs\smooth.obj &
freetype-2.1.9\objs\truetype.obj &
freetype-2.1.9\objs\type1.obj &
freetype-2.1.9\objs\type42.obj &
freetype-2.1.9\objs\winfnt.obj


object_files= SDL_ttf.obj $(freetypefiles)

# Extra stuffs to pass to C compiler:
ExtraCFlags=

#
#==============================================================================
#
!include Watcom.mif

.before
    @set include=$(%os2tk)\h;$(%include);$(%sdlhome)\include;.\;.\freetype-2.1.9\include;

all : $(dllname).dll $(dllname).lib

$(dllname).dll : $(object_files)
    wlink @$(dllname)

$(dllname).lib : $(dllname).dll
    implib $(dllname).lib $(dllname).dll

clean : .SYMBOLIC
    @if exist $(dllname).dll del $(dllname).dll
    @if exist *.lib del *.lib
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.res del *.res
    @if exist *.lst del *.lst
