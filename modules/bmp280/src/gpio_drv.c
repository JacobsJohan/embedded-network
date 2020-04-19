#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "gpio_drv.h"

int gpio_init(char *gpio_pin, char *direction)
{
        int ret = 0;
        int fd = -1;
        char direction_path[128] = "/sys/class/gpio/gpio";

        /* Ask the kernel to export the control of a GPIO to userspace */
        fd = open("/sys/class/gpio/export", O_WRONLY);
        if (fd < 0) {
                perror("Cannot open /sys/class/gpio/export");
                ret = -1;
                goto exit_gpio_init;
        }

        ret = write(fd, gpio_pin, strnlen(gpio_pin, 2));
        if (ret < 0) {
                perror("Error writing to /sys/class/gpio/export");
                goto exit_gpio_init;
        }

        ret = close(fd);
        if (ret < 0) {
                perror("Error closing fd");
                goto exit_gpio_init;
        }

        /* Sleep for 100 ms to avoid race conditions */
        usleep(100000);

        /* Set the pin as an input or output in /sys/class/gpio/gpioX/direction.
         * Set the direction path based on the selected pin.
         */
        strncat(direction_path, gpio_pin, 2);
        strcat(direction_path, "/direction");

        fd = open(direction_path, O_WRONLY);
        if (fd < 0) {
                perror("Cannot open /sys/class/gpio/gpioX/direction");
                ret = -1;
                goto exit_gpio_init;
        }

        /* Write "in" or "out" to the file descriptor */
        ret = write(fd, direction, strnlen(direction, 3));
        if (ret < 0) {
                perror("Error writing to /sys/class/gpio/gpioX/direction");
                goto exit_gpio_init;
        }

exit_gpio_init:
        if (fd != -1) {
                close(fd);
        }
        return ret;
}


int gpio_deinit(char *gpio_pin)
{
        int ret = 0;
        int fd = -1;

        /* Unexport pin from userspace */
        fd = open("/sys/class/gpio/unexport", O_WRONLY);
        if (fd < 0) {
                perror("Cannot open /sys/class/gpio/unexport");
                ret = -1;
                goto exit_gpio_deinit;
        }

        ret = write(fd, gpio_pin, strnlen(gpio_pin, 2));
        if (ret < 0) {
                perror("Error writing to /sys/class/gpio/unexport");
                goto exit_gpio_deinit;
        }

exit_gpio_deinit:
        if (fd != -1) {
                close(fd);
        }
        return ret;
}

int gpio_pin_set(char *gpio_pin, char* value)
{
        int ret = 0;
        int fd = -1;
        char value_path[128] = "/sys/class/gpio/gpio";

        /* Fill in "/sys/class/gpio/gpioX/value" based on the chosen pin */

        strncat(value_path, gpio_pin, 2);
        strcat(value_path, "/value");
        fd = open(value_path, O_WRONLY);
        if (fd < 0) {
                perror("Error opening /sys/class/gpio/gpioX/vale");
                ret = -1;
                goto exit_gpio_set_pin;
        }

        /* Set the GPIO pin as low ("0") or high ("1") */
        ret = write(fd, value, 1);
        if (ret < 0) {
                perror("Error writing to /sys/class/gpio/gpioX/value");
                goto exit_gpio_set_pin;
        }

exit_gpio_set_pin:
        if (fd != -1) {
                close(fd);
        }
        return ret;
}
