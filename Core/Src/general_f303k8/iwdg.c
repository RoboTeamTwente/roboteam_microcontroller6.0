
#include "iwdg.h"
#include "stm32f3xx.h"

#define TIMEOUT		48u		// wait for max 48 ms before starting

#define START		0x0000CCCC
#define RELOAD		0x0000AAAA
#define SET_WRITE	0x00005555
#define LOCK_WRITE	0x00000000


HAL_StatusTypeDef IWDG_Init(IWDG_Handle* hiwdg, uint32_t timeout_ms){

	/* https://www.st.com/resource/en/datasheet/stm32f303k8.pdf - page 25 - 3.14.4
	* https://www.stmicroelectronics.com.cn/content/ccc/resource/training/technical/product_training/group0/ce/34/ce/35/30/1a/42/10/STM32MP1-WDG_TIMERS-Independent_Watchdog_IWDG/files/STM32MP1-WDG_TIMERS-Independent_Watchdog_IWDG.pdf/_jcr_content/translations/en.STM32MP1-WDG_TIMERS-Independent_Watchdog_IWDG.pdf
	* The watchdog clock runs at 40 kHz. Given an 8-bit prescaler of 64, this becomes 625 Hz.
	* The watchdog has an internal 12-bit timer. This gives a range of (1/625) to (2^12/625) seconds, or roughly 1.6 milliseconds to 6.5 seconds
	*/
	float ticks_per_ms = 1000 / 625.f;
	uint32_t reload_value = timeout_ms / ticks_per_ms;
	if(4095 < reload_value) reload_value = 4095;

	hiwdg->mem = (IWDG_REG*)IWDG;
	hiwdg->Settings.Prescaler = IWDG_PRESCALER_64;
	hiwdg->Settings.Window = reload_value;
	hiwdg->Settings.Reload = reload_value;


	WRITE_REG((hiwdg)->mem->Key, 0x0000CCCCu);	// start IWDG
	WRITE_REG((hiwdg)->mem->Key, 0x00005555u);	// set write access

	hiwdg->mem->Pre = hiwdg->Settings.Prescaler;
	hiwdg->mem->Reload = hiwdg->Settings.Reload;

	/* Wait for register to be updated */
	uint32_t  tickstart = HAL_GetTick();
	while (hiwdg->mem->Status != RESET){
		if ((HAL_GetTick() - tickstart) > TIMEOUT){
			return HAL_TIMEOUT;
		}
	}

	hiwdg->mem->Window = hiwdg->Settings.Window;
	return HAL_OK;
}

void IWDG_Refresh(IWDG_Handle* hiwdg)
{
	WRITE_REG((hiwdg)->mem->Key, RELOAD);
}
