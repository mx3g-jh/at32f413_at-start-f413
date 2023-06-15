#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
//system
#include "at32f435_437.h"
#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"

//bsp
#include "timer.h"

//hardware
#include "bsp_spi_lcd.h"
//application
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_demos.h"

void System_Init(void);

#ifdef __cplusplus
}
#endif

#endif
