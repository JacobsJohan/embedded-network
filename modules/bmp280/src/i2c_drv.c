#include <fcntl.h>
#include <linux/i2c-dev.h> /* defines I2C_SLAVE */
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int fd_i2c = -1;

/*********************************** Public functions ***********************************/

/* Initialize an i2c_bus on a given address.
 * @param i2c_bus: name of the i2c bus to open.
 * @param i2c_addr: open the i2c bus at the given address.
 * @return: the opened file descriptor, -1 in case of error.
 */
int i2c_init(const char *i2c_bus, int i2c_addr)
{
        int ret = 0;
        int fd = -1;

        if (i2c_bus == NULL) {
                printf("i2c_bus is NULL in i2c_init\n");
                return -1;
        }

        fd = open(i2c_bus, O_RDWR);
        if (fd < 0) {
                printf("Open i2c_bus failed\n");
                return -1;
        }

        ret = ioctl(fd, I2C_SLAVE, i2c_addr);
        if (ret < 0) {
                close(fd);
                printf("ioctl() failed\n");
                return -1;
        }

        /* Copy fd to the global file descriptor */
        fd_i2c = fd;

        return ret;
}


/* Close the i2c bus.
 * @param fd: file descriptor of the opened i2c bus.
 * @return: 0 on success, -1 on error.
 */
int i2c_deinit(void)
{
        int ret = close(fd_i2c);
        if (ret < 0) {
                perror("close");
        }
        return ret;
}


int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
        (void)i2c_addr;
        int ret = 0;
        uint8_t write_buffer[128];

        if (length >= 128) {
                printf("Error, too much data to write\n");
                return -1;
        }

        // write_buffer = reg_addr + data
        write_buffer[0] = reg_addr;
        for (int k = 0; k < length; k++) {
                write_buffer[k + 1] = *reg_data;
                reg_data++;
        }

        // Send data
        ret = write(fd_i2c, write_buffer, length + 1);
        if (ret < 0) {
                perror("write");
                return -1;
        }

        return 0;
}


int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length)
{
        (void)i2c_addr;
        int ret = 0;

        // Select slave register
        ret = write(fd_i2c, &reg_addr, 1);
        if (ret < 0) {
                perror("write");
                return -1;
        }

        // Receive data
        ret = read(fd_i2c, reg_data, length);
        if (ret < 0) {
                perror("read");
                return -1;
        }

        return 0;
}
