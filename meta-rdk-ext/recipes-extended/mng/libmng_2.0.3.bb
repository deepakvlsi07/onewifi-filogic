DESCRIPTION = "Development files for the Multiple-image Network Graphics library"
HOMEPAGE = "http://www.libmng.com/"
LICENSE = "libmng"
LIC_FILES_CHKSUM = "file://LICENSE;md5=32becdb8930f90eab219a8021130ec09"
SECTION = "devel"
DEPENDS = "zlib lcms"

SRC_URI = "${SOURCEFORGE_MIRROR}/${BPN}/${BP}.tar.gz"

SRC_URI[md5sum] = "7e9a12ba2a99dff7e736902ea07383d4"
SRC_URI[sha256sum] = "cf112a1fb02f5b1c0fce5cab11ea8243852c139e669c44014125874b14b7dfaa"

inherit autotools-brokensep pkgconfig
# FIXME: the build tries to run make clean and does not find config.status
# causing a build failure.
CLEANBROKEN = "1"

PACKAGECONFIG ??= "jpeg"

PACKAGECONFIG[jpeg] = "--with-jpeg,--without-jpeg,libjpeg-turbo"
PACKAGECONFIG[lcms] = "---with-lcms2,--without-lcms2,lcms"

