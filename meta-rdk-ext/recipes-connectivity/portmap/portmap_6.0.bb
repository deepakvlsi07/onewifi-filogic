require portmap.inc

DEPENDS_append_libc-musl = " libtirpc "

PR = "r9"

SRC_URI = "https://fossies.org/linux/misc/old/portmap-6.0.tgz \
           file://destdir-no-strip.patch \
           file://tcpd-config.patch \
           file://portmap.init \
           file://portmap.service"

SRC_URI_append = " file://0001-member-name-update-to-sin6_port-in-sockaddr_in6.patch"
SRC_URI_remove_morty = " file://0001-member-name-update-to-sin6_port-in-sockaddr_in6.patch"

SRC_URI[md5sum] = "ac108ab68bf0f34477f8317791aaf1ff"
SRC_URI[sha256sum] = "02c820d39f3e6e729d1bea3287a2d8a6c684f1006fb9612f97dcad4a281d41de"

S = "${WORKDIR}/${BPN}_${PV}/"

PACKAGECONFIG ??= "tcp-wrappers"
PACKAGECONFIG[tcp-wrappers] = ",,tcp-wrappers"

CPPFLAGS += "-DFACILITY=LOG_DAEMON -DENABLE_DNS -DHOSTS_ACCESS"
CFLAGS += "-Wall -Wstrict-prototypes -fPIC"
EXTRA_OEMAKE += "'NO_TCP_WRAPPER=${@bb.utils.contains('PACKAGECONFIG', 'tcp-wrappers', '', '1', d)}'"
CFLAGS_append_libc-musl = " -I${STAGING_INCDIR}/tirpc "
LDFLAGS_append_libc-musl = " -ltirpc "

DEPENDS_append = " libtirpc"
CFLAGS_append = " -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/tirpc"
LDFLAGS_prepend = " -ltirpc "

DEPENDS_remove_morty = " libtirpc"
CFLAGS_remove_morty = " -I${PKG_CONFIG_SYSROOT_DIR}/usr/include/tirpc"
LDFLAGS_remove_morty = " -ltirpc "

do_install() {
    install -d ${D}${mandir}/man8/ ${D}${base_sbindir} ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/portmap.init ${D}${sysconfdir}/init.d/portmap
    oe_runmake install DESTDIR=${D}

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/portmap.service ${D}${systemd_unitdir}/system
    sed -i -e 's,@BASE_SBINDIR@,${base_sbindir},g' ${D}${systemd_unitdir}/system/portmap.service
}
