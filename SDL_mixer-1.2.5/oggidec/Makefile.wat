#=============================================================================
#          This is a Watcom makefile to build SDLMIXER.DLL for OS/2
#
#
#=============================================================================

object_files=bitwise.obj block.obj codebook.obj floor0.obj floor1.obj framing.obj info.obj mapping0.obj mdct.obj registry.obj res012.obj sharedbook.obj synthesis.obj vorbisfile.obj window.obj

# Extra stuffs to pass to C compiler:
ExtraCFlags=-aa -D__EMX__

#
#==============================================================================
#
!include ..\Watcom.mif

.before
    set include=$(%os2tk)\h;$(%include);$(%sdlhome)\include;

all : $(object_files)

clean : .SYMBOLIC
    @if exist *.dll del *.dll
    @if exist *.lib del *.lib
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.res del *.res
    @if exist *.lst del *.lst
