#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#include <stdio.h>
#if defined   ( __CC_ARM   )
#include <rt_misc.h>
#endif
#include <stdint.h>
#include "../MCU/cm0pikmcu.h"

#define I2C_MODE_SEL_1  0x1
#define I2C_MODE_SEL_2  0x2
#define I2C_MODE_8BIT   0
#define I2C_MODE_16BIT  1

#define I2C_REG_ACCESS_SKIP 0
#define I2C_REG_ACCESS_OK   1

#define I2C_BUS_SLAVE   0
#define I2C_BUS_MASTER  1
    
#define I2C_RX          0
#define I2C_TX          1
    
#define I2C_IRQ_NONE    0
#define I2C_IRQ_WAIT    1

typedef union
{
    uint32_t DATA;

    struct
    {
        uint8_t     BDATA[4];
    } BYTES;

    struct
    {
        uint16_t     WDATA[2];
    } WORDS;

} i2c_register_access_t;

typedef enum
{
    I2C_MASTER_STOP = 0,
    I2C_MASTER_TX_STATUS    = 1,
    I2C_MASTER_RX_STATUS    = 2,
    I2C_MASTER_RX_LAST      = 3
} i2c_master_status_t;

typedef enum
{
    I2C_MASTER_None = 0,
    I2C_MASTER_ACK  = 1
} i2c_master_data_ack_t;

#define __clr_IRQ_I2C2()    do { \
                                MI2C.ICCR.BITS.IRQClr = 0x1; \
                                MI2C.ICCR.BITS.subIRQ = 0x0; \
                            } while(0)


#define __set_PI2C_8BIT_MODE()  (PI2C.SLV_CONF.BITS.ADDR_16BIT_MODE = 0x0)
#define __set_PI2C_16BIT_MODE() (PI2C.SLV_CONF.BITS.ADDR_16BIT_MODE = 0x1)

#define __clr_IRQ_PI2C()    do { \
                                PI2C.SLV_CONF.BITS.IRQclr = 0x1; \
                                PI2C.SLV_CONF.BITS.subIRQ = 0x0; \
                            } while(0)

#define __set_RX_START_MST_I2C2(__ADDRESS__)	do { \
									MI2C.ICSR.DATA = 0x90; \
									MI2C.IDSR.DATA = __ADDRESS__; \
									MI2C.ICSR.DATA = 0xB0; \
								} while(0)


#define __set_RX_STOP_MST_I2C2()	do { \
									MI2C.ICSR.BITS.MST = 0x1; \
									MI2C.ICSR.BITS.TRAN = 0x0; \
									MI2C.ICSR.BITS.BUSY = 0x0; \
									MI2C.ICSR.BITS.SerialOutputEn = 0x0; \
								} while(0)

extern volatile uint32_t i2c_status_flag;
extern volatile uint32_t i2c_data_ack;
extern volatile uint8_t  i2c_wr_buf;
extern volatile uint8_t  i2c_rd_buf;


extern void i2c_master_init(uint32_t I2C_MODE);
extern void i2c_slave_init(void);
extern void i2c_register_access(void);

extern void boot_pi2c1_irqhandler(void);

extern uint32_t i2c_start(uint32_t slvaddr, uint32_t mode, uint32_t waitmode);
extern uint32_t i2c_stop( uint32_t waitmode);
extern uint32_t i2c_master_data_write(uint8_t wdata);
extern uint32_t i2c_master_data_read(uint8_t *rdata);
extern uint32_t write_i2c(uint32_t slave_addr, uint32_t reg_addr, uint8_t *wdata, uint32_t data_size);
extern uint32_t read_i2c(uint32_t slave_addr, uint32_t reg_addr, uint8_t *rdata, uint32_t data_size);

#endif /* __I2C_DRV_H_ */
