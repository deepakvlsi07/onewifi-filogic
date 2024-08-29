CORE_URI_remove = "${@bb.utils.contains('DISTRO_FEATURES', 'extender', 'file://0002-Use-osync_hal-in-inet_gretap.patch', '', d)}"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

OPENSYNC_VENDOR_URI = "git://git@github.com/rdkcentral/opensync-vendor-rdk-rpi.git;protocol=${CMF_GIT_PROTOCOL};branch=main;name=vendor;destsuffix=git/vendor/rpi"
VENDOR_URI = "git://git@github.com/rdkcentral/opensync-vendor-rdk-rpi.git;protocol=${CMF_GIT_PROTOCOL};branch=main;name=vendor;destsuffix=git/vendor/rpi"
VENDOR_URI += "file://config-rdk-multi-psk-disable.patch;patchdir=${WORKDIR}/git/"
VENDOR_URI += "file://service.patch;patchdir=${WORKDIR}/git/"
VENDOR_URI += "file://opensync.service"

DEPENDS_append = " rdk-logger"
DEPENDS_append_extender = " hal-wifi-cfg80211"

#FILES_${PN} = "/usr/include/src"
#FILES_${PN} = "/usr/include/src/memutil.c.h"
do_package_qa[noexec] = "1"
INSANE_SKIP_${PN} = "file-rdeps"

RDK_CFLAGS += " -D_PLATFORM_RASPBERRYPI_"

do_compile_prepend_broadband(){
	cd ${WORKDIR}/git/vendor/rpi/
	rm -rf src
	cd -
}
