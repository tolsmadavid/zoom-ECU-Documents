/**
  ******************************************************************************
  * @file    k_widgets.c
  * @author  MCD Application Team
  * @brief   This file provides the kernel widgets functions
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

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "k_widgets.h"
#include "stm32g474e_eval.h"
#include "stm32g474e_eval_lcd.h"
#include "main.h"

/* External variables --------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct {
  kWidgetsProgressBar_t progressBar;
  uint32_t             progress;
  uint32_t             maxValue;
  uint32_t             step;
}ProgressBar_t;

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*                     P R O G R E S S   B A R                                */
/******************************************************************************/
/**
  * @brief  Create a progress bar
  * @param  pProgressBar Progress Bar descriptor
  * @param  MaxValue Maximum representable value
  * @retval Progress bar handle
  */
void * kWidgets_ProgressBarCreate(kWidgetsProgressBar_t * pProgressBar, uint32_t MaxValue)
{
  ProgressBar_t * pb = (ProgressBar_t *)NULL;

  pb = (ProgressBar_t *) malloc(sizeof(ProgressBar_t));

  if (pb != NULL)
  {
    memcpy(&(pb->progressBar), pProgressBar, sizeof(kWidgetsProgressBar_t));
    pb->progress = 0;
    pb->maxValue = MaxValue;
    pb->step =  MaxValue / pb->progressBar.width;
    GUI_SetTextColor(pProgressBar->backgroungColor);
    GUI_FillRect(pProgressBar->xpos+1, pProgressBar->ypos+1, pProgressBar->width-2, pProgressBar->height-2, pProgressBar->backgroungColor);
    GUI_SetTextColor(pProgressBar->textColor);
    GUI_DrawRect(pProgressBar->xpos, pProgressBar->ypos, pProgressBar->width, pProgressBar->height, pProgressBar->textColor);
  }

  return (void *)pb;
}

/**
  * @brief  Destroy a progress bar
  * @param  hwidgetProgressBar Progress bar handle
  * @retval None
  */
void kWidgets_ProgressBarDestroy(void * hwidgetProgressBar)
{
  free(hwidgetProgressBar);
}

/**
  * @brief  Update a progress bar
  * @param  hwidgetProgressBar Progress bar handle
  * @param  Progress           progress bar update
  * @retval None
  */
void kWidgets_ProgressBarUpdate(void * hwidgetProgressBar, uint32_t Progress)
{
  ProgressBar_t * pb = (ProgressBar_t *) hwidgetProgressBar;
  uint32_t width;
  uint32_t step = pb->step;

  width = Progress - pb->progress;

  if (width >= step )
  {
    GUI_SetTextColor(pb->progressBar.textColor);
    GUI_FillRect(pb->progressBar.xpos + (uint32_t)(pb->progress/step),
                 pb->progressBar.ypos,
                 width/step,
                 pb->progressBar.height,
                 pb->progressBar.textColor);
    pb->progress += step;
  }
}

/**
  * @brief  Reset a progress bar
  * @param  hwidgetProgressBar Progress bar handle
  * @retval None
  */
void kWidgets_ProgressBarReset(void * hwidgetProgressBar)
{
  ProgressBar_t * pb = (ProgressBar_t *) hwidgetProgressBar;

  pb->progress = 0;
  GUI_SetBackColor(pb->progressBar.backgroungColor);
  GUI_SetTextColor(pb->progressBar.backgroungColor);
  GUI_FillRect(pb->progressBar.xpos + 1,
               pb->progressBar.ypos + 1,
               pb->progressBar.width - 2,
               pb->progressBar.height - 2,
               pb->progressBar.backgroungColor);
  GUI_SetTextColor(pb->progressBar.textColor);
  GUI_DrawRect(pb->progressBar.xpos,
               pb->progressBar.ypos,
               pb->progressBar.width,
               pb->progressBar.height,
               pb->progressBar.textColor);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
