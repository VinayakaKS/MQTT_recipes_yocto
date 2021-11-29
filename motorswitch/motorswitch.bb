DESCRIPTION = "MQTT subscriber which switches a DC motor"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://motorswitch.c \
	  file://patch1.patch"
S = "${WORKDIR}"
DEPENDS += "mosquitto" 

do_compile() {
	${CC} motorswitch.c ${LDFLAGS} -o motorswitch -lmosquitto
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 motorswitch ${D}${bindir}
}
