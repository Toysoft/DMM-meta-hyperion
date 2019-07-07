SUMMARY = "Hyperion is an opensource 'AmbiLight' implementation controlled using the RaspBerry Pi"
DESCRIPTION = "Hyperion is an opensource 'AmbiLight' implementation"
HOMEPAGE = "https://github.com/hyperion-project/hyperion"

SECTION = "console/tools"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
PROVIDES = "hyperion"

inherit cmake_qt5 systemd git-project

FILESEXTRAPATHS_append := "${THISDIR}/files"

SRC_URI = " \
    gitsm://github.com/hyperion-project/hyperion.git;protocol=https \
    file://0001-fix-system-protobuf.patch \
    file://0002-adjust-aml-grabber-to-work-with-dreambox-drivers.patch \
    file://init \
"

S = "${WORKDIR}/git"

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "hyperion.service"

PACKAGECONFIG[amlogic] = "-DENABLE_AMLOGIC=ON,-DENABLE_AMLOGIC=OFF"
PACKAGECONFIG[dispmanx] = "-DENABLE_DISPMANX=ON,-DENABLE_DISPMANX=OFF"
PACKAGECONFIG[fb] = "-DENABLE_FB=ON,-DENABLE_FB=OFF"
PACKAGECONFIG[spi] = "-DENABLE_SPIDEV=ON,-DENABLE_SPIDEV=OFF"
PACKAGECONFIG[tinkerforge] = "-DENABLE_TINKERFORGE=ON,-DENABLE_TINKERFORGE=OFF"
PACKAGECONFIG[v4l2] = "-DENABLE_V4L2=ON,-DENABLE_V4L2=OFF,protobuf protobuf-native,"
PACKAGECONFIG[x11] = "-DENABLE_X11=ON,-DENABLE_X11=OFF"
PACKAGECONFIG[ws2812b] = "-DENABLE_WS2812BPWM=ON,-DENABLE_WS2812BPWM=OFF"
PACKAGECONFIG[ws281x] = "-DENABLE_WS281XPWM=ON,-DENABLE_WS281XPWM=OFF"

PACKAGECONFIG ?= " \
    amlogic \
    "

EXTRA_OECMAKE += " \
    -DENABLE_QT5=ON \
    -DENABLE_OSX=OFF \
    -DENABLE_TESTS=OFF \
    -DUSE_SYSTEM_PROTO_LIBS=ON \
    "

DEPENDS = " \
    protobuf \
    protobuf-native \
    libusb \
    python \
    qtbase \
"

RDEPENDS_${PN} = " \
    qtbase \
    bash \
    procps \
    python \
    python-image \
    python-math \
    python-io \
    "

HYPERION_CONFIG_FILE ??= "${S}/config/hyperion.config.json.example"

FILES_${PN} += " \
    ${systemd_unitdir}/system/hyperion.service \
"

do_install_append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/init/systemd/hyperion.service ${D}${systemd_unitdir}/system/

    install -d ${D}${sysconfdir}
    install -d ${D}${sysconfdir}/hyperion
    install ${HYPERION_CONFIG_FILE} ${D}${sysconfdir}/hyperion/hyperion.config.json
}
