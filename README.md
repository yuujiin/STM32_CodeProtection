# STM32 CodeProtection
Helper library to control flash read-out protection (RDP option byte) using STM32 HAL.


# Protection levels

## Level 0
No protection. All flash memory operations are permitted.

## Level 1
All flash memory operations are blocked (hard fault generated) in case:
* Selected boot mode is not User Flash memory (BOOT0 = 0)
* Debugger access is detected

Option bytes can still be modified. 
A full chip erase is performed when reverting to Level 0.

## Level 2
**Warning! Level 2 protection can not be reverted.**
You don't want to enable it on your expensive dev board ;)

In this mode:
* Boot from RAM or System boot loader is not possible
* Boot mode is set to User Flash memory regardless of BOOT0/1 settings
* Debug interface is disabled (no JTAG/SWD access)
* Option bytes can not be changed (including read-out protection level)

Application in User Flash memory still has full access. 
For example, you can reprogram device using custom bootloader with firmware upgrade functionality.


# Code example
`main.c`: include header file
```c
/* USER CODE BEGIN Includes */
#include "codeprotection.h"
/* USER CODE END Includes */
```
`main.c`: place a call to `CodeProtection_SetLevel()` in `main()` function after `HAL_Init()`.
```c
/* USER CODE BEGIN Init */
// Set code protection
#ifndef DEBUG
CodeProtection_SetLevel(1);
#endif
/* USER CODE END Init */
```
Protection is not enabled for Debug build configuration in this example.
