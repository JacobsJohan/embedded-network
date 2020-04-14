#include <stdint.h>

/*********************************** Public functions ***********************************/

/* Initialize an i2c_bus on a given address.
 * @param i2c_bus: name of the i2c bus to open.
 * @param i2c_addr: open the i2c bus at the given address.
 * @return: the opened file descriptor, -1 in case of error.
 */
int i2c_init(const char *i2c_bus, int i2c_addr);


/* Close the i2c bus.
 * @param fd: file descriptor of the opened i2c bus.
 * @return: 0 on success, -1 on error.
 */
int i2c_deinit(int fd);


/* Transmit data over i2c to a register.
 * @param regaddr: 8 bit register address.
 * @param fd: file descriptor of open i2c_bus.
 * @param data: ptr to data to transmit.
 * @param len: length of data.
 * @return: 0 on success, -1 on failure.
 */
int i2c_transmit(uint8_t regaddr, int fd, uint8_t *data, int len);


/* Receive data over i2c from a register.
 * @param regaddr: 8 bit register address.
 * @param fd: file descriptor of open i2c_bus.
 * @param buffer: ptr to buffer to save data.
 * @param len: length of data.
 * @return: 0 on success, -1 on failure.
 */
int i2c_receive(uint8_t regaddr, int fd, uint8_t *buffer, int len);
