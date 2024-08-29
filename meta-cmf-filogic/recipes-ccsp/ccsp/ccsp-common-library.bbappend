require ccsp_common_filogic.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:${THISDIR}/files:"

DEPENDS_append_filogic = " breakpad"
CXXFLAGS_append_filogic = " \
                                -I${STAGING_INCDIR}/breakpad \
                                -std=c++11 \
                              "

SRC_URI_append = " \
    file://ccsp_vendor.h \
    file://wifiinitialized.service \
    file://checkfilogicwifisupport.service \
    file://wifiinitialized.path \
    file://filogicwifiinitialized.path \
    file://checkfilogicwifisupport.path \
    file://wifi-initialized.target \
    file://utopia.service \
"

SRC_URI_remove_dunfell = "file://0001-DBusLoop-SSL_state-TLS_ST_OK.patch"

SRC_URI += "file://0003-add-dependency-to-pandm.patch;apply=no"
SRC_URI += "file://0004-fix-out-of-array-access.patch;apply=no"

SRC_URI_append_dunfell = " file://0001-DBusLoop-SSL_state-TLS_ST_OK.patch;apply=no"


# we need to patch to code for Filogic
do_filogic_patches() {
    cd ${S}
    if [ ! -e patch_applied ]; then
        bbnote "Patching 0003-add-dependency-to-pandm.patch"
        patch -p1 < ${WORKDIR}/0003-add-dependency-to-pandm.patch
        patch -p1 < ${WORKDIR}/0004-fix-out-of-array-access.patch
        if [ "${@bb.utils.contains('DISTRO_CODENAME', 'dunfell', 'dunfell', '', d)}" = "dunfell" ] ; then
            bbnote "Patching 0001-DBusLoop-SSL_state-TLS_ST_OK.patch"
            patch -p1 < ${WORKDIR}/0001-DBusLoop-SSL_state-TLS_ST_OK.patch

        fi
       touch patch_applied
    fi
}
addtask filogic_patches after do_unpack before do_compile

