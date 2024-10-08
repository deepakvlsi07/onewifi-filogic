
EXTRA_OECONF_append = " --with-omx-target=rpi --with-omx-header-path=${STAGING_DIR_TARGET}/usr/include/IL "

GSTREAMER_1_0_OMX_TARGET = "rpi"

GSTREAMER_1_0_OMX_CORE_NAME = "${libdir}/libopenmaxil.so"

EXTRA_OECONF_append  = " CFLAGS="$CFLAGS -I${STAGING_DIR_TARGET}/usr/include/IL -I${STAGING_DIR_TARGET}/usr/include/interface/vcos/pthreads -I${STAGING_DIR_TARGET}/usr/include/interface/vmcs_host/linux""

#examples only build with GL but not GLES, so disable it for RPI
EXTRA_OECONF_append = " --disable-examples"
