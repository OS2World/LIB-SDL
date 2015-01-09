#=============================================================================
#          This is a Watcom makefile to build SDLMIXER.DLL for OS/2
#
#
#=============================================================================

object_files=common.obj controls.obj filter.obj instrum.obj mix.obj output.obj playmidi.obj readmidi.obj resample.obj sdl_a.obj sdl_c.obj tables.obj timidity.obj

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
