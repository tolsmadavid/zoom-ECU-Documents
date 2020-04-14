/**
  ******************************************************************************
  * @file    app_thermometer.c
  * @author  MCD Application Team
  * @brief   Thermometer application implementation.
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
#define __APP_THERMOMETER_C

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32g474e_eval.h"
#include "stm32g474e_eval_lcd.h"
#include "stm32g474e_eval_env_sensor.h"
#include "utils.h"
#include "k_config.h"
#include "k_module.h"
#include "k_menu.h"
#include "k_storage.h"

/* Private typedef ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
KMODULE_RETURN _ThermometerDemoExec(void);
KMODULE_RETURN _ThermometerConfig(void);

void ThermometerDemo(void);
void ThermometerMenuUserAction(uint8_t sel);
void ThermometerUserHeader(void);
void ThermometerUserInformation(float tempvalue);

/* Private Variable ----------------------------------------------------------*/
const tMenuItem ThermometerMenuMenuItems[] =
{
    {"Press down to exit", 14, 30, TYPE_EXEC, MODULE_NONE, ThermometerDemo, ThermometerMenuUserAction, NULL, NULL, NULL  },
};

const tMenu ThermometerMenu = {
  "Temperature", ThermometerMenuMenuItems, countof(ThermometerMenuMenuItems), TYPE_EXEC, 1, 1 };

/* used to exit application */
static __IO uint8_t user_stop=0;

/* Private typedef -----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
const K_ModuleItem_Typedef ModuleTsensor =
{
  MODULE_TSENSOR,
  _ThermometerConfig,
  _ThermometerDemoExec,
  NULL
};

/**
  * @brief  setup the HW for the thermometer application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _ThermometerConfig(void)
{
  if (BSP_ENV_SENSOR_Init(0, ENV_TEMPERATURE) != BSP_ERROR_NONE)
    return KMODULE_ERROR_EXEC;

  if (BSP_ENV_SENSOR_SetOutputDataRate(0, ENV_TEMPERATURE, 0.25) != BSP_ERROR_NONE)
    return KMODULE_ERROR_EXEC;

  if (BSP_ENV_SENSOR_Enable(0, ENV_TEMPERATURE) != BSP_ERROR_NONE)
    return KMODULE_ERROR_EXEC;

  return KMODULE_OK;
}

/**
  * @brief  Run the thermometer application
  * @param  None.
  * @retval KMODULE_RETURN status.
  */
KMODULE_RETURN _ThermometerDemoExec(void)
{
  /* Prepare the main MMI */
  GUI_Clear(GUI_COLOR_WHITE);
  kMenu_Execute(ThermometerMenu);

  /* Execute the app */
  /* App initialization    */
  return KMODULE_OK;
}

/**
  * @brief  thermometer application
  * @param  None.
  * @retval None.
  */
void ThermometerDemo(void)
{
  float    TempValueNew = 0;
  float    TempValueOld = 0;

    /* Display user information */
    ThermometerUserHeader();

    /* Get first temperature value */
    if ( BSP_ENV_SENSOR_GetValue(0, ENV_TEMPERATURE, &TempValueNew) != BSP_ERROR_NONE)
          return;

    /* Display first Temperature Informations */
    ThermometerUserInformation(TempValueNew);

    /* Init Old Temp value at first start */
    TempValueOld = TempValueNew;

    /* Display temperature until user event */
    user_stop = 0;
    while(user_stop == 0)
    {
      /* Get temperature value */
    if ( BSP_ENV_SENSOR_GetValue(0, ENV_TEMPERATURE, &TempValueNew) != BSP_ERROR_NONE)
          return;
    HAL_Delay(1000);

      if(TempValueNew != TempValueOld)
      {
        /* ReInit Old Temp value */
        TempValueOld = TempValueNew;

        /* Display Temperature Informations */
        ThermometerUserInformation(TempValueNew);
      }
    }
}

/**
  * @brief  Display thermometer header screen
  * @param  None.
  * @retval None.
  */
void ThermometerUserHeader(void)
{
  /* Display the Thermometer icon */
  kStorage_OpenFileDrawPixel(28, 6, (uint8_t *)"STFILES/ICON15.bmp");

  /* Set default font */
  GUI_SetFont(&Font20);

  /* Set the Back Color */
  GUI_SetBackColor(GUI_COLOR_WHITE);

  /* Set the Text Color */
  GUI_SetTextColor(GUI_COLOR_ST_PINK);
}


/**
  * @brief  Display thermometer temperature
  * @param  temperature  to display.
  * @retval None.
  */
void ThermometerUserInformation(float temperature)
{
  float    TempCelsiusDisplay = temperature;
  float    TempFahrenheitDisplay = 0;
  uint8_t  LCDStrCelsius[8];
  uint8_t  LCDStrFahrenheit[8];
  uint16_t ThermometerDisplay = 0;

  /* Thermometer update information *******************************************/
  /* Convert Temperature in Celsius to temperature in Fahrenheit */
  TempFahrenheitDisplay = ((float)1.8 * TempCelsiusDisplay) + (float)32;

  sprintf((char*)LCDStrCelsius,    "%5.1f C", TempCelsiusDisplay);
  sprintf((char*)LCDStrFahrenheit, "%5.1f F", TempFahrenheitDisplay);
  GUI_DisplayStringAt(72,LINE(4), (uint8_t*)LCDStrCelsius, LEFT_MODE);
  GUI_DisplayStringAt(72,LINE(5), (uint8_t*)LCDStrFahrenheit, LEFT_MODE);

  ThermometerDisplay = (uint16_t)TempFahrenheitDisplay;

  /* Dynamical thermometer is available only in range 57 to 86 Fahrenheit Degres*/
  if((ThermometerDisplay> 57)&&(ThermometerDisplay < 86))
  {
    /* Set the LCD White Color */
    GUI_SetTextColor(GUI_COLOR_WHITE);
    GUI_FillRect(26, 40,  9, 141-((ThermometerDisplay-57)*5), GUI_COLOR_WHITE);

    GUI_SetTextColor(GUI_COLOR_ST_PINK);
    GUI_FillRect(26, 181-((ThermometerDisplay-57)*5), 9 ,((ThermometerDisplay-57)*5),GUI_COLOR_ST_PINK );
  }
}


/**
  * @brief  Get User action
  * @param  sel   User selection (JOY_SEL,...)
  * @note   This example is the only way to get user information.
  * @retval None
  */
void ThermometerMenuUserAction(uint8_t sel)
{
  switch(sel)
  {
  case JOY_DOWN :
       user_stop = 1;
    break;
  default :
    break;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
