SRC_LIST = bmp280.c i2c_drv.c server.c
SRC_DIR  = src/
SRC      = $(addprefix $(SRC_DIR), $(SRC_LIST))
TARGET = get_temp
CC = arm-linux-gnueabihf-gcc
CFLAGS += -Wall -Werror -Wextra
LDFLAGS += -Iinc

SRC += lib/libzmq.so.5.2.3

.PHONY: all
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: scp
scp: $(TARGET)
	scp $(TARGET) pi@raspberrypi.local:/home/pi
