#ifndef NI2C_H_
#define NI2C_H_

#include "plat/i2c.h"

#define I2C_BUS_ADDRESS_7BIT            (0x0u << 0)
#define I2C_BUS_ADDRESS_10BIT           (0x1u << 0)

#define I2C_SLAVE_RD_NACK               (0x1u << 0)
#define I2C_SLAVE_RD_START_STOP         (0x1u << 1)
#define I2C_SLAVE_RD_REPEAT             (0x2u << 1)

struct i2c_bus_config
{
    uint32_t                    flags;
    uint32_t                    speed;
    uint32_t                    isr_prio;
};

struct i2c_bus;

struct i2c_slave_config
{
    uint32_t                    flags;
    uint8_t                     address;
};

struct i2c_slave
{
    struct i2c_bus *            bus;
    uint32_t                    flags;
    uint8_t                     address;
};

void i2c_driver_init(void);

void i2c_bus_init(
    struct i2c_bus *            bus, 
    const struct i2c_bus_config * config);
    
void i2c_bus_term(
    struct i2c_bus *            bus);
    
void i2c_bus_ack(
    struct i2c_bus *            bus);
    
void i2c_bus_nack(
    struct i2c_bus *            bus);
    
bool i2c_bus_write_array(
    struct i2c_bus *            bus,
    const uint8_t *             data,
    size_t                      size);

bool i2c_bus_write(
    struct i2c_bus *            bus,
    uint8_t                     data);

void i2c_bus_read_array(
    struct i2c_bus *            bus,
    uint8_t *                   data,
    size_t                      size);

uint8_t i2c_bus_read(
    struct i2c_bus *            bus);

void i2c_bus_start(
    struct i2c_bus *            bus);

void i2c_bus_restart(
    struct i2c_bus *            bus);

void i2c_bus_stop(
    struct i2c_bus *            bus);

void i2c_slave_open(
    struct i2c_slave *          slave,
    const struct i2c_slave_config * config,
    struct i2c_bus *            bus,
    uint8_t                     id);

void i2c_slave_close(
    struct i2c_slave *          slave);
    
bool i2c_slave_read(
    struct i2c_slave *          slave,
    uint8_t                     address,
    void *                      data,
    size_t                      size);

bool i2c_slave_write(
    struct i2c_slave *          slave,
    uint8_t                     address,
    const void *                data,
    size_t                      size);

#endif /* NI2C_H_ */