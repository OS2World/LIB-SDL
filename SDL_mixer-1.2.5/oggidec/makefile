#-----------------------------------------------------------------------------
# To build this on your system, first set the following to your toolkit path!
#-----------------------------------------------------------------------------
object_files=bitwise.obj block.obj codebook.obj floor0.obj floor1.obj framing.obj info.obj mapping0.obj mdct.obj registry.obj res012.obj sharedbook.obj synthesis.obj vorbisfile.obj window.obj


#-----------------------------------------------------------------------------
# The next part is somewhat general, for creation of DLL files.
#-----------------------------------------------------------------------------

emx_compatibility_flags = -aa -d__EMX__
dllflags = -bd
cflags = $(emx_compatibility_flags) -bm -bt=OS2 -i=$(os2toolkit_path)\h

.before
    set include=$(%watcom)\h\os2;$(%include)

.extensions:
.extensions: .dll .obj .c

all : $(dllname).dll

$(dllname).dll: $(object_files)

.c.obj : .AUTODEPEND
    wcc386 $[* $(dllflags) $(cflags)

$(dllname).dll : .AUTODEPEND
    wlink @$(dllname)
!ifdef create_packed_dll
    lxlite $(dllname).dll
!endif
clean : .SYMBOLIC
        @if exist *.dll del *.dll
        @if exist *.obj del *.obj
        @if exist *.map del *.map
        @if exist *.lst del *.lst
