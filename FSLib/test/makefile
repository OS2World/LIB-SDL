###############################################################################
#
# This is a Watcom Makefile to create an OS/2 executable
#
###############################################################################
#
#
# Settings
#

exename=test
object_files=test.obj

# Create debug build?
debug_build=defined

#
###############################################################################
#
#
# Common stuff to build a DLL
#

linkfilename = $(exename)

!ifdef debug_build
debugflags = -d2 -dDEBUG_BUILD
linkfilename = $(exename)_Debug
!else
debugflags =
linkfilename = $(exename)_NoDebug
!endif

cflags = $(debugflags) -bm -bt=OS2 -5 -fpi

.before
    set include=$(%os2tk)\h;$(%include);..

.extensions:
.extensions: .exe .obj .c

all : $(exename).exe

$(exename).exe: $(object_files)

.c.obj : .AUTODEPEND
    wcc386 $[* $(cflags)

.obj.exe : .AUTODEPEND
    wlink @$(linkfilename)
clean : .SYMBOLIC
        @if exist $(exename).exe del $(exename).exe
        @if exist *.obj del *.obj
        @if exist *.map del *.map
        @if exist *.res del *.res
        @if exist *.lst del *.lst
