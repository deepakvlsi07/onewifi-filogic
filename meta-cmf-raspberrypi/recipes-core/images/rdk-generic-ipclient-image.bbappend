require add-container-user-group.inc

fixes_tty1_removal() {
    if [ -f ${IMAGE_ROOTFS}/etc/systemd/system/getty.target.wants/getty@tty1.service ]; then
            rm -f "${IMAGE_ROOTFS}/etc/systemd/system/getty.target.wants/getty@tty1.service"
    fi
}
