/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes */
#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_demos.h"
#include "main.h"

#define BufferSize	240*240
uint16_t Buffer_Tx[BufferSize];

/** @addtogroup AT32F435_periph_examples
  * @{
  */

/** @addtogroup 435_GPIO_led_toggle GPIO_led_toggle
  * @{
  */

TaskHandle_t App_main_Handler;
TaskHandle_t Lvgl_task_Handler;
TaskHandle_t Lvgl_display_Handler;

void App_main(void *pvParameters)
{
  // lv_init();
  // lv_port_disp_init();
  // lv_demo_benchmark();
	// crm_clocks_freq_type Get_Clocks;
	// crm_clocks_freq_get(&Get_Clocks);
	// printf("System Clock information\r\n");
	// printf("SYSCLK_Frequency = %d\r\n", (uint32_t)Get_Clocks.sclk_freq);
	// printf("HCLK_Frequency   = %d\r\n", (uint32_t)Get_Clocks.ahb_freq);
	// printf("PCLK1_Frequency  = %d\r\n", (uint32_t)Get_Clocks.apb1_freq);
	// printf("PCLK2_Frequency  = %d\r\n", (uint32_t)Get_Clocks.apb2_freq);
	// u8 task_buff[128];
	while (1)
	{
		// printf("====================Task===================\r\n");
		// printf("  name       state     pri     stack    num\r\n");
		// vTaskList((char *)task_buff);
		// printf("%s", task_buff);
		// printf("===========================================\r\n");
    // 		for(int i = 0; i < BufferSize; i++)
		// {
		// 	Buffer_Tx[i] = RED;
		// }
		// LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		// vTaskDelay(100);
		
		// printf("doing\r\n");
		// for(int i = 0; i < BufferSize; i++)
		// {
		// 	Buffer_Tx[i] = LIGHTBLUE;
		// }
		// LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		// vTaskDelay(100);

		// printf("doing\r\n");
		// for(int i = 0; i < BufferSize; i++)
		// {
		// 	Buffer_Tx[i] = LBBLUE;
		// }
		// LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		// vTaskDelay(100);

		// printf("doing\r\n");
		// for(int i = 0; i < BufferSize; i++)
		// {
		// 	Buffer_Tx[i] = WHITE;
		// }
		// LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		// vTaskDelay(100);
		vTaskDelay(1000);
	}
}

void Lvgl_task(void *pvParameters)
{

  while (1)
  {
    lv_task_handler();
    vTaskDelay(10);
  }
}

void Lvgl_display_task(void *pvParameters)
{
  lv_init();
  lv_ms_tick_tim();
  lv_port_disp_init();
  lv_demo_benchmark();
  while (1)
  {

    vTaskDelay(100);
  }
}

__IO uint32_t time_cnt = 0;
/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  system_clock_config();
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA1_Channel1_IRQn, 1, 0);
  nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 0x01, 0);

  at32_board_init();
  uart_print_init(115200);

  LCD_Init();
  LCD_fill(0,0,240,240,YELLOW);


	taskENTER_CRITICAL();
	xTaskCreate((TaskFunction_t)App_main,
				(const char *)"App_main",
				(uint16_t)256,
				(void *)NULL,
				(UBaseType_t)1,
				(TaskHandle_t *)&App_main_Handler);
  
  xTaskCreate((TaskFunction_t)Lvgl_task,
            (const char *)"lvgl_task",
            (uint16_t)1024,
            (void *)NULL,
            (UBaseType_t)1,
            (TaskHandle_t *)&Lvgl_task_Handler);

  xTaskCreate((TaskFunction_t)Lvgl_display_task,
            (const char *)"Lvgl_display_task",
            (uint16_t)1024,
            (void *)NULL,
            (UBaseType_t)1,
            (TaskHandle_t *)&Lvgl_display_Handler);

	taskEXIT_CRITICAL();
	vTaskStartScheduler();

}

/**
  * @}
  */

/**
  * @}
  */
