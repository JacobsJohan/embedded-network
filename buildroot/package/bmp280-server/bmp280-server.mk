################################################################################
#
# bmp280-server
#
################################################################################
BMP280_SERVER_VERSION = 0.1
BMP280_SERVER_SITE_METHOD = local
BMP280_SERVER_SITE = $(BR2_EXTERNAL_EMBEDDED_NETWORK_PATH)/board/embedded-network/raspberrypi4/bmp280
BMP280_SERVER_INSTALL_STAGING = YES
BMP280_SERVER_AUTORECONF = YES

$(eval $(autotools-package))
