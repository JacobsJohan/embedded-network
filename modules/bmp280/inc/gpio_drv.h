#ifndef GPIO_DRV_H
#define GPIO_DRV_H

/* Initialize a GPIO pin
 * @param gpio_pin: the number of the gpio pin as a string
 * @param direction: set pin as input ("in") or output ("out")
 * @return 0 on success, -1 on failure
 */
int gpio_init(char *gpio_pin, char *direction);

/* De-initialize a GPIO pin */
int gpio_deinit(char *gpio_pin);

/* Set a pin to value "1" or "0" */
int gpio_pin_set(char *gpio_pin, char* value);

#endif /* GPIO_DRV_H */