do_install_append_class-target(){
    # Config files and scripts
    install -m 777 ${S}/scripts/cli_start_arm.sh ${D}/usr/ccsp/cli_start.sh
    install -m 777 ${S}/scripts/cosa_start_arm.sh ${D}/usr/ccsp/cosa_start.sh

    # we need unix socket path
    echo "unix:path=/var/run/dbus/system_bus_socket" > ${S}/config/ccsp_msg.cfg
    install -m 644 ${S}/config/ccsp_msg.cfg ${D}/usr/ccsp/ccsp_msg.cfg
    install -m 644 ${S}/config/ccsp_msg.cfg ${D}/usr/ccsp/cm/ccsp_msg.cfg
    install -m 644 ${S}/config/ccsp_msg.cfg ${D}/usr/ccsp/mta/ccsp_msg.cfg
    install -m 644 ${S}/config/ccsp_msg.cfg ${D}/usr/ccsp/pam/ccsp_msg.cfg
    install -m 644 ${S}/config/ccsp_msg.cfg ${D}/usr/ccsp/tr069pa/ccsp_msg.cfg

    install -m 777 ${S}/systemd_units/scripts/ccspSysConfigEarly.sh ${D}/usr/ccsp/ccspSysConfigEarly.sh
    install -m 777 ${S}/systemd_units/scripts/ccspSysConfigLate.sh ${D}/usr/ccsp/ccspSysConfigLate.sh
    install -m 777 ${S}/systemd_units/scripts/utopiaInitCheck.sh ${D}/usr/ccsp/utopiaInitCheck.sh
    install -m 777 ${S}/systemd_units/scripts/ccspPAMCPCheck.sh ${D}/usr/ccsp/ccspPAMCPCheck.sh

    install -m 777 ${S}/systemd_units/scripts/ProcessResetCheck.sh ${D}/usr/ccsp/ProcessResetCheck.sh
    sed -i -e "s/source \/rdklogger\/logfiles.sh;syncLogs_nvram2/#source \/rdklogger\/logfiles.sh;syncLogs_nvram2/g" ${D}/usr/ccsp/ProcessResetCheck.sh
    # install systemd services
    install -d ${D}${systemd_unitdir}/system
    install -D -m 0644 ${S}/systemd_units/ccspwifiagent.service ${D}${systemd_unitdir}/system/ccspwifiagent.service
    install -D -m 0644 ${S}/systemd_units/CcspCrSsp.service ${D}${systemd_unitdir}/system/CcspCrSsp.service
    install -D -m 0644 ${S}/systemd_units/CcspPandMSsp.service ${D}${systemd_unitdir}/system/CcspPandMSsp.service
    install -D -m 0644 ${S}/systemd_units/PsmSsp.service ${D}${systemd_unitdir}/system/PsmSsp.service
    install -D -m 0644 ${S}/systemd_units/rdkbLogMonitor.service ${D}${systemd_unitdir}/system/rdkbLogMonitor.service
    install -D -m 0644 ${S}/systemd_units/CcspTandDSsp.service ${D}${systemd_unitdir}/system/CcspTandDSsp.service
    install -D -m 0644 ${S}/systemd_units/CcspLMLite.service ${D}${systemd_unitdir}/system/CcspLMLite.service
    install -D -m 0644 ${S}/systemd_units/CcspTr069PaSsp.service ${D}${systemd_unitdir}/system/CcspTr069PaSsp.service
    install -D -m 0644 ${S}/systemd_units/snmpSubAgent.service ${D}${systemd_unitdir}/system/snmpSubAgent.service
    install -D -m 0644 ${S}/systemd_units/CcspEthAgent.service ${D}${systemd_unitdir}/system/CcspEthAgent.service
    install -D -m 0644 ${S}/systemd_units/CcspTelemetry.service ${D}${systemd_unitdir}/system/CcspTelemetry.service
    #rfc service file
    install -D -m 0644 ${S}/systemd_units/rfc.service ${D}${systemd_unitdir}/system/rfc.service

    install -D -m 0644 ${WORKDIR}/wifiinitialized.service ${D}${systemd_unitdir}/system/wifiinitialized.service
    install -D -m 0644 ${WORKDIR}/checkfilogicwifisupport.service ${D}${systemd_unitdir}/system/checkfilogicwifisupport.service

    install -D -m 0644 ${WORKDIR}/wifiinitialized.path ${D}${systemd_unitdir}/system/wifiinitialized.path
    install -D -m 0644 ${WORKDIR}/filogicwifiinitialized.path ${D}${systemd_unitdir}/system/filogicwifiinitialized.path
    install -D -m 0644 ${WORKDIR}/checkfilogicwifisupport.path ${D}${systemd_unitdir}/system/checkfilogicwifisupport.path

    install -D -m 0644 ${WORKDIR}/wifi-initialized.target ${D}${systemd_unitdir}/system/wifi-initialized.target

    install -D -m 0644 ${S}/systemd_units/ProcessResetDetect.service ${D}${systemd_unitdir}/system/ProcessResetDetect.service
    install -D -m 0644 ${S}/systemd_units/ProcessResetDetect.path ${D}${systemd_unitdir}/system/ProcessResetDetect.path

    # Install wrapper for breakpad (disabled to support External Source build)
    #install -d ${D}${includedir}/ccsp
    #install -m 644 ${S}/source/breakpad_wrapper/include/breakpad_wrapper.h ${D}${includedir}/ccsp

    # Install "vendor information"
    install -m 0644 ${WORKDIR}/ccsp_vendor.h ${D}${includedir}/ccsp

    sed -i -- 's/NotifyAccess=.*/#NotifyAccess=main/g' ${D}${systemd_unitdir}/system/CcspCrSsp.service
    sed -i -- 's/notify.*/forking/g' ${D}${systemd_unitdir}/system/CcspCrSsp.service
   
    #copy rfc.properties into nvram
    sed -i '/ExecStartPre/ a\ExecStartPre=-/bin/cp /etc/rfc.properties /nvram/' ${D}${systemd_unitdir}/system/rfc.service
    #reduce sleep time to 12 sconds
    sed -i 's/300/12/g' ${D}${systemd_unitdir}/system/rfc.service
   
    #change for Filogic
    sed -i 's/PIDFile/#&/' ${D}${systemd_unitdir}/system/CcspPandMSsp.service 

    #Telemetry support
     sed -i "/Type=oneshot/a EnvironmentFile=\/etc/\device.properties" ${D}${systemd_unitdir}/system/CcspTelemetry.service
     sed -i "/EnvironmentFile=\/etc\/device.properties/a EnvironmentFile=\/etc\/dcm.properties" ${D}${systemd_unitdir}/system/CcspTelemetry.service
     sed -i "/EnvironmentFile=\/etc\/dcm.properties/a ExecStartPre=\/bin\/sh -c '\/bin\/touch \/rdklogs\/logs\/dcmscript.log'" ${D}${systemd_unitdir}/system/CcspTelemetry.service
     sed -i "s/ExecStart=\/bin\/sh -c '\/lib\/rdk\/dcm.service \&'/ExecStart=\/bin\/sh -c '\/lib\/rdk\/StartDCM.sh \>\> \/rdklogs\/logs\/telemetry.log \&'/g" ${D}${systemd_unitdir}/system/CcspTelemetry.service
     sed -i "s/wan-initialized.target/multi-user.target/g" ${D}${systemd_unitdir}/system/CcspTelemetry.service

    #WanManager - RdkWanManager.service
     DISTRO_WAN_ENABLED="${@bb.utils.contains('DISTRO_FEATURES','rdkb_wan_manager','true','false',d)}"
     if [ $DISTRO_WAN_ENABLED = 'true' ]; then
     install -D -m 0644 ${S}/systemd_units/RdkWanManager.service ${D}${systemd_unitdir}/system/RdkWanManager.service
     sed -i "/WorkingDirectory/a ExecStartPre=/bin/sh /lib/rdk/run_rm_key.sh" ${D}${systemd_unitdir}/system/RdkWanManager.service
     sed -i "s/After=CcspCrSsp.service/After=CcspCrSsp.service utopia.service PsmSsp.service CcspEthAgent.service/g" ${D}${systemd_unitdir}/system/RdkWanManager.service
     sed -i "s/CcspPandMSsp.service/CcspCrSsp.service CcspPandMSsp.service/g" ${D}${systemd_unitdir}/system/CcspEthAgent.service
     install -D -m 0644 ${WORKDIR}/utopia.service ${D}${systemd_unitdir}/system/utopia.service
     install -D -m 0644 ${S}/systemd_units/RdkTelcoVoiceManager.service ${D}${systemd_unitdir}/system/RdkTelcoVoiceManager.service
     install -D -m 0644 ${S}/systemd_units/RdkVlanManager.service ${D}${systemd_unitdir}/system/RdkVlanManager.service
    fi

     DISTRO_FW_ENABLED="${@bb.utils.contains('DISTRO_FEATURES','fwupgrade_manager','true','false',d)}"
     if [ $DISTRO_FW_ENABLED = 'true' ]; then
     	install -D -m 0644 ${S}/systemd_units/RdkFwUpgradeManager.service ${D}${systemd_unitdir}/system/RdkFwUpgradeManager.service
     fi
    ##### erouter0 ip issue
    sed -i '/Factory/a \
IsErouterRunningStatus=\`ifconfig erouter0 | grep RUNNING | grep -v grep | wc -l\` \
if [ \"\$IsErouterRunningStatus\" == 0 ]; then \
ethtool -s erouter0 speed 1000 \
fi' ${D}/usr/ccsp/ccspPAMCPCheck.sh

     DISTRO_OneWiFi_ENABLED="${@bb.utils.contains('DISTRO_FEATURES','OneWifi','true','false',d)}"
     if [ $DISTRO_OneWiFi_ENABLED = 'true' ]; then
         install -D -m 0644 ${S}/systemd_units/onewifi.service ${D}${systemd_unitdir}/system/onewifi.service
         sed -i "s/Unit=ccspwifiagent.service/Unit=onewifi.service/g"  ${D}${systemd_unitdir}/system/filogicwifiinitialized.path
         sed -i "/OSW_DRV_TARGET_DISABLED=1/a ExecStartPre=\/bin\/sh \/usr\/ccsp\/wifi\/onewifi_pre_start.sh"  ${D}${systemd_unitdir}/system/onewifi.service
     fi

    if ${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', 'true', 'false', d)}; then
        install -D -m 0644 ${S}/systemd_units/webconfig.service ${D}${systemd_unitdir}/system/webconfig.service
    fi
}

do_install_append_dunfell_class-target () {
    #for yocto 3.1, Making psm to run after gwprovethwan
    sed -i '/CcspCrSsp.service/c After=CcspCrSsp.service gwprovethwan.service' ${D}${systemd_unitdir}/system/PsmSsp.service
}

SYSTEMD_SERVICE_${PN} += "CcspCrSsp.service"
SYSTEMD_SERVICE_${PN} += "CcspPandMSsp.service"
SYSTEMD_SERVICE_${PN} += "PsmSsp.service"
SYSTEMD_SERVICE_${PN} += "rdkbLogMonitor.service"
SYSTEMD_SERVICE_${PN} += "CcspTandDSsp.service"
SYSTEMD_SERVICE_${PN} += "CcspLMLite.service"
SYSTEMD_SERVICE_${PN} += "CcspTr069PaSsp.service"
SYSTEMD_SERVICE_${PN} += "snmpSubAgent.service"
SYSTEMD_SERVICE_${PN} += "CcspEthAgent.service"
SYSTEMD_SERVICE_${PN} += "wifiinitialized.service"
SYSTEMD_SERVICE_${PN} += "checkfilogicwifisupport.service"
SYSTEMD_SERVICE_${PN} += "wifiinitialized.path"
SYSTEMD_SERVICE_${PN} += "filogicwifiinitialized.path"
SYSTEMD_SERVICE_${PN} += "checkfilogicwifisupport.path"
SYSTEMD_SERVICE_${PN} += "wifi-initialized.target"
SYSTEMD_SERVICE_${PN} += "ProcessResetDetect.path"
SYSTEMD_SERVICE_${PN} += "ProcessResetDetect.service"
SYSTEMD_SERVICE_${PN} += "rfc.service"
SYSTEMD_SERVICE_${PN} += "CcspTelemetry.service"
SYSTEMD_SERVICE_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', 'RdkWanManager.service utopia.service RdkVlanManager.service ', '', d)}"
SYSTEMD_SERVICE_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', 'RdkFwUpgradeManager.service ', '', d)}"
SYSTEMD_SERVICE_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', 'onewifi.service ', 'ccspwifiagent.service', d)}"
SYSTEMD_SERVICE_${PN} += "${@bb.utils.contains('DISTRO_FEATURES', 'webconfig_bin', 'webconfig.service', '', d)}"

FILES_${PN}_append = " \
    /usr/ccsp/ccspSysConfigEarly.sh \
    /usr/ccsp/ccspSysConfigLate.sh \
    /usr/ccsp/utopiaInitCheck.sh \
    /usr/ccsp/ccspPAMCPCheck.sh \
    /usr/ccsp/ProcessResetCheck.sh \
    ${systemd_unitdir}/system/CcspCrSsp.service \
    ${systemd_unitdir}/system/CcspPandMSsp.service \
    ${systemd_unitdir}/system/PsmSsp.service \
    ${systemd_unitdir}/system/rdkbLogMonitor.service \
    ${systemd_unitdir}/system/CcspTandDSsp.service \
    ${systemd_unitdir}/system/CcspLMLite.service \
    ${systemd_unitdir}/system/CcspTr069PaSsp.service \
    ${systemd_unitdir}/system/snmpSubAgent.service \
    ${systemd_unitdir}/system/CcspEthAgent.service \
    ${systemd_unitdir}/system/wifiinitialized.service \
    ${systemd_unitdir}/system/checkfilogicwifisupport.service \
    ${systemd_unitdir}/system/wifiinitialized.path \
    ${systemd_unitdir}/system/filogicwifiinitialized.path \
    ${systemd_unitdir}/system/checkfilogicwifisupport.path \
    ${systemd_unitdir}/system/wifi-initialized.target \
    ${systemd_unitdir}/system/ProcessResetDetect.path \
    ${systemd_unitdir}/system/ProcessResetDetect.service \
    ${systemd_unitdir}/system/rfc.service \
    ${systemd_unitdir}/system/CcspTelemetry.service \
    /lib/systemd/system/ccspwifiagent.service \
"
FILES_${PN}_append = "${@bb.utils.contains('DISTRO_FEATURES', 'rdkb_wan_manager', ' ${systemd_unitdir}/system/RdkWanManager.service ${systemd_unitdir}/system/utopia.service ${systemd_unitdir}/system/RdkVlanManager.service ${systemd_unitdir}/system/RdkTelcoVoiceManager.service ', '', d)}"
FILES_${PN}_append = "${@bb.utils.contains('DISTRO_FEATURES', 'fwupgrade_manager', ' ${systemd_unitdir}/system/RdkFwUpgradeManager.service ', '', d)}"
FILES_${PN}_append = "${@bb.utils.contains('DISTRO_FEATURES', 'OneWifi', ' ${systemd_unitdir}/system/onewifi.service ', '  ${systemd_unitdir}/system/ccspwifiagent.service ', d)}"
