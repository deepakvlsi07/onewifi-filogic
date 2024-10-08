SUMMARY = "Linux Bluetooth Stack Userland V5"
DESCRIPTION = "Linux Bluetooth stack V5 userland components.  These include a system configurations, daemons, tools and system libraries."
HOMEPAGE = "http://www.bluez.org"
SECTION = "libs"
LICENSE = "GPLv2+ & LGPLv2.1+"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e \
                    file://COPYING.LIB;md5=fb504b67c50331fc78734fed90fb0e09 \
                    file://src/main.c;beginline=1;endline=24;md5=9bc54b93cd7e17bf03f52513f39f926e"
DEPENDS = "udev dbus-glib glib-2.0 libcheck"
PROVIDES += "bluez-hcidump"
RPROVIDES_${PN} += "bluez-hcidump"

RCONFLICTS_${PN} = "bluez4"

PACKAGECONFIG ??= "obex-profiles \
    readline \
    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'systemd', '', d)} \
    a2dp-profiles \
    avrcp-profiles \
    network-profiles \
    hid-profiles \
    hog-profiles \
    tools \
    deprecated \
"
PACKAGECONFIG[obex-profiles] = "--enable-obex,--disable-obex,libical"
PACKAGECONFIG[readline] = "--enable-client,--disable-client,readline,"
PACKAGECONFIG[testing] = "--enable-testing,--disable-testing"
PACKAGECONFIG[midi] = "--enable-midi,--disable-midi,alsa-lib"
PACKAGECONFIG[systemd] = "--enable-systemd,--disable-systemd"
PACKAGECONFIG[cups] = "--enable-cups,--disable-cups,,cups"
PACKAGECONFIG[nfc] = "--enable-nfc,--disable-nfc"
PACKAGECONFIG[sap-profiles] = "--enable-sap,--disable-sap"
PACKAGECONFIG[a2dp-profiles] = "--enable-a2dp,--disable-a2dp"
PACKAGECONFIG[avrcp-profiles] = "--enable-avrcp,--disable-avrcp"
PACKAGECONFIG[network-profiles] = "--enable-network,--disable-network"
PACKAGECONFIG[hid-profiles] = "--enable-hid,--disable-hid"
PACKAGECONFIG[hog-profiles] = "--enable-hog,--disable-hog"
PACKAGECONFIG[health-profiles] = "--enable-health,--disable-health"
PACKAGECONFIG[sixaxis] = "--enable-sixaxis,--disable-sixaxis"
PACKAGECONFIG[tools] = "--enable-tools,--disable-tools"
PACKAGECONFIG[threads] = "--enable-threads,--disable-threads"
PACKAGECONFIG[deprecated] = "--enable-deprecated,--disable-deprecated"

SRC_URI = "\
    ${KERNELORG_MIRROR}/linux/bluetooth/bluez-${PV}.tar.xz \
    file://out-of-tree.patch \
    file://init \
    file://run-ptest \
    ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '', 'file://0001-Allow-using-obexd-without-systemd-in-the-user-sessio.patch', d)} \
    file://0001-tests-add-a-target-for-building-tests-without-runnin.patch \
"
#
# Disabled Patches
# file://0001-hciattach-bcm43xx-fix-the-delay-timer-for-firmware-d.patch \
# file://cve-2017-1000250.patch \
#

S = "${WORKDIR}/bluez-${PV}"

CVE_PRODUCT = "bluez"

inherit autotools pkgconfig systemd update-rc.d distro_features_check ptest

EXTRA_OECONF = "\
  --enable-test \
  --enable-datafiles \
  --enable-library \
"

# bluez5 builds a large number of useful utilities but does not
# install them.  Specify which ones we want put into ${PN}-noinst-tools.
NOINST_TOOLS_READLINE ??= ""
NOINST_TOOLS_TESTING ??= ""
NOINST_TOOLS_BT ??= ""
NOINST_TOOLS = " \
    ${@bb.utils.contains('PACKAGECONFIG', 'readline', '${NOINST_TOOLS_READLINE}', '', d)} \
    ${@bb.utils.contains('PACKAGECONFIG', 'testing', '${NOINST_TOOLS_TESTING}', '', d)} \
    ${@bb.utils.contains('PACKAGECONFIG', 'tools', '${NOINST_TOOLS_BT}', '', d)} \
"

do_install_append() {
	install -d ${D}${INIT_D_DIR}
	install -m 0755 ${WORKDIR}/init ${D}${INIT_D_DIR}/bluetooth

	install -d ${D}${sysconfdir}/bluetooth/
	if [ -f ${S}/profiles/network/network.conf ]; then
		install -m 0644 ${S}/profiles/network/network.conf ${D}/${sysconfdir}/bluetooth/
	fi
	if [ -f ${S}/profiles/input/input.conf ]; then
		install -m 0644 ${S}/profiles/input/input.conf ${D}/${sysconfdir}/bluetooth/
	fi

	if [ -f ${D}/${sysconfdir}/init.d/bluetooth ]; then
		sed -i -e 's#@LIBEXECDIR@#${libexecdir}#g' ${D}/${sysconfdir}/init.d/bluetooth
	fi

	# Install desired tools that upstream leaves in build area
	for f in ${NOINST_TOOLS} ; do
		install -m 755 ${B}/$f ${D}/${bindir}
	done

	# Patch python tools to use Python 3; they should be source compatible, but
	# still refer to Python 2 in the shebang
	sed -i -e '1s,#!.*python.*,#!${bindir}/python3,' ${D}${libdir}/bluez/test/*
}

PACKAGES =+ "${PN}-testtools ${PN}-obex ${PN}-noinst-tools"

FILES_${PN} += " \
    ${libdir}/bluetooth/plugins/*.so \
    ${systemd_unitdir}/ ${datadir}/dbus-1 \
    ${libdir}/cups \
"
FILES_${PN}-dev += " \
    ${libdir}/bluetooth/plugins/*.la \
"

FILES_${PN}-obex = "${libexecdir}/bluetooth/obexd \
                    ${exec_prefix}/lib/systemd/user/obex.service \
                    ${datadir}/dbus-1/services/org.bluez.obex.service \
                   "
SYSTEMD_SERVICE_${PN}-obex = "obex.service"

FILES_${PN}-testtools = "${libdir}/bluez/test/*"

def get_noinst_tools_paths (d, bb, tools):
    s = list()
    bindir = d.getVar("bindir", True)
    for bdp in tools.split():
        f = os.path.basename(bdp)
        s.append("%s/%s" % (bindir, f))
    return "\n".join(s)

FILES_${PN}-noinst-tools = "${@get_noinst_tools_paths(d, bb, d.getVar('NOINST_TOOLS', True))}"

RDEPENDS_${PN}-testtools += "python3 python3-dbus python3-pygobject python3-core"

SYSTEMD_SERVICE_${PN} = "${@bb.utils.contains('PACKAGECONFIG', 'systemd', 'bluetooth.service', '', d)}"
INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME_${PN} = "bluetooth"

EXCLUDE_FROM_WORLD = "1"

do_compile_ptest() {
	oe_runmake buildtests
}

do_install_ptest() {
	cp -r ${B}/unit/ ${D}${PTEST_PATH}
	rm -f ${D}${PTEST_PATH}/unit/*.o
}
