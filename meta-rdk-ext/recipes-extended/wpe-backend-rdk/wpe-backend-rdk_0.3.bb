SUMMARY = "WPE WebKit RDK backend"
HOMEPAGE = "https://github.com/WebPlatformForEmbedded"
SECTION = "wpe"
LICENSE = "BSD-2-Clause & Apache-2.0"
LIC_FILES_CHKSUM = "file://COPYING;md5=ab5b52d145a58f5fcc0e2a531e7a2370"

DEPENDS += "libwpe glib-2.0"

PV = "0.3+git${SRCPV}"

# Revision date: Apr 28 2023
SRCREV = "0b0562680e251a3fbf2ae202c89b7c9acfc1d01a"
BASE_URI ?= "git://github.com/WebPlatformForEmbedded/WPEBackend-rdk.git;protocol=http;branch=master"
SRC_URI = "${BASE_URI}"

SRC_URI += "file://comcast-Naive-gamepad-support.patch"
SRC_URI += "file://0001-Fix-browser-crash-when-the-compositor-is-not-created.patch"
SRC_URI += "file://0001-Send-SIGHUP-if-compositor-is-terminated.patch"
SRC_URI += "file://comcast-manette-gamepad-support.patch"

S = "${WORKDIR}/git"

inherit cmake pkgconfig

WPE_BACKEND ?= "essos headless"

PACKAGECONFIG ?= "${WPE_BACKEND}"
PACKAGECONFIG_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'gamepad-using-libmanette', ' manettegamepad', ' gamepad', d)}"

PACKAGECONFIG[westeros] = "-DUSE_BACKEND_WESTEROS=ON -DUSE_KEY_INPUT_HANDLING_LINUX_INPUT=OFF,,wayland westeros libxkbcommon"
PACKAGECONFIG[essos] = "-DUSE_BACKEND_ESSOS=ON -DUSE_INPUT_LIBINPUT=OFF,-DUSE_BACKEND_ESSOS=OFF,essos libxkbcommon"
PACKAGECONFIG[gamepad] = "-DUSE_GENERIC_GAMEPAD=ON,-DUSE_GENERIC_GAMEPAD=OFF,"
PACKAGECONFIG[headless] = "-DUSE_BACKEND_HEADLESS=ON -DUSE_INPUT_LIBINPUT=OFF,-DUSE_BACKEND_HEADLESS=OFF,"
PACKAGECONFIG[manettegamepad] = "-DUSE_LIBMANETTE_GAMEPAD=ON, -DUSE_LIBMANETTE_GAMEPAD=OFF, libmanette"


EXTRA_OECMAKE += " \
    -DCMAKE_BUILD_TYPE=Release \
"

PROVIDES = "wpe-backend-rdk"
RPROVIDES_${PN} = "wpe-backend-rdk"

PACKAGES =+ "${PN}-platform-plugin"
FILES_${PN}-platform-plugin += "${libdir}/*.so ${bindir}/*"
INSANE_SKIP_${PN}-platform-plugin = "dev-so"

#We need the default package, even if empty for SDK
ALLOW_EMPTY_${PN}="1"
