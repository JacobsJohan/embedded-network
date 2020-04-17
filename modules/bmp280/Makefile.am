AM_CFLAGS = -Wall -Wextra -Werror -Iinc

noinst_LIBRARIES = libbmp280.a libi2c.a

libi2c_a_SOURCES = \
	src/i2c_drv.c \
	inc/i2c_drv.h
libi2c_a_CFLAGS = $(AM_CFLAGS)


libbmp280_a_SOURCES = \
	src/bmp280.c \
	inc/bmp280.h \
	inc/bmp280_defs.h
libbmp280_a_CFLAGS = $(AM_CFLAGS)

bin_PROGRAMS = bmp280-server

bmp280_server_SOURCES = src/server.c
bmp280_server_CFLAGS = $(AM_CFLAGS)
bmp280_server_LDADD = libi2c.a libbmp280.a -lzmq
