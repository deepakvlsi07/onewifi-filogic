FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI += "file://ocsp_request_to_CA_Directly.patch \
            file://CVE-2020-8231_7.60.patch \
            file://CVE-2020-8285_7.60.patch \
            file://CVE-2020-8286_7.60.patch \
"

SRC_URI_append = " file://CVE-2021-22924_7.60.0_fix.patch \
                 "

CURLGNUTLS = "--without-gnutls --with-ssl"
DEPENDS += " openssl"

# Latest curl recipe 7.50.1 version comes with Yocto 2.2 is changed to use PACKAGECONFIG
PACKAGECONFIG_remove_class-target = "gnutls"
PACKAGECONFIG_append_class-target = " ssl"

# see https://lists.yoctoproject.org/pipermail/poky/2013-December/009435.html
# We should ideally drop ac_cv_sizeof_off_t from site files but until then
EXTRA_OECONF += "${@bb.utils.contains('DISTRO_FEATURES', 'largefile', 'ac_cv_sizeof_off_t=8', '', d)}"

PACKAGECONFIG_append = " ipv6 "
PACKAGECONFIG[ipv6] = "--enable-ipv6,--disable-ipv6,"
PACKAGECONFIG[brotli] = "--with-brotli,--without-brotli,brotli"
