CPPFLAGS_append = " -DFETCH_PRODUCTCLASS_FROM_MFRLIB"

do_install_append() {
		sed -i 's#exit 2 \# Retry handled by parodus.service (Restart=always)##g' ${D}${base_libdir}/rdk/startParodus.sh
}
