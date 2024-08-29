# logrotate.timer and logrotate.service files are already provided by sysint, which is not right
# right way would be to write a iptable bbappend and add it via
# that, but for now lets remove logrotate to be provider of this
# file for rdk
#
do_install_append() {
	rm -rf ${D}${systemd_system_unitdir}
}

SYSTEMD_SERVICE_logrotate_remove = "logrotate.service logrotate.timer"

