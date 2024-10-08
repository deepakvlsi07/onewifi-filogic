SUMMARY = "System load testing utility"
DESCRIPTION = "Deliberately simple workload generator for POSIX systems. It \
imposes a configurable amount of CPU, memory, I/O, and disk stress on the system."
HOMEPAGE = "https://kernel.ubuntu.com/~cking/stress-ng/"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

SRC_URI = "https://kernel.ubuntu.com/~cking/tarballs/${BPN}/${BP}.tar.xz \
           file://0001-Do-not-preserve-ownership-when-installing-example-jo.patch \
           file://no_daddr_t.patch \
           "
SRC_URI += "file://run_sng.py \
            file://execstress.sh \
            "

SRC_URI[sha256sum] = "ee44b71aba20e9c7d10ec4768efa2245d12579fa17e08b9314c17f06f785ae39"

DEPENDS = "coreutils-native"

PROVIDES = "stress"
RPROVIDES_${PN} = "stress"
RREPLACES_${PN} = "stress"
RCONFLICTS_${PN} = "stress"

inherit bash-completion

do_install() {
    oe_runmake DESTDIR=${D} install
    ln -s stress-ng ${D}${bindir}/stress
    install -m 0455 ${WORKDIR}/run_sng.py ${D}${bindir}/run_sng.py
    install -m 0455 ${WORKDIR}/execstress.sh ${D}${bindir}/execstress.sh
}
FILES_${PN} += "${bindir}/run_sng.py"
FILES_${PN} += "${bindir}/execstress.sh"

RDEPENDS_${PN} += "python3-core"

