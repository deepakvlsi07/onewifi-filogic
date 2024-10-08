SUMMARY = "Open source MQTT v3.1 implemention"
DESCRIPTION = "Mosquitto is an open source (BSD licensed) message broker that implements the MQ Telemetry Transport protocol version 3.1. MQTT provides a lightweight method of carrying out messaging using a publish/subscribe model. "
HOMEPAGE = "http://mosquitto.org/"
SECTION = "console/network"
LICENSE = "EPL-1.0 | EDL-1.0"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=62ddc846179e908dc0c8efec4a42ef20"

DEPENDS = "openssl util-linux c-ares"
DEPENDS += "${@bb.utils.contains_any('DISTRO_FEATURES', 'kirkstone', ' python3', ' python', d)}"

PR = "r0"

SRC_URI = "http://mosquitto.org/files/source/mosquitto-${PV}.tar.gz \
           file://build-1.6.12.patch \
           file://mosquitto.service \
"

export LIB_SUFFIX="${@d.getVar('baselib', True).replace('lib', '')}"

SRC_URI[md5sum] = "beb8d76d6e45f1e66d711006082a631f"
SRC_URI[sha256sum] = "548d73d19fb787dd0530334e398fd256ef3a581181678488a741a995c4f007fb"

do_compile() {
    oe_runmake PREFIX=/usr
}

do_install() {
    oe_runmake install DESTDIR=${D}
    install -d ${D}${libdir}
    install -m 0644 lib/libmosquitto.a ${D}${libdir}/

    install -d ${D}${systemd_unitdir}/system/
    install -m 0644 ${WORKDIR}/mosquitto.service ${D}${systemd_unitdir}/system/
}

PACKAGES += "libmosquitto1 libmosquittopp1 ${PN}-clients ${PN}-python"

FILES_${PN} = "${sbindir}/mosquitto \
               ${bindir}/mosquitto_passwd \
               ${sysconfdir}/mosquitto \
               ${systemd_unitdir}/system/mosquitto.service \
"

FILES_libmosquitto1 = "${libdir}/libmosquitto.so.1"

FILES_libmosquittopp1 = "${libdir}/libmosquittopp.so.1"

FILES_${PN}-clients = "${bindir}/mosquitto_pub \
                       ${bindir}/mosquitto_sub \
"

FILES_${PN}-staticdev += "${libdir}/libmosquitto.a"

FILES_${PN}-python = "/usr/lib/python2.7/site-packages"

inherit systemd

SYSTEMD_SERVICE_${PN} = "mosquitto.service"


