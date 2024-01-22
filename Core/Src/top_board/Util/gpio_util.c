/*
 * gpio_util.c
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#include "gpio_util.h"
#include "main.h"

#define DEFINE_PIN(label,pin_name) GPIO_Pin label = {pin_name##_GPIO_Port, pin_name##_Pin};
// List known GPIO pins


// Wheels PWM
GPIO_Pin RB_PWM_pin			= { RB_PWM_GPIO_Port		, RB_PWM_Pin		};
GPIO_Pin RF_PWM_pin			= { RF_PWM_GPIO_Port		, RF_PWM_Pin		};
GPIO_Pin LB_PWM_pin			= { LB_PWM_GPIO_Port		, LB_PWM_Pin		};
GPIO_Pin LF_PWM_pin			= { LF_PWM_GPIO_Port		, LF_PWM_Pin		};

// Wheels DIR
GPIO_Pin RB_DIR_pin			= { RB_DIR_GPIO_Port		, RB_DIR_Pin		};
GPIO_Pin RF_DIR_pin			= { RF_DIR_GPIO_Port		, RF_DIR_Pin		};
GPIO_Pin LB_DIR_pin			= { LB_DIR_GPIO_Port		, LB_DIR_Pin		};
GPIO_Pin LF_DIR_pin			= { LF_DIR_GPIO_Port		, LF_DIR_Pin		};

// Wheels brake
GPIO_Pin RB_Brake_pin		= { RB_BRK_GPIO_Port		, RB_BRK_Pin		};
GPIO_Pin RF_Brake_pin		= { RF_BRK_GPIO_Port		, RF_BRK_Pin		};
GPIO_Pin LB_Brake_pin		= { LB_BRK_GPIO_Port		, LB_BRK_Pin		};
GPIO_Pin LF_Brake_pin		= { LF_BRK_GPIO_Port		, LF_BRK_Pin		};

// LEDs
GPIO_Pin LED0_pin			= { LED0_GPIO_Port			, LED0_Pin			};
GPIO_Pin LED1_pin			= { LED1_GPIO_Port			, LED1_Pin			};
GPIO_Pin LED2_pin			= { LED2_GPIO_Port			, LED2_Pin			};
GPIO_Pin LED3_pin			= { LED3_GPIO_Port			, LED3_Pin			};
GPIO_Pin LED4_pin			= { LED4_GPIO_Port			, LED4_Pin			};
GPIO_Pin LED5_pin			= { LED5_GPIO_Port			, LED5_Pin			};
GPIO_Pin LED6_pin			= { LED6_GPIO_Port			, LED6_Pin			};
GPIO_Pin LED7_pin			= { LED7_GPIO_Port			, LED7_Pin			};

// ID select
DEFINE_PIN(ID0_pin, DIP_SW0)
DEFINE_PIN(ID1_pin, DIP_SW1)
DEFINE_PIN(ID2_pin, DIP_SW2)
DEFINE_PIN(ID3_pin, DIP_SW3)

// Feature Select
DEFINE_PIN(FT0_pin, DIP_SW4)
DEFINE_PIN(FT1_pin, DIP_SW5)
DEFINE_PIN(FT2_pin, DIP_SW6)
DEFINE_PIN(FT3_pin, DIP_SW7)


//Motor Driver chip selects(for spi)
GPIO_Pin RB_CS_pin 			={ RB_CS_GPIO_Port			, RB_CS_Pin			};
GPIO_Pin RF_CS_pin 			={ RF_CS_GPIO_Port			, RF_CS_Pin			};
GPIO_Pin LB_CS_pin 			={ LB_CS_GPIO_Port			, LB_CS_Pin			};
GPIO_Pin LF_CS_pin 			={ LF_CS_GPIO_Port			, LF_CS_Pin			};

//Encoder Enable
GPIO_Pin Encoder_Enable_pin={Encoder_Enable_GPIO_Port 	, Encoder_Enable_Pin};

// MTi
GPIO_Pin MTi_RST_pin 		= { XSENS_RST_GPIO_Port		, XSENS_RST_Pin		};
GPIO_Pin MTi_IRQ_pin 		= { XSENS_IRQ_GPIO_Port		, XSENS_IRQ_Pin		};
GPIO_Pin MTi_NSS_pin		= { SPI1_NSS_GPIO_Port		, SPI1_NSS_Pin		};

// Wireless
GPIO_Pin SX_IRQ_pin			= { SPI4_IRQ_GPIO_Port 		, SPI4_IRQ_Pin		};
GPIO_Pin SX_RST_pin			= { SPI4_RST_GPIO_Port 		, SPI4_RST_Pin		};
GPIO_Pin SX_NSS_pin			= { SPI4_NSS_GPIO_Port 		, SPI4_NSS_Pin		};
GPIO_Pin SX_BUSY_pin		= { SPI4_BUSY_GPIO_Port 	, SPI4_BUSY_Pin		};

// SD
DEFINE_PIN(SD_CD_pin, SD_MMC1_CD)

