SUMMARY = "Firmware for mt76 USB wifi module"
LICENSE = "Proprietary & ISC & GPLv2"
COMMENT = "Proprietary license allows the use of the firmware with conditions as in the license file at LIC_FILES_CHKSUM"
LIC_FILES_CHKSUM = "file://firmware/LICENSE;md5=1bff2e28f0929e483370a43d4d8b6f8e"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

#dunfell 32b have kernel 5.4.y 
SRC_URI_dunfell = " \
          git://github.com/openwrt/mt76;branch=openwrt-19.07;protocol=https \
          file://mt76_makefile_change.patch \ 
          "

#dunfell 64b have kernel 5.10.y 
SRC_URI_remove_aarch64_dunfell = " \
          git://github.com/openwrt/mt76;branch=openwrt-19.07;protocol=https \
          file://mt76_makefile_change.patch \
          "
SRC_URI_append_aarch64_dunfell = " git://github.com/openwrt/mt76;branch=openwrt-22.03;protocol=https"
SRC_URI_append_aarch64_dunfell = " file://mt76_compilation_errors_fix.patch"
SRC_URI_append_aarch64_dunfell = " file://mt76_dunfell_64b_compilation_errors_fix.patch"

#kirkstone 32b,64b have kernel 5.15.y 
SRC_URI_append_kirkstone = " \
          git://github.com/openwrt/mt76;branch=openwrt-22.03;protocol=https \
          file://mt76_compilation_errors_fix.patch \
          "


SRC_URI += " file://add_support_for_extra_interface.patch"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"
DEPENDS = "virtual/kernel"

inherit module

EXTRA_OEMAKE  = "ARCH=${ARCH}"
EXTRA_OEMAKE += "KSRC=${STAGING_KERNEL_BUILDDIR}"

do_compile () {
    unset LDFLAGS
    oe_runmake
}

do_install () {
    install -d ${D}/lib/modules/${KERNEL_VERSION}
    install -m 0755 ${B}/mt76.ko ${D}/lib/modules/${KERNEL_VERSION}/
    install -m 0755 ${B}/mt76-usb.ko ${D}/lib/modules/${KERNEL_VERSION}/
    install -m 0755 ${B}/mt76x02-lib.ko ${D}/lib/modules/${KERNEL_VERSION}/
    install -m 0755 ${B}/mt76x02-usb.ko ${D}/lib/modules/${KERNEL_VERSION}/
    install -d ${D}/lib/modules/${KERNEL_VERSION}/mt76x2
    install -m 0755 ${B}/mt76x2/mt76x2u.ko ${D}/lib/modules/${KERNEL_VERSION}/mt76x2/mt76x2u.ko
    install -m 0755 ${B}/mt76x2/mt76x2-common.ko ${D}/lib/modules/${KERNEL_VERSION}/mt76x2/mt76x2-common.ko
    install -d ${D}/lib/modules/${KERNEL_VERSION}/mt76x0
    install -m 0755 ${B}/mt76x0/mt76x0u.ko ${D}/lib/modules/${KERNEL_VERSION}/mt76x0/mt76x0u.ko
    install -m 0755 ${B}/mt76x0/mt76x0-common.ko ${D}/lib/modules/${KERNEL_VERSION}/mt76x0/mt76x0-common.ko

    install -d ${D}${base_libdir}/firmware/
    install -m 755 ${S}/firmware/mt7662.bin  ${D}${base_libdir}/firmware/
    install -m 755 ${S}/firmware/mt7662_rom_patch.bin  ${D}${base_libdir}/firmware/
    install -d ${D}${base_libdir}/firmware/mediatek
    install -m 755 ${S}/firmware/mt7610e.bin  ${D}${base_libdir}/firmware/mediatek/
}

FILES_${PN} += "${base_libdir}/firmware/mt7662.bin"
FILES_${PN} += "${base_libdir}/firmware/mt7662.bin"
FILES_${PN} += "${base_libdir}/firmware/mt7662_rom_patch.bin"
FILES_${PN} += "${base_libdir}/firmware/mediatek/mt7610e.bin"
