SUMMARY = "Dobby Container Manager"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c466d4ab8a68655eb1edf0bf8c1a8fb8"

include dobby.inc

SRC_URI_append_kirkstone = " file://Fix_compile_gcc11.patch  \
                             file://Add_config_header_kirkstone.patch \
                           "

DEPENDS = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', ' systemd ', '', d)} libnl dbus jsoncpp boost yajl python3 breakpad breakpad-wrapper "
RDEPENDS_${PN} = "crun (>= 0.14.1) ${@bb.utils.contains('DISTRO_FEATURES', 'dac', '', ' dobby-thunderplugin', d)} "

python do_patch_new () {
    bb.build.exec_func('patch_do_patch', d)
}

addtask do_patch_new after do_configure before do_compile

S = "${WORKDIR}/git"

inherit pkgconfig cmake systemd
#dobby logs storage file is decided using device.properties. syslog-ng-config-gen framework decide the log file.

#config.h file generation for kirkstone builds
DEPENDS_append_kirkstone = " autoconf-native automake-native "
CFLAGS_append_kirkstone = " --sysroot=${RECIPE_SYSROOT}"

# Always build debug version for now
EXTRA_OECMAKE =  " -DCMAKE_BUILD_TYPE=Debug -DBUILD_REFERENCE=${SRCREV}"

# Enable plugins
# Logging, networking, ipc, storage, minidump, oomcrash enabled by default for all builds
PACKAGECONFIG ?= "logging networking ipc storage minidump oomcrash"

# Options for plugins
# -------------------------------------
# RDK Plugins
PACKAGECONFIG[logging]      = "-DPLUGIN_LOGGING=ON,-DPLUGIN_LOGGING=OFF,"
PACKAGECONFIG[networking]   = "-DPLUGIN_NETWORKING=ON,-DPLUGIN_NETWORKING=OFF,"
PACKAGECONFIG[ipc]          = "-DPLUGIN_IPC=ON,-DPLUGIN_IPC=OFF,"
PACKAGECONFIG[storage]      = "-DPLUGIN_STORAGE=ON,-DPLUGIN_STORAGE=OFF,"
PACKAGECONFIG[minidump]     = "-DPLUGIN_MINIDUMP=ON,-DPLUGIN_MINIDUMP=OFF,"
PACKAGECONFIG[oomcrash]     = "-DPLUGIN_OOMCRASH=ON,-DPLUGIN_OOMCRASH=OFF,"
PACKAGECONFIG[testplugin]   = "-DPLUGIN_TESTPLUGIN=ON,-DPLUGIN_TESTPLUGIN=OFF,"
PACKAGECONFIG[gpu]          = "-DPLUGIN_GPU=ON,-DPLUGIN_GPU=OFF,"
PACKAGECONFIG[localtime]    = "-DPLUGIN_LOCALTIME=ON,-DPLUGIN_LOCALTIME=OFF,"
PACKAGECONFIG[rtscheduling] = "-DPLUGIN_RTSCHEDULING=ON,-DPLUGIN_RTSCHEDULING=OFF,"
PACKAGECONFIG[httpproxy]    = "-DPLUGIN_HTTPPROXY=ON,-DPLUGIN_HTTPPROXY=OFF,"
PACKAGECONFIG[appservices]  = "-DPLUGIN_APPSERVICES=ON,-DPLUGIN_APPSERVICES=OFF,"
PACKAGECONFIG[thunder]      = "-DPLUGIN_THUNDER=ON,-DPLUGIN_THUNDER=OFF,"
PACKAGECONFIG[ionmemory]    = "-DPLUGIN_IONMEMORY=ON,-DPLUGIN_IONMEMORY=OFF,"
PACKAGECONFIG[devicemapper] = "-DPLUGIN_DEVICEMAPPER=ON,-DPLUGIN_DEVICEMAPPER=OFF,"
PACKAGECONFIG[gamepad]      = "-DPLUGIN_GAMEPAD=ON,-DPLUGIN_GAMEPAD=OFF,"

# Legacy components (Dobby specs + legacy Sky plugins)
PACKAGECONFIG[legacycomponents] = "-DLEGACY_COMPONENTS=ON,-DLEGACY_COMPONENTS=OFF,ctemplate,"

# -------------------------------------

# Enable Hibernate Memcr implementation
EXTRA_OECMAKE += "${@bb.utils.contains('DISTRO_FEATURES', 'RDKTV_APP_HIBERNATE', ' -DDOBBY_HIBERNATE_MEMCR_IMPL=ON','',d)}"

# Add the systemd service
SYSTEMD_SERVICE_${PN} = "dobby.service"

# Skip harmless QA issue caused by installing but not shipping buildtime cmake files
INSANE_SKIP_${PN} = "installed-vs-shipped"

# Ensure that the unversioned symlinks of libraries are kept (and don't generate a QA error)
INSANE_SKIP_${PN} += "dev-so"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""

FILES_${PN} += "${systemd_system_unitdir}/dobby.service"
FILES_${PN} += "${sysconfdir}/systemd/system/multi-user.target.wants/dobby.service"
FILES_${PN} += "${sysconfdir}/dobby.json"
FILES_${PN} += "${bindir}/DobbyTool"
FILES_${PN} += "${sbindir}/DobbyDaemon"
FILES_${PN} += "${libexecdir}/DobbyInit"
FILES_${PN} += "${libdir}/plugins/dobby/*.so*"
FILES_${PN} += "${libdir}/libethanlog.so*"
FILES_${PN} += "${libdir}/libocispec.so*"
