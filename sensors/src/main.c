#include <stdint.h>
#include <stdio.h>

#include "i2c_drv.h"

#define BMP280_ADDR     (0x77)
#define TEMP_REG_MSB    (0xFA)

static const char i2c_bus[]  = "/dev/i2c-1";

int main(void)
{
        int ret;
        int fd_i2c = -1;
        uint8_t buffer[2] = { 0 };

        fd_i2c = i2c_init(i2c_bus, BMP280_ADDR);
        if (fd_i2c < 0) {
                printf("i2c_init failed\n");
                return -1;
        }

        ret = i2c_receive(TEMP_REG_MSB, fd_i2c, buffer, 2);
        if (ret < 0) {
                printf("i2c_receive failed\n");
                return -1;
        }

        printf("Raw i2c data = 0x%x, 0x%x\n", buffer[0], buffer[1]);

        ret = i2c_deinit(fd_i2c);
        if (ret < 0) {
                printf("i2c_deinit failed\n");
                return -1;
        }

        return 0;
}
