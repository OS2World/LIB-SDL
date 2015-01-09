#=============================================================================
#          This is a Watcom makefile to build SDLIMAGE.DLL for OS/2
#
#
#=============================================================================


object_files=fax3sm_winnt.obj &
tif_aux.obj &
tif_close.obj &
tif_codec.obj &
tif_color.obj &
tif_compress.obj &
tif_dir.obj &
tif_dirinfo.obj &
tif_dirread.obj &
tif_dirwrite.obj &
tif_dumpmode.obj &
tif_error.obj &
tif_extension.obj &
tif_fax3.obj &
tif_flush.obj &
tif_getimage.obj &
tif_jpeg.obj &
tif_luv.obj &
tif_lzw.obj &
tif_msdos.obj &
tif_next.obj &
tif_ojpeg.obj &
tif_open.obj &
tif_packbits.obj &
tif_pixarlog.obj &
tif_predict.obj &
tif_print.obj &
tif_read.obj &
tif_strip.obj &
tif_swab.obj &
tif_thunder.obj &
tif_tile.obj &
tif_version.obj &
tif_warning.obj &
tif_write.obj &
tif_zip.obj


# Extra stuffs to pass to C compiler:
ExtraCFlags=

#
#==============================================================================
#
!include ..\..\Watcom.mif

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
