SUMMARY = "A script that switches the motor according to the command"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
SRC_URI = "file://motor.py \
	 file://setup.py"
S = "${WORKDIR}"
inherit setuptools3

do_install_append () { 
    install -d ${D}${bindir} 
    install -m 0755 motor.py ${D}${bindir} 
}
