SRC_LIST = main.c i2c_drv.c
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))
TARGET = main
CC = arm-linux-gnueabihf-gcc
#CFLAGS += -m32
LDFLAGS += -Iinc

.PHONY: all
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: scp
scp: $(TARGET)
	scp $(TARGET) pi@raspberrypi.local:/home/pi
