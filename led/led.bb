DESCRIPTION = "A code to turn ON led"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
SRC_URI = "file://setup.py \
	file://LED.py \
	file://patch1.patch"
S = "${WORKDIR}"
inherit setuptools3
 
do_install_append () { 
    install -d ${D}${bindir} 
    install -m 0755 LED.py ${D}${bindir} 
} 


