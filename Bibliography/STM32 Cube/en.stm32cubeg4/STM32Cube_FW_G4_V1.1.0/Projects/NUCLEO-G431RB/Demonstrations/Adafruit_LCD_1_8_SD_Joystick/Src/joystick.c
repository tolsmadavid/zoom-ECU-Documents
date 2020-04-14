/**
  ******************************************************************************
  * @file    Adafruit_LCD_1_8_SD_Joystick/Src/joystick.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the joystick feature
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32G4xx-Nucleo_Demo
  * @{
  */

/** @addtogroup Adafruit_LCD_1_8_SD_Joystick
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t x_size, y_size;
/* Private function prototypes -----------------------------------------------*/

static void Joystick_SetHint(void);
void Joystick_SetCursorPosition(void);

/* Private functions ---------------------------------------------------------*/



/**
  * @brief  Joystick Gpio demo
  * @param  None
  * @retval None
  */
void Joystick_demo (void)
{

  int32_t status = 0;
  JoyState = JOY_NONE;
  ADAFRUIT_802_LCD_GetXSize(0, &x_size);
  ADAFRUIT_802_LCD_GetXSize(0, &y_size);

  Joystick_SetHint();

  status = ADAFRUIT_802_JOY_Init(JOY1,  JOY_MODE_EXTI, JOY_ALL);

  if (status != BSP_ERROR_NONE)
  {
    GUI_SetBackColor(GUI_COLOR_WHITE);
    GUI_SetTextColor(GUI_COLOR_RED);
    GUI_DisplayStringAt(0, y_size- 70, (uint8_t *)"ERROR", CENTER_MODE);
    GUI_DisplayStringAt(0, y_size- 55, (uint8_t *)"Joystick cannot", CENTER_MODE);
    GUI_DisplayStringAt(0, y_size- 40, (uint8_t *)"be initialized", CENTER_MODE);
  }

  while (1)
  {
    if (status == BSP_ERROR_NONE)
    {
      if(JoyState == JOY_SEL)
      {
        return;
      }
      /* Get the Joystick State */
      JoyState = ADAFRUIT_802_JOY_GetState(JOY1);
      Joystick_SetCursorPosition();
    }

    HAL_Delay(6);
  }
}

/**
  * @brief  Display joystick demo hint
  * @param  None
  * @retval None
  */
static void Joystick_SetHint(void)
{
  /* Clear the LCD */
  GUI_Clear(GUI_COLOR_WHITE);

  /* Set Joystick Demo description */
  GUI_FillRect(0, 0, x_size, 40, GUI_COLOR_BLUE);
  GUI_SetTextColor(GUI_COLOR_WHITE);
  GUI_SetBackColor(GUI_COLOR_BLUE);
  GUI_SetFont(&Font24);

  GUI_SetFont(&Font12);
  GUI_DisplayStringAt(0, 10, (uint8_t *)"Joystick Demo", CENTER_MODE);
  GUI_DisplayStringAt(0, 25, (uint8_t *)"Move the pointer", CENTER_MODE);


  /* Set the LCD Text Color */
  GUI_DrawRect(10, 50, x_size - 20, y_size- 60, GUI_COLOR_BLUE);
  GUI_DrawRect(11, 51, x_size - 22, y_size- 62, GUI_COLOR_BLUE);
}

/**
  * @brief  Joystick cursor position
  * @param  None
  * @retval None
  */
void Joystick_SetCursorPosition(void)
{
  static uint16_t xPtr = 12;
  static uint16_t yPtr = 52;
  static uint16_t old_xPtr = 12;
  static uint16_t old_yPtr = 52;


      switch(JoyState)
      {
      case JOY_UP:
        if(yPtr > 52)
        {
          yPtr--;
        }
        break;
      case JOY_DOWN:
        if(yPtr < (y_size - 12 - 11))
        {
          yPtr++;
        }
        break;
      case JOY_LEFT:
        if(xPtr > 12)
        {
          xPtr--;
        }
        break;
      case JOY_RIGHT:
        if(xPtr < (x_size - 8 - 11))
        {
          xPtr++;
        }
        break;
      default:
        break;
      }

      GUI_SetBackColor(GUI_COLOR_WHITE);
      GUI_SetTextColor(GUI_COLOR_BLUE);

      if(JoyState == JOY_NONE)
      {
        GUI_SetTextColor(GUI_COLOR_BLUE);
        GUI_DisplayChar(xPtr, yPtr, 'X');
      }
      else
      {
        GUI_SetTextColor(GUI_COLOR_WHITE);
        GUI_DisplayChar(old_xPtr, old_yPtr, 'X');
        GUI_SetTextColor(GUI_COLOR_BLUE);
        GUI_DisplayChar(xPtr, yPtr, 'X');

        old_xPtr = xPtr;
        old_yPtr = yPtr;
      }
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
