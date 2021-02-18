#ifndef _PERI_RGB_H_
#define _PERI_RGB_H_

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t   Reserved:32;
  } BITS;
}RGB_Reserved_Type;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t LED4_EN:2,
			     LED3_EN:2,
			     LED2_EN:2,
			     LED1_EN:2,
			     Reserved1:6,
			     LED5_EN:2,
			     LED1_CURR_SET:8,
			     LED2_CURR_SET:8;
  } BITS;
}RGB_REG_40;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t LED3_CURR_SET:8,
			     LED4_CURR_SET:8,
			     LED5_CURR_SET:8,
			     LED1_RAMP_DN:4,
			     LED1_RAMP_UP:4;
  } BITS;
}RGB_REG_44;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t LED1_OFF_DUR:4,
			     LED1_ON_DUR:4,
			     LED2_RAMP_DN:4,
			     LED2_RAMP_UP:4,
			     LED2_OFF_DUR:4,
			     LED2_ON_DUR:4,
			     LED3_RAMP_DN:4,
			     LED3_RAMP_UP:4;
  } BITS;
}RGB_REG_48;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t LED3_OFF_DUR:4,
			     LED3_ON_DUR:4,
			     LED4_RAMP_DN:4,
			     LED4_RAMP_UP:4,
			     LED4_OFF_DUR:4,
			     LED4_ON_DUR:4,
			     LED5_RAMP_DN:4,
			     LED5_RAMP_UP:4;
  } BITS;
}RGB_REG_4C;

typedef union
{
    uint32_t DATA;
    struct {
        uint32_t LED5_OFF_DUR:4,
			     LED5_ON_DUR:4,
			     REG_RGB_RST:1,
			     LED_ON_SEQ_SEL:1,
			     Pre_CHG_ON:1,
			     ON_OFF_TIME_DUR5:1,
			     ON_OFF_TIME_DUR4:1,
			     ON_OFF_TIME_DUR3:1,
			     ON_OFF_TIME_DUR2:1,
			     ON_OFF_TIME_DUR1:1,
			     Reserved1:3,
			     STEP_CTRL5:1,
			     STEP_CTRL4:1,
			     STEP_CTRL3:1,
			     STEP_CTRL2:1,
			     STEP_CTRL1:1,
			     REG_OTP_REDUMP_REQ:1,
			     RGB_MONITOR_SEL:7;
  } BITS;
}RGB_REG_50;

typedef struct
{
	RGB_Reserved_Type Reserved00;
	RGB_Reserved_Type Reserved04;
	RGB_Reserved_Type Reserved08;
	RGB_Reserved_Type Reserved0C;
	RGB_Reserved_Type Reserved10;
	RGB_Reserved_Type Reserved14;
	RGB_Reserved_Type Reserved18;
	RGB_Reserved_Type Reserved1C;
	RGB_Reserved_Type Reserved20;
	RGB_Reserved_Type Reserved24;
	RGB_Reserved_Type Reserved28;
	RGB_Reserved_Type Reserved2C;
	RGB_Reserved_Type Reserved30;
	RGB_Reserved_Type Reserved34;
	RGB_Reserved_Type Reserved38;
	RGB_Reserved_Type Reserved3C;
	RGB_REG_40        REG_40;
	RGB_REG_44        REG_44;
	RGB_REG_48        REG_48;
	RGB_REG_4C        REG_4C;
	RGB_REG_50        REG_50;
}RGB_BLOCK_Type;
#endif

