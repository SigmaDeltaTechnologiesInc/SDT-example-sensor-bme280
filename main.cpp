/* SDT-example-blinky
 * 
 * Copyright (c) 2018 Sigma Delta Technologies Inc.
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mbed.h"
#include "BME280.h"
#include "BME280_SPI.h"

/* Serial */
#define BAUDRATE 9600
Serial serial_pc(USBTX, USBRX, BAUDRATE);

/* Sensor */
#define _INTERFACE_I2C_     1                   // Do not fix it
#define _INTERFACE_SPI_     0                   // Do not fix it
#define _INTERFACE_         _INTERFACE_SPI_     // You can choose one of two interfaces and must set interface selection on hardware.
#if _INTERFACE_
BME280 bme280_i2c(I2C0_SDA, I2C0_SCL);
#else
BME280_SPI bme280_spi(SPI0_MOSI, SPI0_MISO, SPI0_SCK, SPI0_SS0);
#endif
float temperature, pressure, humidity;



int main(void) {
    serial_pc.printf("< Sigma Delta Technologies Inc. >\n\r");
    
    while(true) {
#if _INTERFACE_
        /* Using I2C */
        temperature = bme280_i2c.getTemperature();
        pressure = bme280_i2c.getPressure();
        humidity = bme280_i2c.getHumidity();
#else
        /* Using SPI */
        temperature = bme280_spi.getTemperature();
        pressure = bme280_spi.getPressure();
        humidity = bme280_spi.getHumidity();
#endif

        serial_pc.printf("%2.2f degC, %04.2f hPa, %2.2f %%\n", temperature, pressure, humidity);
        wait(1);
    }
}
