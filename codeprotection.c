/*
 * Code protection helper library
 * for STM32 HAL
 *
 * Copyright (c) 2021 yuujiin
 * https://github.com/yuujiin
 */

#include "codeprotection.h"

/* Set code protection level (RDP option byte).
 *
 * Input parameters: Level (0..2).
 * 	Level = 0: Protection disabled.
 * 	Level = 1: Read-out protection enabled.
 * 	Level = 2: Permanent chip protection enabled.
 *
 * Returns HAL_OK if desired level is already programmed.
 * Causes system reset on level change.
 *
 * Warning!
 * Reverting Level 1 to Level 0 causes full chip erase.
 * Level 2 can not be reverted.
 */
HAL_StatusTypeDef CodeProtection_SetLevel(uint8_t Level) {
	HAL_StatusTypeDef ret = HAL_OK;
	FLASH_OBProgramInitTypeDef init;
	uint8_t rdp_level;

	// Check input parameters
	switch (Level) {
	case 0:	// Level 0: Read-out protection disabled
		rdp_level = OB_RDP_LEVEL_0;
		break;
	case 1:	// Level 1: Read-out protection enabled
		rdp_level = OB_RDP_LEVEL_1;
		break;
	case 2:	// Level 2: Permanent protection enabled
		rdp_level = OB_RDP_LEVEL_2;
		break;
	default: // Incorrect parameter
		return HAL_ERROR;
	}

	// Read current protection level
	HAL_FLASHEx_OBGetConfig(&init);
	if (init.RDPLevel == rdp_level) {
		return HAL_OK;
	}

	// Only RDP option byte
	init.OptionType = OPTIONBYTE_RDP;
	init.RDPLevel = rdp_level;

	// Program option bytes
	ret = HAL_FLASH_Unlock();
	if (ret != HAL_OK) {
		return ret;
	}
	ret = HAL_FLASH_OB_Unlock();
	if (ret != HAL_OK) {
		return ret;
	}
	ret = HAL_FLASHEx_OBProgram(&init);
	if (ret != HAL_OK) {
		return ret;
	}
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();

	// Reload option bytes (causes system reset)
	HAL_FLASH_OB_Launch();

	return ret;
}
