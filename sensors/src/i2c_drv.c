#include <fcntl.h>
#include <linux/i2c-dev.h> /* defines I2C_SLAVE */
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


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

        return fd;
}


/* Close the i2c bus.
 * @param fd: file descriptor of the opened i2c bus.
 * @return: 0 on success, -1 on error.
 */
int i2c_deinit(int fd)
{
        int ret = close(fd);
        if (ret < 0) {
                perror("close");
        }
        return ret;
}


int i2c_transmit(uint8_t regaddr, int fd, uint8_t *data, int len)
{
        int ret = 0;

        // write to slave register
        ret = write(fd, &regaddr, 1);
        if (ret < 0) {
                perror("write");
                return -1;
        }

        // send data
        ret = write(fd, data, len);
        if (ret < 0) {
                perror("write");
                return -1;
        }

        return 0;
}


int i2c_receive(uint8_t regaddr, int fd, uint8_t *buffer, int len)
{
        int ret = 0;

        // Select slave register
        ret = write(fd, &regaddr, 1);
        if (ret < 0) {
                perror("write");
                return -1;
        }

        // Receive data
        ret = read(fd, buffer, len);
        if (ret < 0) {
                perror("read");
                return -1;
        }

        return 0;
}
