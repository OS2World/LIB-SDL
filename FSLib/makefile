###############################################################################
#
# This is a Watcom Makefile to create the FSLib.DLL
#
###############################################################################
#
#
# Settings
#

dllname=FSLib

object_files=FSLib.obj

# Create debug build?
#debug_build=defined

#
###############################################################################
#
#
# Common stuff to build a DLL
#

dllflags = -bd


!ifdef debug_build
debugflags = -d2 -dDEBUG_BUILD
!else
debugflags =
!endif

cflags = $(debugflags) -bm -bt=OS2 -5 -fpi -sg -otexan -wx -ei

.before
    set include=$(%os2tk)\h;$(%include)

.extensions:
.extensions: .dll .obj .c

all : $(dllname).dll

.c.obj : .AUTODEPEND
    wcc386 $[* $(dllflags) $(cflags)

$(dllname).dll : $(object_files)
    wlink @$(dllname)
    implib $(dllname).lib $(dllname).dll

clean : .SYMBOLIC
        @if exist *.dll del *.dll
        @if exist *.obj del *.obj
        @if exist *.map del *.map
        @if exist *.res del *.res
        @if exist *.lst del *.lst
