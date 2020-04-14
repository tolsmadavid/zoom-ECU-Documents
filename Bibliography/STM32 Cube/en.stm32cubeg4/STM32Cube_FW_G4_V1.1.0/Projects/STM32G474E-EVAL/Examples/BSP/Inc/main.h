/**
  ******************************************************************************
  * @file    DCMI/DCMI_CaptureMode/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MAIN_H
#define MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stm32g4xx_hal.h"
#include "stm32g474e_eval_errno.h"
#include "stm32g474e_eval_conf.h"
#include "stm32g474e_eval.h"
#include "stm32g474e_eval_bus.h"
#include "stm32g474e_eval_idd.h"
#include "stm32g474e_eval_lcd.h"
#include "stm32g474e_eval_audio.h"
#include "stm32g474e_eval_sd.h"
#include "stm32g474e_eval_qspi.h"
#include "stm32g474e_eval_sram.h"
#include "stm32g474e_eval_env_sensor.h"

#include "Basic_GUI/basic_gui.h"

/* Exported variables --------------------------------------------------------*/
extern SRAM_HandleTypeDef           hSramHandle;
extern const unsigned char          stlogo[];
extern uint32_t                     SdmmcTest;
extern volatile uint8_t             mfx_exti_received;
extern uint32_t                     ButtonState;
extern __IO uint32_t UserButtonPressed;

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  int32_t  (*DemoFunc)(void);
  uint8_t  DemoName[50];
} BSP_DemoTypedef;

typedef enum {
  AUDIO_ERROR_NONE = 0,
  AUDIO_ERROR_NOTREADY,
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
}AUDIO_ErrorTypeDef;

/* Exported constants --------------------------------------------------------*/
/* The Audio file is flashed with ST-Link Utility @ flash address =  AUDIO_SRC_FILE_ADDRESS */
#define AUDIO_SRC_FILE_ADDRESS            0x08080000   /* Audio file address in flash */

/* LCD Frame Buffer address */
#define LCD_FRAME_BUFFER                  0xC0000000 /* LCD Frame buffer of size 800x480 in ARGB8888 */
#define AUDIO_REC_START_ADDR              0x08081000

#define SD_DMA_MODE                       0U
#define SD_IT_MODE                        1U
#define SD_POLLING_MODE                   2U
#define SD_BLOCK_LEN                      512U

/* Exported macro ------------------------------------------------------------*/
#define COUNT_OF_EXAMPLE(x)               (sizeof(x)/sizeof(BSP_DemoTypedef))

/* Exported functions ------------------------------------------------------- */
void LCD_demo (void);
void Joystick_demo(void);
int32_t AudioPlay_demo (void);
int32_t AudioPlay_demo2 (void);
void REC_INSTANCE1_HDMI_demo(void);
void REC_INSTANCE1_SingleBuff_demo(void);
void REC_INSTANCE1_MultiBuff_demo(void);
void REC_INSTANCE1_Mute_demo(void);
void REC_INSTANCE1_SetDevice_demo(void);

//void AudioChangeDevice_demo (void);
int32_t AudioRec_demo (void);
int32_t AudioRecAnalog_demo (void);

int32_t  Led_demo(void);
int32_t  Button_demo(void);
int32_t  Pot_demo(void);
int32_t  Bus_demo(void);
#if (USE_BSP_IO_CLASS == 1)
int32_t  Joy_demo(void);
int32_t  Io_demo(void);
int32_t  Idd_demo(void);
int32_t  Lcd_demo(void);
#endif
int32_t  Com_demo(void);
int32_t  SRAM_demo(void);
int32_t  QSPI_demo(void);
int32_t  SD_demo(void);

void     Error_Handler(void);
uint32_t CheckResult(void);
void     StartTest(void);
uint8_t  CheckForUserInput(void);
uint8_t  AUDIO_Process(void);

void ButtonPendingCallback(void);

void Error_Handler(void);

#endif /* MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
