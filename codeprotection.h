/*
 * Code protection helper library
 * for STM32 HAL
 *
 * Copyright (c) 2021 yuujiin
 * https://github.com/yuujiin
 */

#ifndef CODEPROTECTION_H_
#define CODEPROTECTION_H_

/* Include STM32 HAL header */
#include "main.h"
//#include "stm32f3xx_hal.h"


HAL_StatusTypeDef CodeProtection_SetLevel(uint8_t Level);

#endif /* CODEPROTECTION_H_ */
