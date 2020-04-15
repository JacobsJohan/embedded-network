#ifndef I2C_DRV_H
#define I2C_DRV_H

#include <stdint.h>

/*********************************** Public functions ***********************************/

/* Initialize an i2c_bus on a given address.
 * @param i2c_bus: name of the i2c bus to open.
 * @param i2c_addr: open the i2c bus at the given address.
 * @return: 0 on succes, -1 on error.
 */
int i2c_init(const char *i2c_bus, int i2c_addr);


/* Close the i2c bus.
 * @return: 0 on success, -1 on error.
 */
int i2c_deinit(void);


/* Transmit data over i2c to a register.
 * @param i2c_addr: 7 bit i2c device address.
 * @param reg_addr: 8 bit register address.
 * @param reg_data: ptr to data to transmit.
 * @param length: length of data.
 * @return: 0 on success, -1 on failure.
 */
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);

/* Receive data over i2c from a register.
 * @param i2c_addr: 7 bit i2c device address.
 * @param reg_addr: 8 bit register address.
 * @param reg_data: ptr to buffer to store data.
 * @param length: length of data.
 * @return: 0 on success, -1 on failure.
 */
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);

#endif /* I2C_DRV_H */
