#include "stdio.h"
#include "time.h"

#include "bmp280.h"
#include "i2c_drv.h"

static const char i2c_bus[]  = "/dev/i2c-1";

void delay_ms(uint32_t period_ms);
int8_t i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
void print_rslt(const char api_name[], int8_t rslt);

int bmp280_configure(struct bmp280_dev *bmp, struct bmp280_config *conf)
{
        int8_t rslt = 0;

        /* Map the delay function pointer with the function responsible for implementing the delay */
        bmp->delay_ms = delay_ms;

        /* Assign device I2C address based on the status of SDO pin (GND for PRIMARY(0x76) & VDD for SECONDARY(0x77)) */
        bmp->dev_id = BMP280_I2C_ADDR_SEC;

        /* Select the interface mode as I2C */
        bmp->intf = BMP280_I2C_INTF;

        /* Map the I2C read & write function pointer with the functions responsible for I2C bus transfer */
        bmp->read = i2c_reg_read;
        bmp->write = i2c_reg_write;

        rslt = bmp280_init(bmp);
        print_rslt(" bmp280_init status", rslt);

        /* Always read the current settings before writing, especially when
         * not all configurations are modified
         */
        rslt = bmp280_get_config(conf, bmp);
        print_rslt(" bmp280_get_config status", rslt);

        /* configuring the temperature oversampling, filter coefficient and output data rate */
        /* Overwrite the desired settings */
        conf->filter = BMP280_FILTER_COEFF_2;

        /* Temperature oversampling set at 4x */
        conf->os_temp = BMP280_OS_4X;

        /* Pressure over sampling none (disabling pressure measurement) */
        conf->os_pres = BMP280_OS_NONE;

        /* Setting the output data rate as 1HZ(1000ms) */
        conf->odr = BMP280_ODR_1000_MS;
        rslt = bmp280_set_config(conf, bmp);
        print_rslt(" bmp280_set_config status", rslt);

        /* Always set the power mode after setting the configuration */
        rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, bmp);
        print_rslt(" bmp280_set_power_mode status", rslt);

        return 0;
}

int main(void)
{
        int8_t rslt;
        struct bmp280_dev bmp;
        struct bmp280_config conf;
        struct bmp280_uncomp_data ucomp_data;
        int32_t temp32;
        double temp;

        /* Initialize i2c */
        int8_t ret = 0;
        ret = i2c_init(i2c_bus, BMP280_I2C_ADDR_SEC);
        if (ret < 0) {
                printf("i2c_init failed\n");
                i2c_deinit();
                return -1;
        }

        /* Set desired configurations */
        ret = bmp280_configure(&bmp, &conf);

        while (1) {
                /* Reading the raw data from sensor */
                rslt = bmp280_get_uncomp_data(&ucomp_data, &bmp);

                /* Getting the compensated temperature as floating point value */
                rslt = bmp280_get_comp_temp_double(&temp, ucomp_data.uncomp_temp, &bmp);
                printf("T: %.2f\n", temp);

                /* Sleep time between measurements = BMP280_ODR_1000_MS */
                bmp.delay_ms(1000);
        }

        /* De-initialize i2c */
        ret = i2c_deinit();
        if (ret < 0) {
                printf("Error i2c_deinit()\n");
        }

        return ret;
}

/*!
 *  @brief Function that creates a mandatory delay required in some of the APIs such as "bmg250_soft_reset",
 *      "bmg250_set_foc", "bmg250_perform_self_test"  and so on.
 *
 *  @param[in] period_ms  : the required wait time in milliseconds.
 *  @return void.
 *
 */
void delay_ms(uint32_t period_ms)
{
        /* Implement the delay routine according to the target machine */
        int ret = 0;
        struct timespec ts;

        if (period_ms >= 1000) {
                ts.tv_sec = period_ms / 1000;
                ts.tv_nsec = period_ms % 1000 * 1e6;
        } else {
                ts.tv_sec = 0;
                ts.tv_nsec = period_ms * 1000000;
        }

        ret = nanosleep(&ts, NULL);
        if (ret < 0) {
                perror("nanosleep");
        }
}

/*!
 *  @brief Prints the execution status of the APIs.
 *
 *  @param[in] api_name : name of the API whose execution status has to be printed.
 *  @param[in] rslt     : error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void print_rslt(const char api_name[], int8_t rslt)
{
        if (rslt != BMP280_OK) {
                printf("%s\t", api_name);
                if (rslt == BMP280_E_NULL_PTR) {
                        printf("Error [%d] : Null pointer error\r\n", rslt);
                } else if (rslt == BMP280_E_COMM_FAIL) {
                        printf("Error [%d] : Bus communication failed\r\n", rslt);
                } else if (rslt == BMP280_E_IMPLAUS_TEMP) {
                        printf("Error [%d] : Invalid Temperature\r\n", rslt);
                } else if (rslt == BMP280_E_DEV_NOT_FOUND) {
                        printf("Error [%d] : Device not found\r\n", rslt);
                } else {
                        /* For more error codes refer "*_defs.h" */
                        printf("Error [%d] : Unknown error code\r\n", rslt);
                }
        }
}
