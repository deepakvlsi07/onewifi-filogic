require recipes-core/images/rdk-generic-hybrid-wpe-image.bb
require recipes-core/images/add-container-user-group.inc

inherit extrausers
inherit file-owners-and-permissions

require add-users-groups-file-owners-and-permissions.inc
require recipes-core/images/add-non-root-user-group.inc

IMAGE_INSTALL += " \
        packagegroup-lxc-secure-containers \
        strace \
	gstqamtunersrc \
	rdkapps \
"

IMAGE_INSTALL_remove = " \
    westeros-init \
    wpe-webkit-init \
"

ROOTFS_POSTPROCESS_COMMAND += "disable_systemd_services; "

disable_systemd_services() {
        if [ -d ${IMAGE_ROOTFS}${sysconfdir}/systemd/system/multi-user.target.wants/ ]; then
                rm -f ${IMAGE_ROOTFS}${sysconfdir}/systemd/system/multi-user.target.wants/wizardkit.service;

        fi
}

