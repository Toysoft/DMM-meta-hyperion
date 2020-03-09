SUMMARY = "Hyperion Ambient lighting controller for dreamboxes"
LICENSE = "CLOSED"
GITHUB_PROJECT = "enigma2-plugin-hyperioncontrol"
RDEPENDS_${PN} = " \
    enigma2 \
    hyperion \
    kernel-module-usbserial \
    kernel-module-ch341 \
    kernel-module-ftdi-sio \
"

SRCREV = "${@opendreambox_srcrev('0224d5ca9f12d76da309b300b0cd04e1874cf1bf', d)}"

inherit autotools pkgconfig opendreambox-github

PACKAGES += "${PN}-meta"

FILES_${PN} += "${libdir}/enigma2"
FILES_${PN}-meta = "${datadir}/meta"
