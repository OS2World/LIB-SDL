#=============================================================================
#          This is a Watcom makefile to build SDLMIXER.DLL for OS/2
#
#
#=============================================================================

object_files=drv_nos.obj drv_sdl.obj load_it.obj load_mod.obj load_s3m.obj load_xm.obj mdreg.obj mdriver.obj mloader.obj mlreg.obj mlutil.obj mmalloc.obj mmerror.obj mmio.obj mplayer.obj munitrk.obj mwav.obj npertab.obj sloader.obj virtch.obj virtch2.obj virtch_common.obj

# Extra stuffs to pass to C compiler:
ExtraCFlags=

#
#==============================================================================
#
!include ..\Watcom.mif

.before
    set include=$(%os2tk)\h;$(%include);$(%sdlhome)\include;.\;

all : $(object_files)

clean : .SYMBOLIC
    @if exist *.dll del *.dll
    @if exist *.lib del *.lib
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.res del *.res
    @if exist *.lst del *.lst
