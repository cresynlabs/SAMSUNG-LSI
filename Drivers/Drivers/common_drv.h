#ifndef __COMMON_DRV_H
#define __COMMON_DRV_H

#define GPIO_PORT_MODE_CMOS     1
#define GPIO_PORT_OPEN_DRAIN    0

#define GPIO_PORT1             1
#define GPIO_PORT2             2
#define GPIO_PORT3             3
#define GPIO_PORT4             4
#define GPIO_PORT5             5
#define GPIO_PORT6             6

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define BOTH 3

#define LEFT_SHIFT 0
#define RIGHT_SHIFT 1

#define ADDRESS_SC_TIME_DEBOUNCE        0xf0008099
#define ADDRESS_EN_IN_PLG_OFF_RESET     0xf0008097

void gpio_drv_set_to_uart(void);
void gpio_drv_set_enable(uint8_t port, uint8_t mode);
void gpio_drv_set_output_data(uint8_t port, uint8_t data);
uint8_t gpio_drv_get_output_data(uint8_t port);
uint8_t gpio_drv_get_input_data(uint8_t port);

uint8_t hall_drv_get_hall_status(void);
void boot_det_pogo_irqhandler(void);
void pm_drv_set_vpogo_co(uint8_t data);
void pm_drv_set_ipogo_co(uint8_t data);
void sysreg_drv_seten_det_pogo(uint8_t dir, uint8_t data);
uint16_t pm_drv_get_vpogo(uint8_t dir);
uint16_t pm_drv_get_ipogo(uint8_t dir);
void bootcon_drv_set_shutdown_mode(uint8_t data);
void sysreg_drv_seten_det_reset_pogo(uint8_t dir);
void sysreg_drv_set_lpm(uint8_t data);
void direct_address_access(uint32_t address, uint8_t data, uint8_t cal);
void bootcon_drv_set_shipmode(void);
void sysreg_drv_set_wdt(void);
void sysreg_drv_set_wdt_reset(void);
void boot_wdt_irqhandler(void);
void sysreg_drv_set_wdt_disable(void);
void gpio_drv_set_to_uart(void);

void comm_memset16(uint16_t *pdest, uint16_t data, uint8_t nsize);
void comm_memset16_p2p(uint16_t *pdest, uint16_t *psrc, uint8_t nsize);
void comm_memset(uint8_t *pdest, uint8_t data, uint8_t nsize);
uint8_t check_timer(uint32_t time, uint32_t timer);
#endif /* __COMMON_DRV_H */
