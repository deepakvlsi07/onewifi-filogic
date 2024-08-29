FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://mtk-filogic-hal.patch;apply=no \
"


do_filogic_patches() {
        cd ${WORKDIR}/git
        if [ ! -e patch_applied ]; then
            patch -p1 < ${WORKDIR}/mtk-filogic-hal.patch
            #patch -p1 < ${WORKDIR}/0002-fix-5G-and-6G-connect-fail.patch
            touch patch_applied
        fi
}
addtask filogic_patches after do_unpack before do_compile
#addtask  do_unpack before do_compile

CFLAGS_append = " -DMTK_FILOGIC -DCONFIG_MBO"
CFLAGS_append_kirkstone = " -fcommon"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' ONE_WIFIBUILD=true ', '', d)}"
EXTRA_OECONF_append = " ${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' MTK_FILOGIC=true ', '', d)}"

