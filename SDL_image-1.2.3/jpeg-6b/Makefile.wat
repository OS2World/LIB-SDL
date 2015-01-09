#=============================================================================
#          This is a Watcom makefile to build SDLIMAGE.DLL for OS/2
#
#
#=============================================================================


object_files= jcapimin.obj jcapistd.obj jccoefct.obj jccolor.obj jcdctmgr.obj jchuff.obj &
        jcinit.obj jcmainct.obj jcmarker.obj jcmaster.obj jcomapi.obj jcparam.obj &
        jcphuff.obj jcprepct.obj jcsample.obj jctrans.obj jdapimin.obj jdapistd.obj &
        jdatadst.obj jdatasrc.obj jdcoefct.obj jdcolor.obj jddctmgr.obj jdhuff.obj &
        jdinput.obj jdmainct.obj jdmarker.obj jdmaster.obj jdmerge.obj jdphuff.obj &
        jdpostct.obj jdsample.obj jdtrans.obj jerror.obj jfdctflt.obj jfdctfst.obj &
        jfdctint.obj jidctflt.obj jidctfst.obj jidctint.obj jidctred.obj jquant1.obj &
        jquant2.obj jutils.obj jmemmgr.obj jmemnobs.obj

# Extra stuffs to pass to C compiler:
ExtraCFlags=

#
#==============================================================================
#
!include ..\Watcom.mif

.before
    set include=$(%os2tk)\h;$(%include);.\;

all : $(object_files)

clean : .SYMBOLIC
    @if exist *.dll del *.dll
    @if exist *.lib del *.lib
    @if exist *.obj del *.obj
    @if exist *.map del *.map
    @if exist *.res del *.res
    @if exist *.lst del *.lst
