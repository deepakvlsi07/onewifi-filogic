PACKAGECONFIG_append = " ${@bb.utils.filter('DISTRO_FEATURES', 'alsa x11', d)}"

#removing the patch for 64bit builds, where -mfloat-abi=hard flag was introduced which is not available on 64bit gcc.
SRC_URI_remove_aarch64 = "file://0001-gst-plugins-base-stubs-soft.h-not-existing-compilati.patch"
